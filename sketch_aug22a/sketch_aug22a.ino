// Interfacing Arduino with DHT11 humidity and temperature sensor
 
// include LCD library code
#include <LiquidCrystal.h>
// include DHT library code
#include "DHT.h"
 
#define DHTPIN 8            // DHT11 data pin is connected to Arduino pin 8
 
// LCD module connections (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
 
#define DHTTYPE DHT11       // DHT11 sensor is used
DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT library
 
char temperature[] = "Temp = 00.0 C  ";
char humidity[]    = "RH   = 00.0 %  ";

// Motor

int val = 150;

// Buzzer

#define buzz 13

// LED

int led = 12;


void setup() {
  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  dht.begin();
  Serial.begin(9600);
  
  pinMode(led, OUTPUT);

  pinMode(buzz, OUTPUT);
}
 
void loop() {
  delay(1000);           // wait 1s between readings
  // Read humidity
  byte RH = dht.readHumidity();
  //Read temperature in degree Celsius
  byte Temp = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again)
  if (isnan(RH) || isnan(Temp)) {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Error");
    return;
  }
 
  temperature[7]     = Temp / 10 + 48;
  temperature[8]     = Temp % 10 + 48;
  temperature[11]    = 223;
  humidity[7]        = RH / 10 + 48;
  humidity[8]        = RH % 10 + 48;
  lcd.setCursor(0, 0);
  lcd.print(temperature);
  lcd.setCursor(0, 1);
  lcd.print(humidity);

  // Motor

  if (Temp >= 28){
    analogWrite(9, val);
    analogWrite(10, 0);
    delay(1000);
  }
  else{
    analogWrite(9, 0);
    analogWrite(10, 0);
    delay(1000);
  }

  if (Temp >= 40){
    tone(buzz, 1000);
    delay(1000);
    noTone(buzz);
    digitalWrite(buzz, HIGH);
    digitalWrite(led, HIGH);
    
  }
  else {
    noTone(buzz);
    digitalWrite(buzz, LOW);
    digitalWrite(led, LOW);
  }
  
  Serial.println(temperature);
  Serial.println(humidity);
  delay(1);
}
