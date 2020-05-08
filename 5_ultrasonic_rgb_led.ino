// 2015312229 Yoseob Kim
const int trig = 3;
const int echo = 2;
const int red = 11;
const int blue = 10;
const int green = 9;
void setup(){
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop(){
  int duration, cm;
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  duration = pulseIn(2, HIGH);
  cm = ms2cm(duration);
  
  Serial.print(String(cm)+" cm");
  
  if(cm >= 0 && cm < 10){ // red #ff0000
    analogWrite(red, 255);
    analogWrite(green, 0);
    analogWrite(blue, 0);
    Serial.println(" - RED");
  }
  else if(cm >= 10 && cm < 20){ // orange #ff4000
    analogWrite(red, 255);
    analogWrite(green, 64);
    analogWrite(blue, 0);
    Serial.println(" - ORANGE");
  }
  else if(cm >= 20 && cm < 30){ // yellow #ffff00
    analogWrite(red, 255);
    analogWrite(green, 255);
    analogWrite(blue, 0);
    Serial.println(" - YELLOW");
  }
  else if(cm >= 30 && cm < 40){ // green #00ff00
    analogWrite(red, 0);
    analogWrite(green, 255);
    analogWrite(blue, 0);
    Serial.println(" - GREEN");
  }
  else if(cm >= 40 && cm < 50){ // purple #8000ff
    analogWrite(red, 128);
    analogWrite(green, 0);
    analogWrite(blue, 255);
    Serial.println(" - PURPLE");
  }
  else { // RGB LED off
    analogWrite(red, 0);
    analogWrite(green, 0);
    analogWrite(blue, 0);
    Serial.println(" - RGB LED off");
  }
  
  delay(300);
}

int ms2cm(int ms){
  return ms / 29 / 2;
}