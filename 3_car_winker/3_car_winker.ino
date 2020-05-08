// 2015312229 Yoseob Kim
const int l_btn = 12;
const int r_btn = 3;
const int tiktok = 10;
const int l_led = 13;
const int r_led = 2;

bool pressed[2], toggle[2];

void setup(){
  Serial.begin(9600);
  pinMode(l_btn, INPUT_PULLUP); // left button with pullup R
  pinMode(r_btn, INPUT_PULLUP); // right button with pullup R
  pinMode(l_led, OUTPUT); // left direction led
  pinMode(r_led, OUTPUT); // right direction led
  pressed[0] = pressed[1] = false; // 0 = left, 1 = right
  toggle[0] = toggle[1] = false;
}

void loop(){
  int left, right;
  static bool flicker = false;
  left = digitalRead(l_btn);
  right = digitalRead(r_btn);
  
  // if one of the switches is pressed: just check pressed button
  if(left == LOW || right == LOW){
    pressed[0] = !left;
    pressed[1] = !right;
  }
  
  if(left == HIGH || right == HIGH){
    // if pressed button is just released:
    if(pressed[0] && left == HIGH || pressed[1] && right == HIGH){
      if(pressed[0] && left == HIGH){
        toggle[0] = !toggle[0];
        digitalWrite(l_led, (toggle[0]?HIGH:LOW));
      }
      if(pressed[1] && right == HIGH){
        toggle[1] = !toggle[1];
        digitalWrite(r_led, (toggle[1]?HIGH:LOW));
      }
      
      // print current status
      if(toggle[0] && toggle[1]){
        Serial.println("Emergency light - both sides flickering");
      }
      else{
        Serial.print(String("left: ")+(toggle[0]?"on":"off"));
        Serial.println(String(" right: ")+(toggle[1]?"on":"off"));
      }
    }
    // normal case - not related to current switch input
    else{
      // do sth only if at least one of the toggle is on: 
      if(toggle[0] || toggle[1]){
        flicker = !flicker; // synchronize flicker
        if(flicker){
          tone(10, 700, 100);
          if(toggle[0]){
          	digitalWrite(l_led, HIGH);
          }
          if(toggle[1]){
            digitalWrite(r_led, HIGH);
          }
        }
        else { // flicker on and off with 0.5s periods
          tone(10, 500, 100);
          if(toggle[0]){
          	digitalWrite(l_led, LOW);
          }
          if(toggle[1]){
            digitalWrite(r_led, LOW);
          }
        }
      }
    }
    
    // adjust pressed status value 
    if(left == HIGH){
      pressed[0] = false;
    }
    if(right == HIGH){
      pressed[1] = false;
    }
  }

  delay(500); // loop with 0.5s periods
}