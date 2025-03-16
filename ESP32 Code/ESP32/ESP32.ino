#include <WiFi.h>
#include <WiFiClient.h>

const char *ssid = "ESP32D";
const char *password = "123456789";
WiFiServer server(10020);
WiFiClient client;

void setup() 
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  //Serial.print("IP: ");
  //Serial.println(WiFi.softAPIP());

  server.begin();
  //Serial.println("Server started");
}

void loop() 
{
  if (!client || !client.connected()) 
  {
    client = server.available();
  }

  if (client.connected() && client.available()) 
  {
    String command = client.readStringUntil('\n');
    //command.trim();
    if (command.indexOf("E=") == -1)
    {
      Serial.println(command);
      //delay(50);
    }
    //client.print(command);
  }

  while (Serial.available()) 
  {
    String dataFromSTM32 = Serial.readStringUntil('\n');
    if (dataFromSTM32.length() > 0) 
    {
      if (client.connected()) 
      { 
        if (dataFromSTM32.startsWith("E="))
        {
          client.print(dataFromSTM32);
          //Serial.println("Sent: " + dataFromSTM32);
          //delay(50);
        }
      } 
    }
  }
}