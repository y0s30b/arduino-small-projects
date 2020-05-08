// 2015312229 Yoseob Kim
int cnt;
void setup(){
  pinMode(13, OUTPUT);
  
  Serial.begin(9600);
  pinMode(10, INPUT_PULLUP);
  
  cnt = 0;
}

void loop(){
  int d10 = digitalRead(10);
  // Serial.println(d10); // D10 이 눌렸는지 확인
  
  if(d10 == 0){
    cnt += 5;
  }
  Serial.println("before dW: " + String(cnt));
  
  if(cnt > 0){
    -- cnt;
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
  Serial.println("after dW: " + String(cnt));
  delay(1000);
}
