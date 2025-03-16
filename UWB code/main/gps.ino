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
static float offset1=  0., offset2 = 0.15;
char gps[20];
char xstr[10];
char ystr[10];
int cnt1 = 0;
int cnt2 = 0;
float pos1 = 0;
float pos2 = 0;
float pos1_pre = 0;
float pos2_pre = 0;
float x=0.00,y=0.00;
float a=0.00,b=0.00,cos_a=0.00;
static float c = 1.2;
static float h1 = 0.1,h2 = 0.1;
int name;

// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

void setup() {
  Serial.begin(9600);
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
//pos_xy();
}

void newRange() {
//  Serial.print("from: "); Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
//  Serial.print("\t Range: "); Serial.print(DW1000Ranging.getDistantDevice()->getRange() ); Serial.print(" m");
//  Serial.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
pos_xy();
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
void pos_xy()
{
    
  name = DW1000Ranging.getDistantDevice()->getShortAddress();
 
  if (name == 6018 && cnt1 == 0)
    {
      name =0;
      cnt1 = 1;
      pos1_pre = DW1000Ranging.getDistantDevice()->getRange();
      pos1 = pos1_pre-offset1;
      //if (cnt1 == 5)
     // {
      //  pos1 = pos1/5;
        a = pos1*pos1 - h1*h1;
        a = abs(sqrt(a));
      //  pos1 = 0;
      //  cnt1 = 0;
      //}
    }
  if (name == 6019 && cnt2 == 0)
    {
      name = 0;
      cnt2 = 1;
      pos2_pre = DW1000Ranging.getDistantDevice()->getRange();
      pos2 = pos2_pre-offset2;
      // if (cnt2 == 5)
      //{
       // pos2 = pos2/5;
        b = pos2*pos2 - h2*h2;
        b = abs(sqrt(b));
      //  pos2 = 0;
      //  cnt2 = 0;
     // }

    }

  if (a!= 0 && b != 0 && cnt1 == 1 && cnt2 == 1)
  {
    cos_a = (b * b + c*c - a * a) / (2 * b * c);
    x = b * cos_a;
    if((1 - cos_a*cos_a) >= 0)
    {
      y = b * sqrt(1 - cos_a * cos_a);
      
      dtostrf(x, 4, 2, xstr);
      dtostrf(y, 4, 2, ystr);
      sprintf(gps,"P%s;%s",xstr,ystr);
      //Serial.print("P:");Serial.print(x);Serial.print(";");Serial.println(y);
      Serial.println(gps);
      // Serial.println(strlen(gps));
    }
    a = 0;
    b= 0;
    cnt1 = 0;
    cnt2 = 0;
  }
}
