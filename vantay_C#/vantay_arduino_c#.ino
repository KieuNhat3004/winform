#include <Adafruit_Fingerprint.h> //Libraries needed
#include <SoftwareSerial.h>
#include <Keypad.h>



SoftwareSerial mySerial(2, 3);   //Fingerprint sensor wiring RX 3, TX 2 

const byte numRows= 4;          //number of rows on the keypad
const byte numCols= 4;          //number of columns on the keypad

char keypressed;
String pass = "1111", a_out = "1", b_out = "", data_in = "",chuoi1 ="A", chuoi2 = "001", chuoi3 = "C",chuoi4 ="E", chuoi5 = "G";

char code[]={'1','2','3','4'}; //Passcode needed you can change it just keep the format "4 digits as char array"
char c[4];                     //Array to get the code from the user
int ij, count = 0;

int in1 = 5; 
int buzzer = 4;


//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};


byte rowPins[numRows] = {9,8,7,6}; //Rows 0 to 3 //if you modify your pins you should modify this too
byte colPins[numCols]= {13,12,11,10}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows,  numCols);


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id;

void setup()  
{
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(buzzer, OUTPUT);
  finger.begin(57600); 
  delay(500);
}



void loop() 
{ 
  if(Serial.available() >0){
    data_in = Serial.readString();
  }
  xulychuoiIN();
  getFingerprintIDez();                //Waiting for a fingerprint to scan if it's valid or not
  keypressed = myKeypad.getKey();      //Reading the buttons typed by the keypad
  if(chuoi3 == "D"){               //If it's 'A' it triggers "Adding new template" sequence

            ij=0;                      //ij is set to 0
            Serial.println("Nhap Mat Khau");
            getPassword();            //Getting the passcode function
            if(ij == 4){ 
              //If the passcode is correct we can start enrolling new finger template
            Enrolling();              //Enrolling function
            delay(2000);
            }
            else{                    //If the code is wrong we can't add new users (templates)
            Serial.println("Sai Mat Khau");
            delay(2000);
            }
  }
 if(chuoi4 == "F")        //As the keypad is meant to stay inside the 'B' button opens the door lock
 {    
  //Because the system I used needs an electrical signal to open
  Serial.println(".Xin Chao! - Da mo !!! ");
  OpenDoor();
  delay(3000);                //Opening delay
  CloseDoor();
 }

 if(chuoi5 == "H")        //As the keypad is meant to stay inside the 'B' button opens the door lock
 {    
  ij=0;                      //ij is set to 0
  Serial.println("Nhap Mat Khau");
  getPassword();           
  if(ij==4)
  {
    deleteFingerprint(id);
    delay(2000);
  }
  else
  {                   
    Serial.println("Sai Mat Khau");
    delay(2000);
  }
 }
  Serial.println(String("Dat Ngon Tay"));
  delay(100);
}

//Getting password (code) function, it gets the characters typed
//and store them in c[4] array
void getPassword(){
   for (int i=0 ; i<4 ; i++){
    
    c[i]= myKeypad.waitForKey();
   }
   for (int j=0 ; j<4 ; j++){ //comparing the code entred with the code stored
    if(c[j]==code[j])
     ij++;                    //Everytime the char is correct we increment the ij until it reaches 4 which means the code is correct
   } //Otherwise it won't reach 4 and it will show "wrong code" as written above
}

//The Enrolling and getFingerprintEnroll functions are mainly based on the "Enroll" example code from the library
//Only the modifications will be commented, return to the example to see each step in details, as here it's shortened

void Enrolling()  {
  keypressed = NULL;
  Serial.println("Ma Van Tay Moi");
  delay(2000);
  Serial.println("ID Ma Van Tay Moi: ");
  id = readnumber();                           //This function gets the Id it was meant to get it from the Serial monitor but we modified it
  if (id == 0) {// ID #0 not allowed, try again!
     return;
  }
  
  while (!  getFingerprintEnroll() );
  }

//Enrolling function only the modifications are commented
uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.println(String("ID Ma Van Tay Moi: ") +id + String("          Dat Ngon Tay"));
//  Serial.println(String("Ma ID: ") + id + String("Dat Ngon Tay"));
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      break;
    case FINGERPRINT_IMAGEMESS:
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      return p;
    case FINGERPRINT_FEATUREFAIL:
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      return p;
    default:
      return p;
  }
  Serial.println("Vui Long Lay Ngon Tay Ra!");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  
  p = -1;
  Serial.println("Da Quet, Vui long!                    Dat Ngon Tay Lai");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      break;
    case FINGERPRINT_IMAGEMESS:
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      return p;
    case FINGERPRINT_FEATUREFAIL:
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      return p;
    default:
      return p;
  }
  
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    return p;
  } else {
    return p;
  }   
  
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK)
  {
  Serial.println(String("Da Luu - ID: ") +id);
  delay(3000);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    return p;
  } else {
    return p;
  }   
}

//This function gets the ID number as 3 digits format like 001 for ID 1
//And return the number to the enrolling function
uint8_t readnumber(void) {
  uint8_t num = 0;
   while (num == 0) {
      char keey = myKeypad.waitForKey();
    int  num1 = keey-48;
         keey = myKeypad.waitForKey();
    int  num2 = keey-48;
         keey = myKeypad.waitForKey();
    int  num3 = keey-48;
         delay(1000);
         num=(num1*100)+(num2*10)+num3;
         keey=NO_KEY;
  }
  return num;
}

//Main function taken from the "fingerprint" example and modified
//Only the modifications are commented
//This function waits for a fingerprint, scan it and give it access if recognised

int getFingerprintIDez() {
  uint8_t p = finger.getImage();        //Image scanning
  if (p != FINGERPRINT_OK)  return -1;  

  p = finger.image2Tz();               //Converting
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();     //Looking for matches in the internal memory
  if (p != FINGERPRINT_OK){          //if the searching fails it means that the template isn't registered
    Serial.println("Mat Ma Sai");
    delay(2000);
    Serial.println("Dat Ngon Tay");
    return -1;
  }

  Serial.println(String(".Xin Chao - ID: ")+finger.fingerID); 
  OpenDoor();
  delay(3000);
  CloseDoor();
  Serial.println("Dat Ngon Tay");
  return finger.fingerID; 
  
}

uint8_t deleteFingerprint(uint8_t id) {
  uint8_t p = -1;
  keypressed = NULL;
  Serial.println("Nhap ID Can Xoa!");
  id = readnumber(); 
  if (id == 0) {// ID #0 not allowed, try again!
     return;
  }
  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println(String("Da Xoa! - ID: ")+id);
    delay(3000);
  } 
  else if (p == FINGERPRINT_PACKETRECIEVEERR) {
//    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
//    Serial.println("Could not delete in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
//    Serial.println("Error writing to flash");
    return p;
  } else {
//    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  }
}

void xulychuoiIN()
{
  int pin =0;
  chuoi1 = data_in.substring(1,2);
  chuoi2 = data_in.substring(2,5); //8/12
  chuoi3 = data_in.substring(5,6);
  chuoi4 = data_in.substring(6,7);
  chuoi5 = data_in.substring(7,8);
  pass = data_in.substring(8,12);
  if(chuoi1 == "B"){
    pin =1;
  }
  if(chuoi1 == "A"){
    pin =0;
  }
  if(pin == 1) digitalWrite(in1, 1);
  else digitalWrite(in1, 0);
}


void OpenDoor(){
  digitalWrite(buzzer, HIGH); //it's not the delay for the whole sequence
  digitalWrite(in1, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW); //it's not the delay for the whole sequence
}

void CloseDoor(){
  digitalWrite(in1, LOW);
  digitalWrite(buzzer, HIGH); //it's not the delay for the whole sequence
  delay(100);
  digitalWrite(buzzer, LOW); //it's not the delay for the whole sequence
}
