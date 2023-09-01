#include "arduino_secrets.h" 
#include <WiFiNINA.h>
int intense;

char ssid[] = SECRET_SSID;

char pass[] = SECRET_PASSWORD;


WiFiClient client;
char   HOST_NAME[] = "maker.ifttt.com";

String PATH_NAME   = "/trigger/Sunlight_capture/with/key/dnaRDV8XvdbVFbudVUbFOXFl8Tbywg12Q8Ya38uOMng"; 

String queryString = "?value1=57&value2=25";


void setup() {
  WiFi.begin(ssid, pass);


  Serial.begin(9600);

  while (!Serial);

  if (client.connect(HOST_NAME, 80)) {

    Serial.println("Connected to server");

  }

  else {
    Serial.println("connection failed");
  }

}


void loop() {

  intense = analogRead(A5);
  Serial.println(intense);
  if (intense > 620) {

    client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");

    client.println("Host: " + String(HOST_NAME));

    client.println("Connection: close");

    client.println(); 
    while (client.connected()) {

      if (client.available()) {
        char c = client.read();
        Serial.print(c);
      }

    }
    client.stop();
    Serial.println();
    Serial.println("disconnected");

}

}
