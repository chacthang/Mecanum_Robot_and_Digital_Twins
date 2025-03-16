/**
 * 
 * @todo
 *  - move strings to flash (less RAM consumption)
 *  - fix deprecated convertation form string to char* startAsTag
 *  - give example description
 */
#include <SPI.h>
#include "DW1000Ranging.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SimpleKalmanFilter.h>
SimpleKalmanFilter kf1(0.0614, 0.1, 0.8); // 0.0614
SimpleKalmanFilter kf2(0.024, 0.1, 0.8); //  0.024
float d1_kf,d2_kf;
int f1 = 0, f2 = 0;
float d1=0,d2=0;
char d1str[4];
char d2str[4];
char d1f4[10];
char d2f4[10];
char d_f4[50];
int name = 0;

// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

void setup() {
  Serial.begin(115200);
  delay(1000);
  //init the configuration
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  //define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  //Enable the filter to smooth the distance
  //DW1000Ranging.useRangeFilter(true);
  
  //we start the module as a tag
  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);
  
}

void loop() {
 DW1000Ranging.loop();

}

void newRange() {
  //Serial.print("from: "); Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  //  Serial.print("\t Range: ");
  name = DW1000Ranging.getDistantDevice()->getShortAddress();
  if (name == 6019 )
  {

    d1 = DW1000Ranging.getDistantDevice()->getRange();
    d1_kf = kf1.updateEstimate(d1);
    dtostrf(d1_kf, 4, 2, d1str);
    sprintf(d1f4,"A%s",d1str);
    Serial.println(d1f4);

  }
  if (name == 6018 )
  {

    d2 = DW1000Ranging.getDistantDevice()->getRange();
    d2_kf = kf2.updateEstimate(d2);
    dtostrf(d2_kf, 4, 2, d2str);
    sprintf(d2f4,"B%s",d2str);
    Serial.println(d2f4);
  
  }

// Serial.print(" m");
//  Serial.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");

}

void newDevice(DW1000Device* device) {
  //Serial.print("ranging init; 1 device added ! -> ");
 // Serial.print(" short:");
 // Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device* device) {
 // Serial.print("delete inactive device: ");
 // Serial.println(device->getShortAddress(), HEX);
}

