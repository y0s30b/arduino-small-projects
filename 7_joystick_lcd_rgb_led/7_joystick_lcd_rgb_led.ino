// 2015312229 Yoseob Kim
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // (address, column, row)

// 1-1: setting for joystick, rgb-led (variable declaration)
const int joy_sw = 4;
const int red = 5; 
// green = 6, blue = 7 (using for loop)
// pin number 2~13 is used for PWM.
const byte color_info[][3] = {  // default
                                {0xff, 0xff, 0xff}, // white
                                // east, north, west, south
                                {0xff, 0x00, 0x00}, // red
                                {0xff, 0x40, 0x00}, // orange
                                {0x00, 0xff, 0x00}, // green
                                {0x00, 0x00, 0xff}, // blue
                                // ne, nw, sw, se
                                {0x80, 0x00, 0x80}, // purple
                                {0x00, 0x80, 0x80}, // teal
                                {0xff, 0xff, 0x00}, // Yellow
                                {0x55, 0x6b, 0x2f} // dark olive
                             };
const char* color_name[] = {"White", "Red", "Orange", "Green", "Blue",
                            "Purple", "Teal", "Yellow", "Dark Olive"};
int current_color;

void setup(){
    pinMode(4, INPUT_PULLUP);

    Serial.begin(9600);
    Serial.println("Code written by Yoseob Kim (SKKU)");

    lcd.init();
    lcd.backlight();

    current_color = 0; // initial setting to white color
}

void loop(){
    // 1-2: setting for joystick, lcd module
    int x_axis, y_axis, sw_input;
    x_axis = analogRead(A1);
    y_axis = analogRead(A0);
    sw_input = digitalRead(joy_sw);
    lcd.clear(); // lcd clear

    // 2: lcd display - position of joystick
    lcd.setCursor(0, 0); // set cursor to first row - print x axis
    lcd.print("X = ");
    lcd.print(x_axis);

    lcd.setCursor(0, 1); // set cursor to second row - print y axis
    lcd.print("Y = ");
    lcd.print(y_axis);

    // 3: rgb-led color changing by position of joystick

    // 4: turn-off rtb-led
    if(sw_input == LOW){
        for(int i=0;i<3;++i){
            analogWrite(red+i, 0);
        }
    }

    // 5: serial monitor output
    Serial.print("X: ");
    Serial.print(x_axis);
    Serial.print("\tY: ");
    Serial.print(y_axis);
    if(sw_input == HIGH){
        Serial.print("\tNot Pressed!");
        Serial.print("\tLED Color: ");
        Serial.println(color_name[current_color]);
    }
    else {
        Serial.println("\tPressed! - Turn OFF LED");
    }

    delay(200);
}