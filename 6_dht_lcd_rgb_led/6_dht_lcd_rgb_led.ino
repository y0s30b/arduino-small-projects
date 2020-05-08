// 2015312229 Yoseob Kim
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2 // DHT11 data pin
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // (address, column, row)

const int red = 5; 
// green = 6, blue = 7 (using for loop)
// pin number 2~13 is used for PWM.
const byte color_info[][3] = {  {0xff, 0x00, 0x00}, // red
                                {0xff, 0x40, 0x00}, // orange
                                {0xff, 0xff, 0x00}, // yellow
                                {0x00, 0xff, 0x00}, // green
                                {0x80, 0x00, 0xff}  // purple
                             }; // 5 colors used in homework 5.
const char* color_name[] = {"Red", "Orange", "Yellow", "Green", "Purple"};
int current_color;

void setup() {
    Serial.begin(9600);
    Serial.println("Code written by Yoseob Kim (SKKU)");

    lcd.init();
    lcd.backlight();

    current_color = 4; // initial setting to below-zero-temperature
}

void loop() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // 1: Serial monitor output
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" C\t");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");

    // 2: Change color depending on temperature
    if(temperature < 15){
        // purple
        current_color = 4;
    }
    else if(temperature >= 15 && temperature < 20){
        // green
        current_color = 3;
    }
    else if(temperature >= 20 && temperature < 25){
        // yellow
        current_color = 2;
    }
    else if(temperature >= 25 && temperature < 30){
        // orange
        current_color = 1;
    }
    else { // temperature >= 30: red
        current_color = 0;
    }
    Serial.print("LED: ");
    Serial.println(color_name[current_color]);
    for(int i=0;i<3;++i){
        analogWrite(red+i, color_info[current_color][i]);
    }

    // 3: Display temperature in the first row
    lcd.clear(); // lcd clear
    lcd.setCursor(0, 0); // set cursor to first row
    lcd.print("Temp = ");
    lcd.print(temperature);

    // 4: Display RGB LED Color in the second row
    lcd.setCursor(0, 1); // set cursor  to second row
    lcd.print("Colr = ");
    lcd.print(color_name[current_color]);

    delay(1000);
}
