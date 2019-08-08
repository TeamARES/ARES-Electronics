String data = "";
String serialData = "";
int motor;
int PWM[6];

#define RC_CH1  0
#define RC_CH2  1
#define RC_CH3  2
#define RC_CH4  3
#define RC_CH5  4 
#define RC_CH6  5

////////// VARIABLES FOR IBT2 //////////////////////
//Left front
#define RPWM_PIN_FRONT_LEFT 12 // Arduino PWM output pin 6; connect to IBT-2 pin 1 (RPWM)
#define LPWM_PIN_FRONT_LEFT 13 // Arduino PWM output pin 2; connect to IBT-2 pin 2 (LPWM)
//Right Front
#define RPWM_PIN_FRONT_RIGHT 11 // Arduino PWM output pin 9; connect to IBT-2 pin 1 (RPWM)
#define LPWM_PIN_FRONT_RIGHT 10 // Arduino PWM output pin 5; connect to IBT-2 pin 2 (LPWM)

//Left Rear
#define RPWM_PIN_REAR_LEFT 12 // Arduino PWM output pin 6; connect to IBT-2 pin 1 (RPWM)
#define LPWM_PIN_REAR_LEFT 13 // Arduino PWM output pin 2; connect to IBT-2 pin 2 (LPWM)
//Right Rear
#define RPWM_PIN_REAR_RIGHT 8 // Arduino PWM output pin 9; connect to IBT-2 pin 1 (RPWM)
#define LPWM_PIN_REAR_RIGHT 9// Arduino PWM output pin 5; connect to IBT-2 pin 2 (LPWM)

///////////////// Direction of DRIVING //////////////////////////////////////////////
#define FORWARD 0
#define BACKWARD 1

#define LEFT 0
#define RIGHT 1

int driveDirFB = -1;  //This is direction if rover is moving FORWARD or BACKWARD
int driveDirRL = -1;  //This is direction if rover is moving RIGHT or LEFT


////////////////////////////////////////////////////////////
////////////////////////////// SETUP //////////////////////////////
////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  motor = 0;
  for(int i=0; i<6; i++){
    PWM[i] = 0;
  }
}

////////////////////////////////////////////////////////////
////////////////////////////// LOOP //////////////////////////////
////////////////////////////////////////////////////////////
void loop() {
  //Loop: Subsection 1:
  ///////////This part read from Serial monitor///////////////////
  ///////////and store data in required variables///////////////////
  while(Serial.available() == 0){
      //Do nothing
  }
  serialData = Serial.readString();

  int posl = 0;
  int posr = 0;
  
  posr = serialData.indexOf(',',posl);
  data = serialData.substring(posl,posr);
  motor = data.toInt();

  posl = posr + 1;
  posr = serialData.indexOf(',',posl);
  data = serialData.substring(posl,posr);
  PWM[0] = data.toInt();

  posl = posr + 1;
  posr = serialData.indexOf(',',posl);
  data = serialData.substring(posl,posr);
  PWM[1] = data.toInt();

  posl = posr + 1;
  posr = serialData.indexOf(',',posl);
  data = serialData.substring(posl,posr);
  PWM[2] = data.toInt();

  posl = posr + 1;
  posr = serialData.indexOf(',',posl);
  data = serialData.substring(posl,posr);
  PWM[3] = data.toInt();
  
  posl = posr + 1;
  posr = serialData.indexOf(',',posl);
  data = serialData.substring(posl,posr);
  PWM[4] = data.toInt();
  
  posl = posr + 1;
  data = serialData.substring(posl);
  PWM[5] = data.toInt();
  
  
  if(motor == 1){
    Serial.println("P1:"+String(motor)+":"+String(PWM[0])+":"+String(PWM[1])+":"+String(PWM[2])+":"+String(PWM[3])+":"+String(PWM[4])+":"+String(PWM[5]));
  }else{
    Serial.println("A1:"+String(motor)+":"+String(PWM[0])+":"+String(PWM[1])+":"+String(PWM[2])+":"+String(PWM[3])+":"+String(PWM[4])+":"+String(PWM[5]));
  }

  //Loop: Subsection 1 ENDS:///////////////////////////////////////////////////

  
  
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// HELPING FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
 * Function : setupIBT2Pins
 * Role     : To set all pins used for IBT2 as OUTPUT
 * 
 */
void setupIBT2Pins(){
  Serial.println("========== SETTING IBT2 PINS =============");
  pinMode(RPWM_PIN_FRONT_LEFT, OUTPUT);
  pinMode(LPWM_PIN_FRONT_LEFT, OUTPUT);
  
  pinMode(RPWM_PIN_FRONT_RIGHT, OUTPUT);
  pinMode(LPWM_PIN_FRONT_RIGHT, OUTPUT);

  pinMode(RPWM_PIN_REAR_LEFT, OUTPUT);
  pinMode(LPWM_PIN_REAR_LEFT, OUTPUT);
  
  pinMode(RPWM_PIN_REAR_RIGHT, OUTPUT);
  pinMode(LPWM_PIN_REAR_RIGHT, OUTPUT);

  analogWrite(RPWM_PIN_FRONT_LEFT, 0);
  analogWrite(LPWM_PIN_FRONT_LEFT, 0);
  
  analogWrite(RPWM_PIN_FRONT_RIGHT, 0);
  analogWrite(LPWM_PIN_FRONT_RIGHT, 0);

  analogWrite(RPWM_PIN_REAR_LEFT, 0);
  analogWrite(LPWM_PIN_REAR_LEFT, 0);
  
  analogWrite(RPWM_PIN_REAR_RIGHT, 0);
  analogWrite(LPWM_PIN_REAR_RIGHT, 0);
  
  Serial.println("========== SETTING OVER =============");
}

void driveForward(int pwmSignal1, int pwmSignal2, int pwmSignal3, int pwmSignal4){
  Serial.println(String(RPWM_PIN_FRONT_LEFT)+" : "+pwmSignal1);
  Serial.println(String(RPWM_PIN_FRONT_RIGHT)+" : "+pwmSignal2);
  Serial.println(String(RPWM_PIN_REAR_LEFT)+" : "+pwmSignal3);
  Serial.println(String(RPWM_PIN_REAR_RIGHT)+" : "+pwmSignal4);
  
  analogWrite(RPWM_PIN_FRONT_LEFT, pwmSignal1);
  analogWrite(LPWM_PIN_FRONT_LEFT, 0);

  analogWrite(RPWM_PIN_FRONT_RIGHT, pwmSignal2);
  analogWrite(LPWM_PIN_FRONT_RIGHT, 0);

  analogWrite(RPWM_PIN_REAR_LEFT, pwmSignal3);
  analogWrite(LPWM_PIN_REAR_LEFT, 0);

  analogWrite(RPWM_PIN_REAR_RIGHT, pwmSignal4);
  analogWrite(LPWM_PIN_REAR_RIGHT, 0);
}

void driveBackward(int pwmSignal1, int pwmSignal2, int pwmSignal3, int pwmSignal4){
  
  analogWrite(RPWM_PIN_FRONT_LEFT, 0);
  analogWrite(LPWM_PIN_FRONT_LEFT, pwmSignal1);

  analogWrite(RPWM_PIN_FRONT_RIGHT, 0);
  analogWrite(LPWM_PIN_FRONT_RIGHT, pwmSignal2);

  analogWrite(RPWM_PIN_REAR_LEFT, 0);
  analogWrite(LPWM_PIN_REAR_LEFT, pwmSignal3);

  analogWrite(RPWM_PIN_REAR_RIGHT, 0);
  analogWrite(LPWM_PIN_REAR_RIGHT, pwmSignal4);
}

void driveRight(int pwmSignal1, int pwmSignal2, int pwmSignal3, int pwmSignal4){
  analogWrite(RPWM_PIN_FRONT_LEFT, pwmSignal1);
  analogWrite(LPWM_PIN_FRONT_LEFT, 0);

  analogWrite(RPWM_PIN_FRONT_RIGHT, 0);
  analogWrite(LPWM_PIN_FRONT_RIGHT, pwmSignal2);

  analogWrite(RPWM_PIN_REAR_LEFT, pwmSignal3);
  analogWrite(LPWM_PIN_REAR_LEFT, 0);

  analogWrite(RPWM_PIN_REAR_RIGHT, 0);
  analogWrite(LPWM_PIN_REAR_RIGHT, pwmSignal4);
}

void driveLeft(int pwmSignal1, int pwmSignal2, int pwmSignal3, int pwmSignal4){
  analogWrite(RPWM_PIN_FRONT_LEFT, 0);
  analogWrite(LPWM_PIN_FRONT_LEFT, pwmSignal1);

  analogWrite(RPWM_PIN_FRONT_RIGHT, pwmSignal2);
  analogWrite(LPWM_PIN_FRONT_RIGHT, 0);

  analogWrite(RPWM_PIN_REAR_LEFT, 0);
  analogWrite(LPWM_PIN_REAR_LEFT, pwmSignal3);

  analogWrite(RPWM_PIN_REAR_RIGHT, pwmSignal4);
  analogWrite(LPWM_PIN_REAR_RIGHT, 0);
}

void stopDrive(){
  analogWrite(RPWM_PIN_FRONT_LEFT, 0);
  analogWrite(LPWM_PIN_FRONT_LEFT, 0);

  analogWrite(RPWM_PIN_FRONT_RIGHT, 0);
  analogWrite(LPWM_PIN_FRONT_RIGHT, 0);

  analogWrite(RPWM_PIN_REAR_LEFT, 0);
  analogWrite(LPWM_PIN_REAR_LEFT, 0);

  analogWrite(RPWM_PIN_REAR_RIGHT, 0);
  analogWrite(LPWM_PIN_REAR_RIGHT, 0);
}

//////////////////// MAIN DRIVER FUNCTION //////////////////
void drive2(int forBackWardChannel, int leftRightChannel){
  int motorSpeedLeft = 0;
  int motorSpeedRight = 0;
  int driveDir = -1;                                      //0--> Forward, 1 ---> Backward
  
  if(PWM[forBackWardChannel] >= 10){                  //Drive Forward
     motorSpeedLeft = PWM[forBackWardChannel];
     motorSpeedRight = PWM[forBackWardChannel];
     driveDir = 0;
  }else if(PWM[forBackWardChannel] < -10){           //Drive Backward
     motorSpeedLeft = (-1)*PWM[forBackWardChannel];
     motorSpeedRight = (-1)*PWM[forBackWardChannel];
     driveDir = 1;
  }else{
    driveDir = -1;
  }
  
  Serial.print("drivedir = ");Serial.println(driveDir);

  if(PWM[leftRightChannel] > 20 || PWM[leftRightChannel] < -20){
    
    if(PWM[leftRightChannel] >= 20){                        //Drive Right:
      motorSpeedLeft += PWM[leftRightChannel];
      motorSpeedRight -= PWM[leftRightChannel];
      if (motorSpeedRight < 0) {
        motorSpeedRight = 0;
      }
      if (motorSpeedLeft > 255) {
        motorSpeedLeft = 255;
      }
    }else if(PWM[leftRightChannel] < -20){
      motorSpeedLeft -= (-1)*PWM[leftRightChannel];
      motorSpeedRight +=(-1)*PWM[leftRightChannel];
      if (motorSpeedLeft < 0) {
        motorSpeedLeft = 0;
      }
      if (motorSpeedRight > 255) {
        motorSpeedRight = 255;
      }
      
    }

    
  }

  if(driveDir == 0){
    Serial.print("Forward: ");Serial.print(motorSpeedLeft);Serial.print(" ");Serial.println(motorSpeedRight);
 
    driveForward(motorSpeedLeft,motorSpeedRight,motorSpeedLeft ,motorSpeedRight);
  
  }
  else if(driveDir == 1){
    Serial.print("Backward: ");Serial.print(motorSpeedLeft);Serial.print(" ");Serial.println(motorSpeedRight);
    
    driveBackward(motorSpeedLeft,motorSpeedRight,motorSpeedLeft ,motorSpeedRight);
  
  }else if(driveDir == -1){
    Serial.println("just leftRight: ");
    if(PWM[leftRightChannel] > 50 || PWM[leftRightChannel] < -50){
      if(PWM[leftRightChannel] >= 50){
        Serial.print("left");

        int driveLeftSignal = PWM[leftRightChannel] - 50;
        driveLeft(driveLeftSignal,driveLeftSignal,driveLeftSignal,driveLeftSignal);
        
      }else if(PWM[leftRightChannel] < -50){
        Serial.print("right");

        int driveRightSignal = ((-1)*PWM[leftRightChannel])-50;
        driveRight(driveRightSignal,driveRightSignal,driveRightSignal,driveRightSignal);
        
      }else{
        stopDrive();
      }
    }else{
      stopDrive();
    }
  }else{
    stopDrive();
  }
  
}
