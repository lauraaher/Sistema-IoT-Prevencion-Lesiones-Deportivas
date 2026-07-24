Sistema IoT para la Prevención de Lesiones Deportivas
Descripción

Este proyecto desarrolla un sistema IoT orientado a la prevención de lesiones en deportistas mediante la adquisición de datos fisiológicos, biomecánicos y ambientales en tiempo real.

El sistema emplea dos microcontroladores ESP32 que se comunican mediante ESP-NOW. Un ESP32-S3 actúa como nodo principal encargado de integrar la información proveniente de los sensores ambientales y de movimiento, mientras que un ESP32 Mini ubicado en la muñeca del deportista obtiene la frecuencia cardíaca y el nivel de saturación de oxígeno.

Posteriormente toda la información es enviada mediante MQTT hacia un servidor para su almacenamiento, procesamiento y análisis utilizando técnicas de Inteligencia Artificial.

Objetivo General

Diseñar e implementar un sistema IoT capaz de adquirir información biométrica, ambiental y de movimiento para apoyar la prevención de lesiones deportivas mediante modelos de Inteligencia Artificial.

Sensores
ESP32 Principal
BME280
Temperatura
Humedad
Presión
MPU6050
Acelerómetro
Giroscopio
ESP32 Mini
MAX30102
Frecuencia cardíaca
Saturación de oxígeno
Comunicación

ESP32 Mini

↓

ESP-NOW

↓

ESP32 Principal

↓

MQTT

↓

HiveMQ

↓

Base de Datos

↓

Inteligencia Artificial

Arquitectura de datos
DatosAtleta

│

├── Ambiente

│ ├── Temperatura

│ ├── Humedad

│ └── Presión

│

├── Movimiento

│ ├── Accel X

│ ├── Accel Y

│ ├── Accel Z

│ ├── Gyro X

│ ├── Gyro Y

│ └── Gyro Z

│

└── Biometría

├── Frecuencia Cardíaca

└── SpO₂
