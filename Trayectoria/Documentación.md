# 📜 Bitácora de Desarrollo: BIT-KILLER
Autor Principal: Luisferpc13 (STARLUX)

Hardware: Montaje original en PCB | Software: Desarrollo Propio (2026)

## 🏗️ 1. Ingeniería de Hardware y Conexión
El diseño físico del BIT-KILLER es un híbrido de precisión:

Montaje en PCB: El diseño, la disposición de los componentes y la solución de triple antena en la placa son 100% autoría de Luisferpc13.

Esquema de Conexión: Para garantizar la compatibilidad con los estándares de auditoría, se adoptaron los puntos de conexión base del repositorio ESP32-BlueJammer (EmenstaNougat), asegurando un mapeo de pines optimizado para el NodeMCU-32S.

## 💻 2. Desarrollo de Software (Código Original)
A diferencia de otras versiones que son cajas cerradas (binarios web), el firmware del BIT-KILLER fue escrito desde cero en Arduino IDE:

Ingeniería Inversa de Funciones: Se tomó la idea conceptual del uso del botón  (GPIO 0) para el cambio de modos, pero la lógica interna, los tiempos de salto de frecuencia y la gestión de paquetes fueron desarrollados de forma independiente.BOOT

Algoritmos Exclusivos: Se integró el sistema Power Sentinel, una capa de software propia que monitorea el consumo de los nRF24L01 para prevenir daños por sobrecarga en la PCB.

## 🧪 3. El Proceso de Creación
Deducción Técnica: Al no tener acceso al código fuente original (solo disponible como flasheador web), se procedió a programar cada función de interferencia y escaneo desde una hoja en blanco.

Optimización de Bus: Se implementó una gestión manual de los buses SPI para permitir que el NodeMCU-32S controle ambos módulos de radio sin pérdida de paquetes.

Formalización: El proyecto evolucionó de un script de prueba a un repositorio profesional con licencias MIT (para el software de Luisferpc13) y Apache 2.0 (respetando la base conceptual).

## 🕒 Resumen de Autoría
Concepto de Interfaz (Botón): Inspirado en EmenstaNougat.

Puntos de Conexión: Referenciados de EmenstaNougat.

Diseño de PCB y Montaje: 100% Luisferpc13.

Código Fuente y Lógica: 100% Luisferpc13.
