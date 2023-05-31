#include <LiquidCrystal_I2C.h>       
LiquidCrystal_I2C lcd(0x27,16,2);
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);

int buzzer = 13;
int GASA0 = 0;
int gasvalue;

void setup() {
  
 lcd.init();                       // initialize the lcd
 lcd.init();
 lcd.backlight(); 
 mySerial.begin(9600);
 Serial.begin(9600);
 pinMode(buzzer, OUTPUT); 
 lcd.setCursor(3,0);
 lcd.print("welcome to"); 
 lcd.setCursor(1,1);
 lcd.print("Infinite Xpro"); 
 delay(5000);     
}

void loop() {
  int analogSensor = analogRead(GASA0);
  int gasvalue=(analogSensor-50)/10;
  
  lcd.setCursor(0,0);
  lcd.print("GAS Level:");
  lcd.setCursor(10,0);
  lcd.print(gasvalue);
  lcd.setCursor(12,0);
  lcd.print("%");
  
  // Checks if it has reached the threshold value
  if (gasvalue >= 10)
  {
    SendTextMessage();
    lcd.setCursor(0,1);
  lcd.print("DANGER");
    tone(buzzer, 1000, 200);
  }
  else
  {
  lcd.setCursor(0,1);
  lcd.print("NORMAL");
    noTone(buzzer);
  }
  delay(500);
  lcd.clear();
}

void SendTextMessage()
{
  mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  mySerial.println("AT+CMGS=\"+918088XXX85\"\r");  // change to the phone number you using
  delay(1000);
  mySerial.println("Gas Leaking!");//the content of the message
  delay(200);
  mySerial.println((char)26);//the stopping character
  delay(1000);
  
}
