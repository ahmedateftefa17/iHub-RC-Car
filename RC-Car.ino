// Constants
// Motors
const int ENA = 2; // Control speed of Right Motor
const int MIN1 = 31; // Right Yellow
const int MIN2 = 32; // Right Grey
const int ENB = 3; // Control speed of Left Motor
const int MIN3 = 33; // Left Yellow
const int MIN4 = 34; // Left Grey
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// Variables
char rBluetoothChar;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// Functions
void setMove(int MIN1D, int MIN2D, int MIN3D, int MIN4D){
  digitalWrite(MIN1, MIN1D);
  digitalWrite(MIN2, MIN2D);
  digitalWrite(MIN3, MIN3D);
  digitalWrite(MIN4, MIN4D);
  //Serial.println("Motor Directions is ");
  //Serial.println(MIN1D);
  //Serial.println(MIN2D);
  //Serial.println(MIN3D);
  //Serial.println(MIN4D);
  //Serial.println("------------------------");
}
void setMotorSpeed(int MotorControlPin, char receivedChar){
  if(receivedChar == 'q'){
    analogWrite(MotorControlPin, 255);
    //Serial.println("Motor Speed is Changed to 255");
  }
  else {
    analogWrite(MotorControlPin, ((int(receivedChar) - 48) * 255) / 10);
    //Serial.print("Motor Speed is Changed to ");
    //Serial.println(((int(receivedChar) - 48) * 255) / 10);
  }
  //Serial.println("------------------------");
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// Start
void setup() {
  // Setup Pins Mode
  pinMode(ENA, OUTPUT);
  pinMode(MIN1, OUTPUT);
  pinMode(MIN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(MIN3, OUTPUT);
  pinMode(MIN4, OUTPUT);
  // pinMode(13, INPUT);
  // pinMode(trigPin, OUTPUT);
  // pinMode(echoPin, INPUT);
  // pinMode(lineFollowerRightPin, INPUT);
  // pinMode(lineFollowerLeftPin, INPUT);
  // Start Serial
  Serial.begin(9600);
  // Set Max speed as default... Run Once! (first time ONLY)
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  // setMove(1, 1, 1, 1);
}

void loop() {
  // Check if char recieved?
  if(Serial.available()){
    // Get received Char
    rBluetoothChar = Serial.read();
    Serial.print("Received Char is => ");
    Serial.println(rBluetoothChar);
    Serial.println("------------------------");
    if(rBluetoothChar == 'F'){
      // Move forward
      setMove(1, 0, 0, 1);
    } else if(rBluetoothChar == 'B'){
      // Move backward
      setMove(0, 1, 1, 0);
    } else if(rBluetoothChar == 'L'){
      // Rotate Left
      setMove(1, 0, 1, 0);
    } else if(rBluetoothChar == 'R'){
      // Rotate Right
      setMove(0, 1, 0, 1);
    } else if(rBluetoothChar == 'J'){
      // Turn Back Right
      setMove(0, 1, 0, 0);
    } else if(rBluetoothChar == 'H'){
      // Turn Back Left
      setMove(0, 0, 1, 0);
    } else if(rBluetoothChar == 'I'){
      // Turn Forward Right
      setMove(0, 0, 0, 1);
    } else if(rBluetoothChar == 'G'){
      // Turn Forward Left
      setMove(1, 0, 0, 0);
    } else if(rBluetoothChar == 'S'){
      setMove(0, 0, 0, 0);
    } else if(rBluetoothChar == 'V'){
      // Line follower
      do{
        lineFollowerRightOUT = analogRead(lineFollowerRightPin);
        lineFollowerLeftOUT  = analogRead(lineFollowerLeftPin);
        if(lineFollowerRightOUT > 700 && lineFollowerLeftOUT < 700 ){
          // Turn Forward Right
          setMove(0, 1, 0, 0);
        }
        else if(lineFollowerRightOUT < 700 && lineFollowerLeftOUT > 700 ){
          // Turn Forward Left
          setMove(0, 0, 1, 0);
        }
        else if(lineFollowerRightOUT > 700 && lineFollowerLeftOUT > 700){
          // Stop Car
          setMove(0, 0, 0, 0);
          delay(5000);
          // Move forward
          setMove(0, 1, 1, 0);
          delay(1000);
        }
        else {
          // Move forward
          setMove(0, 1, 1, 0);
        }
        rBluetoothChar = Serial.read();
      } while(rBluetoothChar != 'v');
      // Stop Auto
      setMove(0, 0, 0, 0);
    } else if(rBluetoothChar == 'U'){
      // Do nothing yet!
    } else if(rBluetoothChar == 'u'){
      // Do nothing yet!
    } else if(rBluetoothChar == 'W'){
      // Do nothing yet!
    } else if(rBluetoothChar == 'w'){
      // Do nothing yet!
    } else if(rBluetoothChar == 'X'){
      // Auto Ultra Sonic
      do{
        distanceInCm = getDistanceInCm();
        if(distanceInCm < 15){
          setMotorSpeed(ENA, 'q');
          setMotorSpeed(ENB, 'q');
          // Rotate Right
          setMove(0, 1, 0, 1);
        }
        else if(distanceInCm < 30){
          setMotorSpeed(ENA, '3');
          setMotorSpeed(ENB, '3');
        }
        else if(distanceInCm < 60){
          setMotorSpeed(ENA, '6');
          setMotorSpeed(ENB, '6');
        }
        else {
          // Move Forward
          setMove(0, 1, 1, 0);
        }
        delay(50);
        rBluetoothChar = Serial.read();
      } while(rBluetoothChar != 'x');
      // Stop Auto
      setMove(0, 0, 0, 0);
    } else if(rBluetoothChar == 'D'){
      // Stop Every thing
      setMove(0, 0, 0, 0);
    } else {
      setMotorSpeed(ENA, rBluetoothChar);
      setMotorSpeed(ENB, rBluetoothChar);
    }
  } else {
    // when not reciving any thing!
    // Stop any Move!
    setMove(0, 0, 0, 0);
  }
}
