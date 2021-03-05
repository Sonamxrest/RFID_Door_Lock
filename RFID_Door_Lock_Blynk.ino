
#include <SPI.h>
#include <MFRC522.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 #include <Servo.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
Servo myservo;
#define SS_PIN 4  //sda pin
#define RST_PIN 2// rst pin
#define TRIGGER 0//d0
#define ECHO    16//d3
MFRC522 mfrc522(RST_PIN, SS_PIN);   //MFRC522 instance.
char auth[] ="xcKXzJuqRwRJ4HsGsGeAw03p9TR_kOvn";// authentication code
 const long utcOffsetInSeconds = 19260;
char ssid[] = "asd";//wifi ssid
char pass[] = "12345678";//password
SimpleTimer timer;// SimpleTimer instance
int fflag = 1; //setting flags to 1
int eflag = 1; 
int jflag = 1; 
WidgetTerminal terminal(V2);// Blynk terminal
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup() {
  pinMode(5,OUTPUT);
   
  
  timeClient.begin();
   myservo.attach(15); // servo motor pin defination
        Serial.begin(9600);        // Initialize serial communications with the PC
         pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
        Blynk.begin(auth, ssid, pass);//connection to blynk server
        SPI.begin();                // Init SPI bus
        mfrc522.PCD_Init();        // Init MFRC522 card
          timer.setInterval(1000L, iot_rfid);
}
 
void loop() {
        digitalWrite(5,LOW);
        timeClient.update();
  timer.run(); 
  Blynk.run();
   long duration;
  long distance;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;
 int pos;
  if(distance>0 && distance<=10){
  //  digitalWrite(5,HIGH);
    //delay(1000);
    //digitalWrite(5,LOW);
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
                           // waits 15ms for the servo to reach the position
  }
 
  delay(5000);
  for (pos = 110; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
    }

    

 
       
}
 
void iot_rfid()
{

 
        // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
        MFRC522::MIFARE_Key key;
        for (byte i = 0; i < 6; i++) {
                key.keyByte[i] = 0xFF;
        }
        // Look for new cards
        if ( ! mfrc522.PICC_IsNewCardPresent()) {
                return;
        }
 
        // Select one of the cards
        if ( ! mfrc522.PICC_ReadCardSerial()) {
                return;
        }
        // Now a card is selected. The UID and SAK is in mfrc522.uid.
        
        // Dump UID
        Serial.print("Card UID:");
        for (byte i = 0; i < mfrc522.uid.size; i++) {
               Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
               Serial.print(mfrc522.uid.uidByte[i], DEC);
        } 
        Serial.println();
        
 
        // Dump PICC type
        byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    //    Serial.print("PICC type: ");
//Serial.println(mfrc522.PICC_GetTypeName(piccType));
        if (        piccType != MFRC522::PICC_TYPE_MIFARE_MINI 
                &&        piccType != MFRC522::PICC_TYPE_MIFARE_1K
                &&        piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
                //Serial.println("This sample only works with MIFARE Classic cards.");
                return;
        }
        // defining Cards here 
       
        if( ((mfrc522.uid.uidByte[0] == 137) && (mfrc522.uid.uidByte[1] == 168) && (mfrc522.uid.uidByte[2] == 79) && (mfrc522.uid.uidByte[3] == 184)) && (fflag == 1) )
        {int pos;
        String message ="";
        message ="Shubham has just entered on "+ String(daysOfTheWeek[timeClient.getDay()]) +" - "+ String(timeClient.getHours())+" : "+String(timeClient.getMinutes());
         Blynk.virtualWrite(V2,  message);
        for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
                           // waits 15ms for the servo to reach the position
  }
  delay(2000);
 
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
        }


        else
        if(( (mfrc522.uid.uidByte[0] == 214) && (mfrc522.uid.uidByte[1] == 145) && (mfrc522.uid.uidByte[2] == 242) && (mfrc522.uid.uidByte[3] == 249)  && (eflag == 1) ) )
        {
          int pos;
           String message ="";
        message ="Sonam has just entered on "+ String(daysOfTheWeek[timeClient.getDay()]) +" - "+ String(timeClient.getHours())+ " : " + String(timeClient.getMinutes());
        
         Blynk.virtualWrite(V2, message);
          for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
                           // waits 15ms for the servo to reach the position
  }
  delay(5000);
  for (pos = 110; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
        }
        
 
        else {

 if(( (mfrc522.uid.uidByte[0] == 214) && (mfrc522.uid.uidByte[1] == 145) && (mfrc522.uid.uidByte[2] == 242) && (mfrc522.uid.uidByte[3] == 249)  && (eflag == 0) ) )
        {
           Serial.println("Sonam just tried to access the door");
        digitalWrite(5,HIGH);
        delay(1500);
        digitalWrite(5,LOW);
        Serial.println(fflag);
        Blynk.virtualWrite(V2, "non Authorized Person" );
        Blynk.notify("Sonam just tried to access the door");
          }
        if( ((mfrc522.uid.uidByte[0] == 137) && (mfrc522.uid.uidByte[1] == 168) && (mfrc522.uid.uidByte[2] == 79) && (mfrc522.uid.uidByte[3] == 184)) && (fflag == 0) )
        {
           Serial.println("Shubham just tried to access the door");
        digitalWrite(5,HIGH);
        delay(1500);
        digitalWrite(5,LOW);
        Serial.println(fflag);
        Blynk.virtualWrite(V2, "non Authorized Person" );
        Blynk.notify("Shubham just tried to access the door");}
        }
          }
          
         
        
  

 
// in Blynk app writes values to the Virtual Pin 3
BLYNK_WRITE(V3)
{
   fflag = param.asInt(); // assigning incoming value from pin V3 to a variable
  // Blynk.virtualWrite(V2, fflag );
 
}
 
 
// in Blynk app writes values to the Virtual Pin 4
BLYNK_WRITE(V4)
{
   eflag = param.asInt(); // assigning incoming value from pin V4 to a variable
 
}
 
