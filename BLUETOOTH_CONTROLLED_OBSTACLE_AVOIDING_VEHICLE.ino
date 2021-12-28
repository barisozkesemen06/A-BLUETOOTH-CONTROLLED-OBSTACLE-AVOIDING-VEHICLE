/*
 Project Name   : BLUETOOTH CONTROLLED OBSTACLE AVOIDING VEHICLE
 Revision Date  : 23.12.2021
 Author         : Barış Özkesemen

 Purpose        : To prevent bad consequences such as death and injury that may occur due to accidents,

 System Work    : Although it is Bluetooth controlled, it is ensured that it does not crash into obstacles with the help of the distance sensor
 and the buzzer that gives a warning sound in order to prevent bad results that may arise from accidents.
 */
// Definitions of Motor Pins
const int in1 = 6;  //Right engine forward
const int in2 = 9;  //Right engine backward 
const int in3 = 10; //Left engine backward
const int in4 = 11; //Left engine forward
//Definetion of Speed
int Vspeed= 255;
//Definetions of duration and distance
int duration;
unsigned int distance;
//Variable definition for Bluetooth 
int state;
void setup() {
  //Engines output pin modes
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //Distance sensors pin modes definition.
  pinMode(2, OUTPUT); // Trigger pin defined as OUTPUT.
  pinMode(3, INPUT);  // Echo pin defined as INPUT.
  Serial.begin(9600);

 //Buzzer pins
  pinMode(4, OUTPUT); // Buzzer pin defined as OUTPUT.
}

void loop() {

  if (digitalRead(state) == LOW) {
    state = 'S';
  }

  if (Serial.available() > 0) {
    state = Serial.read();
  }

//Distance calculation is done.
  digitalWrite(2, LOW); // LOW pulse to ensure a clean HIGH pulse.   
  delayMicroseconds(2);  // Wait for a short time
  digitalWrite(2, HIGH);// The sensor is triggered by a HIGH pulse.
  delayMicroseconds(20);  // The sensor is triggered 20 microseconds
  digitalWrite(2, LOW);  // LOW again 
  duration = pulseIn(3, HIGH); // It measures the time taken
  distance = (duration / 2) / 29.1; 
//We determine the vehicle speed.
  if (state == '0') {
    Vspeed = 0;
  }
  else if (state == '1') {
    Vspeed = 100;
  }
  else if (state == '2') {
    Vspeed = 180;
  }
  else if (state == '3') {
   Vspeed = 200;
  }
  else if (state == '4') {
   Vspeed = 255;
  }
  //We slow down the inner wheel by 50% for turns.
  int slow_wheel = Vspeed * 50 / 100;

Serial.print("Distance: ");
Serial.println( distance);

  //There is an obstacle, the vehicle stops
  if (distance <= 25) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(A5, 250);
    delay(100);
    analogWrite(A5, 2);
    delay(100);
  }
else if(distance<=40)
  {
analogWrite(A5, 250);
delay(200);
analogWrite(A5, 2);
delay(200);
  }
 
  /***********************forward direction****************************/
  else if (state == 'F') {
    analogWrite(in1, Vspeed);
    analogWrite(in2, 0);
    analogWrite(in3, 0);
    analogWrite(in4, Vspeed);
  

  }
  /***********************back direction****************************/
  else if (state == 'B') {
     analogWrite(in1, 0);
    analogWrite(in2, Vspeed);
    analogWrite(in3, Vspeed);
    analogWrite(in4, 0);
   
  }
  /***************************left*****************************/
else if (state == 'L') {
    analogWrite(in1, Vspeed);
    analogWrite(in2, 0);
    analogWrite(in3, Vspeed);
    analogWrite(in4, 0);
   
  }

  /***************************riht*****************************/
  else if (state == 'R') {
    analogWrite(in1, 0);
    analogWrite(in2, Vspeed);
    analogWrite(in3, 0 );
    analogWrite(in4, Vspeed);
   
  }

  /***************************left forward*****************************/
  else if (state == 'G') {
    analogWrite(in1, Vspeed);
    analogWrite(in2, 0);
    analogWrite(in3, slow_wheel);
    analogWrite(in4, 0);
   
  }
  /***************************right forward*****************************/
  else if (state == 'I') {
    analogWrite(in1, slow_wheel);
    analogWrite(in2, 0 );
    analogWrite(in3, Vspeed);
    analogWrite(in4, 0);
   
  }

  /***************************left back*****************************/
  else if (state == 'H') {
    analogWrite(in1, 0);
    analogWrite(in2, Vspeed);
    analogWrite(in3, 0);
    analogWrite(in4, slow_wheel);
    
  }
  /***************************right back*****************************/
  else if (state == 'J') {
    analogWrite(in1, 0);
    analogWrite(in2, slow_wheel);
    analogWrite(in3, 0);
    analogWrite(in4, Vspeed);
   
  }
  /***************************horn*****************************/
  else if (state == 'V') {
    analogWrite(A5, 250);
  }
  /***************************horn*****************************/
  else if (state == 'v') {
    analogWrite(A5,0);
  }

}
