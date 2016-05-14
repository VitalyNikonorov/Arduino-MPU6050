#include <SoftwareSerial.h>
int ledpin = 13; // LED connected to pin 48 (on-board LED)
#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

SoftwareSerial mySerial(0, 1); // RX, TX

char myChar;

MPU6050 accelgyro;
int incomingByte = 0;

int16_t ax, ay, az;
int16_t gx, gy, gz;

#define OUTPUT_READABLE_ACCELGYRO

#define LED_PIN 13
bool blinkState = false;
bool flag = false;

void setup()
{ 
    pinMode(ledpin, OUTPUT);  // pin 48 (on-board LED) as OUTPUT
    Serial.begin(9600);

    //mySerial.begin(38400);
    mySerial.begin(9600);

    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
    
    accelgyro.initialize();accelgyro.initialize();
    pinMode(LED_PIN, OUTPUT);pinMode(LED_PIN, OUTPUT);
    mySerial.print("AT");
    delay(1000);
}

void loop() // run over and over
{
    if ( mySerial.available() ){ 
        myChar = Serial.read();
        if( myChar == 'b' ){
          digitalWrite(ledpin, HIGH);  // turn ON the LED
          flag = true;
        } 
      
      if (myChar == 'e') { 
        digitalWrite(ledpin, LOW);   // otherwise turn it OFF
        flag = false;
      }
      myChar = 0;
    }

      if (flag){
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    #ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
        Serial.print("a/g:\t");
        Serial.print(ax); Serial.print("\t");
        Serial.print(ay); Serial.print("\t");
        Serial.print(az); Serial.print("\t");
        Serial.print(gx); Serial.print("\t");
        Serial.print(gy); Serial.print("\t");
        Serial.println(gz);
    #endif
  }
}

