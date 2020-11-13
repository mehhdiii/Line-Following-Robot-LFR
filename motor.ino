int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;

int PWM1 = 9;
int PWM2 = 10;
int test_x = 0;

void motor_start(int direction_r, int motor_number){
  // 1 for clockwise and 0 for anticlockwise
  if(motor_number==1 && direction_r == 1){
        digitalWrite(motor1pin1, HIGH);
        digitalWrite(motor1pin2, LOW);
    }
  else if (motor_number == 2 && direction_r==1){
          digitalWrite(motor2pin1, HIGH);
          digitalWrite(motor2pin2, LOW);
    }
  else if (motor_number == 1 && direction_r==-1){
          digitalWrite(motor1pin1, LOW);
          digitalWrite(motor1pin2, HIGH);
    }

   else if (motor_number == 2 && direction_r==-1){
          digitalWrite(motor2pin1, LOW);
          digitalWrite(motor2pin2, HIGH);
    }
  }

void motor_stop(int motor_number){
  if(motor_number==1){
        digitalWrite(motor1pin1, LOW);
        digitalWrite(motor1pin2, LOW);
    }
  else if (motor_number == 2){
          digitalWrite(motor2pin1, LOW);
          digitalWrite(motor2pin2, LOW);
  }
    
  }




void turn(int direction_r){
  //direction -1(left) or 1 (right) or 0(straight)

  int m1_leftspeed = 150; 
  int m2_leftspeed = 50; 

  int m1_rightspeed = 70; 

  int m2_rightspeed = 150; 
  
  if (direction_r==-1){
    analogWrite(PWM1, m1_leftspeed); 
    analogWrite(PWM2, m2_leftspeed); 
    }
  

  else if (direction_r==1){
    analogWrite(PWM1, m1_rightspeed); 
    analogWrite(PWM2, m2_rightspeed); 
    }
  else {
    analogWrite(PWM1, 255); 
    analogWrite(PWM2, 255); 
    }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
//  analogWrite(9, 150);
//  analogWrite(10, 60); 
//  analogWrite(PWM2, 255);
}

void loop() {
  // put your main code here, to run repeatedly:   
    motor_start(-1, 1); 
    motor_start(-1, 2);
    turn(-1); 
    delay(5000); 
}
