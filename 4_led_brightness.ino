// 2015312229 Yoseob Kim
const int led = 9;
const int potentiometer = 4;
void setup(){
  Serial.begin(9600);
}

void loop(){
  int A4 = analogRead(potentiometer);
  // Serial.println(A4);
  
  // up to 10kOhm
  // A4 value range 0~1023
  
  int brightness = map(A4, 0, 1023, 255, 0);
  analogWrite(led, brightness);
 
  Serial.println("brightness: "+String(brightness));
  delay(100);
}