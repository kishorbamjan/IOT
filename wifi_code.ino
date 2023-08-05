#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>

// Define the TX and RX pins
#define RX_PIN D1 // rx to d2 in node mcu
#define TX_PIN D2 // tx to d1 in node mcu


// Create a SoftwareSerial object for serial communication
SoftwareSerial mySerial(RX_PIN, TX_PIN); 

//college  wifi
const char* ssid = "Islington-College";
const char* password = "I$LiNGT0N2023";

WiFiClient client;

// ThingSpeak channel details
unsigned long CHANNEL_ID = 2118242;
const char* WRITE_API_KEY = "RW62V928QV4BYQBO";


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  //print a new line, then print WiFi connected and the IP address
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

void loop(){
//String data = "Good Air (^_^) 31.00C 13.00%H199";

String data = mySerial.readStringUntil('\n');

// int tempStartIndex = data.indexOf(" ") ;
// int tempEndIndex = data.indexOf("C");
int tempStartIndex = data.indexOf("^_^") + 4;
int tempEndIndex = data.indexOf("C", tempStartIndex);

int humidStartIndex = data.indexOf(" ", tempEndIndex);
int humidEndIndex = data.indexOf("%", humidStartIndex);

String tempString = data.substring(tempStartIndex , tempEndIndex);
String humidString = data.substring(humidStartIndex+1, humidEndIndex);

float tempValue = tempString.toFloat();
int humidValue = humidString.toInt();

Serial.print("Temperature: ");
Serial.println(tempValue);
Serial.print("Humidity: ");
Serial.println(humidValue);

if (tempValue > 0.00 && humidValue > 0) {
  ThingSpeak.setField(1, tempValue);
  ThingSpeak.setField(2, humidValue);

  int status = ThingSpeak.writeFields(CHANNEL_ID, WRITE_API_KEY);
  if (status == 200) {
    Serial.println("Data sent successfully!");      
  } else {
    Serial.println("Failed to send data to ThingSpeak");
  }
}

  delay(10); // wait for 1 seconds before sending the next set of data
}
