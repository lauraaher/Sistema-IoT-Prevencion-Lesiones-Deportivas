/*******************************************************
 * Proyecto: Sistema IoT para Prevención de Lesiones
 * Autor: Laura Hernandez
 * Dispositivo: ESP32-S3
 *
 * Sensores:
 * - BME280
 * - MPU6050
 *
 * Comunicación futura:
 * - ESP-NOW (ESP32 Mini -> ESP32-S3)
 * - MQTT
 *******************************************************/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>

#include "estructuras.h"

/*******************************************************
                CONFIGURACIÓN I2C
********************************************************/

#define SDA_PIN 8
#define SCL_PIN 9

#define BME280_ADDRESS 0x76

/*******************************************************
                  OBJETOS
********************************************************/

Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;

DatosAtleta atleta;

/*******************************************************
              PROTOTIPOS DE FUNCIONES
********************************************************/

void inicializarEstructuras();

bool iniciarBME280();

bool iniciarMPU6050();

void leerBME280();

void leerMPU6050();

void mostrarDatos();

/*******************************************************
                      SETUP
********************************************************/

void setup()
{

    Serial.begin(115200);

    delay(1500);

    Serial.println();
    Serial.println("==========================================");
    Serial.println(" Sistema IoT Prevencion de Lesiones");
    Serial.println(" ESP32-S3");
    Serial.println("==========================================");

    Wire.begin(SDA_PIN, SCL_PIN);

    inicializarEstructuras();

    if(iniciarBME280())
    {
        Serial.println("BME280 inicializado correctamente.");
    }
    else
    {
        Serial.println("ERROR inicializando BME280");
        while(true);
    }

    if(iniciarMPU6050())
    {
        Serial.println("MPU6050 inicializado correctamente.");
    }
    else
    {
        Serial.println("ERROR inicializando MPU6050");
        while(true);
    }

    Serial.println();
    Serial.println("Sistema listo.");
    Serial.println();

}

/*******************************************************
                       LOOP
********************************************************/

void loop()
{

    leerBME280();

    leerMPU6050();

    mostrarDatos();

    delay(1000);

}

/*******************************************************
        INICIALIZAR ESTRUCTURA DE DATOS
********************************************************/

void inicializarEstructuras()
{

    //=====================
    // BME280
    //=====================

    atleta.ambiente.temperatura.nombre = "Temperatura";
    atleta.ambiente.temperatura.unidad = "°C";

    atleta.ambiente.humedad.nombre = "Humedad";
    atleta.ambiente.humedad.unidad = "%";

    atleta.ambiente.presion.nombre = "Presion";
    atleta.ambiente.presion.unidad = "hPa";

    //=====================
    // MPU6050
    //=====================

    atleta.movimiento.accelX.nombre="Accel X";
    atleta.movimiento.accelY.nombre="Accel Y";
    atleta.movimiento.accelZ.nombre="Accel Z";

    atleta.movimiento.accelX.unidad="m/s²";
    atleta.movimiento.accelY.unidad="m/s²";
    atleta.movimiento.accelZ.unidad="m/s²";

    atleta.movimiento.gyroX.nombre="Gyro X";
    atleta.movimiento.gyroY.nombre="Gyro Y";
    atleta.movimiento.gyroZ.nombre="Gyro Z";

    atleta.movimiento.gyroX.unidad="rad/s";
    atleta.movimiento.gyroY.unidad="rad/s";
    atleta.movimiento.gyroZ.unidad="rad/s";

    //=====================
    // MAX30102
    // (ESP32 Mini)
    //=====================

    atleta.biometria.frecuenciaCardiaca.nombre="Frecuencia Cardiaca";
    atleta.biometria.frecuenciaCardiaca.unidad="BPM";

    atleta.biometria.spo2.nombre="SpO2";
    atleta.biometria.spo2.unidad="%";

}

/*******************************************************
            INICIALIZAR BME280
********************************************************/

bool iniciarBME280()
{

    if(!bme.begin(BME280_ADDRESS))
    {
        return false;
    }

    return true;

}

/*******************************************************
            INICIALIZAR MPU6050
********************************************************/

bool iniciarMPU6050()
{

    if(!mpu.begin())
    {
        return false;
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

    mpu.setGyroRange(MPU6050_RANGE_500_DEG);

    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    return true;

}
/*******************************************************
                LEER BME280
********************************************************/
void leerBME280()
{
    atleta.ambiente.temperatura.valor = bme.readTemperature();

    atleta.ambiente.humedad.valor = bme.readHumidity();

    atleta.ambiente.presion.valor = bme.readPressure() / 100.0F;
}

/*******************************************************
                LEER MPU6050
********************************************************/
void leerMPU6050()
{
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;

    mpu.getEvent(&accel, &gyro, &temp);

    atleta.movimiento.accelX.valor = accel.acceleration.x;
    atleta.movimiento.accelY.valor = accel.acceleration.y;
    atleta.movimiento.accelZ.valor = accel.acceleration.z;

    atleta.movimiento.gyroX.valor = gyro.gyro.x;
    atleta.movimiento.gyroY.valor = gyro.gyro.y;
    atleta.movimiento.gyroZ.valor = gyro.gyro.z;
}

/*******************************************************
            MOSTRAR DATOS POR SERIAL
********************************************************/
void mostrarDatos()
{
    Serial.println();
    Serial.println("==============================================");
    Serial.println("          DATOS DEL ATLETA");
    Serial.println("==============================================");

    //==================================================
    // BME280
    //==================================================

    Serial.println();
    Serial.println("------ AMBIENTE ------");

    Serial.print(atleta.ambiente.temperatura.nombre);
    Serial.print(": ");
    Serial.print(atleta.ambiente.temperatura.valor, 2);
    Serial.print(" ");
    Serial.println(atleta.ambiente.temperatura.unidad);

    Serial.print(atleta.ambiente.humedad.nombre);
    Serial.print(": ");
    Serial.print(atleta.ambiente.humedad.valor, 2);
    Serial.print(" ");
    Serial.println(atleta.ambiente.humedad.unidad);

    Serial.print(atleta.ambiente.presion.nombre);
    Serial.print(": ");
    Serial.print(atleta.ambiente.presion.valor, 2);
    Serial.print(" ");
    Serial.println(atleta.ambiente.presion.unidad);

    //==================================================
    // MPU6050
    //==================================================

    Serial.println();
    Serial.println("------ ACELERÓMETRO ------");

    Serial.print(atleta.movimiento.accelX.nombre);
    Serial.print(": ");
    Serial.print(atleta.movimiento.accelX.valor, 3);
    Serial.print(" ");
    Serial.println(atleta.movimiento.accelX.unidad);

    Serial.print(atleta.movimiento.accelY.nombre);
    Serial.print(": ");
    Serial.print(atleta.movimiento.accelY.valor, 3);
    Serial.print(" ");
    Serial.println(atleta.movimiento.accelY.unidad);

    Serial.print(atleta.movimiento.accelZ.nombre);
    Serial.print(": ");
    Serial.print(atleta.movimiento.accelZ.valor, 3);
    Serial.print(" ");
    Serial.println(atleta.movimiento.accelZ.unidad);

    Serial.println();
    Serial.println("------ GIROSCOPIO ------");

    Serial.print(atleta.movimiento.gyroX.nombre);
    Serial.print(": ");
    Serial.print(atleta.movimiento.gyroX.valor, 3);
    Serial.print(" ");
    Serial.println(atleta.movimiento.gyroX.unidad);

    Serial.print(atleta.movimiento.gyroY.nombre);
    Serial.print(": ");
    Serial.print(atleta.movimiento.gyroY.valor, 3);
    Serial.print(" ");
    Serial.println(atleta.movimiento.gyroY.unidad);

    Serial.print(atleta.movimiento.gyroZ.nombre);
    Serial.print(": ");
    Serial.print(atleta.movimiento.gyroZ.valor, 3);
    Serial.print(" ");
    Serial.println(atleta.movimiento.gyroZ.unidad);

    //==================================================
    // MAX30102 (ESP32 MINI)
    //==================================================

    Serial.println();
    Serial.println("------ BIOMETRÍA ------");

    Serial.print(atleta.biometria.frecuenciaCardiaca.nombre);
    Serial.print(": ");
    Serial.print(atleta.biometria.frecuenciaCardiaca.valor, 1);
    Serial.print(" ");
    Serial.println(atleta.biometria.frecuenciaCardiaca.unidad);

    Serial.print(atleta.biometria.spo2.nombre);
    Serial.print(": ");
    Serial.print(atleta.biometria.spo2.valor, 1);
    Serial.print(" ");
    Serial.println(atleta.biometria.spo2.unidad);

    Serial.println();
    Serial.println("==============================================");
}