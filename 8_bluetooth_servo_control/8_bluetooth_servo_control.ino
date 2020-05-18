// 2015312229 Yoseob Kim
// Bluetooth Servo motor Control (BSC)
#include <SoftwareSerial.h>
#include <Servo.h>

const int bscTx = 11;
const int bscRx = 10;

// 1: declare class instances for using bluetooth and servo motor
SoftwareSerial bscSerial(bscTx, bscRx);
Servo bscServo;

void setup() {
    Serial.begin(9600);
    bscSerial.begin(9600);

    bscServo.attach(7);
    bscServo.write(0); // delete previous state (set to 0 angle)

    // 3: print notice to smartphone
    while(!bscSerial.available());
    bscSerial.println("Yoseob Kim - capstone design hw8");
    bscSerial.println("Enter the up or down");
    bscSerial.println("up = angle + 15");
    bscSerial.println("down = angle - 15");
    
    // 2: initial angle = 90
    for(int pos = 0; pos <= 90; pos += 1) {
        bscServo.write(pos);
        delay(5);
    }
    bscSerial.println("Initializing... Current Angle = 90");
    delay(100);
}

void loop() {
    /*if(bscSerial.available()){Serial.write(bscSerial.read());}
    if(Serial.available()){bscSerial.write(Serial.read());}*/

    static int bscAngle = 90;
    String bscString;
    static boolean ignored_first_error = false;
    
    // read data from smartphone
    bscString = bscSerial.readString();

    if(!bscString.equals("")){
        // print read data to computer's serial monitor
        Serial.println("input val: " + bscString);

        // 4: input 'up' from smartphone
        if(bscString == "up"){
            if(bscAngle != 180){
                for(int pos = bscAngle; pos <= bscAngle+15; pos += 1) {
                    bscServo.write(pos);
                    delay(5);
                }
    
                bscAngle += 15;
                bscSerial.print("+15, Current Angle = ");
                bscSerial.println(bscAngle);
            }
            else {
                bscSerial.println("Maximum Angle! (180)");
            }
        }
        // 5: input 'down' from smartphone
        else if(bscString == "down"){
            if(bscAngle != 0){
                for(int pos = bscAngle; pos >= bscAngle-15; pos -= 1) {
                    bscServo.write(pos);
                    delay(5);
                }
    
                bscAngle -= 15;
                bscSerial.print("-15, Current Angle = ");
                bscSerial.println(bscAngle);
            }
            else {
                bscSerial.println("Minimum Angle! (0)");
            }
        }
        // 6: print error message
        else {
            if(!ignored_first_error){
                ignored_first_error = true;
            }
            else {
                bscSerial.println("wrong operation!!");   
            }
        }
    }
    delay(100);
}
