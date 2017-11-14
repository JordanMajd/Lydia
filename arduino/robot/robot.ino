#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Adafruit_PWMServoDriver.h>

const char* ssid = "...";
const char* pass = "...";

#define MAX 600
#define RESET 400
#define MIN 150

ESP8266WebServer server(80);
Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver();

uint8_t hip = 0;
uint8_t knee = 1;

//{hip, knee}
uint8_t fl[2] = {0,4};
uint8_t fr[2] = {1,5};
uint8_t bl[2] = {2,6};
uint8_t br[2] = {3,7};

void setup(){

  Serial.begin(115200);
  Serial.println("Initializing...");
  
  Serial.print("Connecting to network...");

  // connect to WiFi
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("Connected: ");
  Serial.println(ssid);
  Serial.println(WiFi.localIP());

  // init pwm
  pwmDriver.begin();
  pwmDriver.setPWMFreq(60);
  // center leg position
 // center();

  // init server & routes
  server.on("/", handleRoot);
  server.on("/walk", handleWalk);
  server.on("/turn", handleTurn);
  server.onNotFound(handleError);
  server.begin();
}

void loop(){
  server.handleClient();
}

// GET /
// Returns API info
// TODO
void handleRoot(){
  server.send(200, "application/json", "{\"message\":\"success!\"}");
}


void handleError(){
  
  String mthd = server.method() == HTTP_GET ? "GET" : "POST";
  String msg = "{";
  msg += "\n\"message\":\"";
  msg +=  "404: Something went wrong!\",";
  msg += "\n\"URI\":\"" + server.uri() + "\",";
  msg += "\n\"Method\":\"" + mthd + "\",";
  msg += "\n\"Args\":{";

  for(uint8_t i = 0; i < server.args(); i++){
    msg += "\n\"" + server.argName(i) + "\":\"" + server.arg(i)  + "\",";
  }

  msg += "\n}\n}";
  
  server.send(404, "application/json",  msg);
}

// POST /walk
// Direction:
// - Forward
// - Left
// - Right
// - Backward
// Duration
void handleWalk(){
  
  moveLeg(fl);
  moveLeg(br);
  moveLeg(fr);
  moveLeg(bl);

  moveBody();

  server.send(200, "application/json", "{\"message\":\"Success!\"}");
}


// POST /turn
// Direction
//  - Clockwise
//  - Counter-clockwise
// Duration
void handleTurn(){
  server.send(403, "application/json", "{\"message\":\"Not Implemented!\"}");
}

void center(){

  for (uint8_t curServo = 0; curServo < 7; curServo++){
    pwmDriver.setPWM(curServo, 0, RESET);
  }

  delay(300);
}


void moveLeg(uint8_t *leg){

  //move knee up
  pwmDriver.setPWM(leg[knee], 0, MAX);

  delay(300);

  //move hip forward
  pwmDriver.setPWM(leg[hip], 0, MAX);

  delay(300);

  //move knee down
  pwmDriver.setPWM(leg[knee], 0, MIN);
  
  delay(300);
}

void moveBody(){
  pwmDriver.setPWM(fl[hip], 0, MIN);
  pwmDriver.setPWM(bl[hip], 0, MIN);
  pwmDriver.setPWM(fr[hip], 0, MIN);
  pwmDriver.setPWM(fl[hip], 0, MIN);

  delay(300);
}

