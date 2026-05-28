#include <HardwareSerial.h>
#include <string.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


HardwareSerial MySerial(1); // define a Serial for UART1
const int MySerialRX = 16;
const int MySerialTX = 17;
const int MySerialRTS = 18;
const int MySerialCTS = 19; 
int LED_BUILTIN = 2;
char inputString[50];
bool stringComplete = false;
const char test[] = "hi";
const char* ssid = "wifi";
const char* password = "password";

bool complete = true;
char cube[57];

const char* apiEndpoint = "https://xxe2nvowb5.execute-api.us-east-2.amazonaws.com/default/cubie";

void writeHi(void);
void readSerial(char* buffer);
void waitForAck(void);
void ack(void);
void sendSteps(String steps);

void setup() {
  // put your setup code here, to run once:
  MySerial.begin(9600, SERIAL_8N1, MySerialRX, MySerialTX);
  Serial.begin(9600, SERIAL_8N1);
  pinMode (LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  if(complete)

  delay(1000);
  Serial.println("reading...");
  waitForAck();
  readSerial(cube);
  if (WiFi.status() == WL_CONNECTED) {
    

    
    HTTPClient http;  // Create an HTTP client instance

    http.begin(apiEndpoint);  // Specify the endpoint
    http.setTimeout(120000);  // Wait up to 90 seconds for server response
    http.addHeader("Content-Type", "application/json");  // Set the content type
    
    // Create a JSON object
    StaticJsonDocument<2000> jsonDoc;  // Allocate memory for the JSON object
    jsonDoc["key1"] = cube;
    // Serialize JSON to a string
    String jsonString;
    serializeJson(jsonDoc, jsonString);
    Serial.println("JSON String: " + jsonString);
    // Send HTTP POST request
    int httpResponseCode = http.POST(jsonString);
    
    // Print the HTTP response
    Serial.print("Response code: ");
    Serial.println(httpResponseCode);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response: " + response);
      sendSteps(response);
    } else {
      Serial.print("Error: ");
      Serial.println(http.errorToString(httpResponseCode));
    }

    http.end();  // Close connection
  }
  delay(100000);
  complete = false;
}

void readSerial(char* buffer){
  int i = 0;
  while (!MySerial.available()) {
      // Wait for data to become available
    }
    for(i = 0; i < 57; i++){
    buffer[i] = MySerial.read();
    Serial.print(buffer[i]);
    delay(400);
    ack();
    delay(400);
  }
}

void sendSteps(String steps){
  Serial.println("I am");
  if(MySerial.availableForWrite()){
    Serial.println("trying to");
    for(int i = 0; i < steps.length(); i++){
      MySerial.write(steps[i]);
      delay(400);
      waitForAck();
      delay(400);
    }
    MySerial.write('\0)');
    delay(400);
    waitForAck();
    delay(400);
  }
}

void waitForAck(void){
  bool acked = false;
  while(!acked){
    if(MySerial.available() > 0){
      if(MySerial.peek() == 'A'){
        MySerial.read();
        acked = true;
      }else
      Serial.println("going to be stuck!");
    }
  }
}

void ack(void){
  if(MySerial.availableForWrite()){
    MySerial.write('A');
  }
}
