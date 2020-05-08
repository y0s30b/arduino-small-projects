// 2015312229 Yoseob Kim
void setup()
{
  Serial.begin(9600); // 9600 bps
  
  Serial.println("2015312229 KIM YOSEOB - HW #1");
  Serial.println();
  Serial.println("<1> 9-TIMES TABLE using 'for' loop");
  for(int i=1;i<=9;++i){
    Serial.println("9 x "+String(i)+" = "+String(9*i));
  }
  Serial.println();
  Serial.println("<2> 9-TIMES TABLE using 'while' loop");
  int i = 1;
  while(i < 10){
    Serial.println("9 x "+String(i)+" = "+String(9*(i)));
	++i;
  }
}
void loop() {}   
