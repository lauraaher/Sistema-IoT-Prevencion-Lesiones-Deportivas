#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <Arduino.h>

/*
==========================================
TIPO DE DATO GENÉRICO
Representa una medición de cualquier sensor
==========================================
*/

struct SensorData
{
    String nombre;
    float valor;
    String unidad;
};

/*
==========================================
SENSOR BME280
==========================================
*/

struct BME280Data
{
    SensorData temperatura;
    SensorData humedad;
    SensorData presion;
};

/*
==========================================
SENSOR MPU6050
==========================================
*/

struct MPU6050Data
{
    SensorData accelX;
    SensorData accelY;
    SensorData accelZ;

    SensorData gyroX;
    SensorData gyroY;
    SensorData gyroZ;
};

/*
==========================================
SENSOR MAX30102
==========================================
*/

struct MAX30102Data
{
    SensorData frecuenciaCardiaca;
    SensorData spo2;
};

/*
==========================================
ESTRUCTURA GENERAL DEL ATLETA
==========================================
*/

struct DatosAtleta
{
    BME280Data ambiente;

    MPU6050Data movimiento;

    MAX30102Data biometria;
};

#endif