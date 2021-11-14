uint8_t btLeft = 5, btRight = 3, btL = 2, btX = 4,btrst = 7, btstop = 6, 
a = 0, b = 0, c = 0, d = 0, value = 0 , count = 2;
long int e, f = 0, controlAL = 0;
String chuoisend = "", aa = "", bb =""; 
void setup() {
  Serial.begin(9600);
  pinMode(btLeft, INPUT_PULLUP);
  pinMode(btRight, INPUT_PULLUP);
  pinMode(btL, INPUT_PULLUP);
  pinMode(btX, INPUT_PULLUP);
}

void loop() {
  delay(100);
  a = digitalRead(btLeft);
  b = digitalRead(btRight);
  
  c = digitalRead(btL);
  d = digitalRead(btX);
  
  if(a == 0) value = 1;
  if(b == 0) value = 2;
  if(c == 0 && count < 30)
  {
    count ++;
  }
  if(d == 0 && count > 2)
  {
    count --;
  }
  if((a == 1) && (b == 1)) value = 0;
  if(count >= 0 && count <10) aa = "0";
  if(count >= 10) aa = "";
  chuoisend = aa + String(count) + String(value);
  Serial.println(chuoisend);
//  Serial.println(value);

}
