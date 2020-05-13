// 2015312229 Yoseob Kim
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // (address, column, row)

// 1-1: setting for joystick, rgb-led (variable declaration)
const int joy_sw = 4;
const int red = 5; 
// green = 6, blue = 7 (using for loop)
// pin number 2~13 is used for PWM.
const byte color_info[][3] = {  // color - direction (x_range, y_range): index = x_range*3 + y_range
                                {0x80, 0x00, 0x80}, // purple - ne (0, 0): 0
                                {0xff, 0x40, 0x00}, // orange - north (0, 1): 1
                                {0x00, 0x80, 0x80}, // teal - nw (0, 2): 2

                                {0xff, 0x00, 0x00}, // red - east (1, 0): 3
                                {0xff, 0xff, 0xff}, // white - center (1, 1): 4
                                {0x00, 0xff, 0x00}, // green - west (1, 2): 5

                                {0x55, 0x6b, 0x2f}, // dark olive - se (2, 0): 6
                                {0x00, 0x00, 0xff}, // blue - south (2, 1): 7                    
                                {0xff, 0xff, 0x00}, // yellow - sw (2, 2): 8

                                {0xff, 0xc0, 0xcb} // pink - gap: 9
                             };
const char* color_name[] = {"Purple", "Orange", "Teal",
                            "Red", "White", "Green",
                            "Dark Olive", "Blue", "Yellow", "Pink"};
int current_color;

void setup(){
    pinMode(4, INPUT_PULLUP);

    Serial.begin(9600);
    Serial.println("Code written by Yoseob Kim (SKKU)");

    lcd.init();
    lcd.backlight();

    current_color = 0; // initial setting to white color
}

inline int get_range(int value){
    if(value >= 1020){ // west, south
        return 2;
    }
    else if(value >= 530 && value < 1020){ // do nothing
        return -1;
    }
    else if(value >= 480 && value < 530){ // center
        return 1;
    }
    else if(value >= 10 && value < 480){ // do nothing
        return -1;
    }
    else { // value < 10 : east, north
        return 0;
    }
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
    int x_range, y_range;
    x_range = get_range(x_axis);
    y_range = get_range(y_axis);
    current_color = (x_range >=0 && y_range >=0)?(x_range*3+y_range):9;
    for(int i=0;i<3;++i){
        analogWrite(red+i, color_info[current_color][i]);
    }

    // 4: turn-off rtb-led
    if(sw_input == LOW){
        for(int i=0;i<3;++i){
            analogWrite(red+i, LOW);
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

    delay(500);
}
