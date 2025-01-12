#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

//Adafruit_SSD1306 display(128, 64, &Wire, -1);
const int CURSORX = 10;
const int CURSORY = 32;
const int TEXTSIZE = 2;

bool beginDisplay(Adafruit_SSD1306 *display){
    if(!display->begin(SSD1306_SWITCHCAPVCC, 0x3C)){
        return false;
    }
    display->clearDisplay();
    return true;
}

void updateDisplay(Adafruit_SSD1306 *display, String text){
    display->clearDisplay();  
    display->setCursor(CURSORX, CURSORY);
    display->setTextSize(TEXTSIZE);
    display->setTextColor(WHITE);
    display->print(text);
    display->display();
}
