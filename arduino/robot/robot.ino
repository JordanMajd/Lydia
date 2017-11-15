#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Adafruit_PWMServoDriver.h>

const char* ssid = "...";
const char* pass = "...";

enum w_direction {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

enum t_direction {
  CLOCKWISE,
  COUNTER
};

struct leg {
  uint8_t hip_pin;
  uint8_t knee_pin;
  uint16_t hip_forward;
  uint16_t hip_backward;
  uint16_t knee_up;
  uint16_t knee_down;
};

#define PMIN 150
#define PMAX 500
#define dlen 500

//black screws = front
struct leg fl {5, 4, PMAX, PMIN, PMIN, PMAX};
struct leg fr {6, 7, PMIN, PMAX, PMAX, PMIN};
struct leg bl {2, 3, PMAX, PMIN, PMAX, PMIN};
struct leg br {1, 0, PMIN, PMAX, PMIN, PMAX};


ESP8266WebServer server(80);
Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver();

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

/*
 *  HTTP  Methods
 */

// GET /
void handleRoot(){
  server.send(200, "application/json", "{\"message\":\"success!\"}");
}

void handleError(){
  
  String mthd = server.method() == HTTP_GET ? "GET" : "POST";
  String msg = "{";
  msg += "\n\"message\":\"";
  msg +=  "404: Invalid Request:\",";
  msg += "\n\"URI\":\"" + server.uri() + "\",";
  msg += "\n\"Method\":\"" + mthd + "\",";
  msg += "\n\"Args\":{";

  for(uint8_t i = 0; i < server.args(); i++){
    msg += "\n\"" + server.argName(i) + "\":\"" + server.arg(i)  + "\",";
  }

  msg += "\n}\n}";
  
  server.send(404, "application/json",  msg);
}

// POST /walk?direction=forward&duration=3000
void handleWalk(){

  if(isValid()) {
    
   String direction = server.arg("direction");
   uint16_t  duration = server.arg("duration").toInt();
   
    walk(direction, duration);
    
    server.send(200, "application/json", "{\"message\":\"Success!\"}");
    
  } else {
    handleError();
  }
}


// POST /turn?direction=clockwise&duration=3000
void handleTurn(){

  if(isValid()){

   String direction = server.arg("direction");
   uint16_t  duration = server.arg("duration").toInt();
   
    turn(direction, duration);
    
    server.send(200, "application/json", "{\"message\":\"Success!\"}");
  } else {
    handleError();
  }
}


bool isValid(){

  bool isValid = true;

  isValid = server.args() == 2;
  isValid = server.arg("direction").length() > 0;
  isValid = server.arg("duration").length() > 0;

  return isValid;
}


/*
 *  Robot  Control Methods
 */

void walk( String direction, int duration ){

  Serial.println("Walk: " + direction + ", " + duration);

  moveLeg(fl);
  moveLeg(br);
  moveLeg(fr);
  moveLeg(bl);

  moveBody();
}

void turn(String direction, int duration){
  
  Serial.println("Turn: " + direction + ", " + duration);
}


void moveLeg(leg l){

  //move knee up
  pwmDriver.setPWM(l.knee_pin, 0, l.knee_up);

  delay(dlen);

  //move hip forward
  pwmDriver.setPWM(l.hip_pin, 0, l.hip_forward);

  delay(dlen);

  //move knee down
  pwmDriver.setPWM(l.knee_pin, 0, l.knee_down);
  
  delay(dlen);
}

void moveBody(){
  pwmDriver.setPWM(fl.hip_pin, 0, fl.hip_backward);
  pwmDriver.setPWM(fr.hip_pin, 0, fr.hip_backward);
  pwmDriver.setPWM(bl.hip_pin, 0, bl.hip_backward);
  pwmDriver.setPWM(br.hip_pin, 0, br.hip_backward);

  delay(dlen);
}

void calibrateForward(){
  pwmDriver.setPWM(fl.hip_pin, 0, fl.hip_forward);
  pwmDriver.setPWM(fr.hip_pin, 0, fr.hip_forward);
  pwmDriver.setPWM(bl.hip_pin, 0, bl.hip_forward);
  pwmDriver.setPWM(br.hip_pin, 0, br.hip_forward);
}

void calibrateUp(){
  pwmDriver.setPWM(fl.knee_pin, 0, fl.knee_up);
  pwmDriver.setPWM(fr.knee_pin, 0, fr.knee_up);
  pwmDriver.setPWM(bl.knee_pin, 0, bl.knee_up);
  pwmDriver.setPWM(br.knee_pin, 0, br.knee_up);
}


