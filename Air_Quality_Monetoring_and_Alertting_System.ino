#include <LiquidCrystal_I2C.h>
#include <dht.h>
dht DHT;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Setting the LCD address to 0x27 for a 16 characters and 2 line display

int sensorValue;  // for sensing the analog value
int digitalValue; // for sensing the digital value

#define DHT11_PIN 11

void setup()
{
  Serial.begin(9600); // sets the serial port to 9600

  lcd.init();
  lcd.backlight();

  pinMode(5, OUTPUT); // led and buzzer [buzzer and red leds]
  pinMode(2, INPUT); 
  pinMode(7,OUTPUT); //led normal led pin 7 ma xa
  int chk = DHT.read11(DHT11_PIN); // initialize the DHT11 sensor
}

void loop()
{
  sensorValue = analogRead(A0); // read analog input pin 0 [MQ135]
  digitalValue = digitalRead(2); // digital pin MQ135 connection
  int chk = DHT.read11(DHT11_PIN); // read temperature and humidity from DHT11 sensor
  
  if (sensorValue >= 400)
  {

    //lcd ma display garne
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Poor Air (>_<) ");
    lcd.setCursor(0, 1);
    lcd.print(DHT.temperature);
    lcd.print("C ");
    lcd.print(DHT.humidity);
    lcd.print("%H");

    // This is for serial monitor
    Serial.print("Poor Air (^_^) ");
    Serial.print(DHT.temperature);
    Serial.print("C ");
    Serial.print(DHT.humidity);
    Serial.println("%H");

    alertState();
  }
  else{

    //lcd ma display garne
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Good Air (^_^) ");
    lcd.setCursor(0, 1);
    lcd.print(DHT.temperature);
    lcd.print("C ");
    lcd.print(DHT.humidity);
    lcd.print("%H");

    // This is for serial monitor
    Serial.print("Good Air (^_^) ");
    Serial.print(DHT.temperature);
    Serial.print("C ");
    Serial.print(DHT.humidity);
    Serial.println("%H");

    normalState();
  }
  delay(3000); // wait 3 sec
}

void normalState(){
    digitalWrite(7, HIGH); // normal air ko lagi xa
    digitalWrite(5,LOW); // off the red and buzzer
}

void alertState(){
    digitalWrite(5, HIGH); // turn on buzzer and red LED if MQ135 sensor reading is high
    digitalWrite(7,LOW); // normal led off hunu parxa
}