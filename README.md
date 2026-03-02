# ⚡ BIT-KILLER : SYSTEM OVERRIDE
> **Developed by STARLUX**

```text
 +-------------------------------------------------------+
 |  ____  ___ _____   _  _____ _     _     _____ ____    |
 | | __ )|_ _|_   _| | |/ /_ _| |   | |   | ____|  _ \   |
 | |  _ \ | |  | |   | ' / | || |   | |   |  _| | |_) |  |
 | | |_) || |  | |   | . \ | || |___| |___| |___|  _ <   |
 | |____/|___| |_|   |_|\_\___|_____|_____|_____|_| \_\\ |
 |                                                       |
 |            S Y S T E M    B Y    S T A R L U X        |
 +-------------------------------------------------------+

📟 Descripción
BIT-KILLER es un sistema de auditoría de radiofrecuencia para el espectro de 2.4GHz. Utiliza un ESP32 (NodeMCU-32S)
con doble bus SPI para controlar dos módulos nRF24L01+PA+LNA de forma independiente.


🛡️ Power Sentinel (Prevención de Energía)
El sistema incluye un algoritmo de monitoreo de hardware. Si detecta una caída de tensión por debajo de los niveles críticos
en los módulos de radio, la interfaz mostrará una alerta dinámica:

ADVERTENCIA: Tensión insuficiente detectada.

ACCIÓN: Desconectar un módulo físicamente para operar a máxima potencia con el restante.


🚀 Modos de Ataque:

MODO BLE: Interferencia dirigida a protocolos Bluetooth (Bafles/Auriculares).

MODO WIFI: Saturación de canales de red inalámbrica.

PANICO: Ejecución simultánea en ambos módulos para saturación total del espectro.


⚠️ Disclaimer: Este software es estrictamente para fines educativos y pruebas de penetración autorizadas.

-----------------------------------------------------------------------------------------------------------------------------------
