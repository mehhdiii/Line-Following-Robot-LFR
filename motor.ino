// Include the Servo library 
#include <Servo.h> 

//MOTOR DEFINITIONS
int EnA = 4;   //RIGHT MOTOR PWM PIN
int EnB = 5;  //LEFT MOTOR PWM PIN
int INT_1 = 2; //KEEP LOW TO MOVE FORWARD
int INT_2 = 3; //KEEP HIGH TO MOVE FORWARD
int INT_3 = 9; //KEEP LOW TO MOVE FORWARD
int INT_4 = 10; //KEEP HIGH TO MOVE FORWARD

//SENSOR DEFINITIONS
int S1 = A0; //LEFT MOST 
int S2 = A1; 
int S3 = A2; //CENTER 
int S4 = A3; 
int S5 = A4; //RIGHT MOST

// SERVO DEFINITIONS
int servo1Pin = 6; 
int servo2Pin = 7; 

//BLUETOOTH DEFINITIONS
const char START_FLAG = 's';
const char STOP_FLAG = 'S'; 
char received_char; 
bool bluetooth_en_flag = 0; 


//VARIABLE DEFINITIONS

//MOTOR VARIABLES

//FASTEST SPEED POSSIBLE
//int MAX_EnA =255; //CALIBRATED MAX SPEED FOR RIGHT MOTOR
//int MAX_EnB = 210;  //CALIBRATED MAX SPEED FOR LEFT MOTOR

////CALIBRATED SPEED FOR NORMAL OPERATION 
//int MAX_EnA =200; //CALIBRATED MAX SPEED FOR RIGHT MOTOR
//int MAX_EnB = 165;  //CALIBRATED MAX SPEED FOR LEFT MOTOR

//CALIBRATED SPEED FOR NORMAL OPERATION 
int MAX_EnA =125; //CALIBRATED MAX SPEED FOR RIGHT MOTOR
int MAX_EnB = 101;  //CALIBRATED MAX SPEED FOR LEFT MOTOR


//CALIBRATED SPEED FOR MAKING A LIGHT LEFT/RIGHT ADJUSTMENT
//LIGHT RIGHT TURN
int RIGHT_TURN_EnA_LIGHT = 115;
int RIGHT_TURN_EnB_LIGHT = 101;  

//LIGHT LEFT TURN
int LEFT_TURN_EnA_LIGHT = 125;   
int LEFT_TURN_EnB_LIGHT = 85;

//CALIBRATED SPEED FOR MAKING A HARD LEFT/RIGHT ADJUSTMENT 
//HARD RIGHT TURN 
int RIGHT_TURN_EnA_HARD = 100;
int RIGHT_TURN_EnB_HARD = 105;  

//HARD LEFT TURN 
int LEFT_TURN_EnA_HARD = 145;
int LEFT_TURN_EnB_HARD = 75; 


//SENSOR VARIABLES

const int black = 0; 
const int white = 1; 
int Value_Sn[5]; 


// MAP VARIABLES
int max_count = 3; //THE NUMBER OF INTERSECTIONS THAT ARE DESIRED TO BE COUNTED
int count=0; //COUNTER VARIABLE THAT COUNTS THE INTERESECTIONS; RESETTED TO 0 WHEN THE STRAIGHT LINE DESTINATION IS REACHED
bool flag_count = 0; //FLAG WHICH DETECTS THE STARTING OF AN INTERSECTION

//CASES VARIABLES AND CONDITIONS FOR MAP NAVIGATION: 
int first_straight_done=0; 
int first_turn_done = 0;
int second_straight_done = 0; 
int first_reverse_done = 0; 
int second_turn_done = 0; 
int third_straight_done = 0; 

// SERVO OBJECTS 
Servo Servo1;
Servo Servo2;


//HELPER FUNCTIONS
void motor_forward(){
  //RUN MOTORS FORWARD
  digitalWrite(INT_1, LOW);  
  digitalWrite(INT_2, HIGH);
  digitalWrite(INT_3, LOW);
  digitalWrite(INT_4, HIGH);

  
  }
void motor_backward(){
  //RUN MOTORS BACKWARD
  digitalWrite(INT_1, HIGH); 
  digitalWrite(INT_2, LOW);
  digitalWrite(INT_3, HIGH);
  digitalWrite(INT_4, LOW);
  
  }

void motor_stop(){
    digitalWrite(INT_1, LOW); 
    digitalWrite(INT_2, LOW);
    digitalWrite(INT_3, LOW);
    digitalWrite(INT_4, LOW); 
    analogWrite(EnA, MAX_EnA); //RIGHT MOTOR
    analogWrite(EnB, MAX_EnB); //LEFT MOTOR
  }

void update_alignment(){
  //UPDATES THE SENSOR VARIABLES
  Value_Sn[0] = digitalRead(S1); 
  Value_Sn[1] = digitalRead(S2); 
  Value_Sn[2] = digitalRead(S3);  
  Value_Sn[3] = digitalRead(S4); 
  Value_Sn[4] = digitalRead(S5); 
  }


void forward_right_turn(){
  //FORWARD RIGHT TURN SPEEDS
  int RIGHT_TURN_EnA = 100; 
  int RIGHT_TURN_EnB = 200; 

  //SET MOTOR DIRECTION
  motor_forward(); 
  
  //SET SPEED 
  analogWrite(EnA, RIGHT_TURN_EnA); //RIGHT MOTOR
  analogWrite(EnB, RIGHT_TURN_EnB); //LEFT MOTOR
  
  //SUSPEND OPERATIONS UNTIL TURN IS MADE
  delay(800); 
}


void forward_left_turn(){
  //FORWARD RIGHT TURN SPEEDS
  int LEFT_TURN_EnA = 200; //RIGHT MOTOR
  int LEFT_TURN_EnB = 0; //LEFT MOTOR

  //SET MOTOR DIRECTION
  motor_forward(); 
  
  //SET SPEED 
  analogWrite(EnA, LEFT_TURN_EnA); //RIGHT MOTOR
  analogWrite(EnB, LEFT_TURN_EnB); //LEFT MOTOR
  
  //SUSPEND OPERATIONS UNTIL TURN IS MADE
  delay(800); 
}


//HELPER FUNCTION TO COMPARE THE Value_Sn array: 



  
void line_follower(){  //detects and tracks the line
  
  if(Value_Sn[0] == black && Value_Sn[1]==black && Value_Sn[2] == white && Value_Sn[3]==white && Value_Sn[4]==white){  //SOFT TURN LEFT
    analogWrite(EnA,LEFT_TURN_EnA_LIGHT); 
    analogWrite(EnB, LEFT_TURN_EnB_LIGHT);     
  }
  
  else if(Value_Sn[0] == black && Value_Sn[1]==white && Value_Sn[2] == white && Value_Sn[3]==white && Value_Sn[4]==white){  //HARD TURN LEFT
    analogWrite(EnA,LEFT_TURN_EnA_HARD);
    analogWrite(EnB, LEFT_TURN_EnB_HARD);     
  }
  
  if(Value_Sn[0] == white && Value_Sn[1]==black && Value_Sn[2] == black && Value_Sn[3]==white && Value_Sn[4]==white){  //SOFT TURN LEFT
    analogWrite(EnA,LEFT_TURN_EnA_LIGHT);
    analogWrite(EnB, LEFT_TURN_EnB_LIGHT);     
  }
   
  else if(Value_Sn[0] == white && Value_Sn[1]==white && Value_Sn[2] == white && Value_Sn[3]==black && Value_Sn[4]==black){  //SOFT TURN RIGHT
    analogWrite(EnA,RIGHT_TURN_EnA_LIGHT);
    analogWrite(EnB, RIGHT_TURN_EnB_LIGHT);     
  }
   
  else if(Value_Sn[0] == white && Value_Sn[1]==white && Value_Sn[2] == white && Value_Sn[3]==white && Value_Sn[4]==black){  //HARD TURN RIGHT
    analogWrite(EnA,RIGHT_TURN_EnA_HARD);
    analogWrite(EnB, RIGHT_TURN_EnB_HARD);     
  }
   
  else if(Value_Sn[0] == white && Value_Sn[1]==white && Value_Sn[2] == black && Value_Sn[3]==black && Value_Sn[4]==white){  //SOFT TURN RIGHT
    analogWrite(EnA,RIGHT_TURN_EnA_LIGHT);
    analogWrite(EnB, RIGHT_TURN_EnB_LIGHT);     
  }

  else if(Value_Sn[0] == white && Value_Sn[1]==black && Value_Sn[2] == black && Value_Sn[3]==black && Value_Sn[4]==white){//IF TRUE THEN MOVE STRAIGHT
      //SET SPEED 
      analogWrite(EnA, MAX_EnA); //RIGHT MOTOR SPEED
      analogWrite(EnB, MAX_EnB); //LEFT MOTOR SPEED      
  }

  else if(Value_Sn[0] == black && Value_Sn[1]==black && Value_Sn[2] == black && Value_Sn[3]==black && Value_Sn[4]==black){//ON INTERSECTION MOVE STTRAIGHT 
      //SET SPEED 
      analogWrite(EnA, MAX_EnA); //RIGHT MOTOR SPEED 
      analogWrite(EnB, MAX_EnB); //LEFT MOTOR SPEED      
  }

  else if(Value_Sn[0] == black && Value_Sn[1]==black && Value_Sn[2] == black && Value_Sn[3]==white && Value_Sn[4]==white){  //SOFT TURN LEFT TEMP WHEN S3 IS ALSO ON BLACK
    analogWrite(EnA,LEFT_TURN_EnA_LIGHT);
    analogWrite(EnB, LEFT_TURN_EnB_LIGHT);     
  }

  else if(Value_Sn[0] == white && Value_Sn[1]==white && Value_Sn[2] == black && Value_Sn[3]==black && Value_Sn[4]==black){  //SOFT TURN RIGHT TEMP WHEN S3 IS ALSO ON BLACK
    analogWrite(EnA,RIGHT_TURN_EnA_LIGHT);
    analogWrite(EnB, RIGHT_TURN_EnB_LIGHT);     
  }

//  else {
//    analogWrite(EnA, MAX_EnA); //RIGHT MOTOR SPEED
//    analogWrite(EnB, MAX_EnB); //LEFT MOTOR SPEED 
//  }
  
}


void counting_intersections(){
  //COUNTS THE NUMBER OF INTERSECTIONS 

  if(count==max_count){ //IF COUNT IS REACHED, CONTINOUSLY STOP THE MOTOR
    Serial.println(count); 
    motor_stop(); 
    count = 0; 

    //CASE 1: FIRST STRAIGHT
    if(first_straight_done ==0){
      first_straight_done = 1;
      }
    else if (second_straight_done ==0){
      second_straight_done=1; 
      
      }
  }
  
  else{ //IF COUNT IS NOT REACHED, CHECK FOR CONDITIONS
      if(flag_count==0 && Value_Sn[0] == black && Value_Sn[1] == black && Value_Sn[2] == black && Value_Sn[3] == black && Value_Sn[4] == black ){//CHECK IF THE BOT IN ON AN INTERSECTION 
         flag_count = 1;  
      } 
      else if(Value_Sn[0] == white && Value_Sn[4] == white && flag_count ==1){ //CHECK IF BOT HAS CROSSED THE INTERSECTION
         count+=1; 
         flag_count = 0; 
      
      }
      motor_forward(); 
    }
  
}


//SERVO HELPER FUNCTION
void drop_ball(){
   Servo1.write(0); 
   Servo2.write(0);
   delay(1000); 
   // Make servo1 go to 90 degrees 
   Servo1.write(90); 
   delay(1000); 
   // servo1 return to 0 degrees
   Servo1.write(0);
   delay(1000);   
   // Make servo2 go to 90 degrees and 
   Servo2.write(90);
   delay(1000);
  }







  
void setup() {
  // put your setup code here, to run once:
  pinMode(INT_1, OUTPUT); 
  pinMode(INT_2, OUTPUT); 
  pinMode(INT_3, OUTPUT); 
  pinMode(INT_4, OUTPUT); 
  pinMode(EnA, OUTPUT); 
  pinMode(EnB, OUTPUT); 
  Servo1.attach(servo1Pin);
  Servo2.attach(servo2Pin); 
  
  Serial.begin(9600);

}




int temp=0; //used to give initial delay 


void loop() {
  // put your main code here, to run repeatedly:
  

  //INTIAL DELAY: 
  if(temp==0){
      delay(4000); 
      temp++; 
      Serial.println("initial delay passed!");   
  }

  //update sensor values
  update_alignment(); 
  
  
  //CASE 1: MOVE STRAIGHT: 
  if(first_straight_done == 0){
        max_count = 3; //SET THE DESIRED NUMBER OF HOPS YOU WANT THE ROBOT TO TRAVERSE IN THE FIRST LINE
        //LFR COMMAND FLOW 
        line_follower();
        counting_intersections();   //COUNTING THE INTERSECTIONS CROSSINGS
        Serial.println("inside first straight"); 
        
    }
   
//  //CASE 2: MAKE A LEFT TURN
  else if (first_turn_done ==0){
        
        forward_left_turn(); 
        first_turn_done =1; 
  
  }
// CASE3: MOVE STRAIGHT (FOR THE SECOND TIME)
  else if (second_straight_done ==0){
        max_count = 1; //SET THE DESIRED NUMBER OF HOPS YOU WANT THE ROBOT TO TRAVERSE IN THE SECOND LINE
        line_follower();
        counting_intersections();   //COUNTING THE INTERSECTIONS CROSSINGS
    }



//CASE N-1: STOP THE MOVEMENT
  else{
        motor_stop(); 
        
        
    }
}























//  //RECEIVE DATA FROM BLUETOOTH MODULE
//  if(Serial.available()){
//    delay(10); 
//    received_char = Serial.read(); 
//    Serial.print("Bluetooth rx: "); 
//    Serial.println(received_char); 
//    }
//
//  //UPDATE BLUETOOTH ENABLE FLAG
//  if(received_char == START_FLAG){
//    bluetooth_en_flag=1; 
//    Serial.println("Im in"); 
//    }
//  else if(received_char == STOP_FLAG){
//    bluetooth_en_flag = 0; 
//    }
//  if(bluetooth_en_flag==1){//START THE LFR WHEN BLUETOOTH START COMMAND IS RECEIVED
//
//    }


















//  if(Value_S3!=black){//IF TRUE THEN ROBOT IS NOT IN LINE: 
//
//  
//    //CHECK LEFT RIGHT SENSORS: 
//    
//    //FINDING THE WEIGHTS ACCORDING TO WHICH THE ROBOT HAS DEVIATED FROM THE LINE 
//    int left_blacks = 0;  
//    int right_blacks = 0;
//    left_blacks+= !(Value_S2);  
//    left_blacks+= !(Value_S1);
//    right_blacks+= !(Value_S4);
//    right_blacks+= !(Value_S5);
//    
//    Serial.print("black weight (Left): ");
//    Serial.print(left_blacks);
//    Serial.print("::black weight (Right): ");
//    Serial.println(right_blacks); 
//    //ALIGNING THE ROBOT ACCORDING TO THE DEVIATION WEIGHTS
//
//    if(right_blacks == 2){ //MAKE A LIGHT RIGHT TURN
//        //SET SPEED 
//        analogWrite(EnA, RIGHT_TURN_EnA_LIGHT); //RIGHT MOTOR SPEED
//        analogWrite(EnB, RIGHT_TURN_EnB_LIGHT); //LEFT MOTOR SPEED
//    }
//    else if(right_blacks == 1){ //TURN RIGHT WITH A BIT FASTER SPEED
//        //SET SPEED 
//        analogWrite(EnA, RIGHT_TURN_EnA_HARD); //RIGHT MOTOR SPEED
//        analogWrite(EnB, RIGHT_TURN_EnB_HARD); //LEFT MOTOR SPEED
//    }
//    else if(left_blacks == 2){ //TURN LEFT WITH SLOWER SPEED
//        //SET SPEED 
//        analogWrite(EnA, LEFT_TURN_EnA_LIGHT); //RIGHT MOTOR SPEED
//        analogWrite(EnB, LEFT_TURN_EnB_LIGHT); //LEFT MOTOR SPEED
//    }
//    else if(left_blacks == 1){ //TURN LEFT WITH A BIT FASTER SPEED
//        //SET SPEED 
//        analogWrite(EnA, LEFT_TURN_EnA_HARD); //RIGHT MOTOR SPEED
//        analogWrite(EnB, LEFT_TURN_EnB_HARD); //LEFT MOTOR SPEED
//    }
//
//    else{//IN CASE ALL THE ABOVE CONDITIONS DONT MEET, RUN STRAIGHT TO FIND A LINE 
//        analogWrite(EnA, MAX_EnA); //RIGHT MOTOR SPEED
//        analogWrite(EnB, MAX_EnB); //LEFT MOTOR SPEED
//      }
//  }
  
