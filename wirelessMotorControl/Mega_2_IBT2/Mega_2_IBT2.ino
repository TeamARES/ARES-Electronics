#define RC_NUM_CHANNELS  5
int PWM[RC_NUM_CHANNELS];
//Following are indexes are for above Array:
#define RC_CH1  0
#define RC_CH2  1
#define RC_CH3  2
#define RC_CH4  3
#define RC_CH5  4 
#define RC_CH6  5

int motorOrARM = 0;  //0 FOR MOTOR AND 1 FOR ARM

////////// VARIABLES FOR IBT2 //////////////////////
//Left front
#define RPWM_PIN_FRONT_LEFT 8 // Arduino PWM output pin 6; connect to IBT-2 pin 1 (RPWM)
#define LPWM_PIN_FRONT_LEFT 9 // Arduino PWM output pin 2; connect to IBT-2 pin 2 (LPWM)
//Right Front
#define RPWM_PIN_FRONT_RIGHT 12 // Arduino PWM output pin 9; connect to IBT-2 pin 1 (RPWM)
#define LPWM_PIN_FRONT_RIGHT 13 // Arduino PWM output pin 5; connect to IBT-2 pin 2 (LPWM)

//Left Rear
#define RPWM_PIN_REAR_LEFT 10 // Arduino PWM output pin 6; connect to IBT-2 pin 1 (RPWM)
#define LPWM_PIN_REAR_LEFT 11 // Arduino PWM output pin 2; connect to IBT-2 pin 2 (LPWM)
//Right Rear
#define RPWM_PIN_REAR_RIGHT 44 // Arduino PWM output pin 9; connect to IBT-2 pin 1 (RPWM)
#define LPWM_PIN_REAR_RIGHT 45 // Arduino PWM output pin 5; connect to IBT-2 pin 2 (LPWM)

///////////////// Direction of DRIVING //////////////////////////////////////////////
#define FORWARD 0
#define BACKWARD 1

#define LEFT 0
#define RIGHT 1

int driveDirFB = -1;  //This is direction if rover is moving FORWARD or BACKWARD
int driveDirRL = -1;  //This is direction if rover is moving RIGHT or LEFT


////////////////////////////////////////////////////////////////////////////////
///////////////////SET UP and LOOP///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  setupIBT2Pins();

  
}



void loop() {
 readSerialData();
}


//Data fromat = B’0,10,20,30,40,50,60’
void readSerialData(){
    String data = "";
    while(Serial.available() == 0){
      //Do nothing
    }
    data = Serial.readString();
    
    Serial.println(data.indexOf(','));
    Serial.println(data.charAt(1));
    Serial.println(data.charAt(2));
    Serial.println(data.charAt(3));
    Serial.println(data.charAt(4));
    Serial.println(data.charAt(5));
    Serial.println(data.charAt(6));
    Serial.println(data.charAt(7));
    
    Serial.println(data.length());

//    data = data.substring(4,data.length()-4);
    Serial.println(data);
    Serial.println("-------");
    String text = data;
    Serial.println(text);
    Serial.println("-------");
    Serial.println(text.charAt(0));
    Serial.println(text.charAt(1));
    Serial.println(text.charAt(3));
    Serial.println(text.charAt(4));
    Serial.println(text.charAt(5));
    Serial.println(text.charAt(6));
//    Serial.println(data.charAt(7));
    
    bool stored = storeDataInVariables(data);
//    Serial.println("WE GET FALSE : "+stored);

    
    
//    Serial.print(String(motorOrARM)+",");
//    for(int i=0; i<6;i++){
//      Serial.print(String(PWM[i])+",");
//    }
//    Serial.println(" ");
 

//  Serial.flush();
//  Serial.println("FLUSHIN DATA");
  
}
////////////////////////////////////////////////////////////////////////////////
/////////////////////////// HELPING FUNCTIONS //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*
 * Function : storeDataInVariables
 * Role     : To store variables in PWM[] and motorOrARM
 */
bool storeDataInVariables(String text){
  String text1 = text;
  Serial.println(text.indexOf(','));
  Serial.println(text);
  
  int posl = 0;
  Serial.println(posl);
  Serial.println(text.charAt(1));
  int posr = text.indexOf(',',posl);
  
  Serial.println("\n\n POSR = "+posr);
  
  //We will check if posr exist or not.It is does not exist then nothing was saved in backup files
  if(posr < 0){
    return false;
  }
  
  String data = text.substring(posl,posr);
  motorOrARM = data.toInt();

  Serial.println("\nmotorOrARM = "+motorOrARM);
  
  //Now storing values in PWM[RC_NUM_CHANNELS]
  for(int i=RC_CH1; i<=RC_CH5;i++){
    //Second Field is ground altitude from bmp:
    posl = posr+1;
    posr = text.indexOf(",",posl);
    if(posr == -1) return false;

    data = text.substring(posl,posr);
    PWM[i] = data.toInt();
  }
  
  int lastPos = text.lastIndexOf(",");
  data = text.substring(lastPos+1,text.length());
  PWM[RC_CH6] = data.toInt();

  return true;
}

/*
 * Function : setupIBT2Pins
 * Role     : To set all pins used for IBT2 as OUTPUT
 * 
 */
void setupIBT2Pins(){
  pinMode(RPWM_PIN_FRONT_LEFT, OUTPUT);
  pinMode(LPWM_PIN_FRONT_LEFT, OUTPUT);
  
  pinMode(RPWM_PIN_FRONT_RIGHT, OUTPUT);
  pinMode(LPWM_PIN_FRONT_RIGHT, OUTPUT);

  pinMode(RPWM_PIN_REAR_LEFT, OUTPUT);
  pinMode(LPWM_PIN_REAR_LEFT, OUTPUT);
  
  pinMode(RPWM_PIN_REAR_RIGHT, OUTPUT);
  pinMode(LPWM_PIN_REAR_RIGHT, OUTPUT);
}

/*
 * Function : DRINVING FUNCTIONS
 * Role     : FRONT, BACK, LEFT, RIGHT Functions for MEGA
 */
void driveForward(int pwmSignal1, int pwmSignal2, int pwmSignal3, int pwmSignal4){
  
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
