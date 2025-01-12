#include <Arduino.h>
#include <WiFi.h>
#include "time.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include "displayWrapper.hpp"
#include "credentials.h"

const char* ntpServer = "pool.ntp.org";
const int gmtOffset = -10800;
const int daylightOffset = 3600;

struct tm timeinfo;
char curTime[9]; 

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void updateTime();
void startWifi();

void setup() {
	Serial.begin(115200);
	beginDisplay(&display);
	startWifi();
	delay(1000);
	configTime(gmtOffset, daylightOffset, ntpServer);
	delay(2000);
	updateTime();
	WiFi.disconnect(true);
  	WiFi.mode(WIFI_OFF);
}

void loop() {
	updateTime();
	Serial.println(&timeinfo, "%H:%M:%S");
	strftime(curTime, sizeof(curTime), "%H:%M:%S", &timeinfo);
	updateDisplay(&display, curTime);
	delay(1000); 
}

void startWifi(){
	WiFi.begin(SECRET_SSID, SECRET_PASSWORD);
	Serial.print("Conectando.");

	while(WiFi.status() != WL_CONNECTED){
		Serial.print(".");
        delay(100);
    }
	Serial.println("\nConectado!");
	Serial.print("IP Local: ");
    Serial.println(WiFi.localIP());
}

void updateTime(){
	if(!getLocalTime(&timeinfo)){
    	Serial.println("No se puede obtener el tiempo.");
    	return;
 	}
}