#include <ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include<FS.h>

ESP8266WebServer server(80);

const char *ssid = "jamilzone";
const char *password = "056226453";

void handleRoot(){
  File file = SPIFFS.open("/index.html","r");
  size_t sent = server.streamFile(file,"text/HTML");
  file.close();
}
void handlePic(){
  File file = SPIFFS.open("/teddy.jpg","r");
  size_t sent = server.streamFile(file,"image/jpg");
  file.close();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  
  Serial.println();
  
  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(' ');
  }
  SPIFFS.begin();
  server.on("/",handleRoot);
  server.on("/teddy",handlePic );
  
  server.begin();
  
  Serial.println("Connected to:");
  Serial.print(WiFi.localIP());

  if(SPIFFS.exists("/index.html"))
    Serial.println("Files loaded");
  else
    Serial.println("Files not loaded");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}


//server.on("/upload", HTTP_POST,[](){ server.send(200); }, handleFileUpload);
