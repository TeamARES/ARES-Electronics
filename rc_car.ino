#define inl_f 2 // connect in3 
#define inl_b 3 // connect in4 
#define inr_f 12 // connect in1
#define inr_b 13 // connect in2
#define enl 5 // connect enB 
#define enr 6 // connect enA 

void setup()
{
 // set all the motor control pins to outputs
 pinMode(enl, OUTPUT);
 pinMode(enr, OUTPUT);
 pinMode(inl_f, OUTPUT);
 pinMode(inl_b, OUTPUT);
 pinMode(inr_f, OUTPUT);
 pinMode(inr_b, OUTPUT);

 digitalWrite(inl_f , LOW);
 digitalWrite(inr_f , LOW);
 digitalWrite(inl_b , LOW);
 digitalWrite(inr_b , LOW);
 
 Serial.begin(9600);
}

void backward(){
 
 digitalWrite(inl_f , LOW);
 digitalWrite(inr_f , LOW);
 digitalWrite(inl_b , HIGH);
 digitalWrite(inr_b , HIGH);
 //digitalWrite(enl, HIGH);
 //digitalWrite(enr, HIGH);
 analogWrite(enl , 100);
 analogWrite(enr , 100);
 
 Serial.println("backward");
}

void forward(){
 
 digitalWrite(inl_b , LOW);
 digitalWrite(inr_b , LOW);
 digitalWrite(inl_f , HIGH);
 digitalWrite(inr_f , HIGH);
 
 analogWrite(enl , 100);
 analogWrite(enr , 100);
 
 Serial.println("forward");
}

void left(){
   
 digitalWrite(inl_f , HIGH);
 digitalWrite(inl_b , LOW);
 digitalWrite(inr_b , HIGH);
 digitalWrite(inr_f , LOW);
 
 analogWrite(enl , 150);
 analogWrite(enr , 150);
 
 Serial.println("left");
}

void right(){
 
 digitalWrite(inl_b , HIGH);
 digitalWrite(inl_f , LOW);
 digitalWrite(inr_f , HIGH);
 digitalWrite(inr_b , LOW);
 
 analogWrite(enl , 150);
 analogWrite(enr , 150);
 
 Serial.println("right");
}

void hold(){
 digitalWrite(inl_f , LOW);
 digitalWrite(inr_f , LOW);
 digitalWrite(inl_b , LOW);
 digitalWrite(inr_b , LOW);
 
 analogWrite(enl , 0);
 analogWrite(enr , 0); 
 
 Serial.println("HOLD");
}
void loop()
{
  while(Serial.available()>=1){
    int x = Serial.read();
    Serial.print("command = ");
    Serial.print(x);
    switch (x){
    case '1':{
      backward();
      break;
    }
    case '2':{
      forward();
      break;
    }
    case '3':{
      right();
      break;
    }
    case '4':{
      left();
      break;
    }
    case '5':{
      hold();
      break;
    }
  }
  }
}
