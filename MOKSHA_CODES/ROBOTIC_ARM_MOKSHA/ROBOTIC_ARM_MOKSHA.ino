#include<SoftwareSerial.h>
#define xcord A0 // x coordinte of the analog joystick
#define ycord A1 // y coordinte of the analog joystick
#define xmid 511 // mid value of the x coordinate of the analog joystick
#define ymid 508 // mid value of the y coordinate of the analog joystick

unsigned const int lim = 8;

///////////////////////////////////ACTUATOR/////////////////////////////////////////
//1st actuator
#define enA 2
#define in1 3
#define in2 4
//2nd actuator
#define in3 5
#define in4 6
#define enB 7
//claw
#define enAc 10 
#define in1c 11
#define in2c 12
int state = 1;
int count = 0;

void changeState(){
  if(count%3 == 0){
    state = 1; //claw
  }
  else if(count%3 == 1){
    state = 2; //1st actuaror
  }
  else if(count%3 == 2){
    state = 3; //2nd actuator
  }
  count++;
}

void setupActuators(){
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void claw_close(int y){
 int ip = map(y , 0 , ymid-lim , 0 , 255);
 
 digitalWrite(in1c , LOW);
 digitalWrite(in2c , HIGH);
 analogWrite(enAc , 255-ip);
 Serial.print("check 1  ");
 Serial.println(255-ip);
}

void claw_open(int y){
 int ip = map(y , y+lim , 1023 , 0 , 255);
 
 digitalWrite(in2c , LOW);
 digitalWrite(in1c , HIGH);
 analogWrite(enAc , ip);
 Serial.print("check 2  ");
}

void acc_one_close(int pwmSignal){
  
 digitalWrite(in1 , LOW);
 digitalWrite(in2 , HIGH);
 analogWrite(enA , pwmSignal);
 Serial.print("check 3  ");
 Serial.println(pwmSignal);
}

void acc_one_open(int pwmSignal){
 digitalWrite(in2 , LOW);
 digitalWrite(in1 , HIGH);
 analogWrite(enA , pwmSignal);
 Serial.print("check 4  ");
}

void acc_two_close(int pwmSignal){
 digitalWrite(in3 , LOW);
 digitalWrite(in4 , HIGH);
 analogWrite(enB , pwmSignal);
 Serial.print("check 5  ");
}

void acc_two_open(int pwmSignal){
 digitalWrite(in4 , LOW);
 digitalWrite(in3 , HIGH);
 analogWrite(enB , pwmSignal);
 Serial.print("check 6  ");
}

void hold(){
  digitalWrite(in1 , LOW);
  digitalWrite(in2 , LOW);
  digitalWrite(in3 , LOW);
  digitalWrite(in4 , LOW);
  digitalWrite(in1c , LOW);
  digitalWrite(in2c , LOW);
  analogWrite(enA , 0);
  analogWrite(enB , 0);
  analogWrite(enAc , 0);
  Serial.print("check 7  ");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  pinMode(xcord , INPUT);
  pinMode(ycord , INPUT);
//  attachInterrupt(digitalPinToInterrupt(21),changeState, LOW);

  setupActuators();
}

void loop() {
  int xval = map(analogRead(xcord), 0 , 1023 , -255 , 255);
  int yval = map(analogRead(ycord), 0 , 1023 , -255 , 255);
  Serial.print("x");
  Serial.println(xval);
  Serial.print("y");
  Serial.println(yval);
  
//  if(state == 1 && ((yval<(ymid-lim)&&(xval<=(xmid+lim) && xval>=(xmid-lim)))) ){
//      claw_close(yval);
//    }
//    else if(state == 1 && (yval>(ymid+lim)&&(xval<=(xmid+lim)&&xval>=(xmid-lim))) ){
//      claw_open(yval);
//    }
//    else if(state == 2 && ((yval<(ymid-lim)&&(xval<=(xmid+lim) && xval>=(xmid-lim)))) ){
//      acc_one_close(yval);
//    }
//    else if(state == 2 && (yval>(ymid+lim)&&(xval<=(xmid+lim)&&xval>=(xmid-lim))) ){
//      acc_one_open(yval);
//    }
//    else if(state == 3 && ((yval<(ymid-lim)&&(xval<=(xmid+lim) && xval>=(xmid-lim)))) ){
//      acc_two_close(yval);
//    }
//    else if(state == 3 && (yval>(ymid+lim)&&(xval<=(xmid+lim)&&xval>=(xmid-lim)))) {
//      acc_one_open(yval);
//    }
//    else{
//      hold();
//    }

   if(xval<-20 || xval>20){
        if(xval > 20){
          acc_one_close(xval);
        }else if(xval < -20){
          acc_one_open((-1)*xval);
        }else{
          hold();
        }
   }
   else if(yval<-20 || yval>20){
      if(yval > 20){
          acc_two_close(yval);
        }else if(yval < -20){
          acc_two_open((-1)*yval);
        }else{
          hold();
        }
   }
   else{
    hold();
   }
   
  
}
