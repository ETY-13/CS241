#include<Servo.h>

const int motor_left_1 = 2;
const int motor_left_2 = 3;

const int motor_right_1 = 4;
const int motor_right_2 = 5;

const int motor_source_1 = 8;
const int motor_source_2 = 9;

const int ultra_echo = 11;
const int ultra_trig = 12;
const int ultra_source = 13;

const int servo_pin = 7;
Servo servo;
void setup(){
  // motor left
  pinMode(motor_left_1,OUTPUT);
  pinMode(motor_left_2, OUTPUT);
  // motor right
  pinMode(motor_right_1,OUTPUT);
  pinMode(motor_right_2,OUTPUT);
  
  // motor source
  pinMode(motor_source_1,OUTPUT);
  pinMode(motor_source_2,OUTPUT);
  analogWrite(motor_source_1,255); 
  analogWrite(motor_source_2,255);
  
  // ultra_sonic
  pinMode(ultra_trig, OUTPUT);
  pinMode(ultra_echo, INPUT);
  pinMode(ultra_source, OUTPUT);
  analogWrite(ultra_source,255);

  // servo
  servo.write(95);
  servo.attach(servo_pin);
  
  Serial.begin(9600);
}

// See if there's obstacle close by
float get_distance(){
  digitalWrite(ultra_trig, HIGH);
  delayMicroseconds(10); /* fire! */
  digitalWrite(ultra_trig, LOW);
  long echoTime = pulseIn(ultra_echo, HIGH);
  float distance_mm = echoTime*0.343/2;
  return distance_mm;
}

// Turn the ultra sonic sensor to look
// at a direction--front/left/right
int look_around(char dir){
  
  if(dir == 'l'){
    servo.write(0);
  }
  else if (dir =='r'){
    servo.write(180);
  }
  else if (dir =='f'){
    servo.write(95);
  }

 float distance = 0.0;
 const int average_over = 10;
 for(auto iter = 0; iter < average_over; ++iter){
  distance += get_distance();
 }
 
 return (distance/average_over);
}

void stop_drive(){
  digitalWrite(motor_left_1,LOW);
  digitalWrite(motor_left_2,LOW); 
  digitalWrite(motor_right_1,LOW);
  digitalWrite(motor_right_2,LOW);
}
void drive(char dir){
  if(dir == 'f'){
    digitalWrite(motor_left_1,HIGH);
    digitalWrite(motor_left_2,LOW); 
    digitalWrite(motor_right_1,HIGH);
    digitalWrite(motor_right_2,LOW);
  }
  else if(dir == 'r'){
    digitalWrite(motor_left_1,HIGH);
    digitalWrite(motor_left_2,LOW); 
  }
  else if(dir == 'l'){
    digitalWrite(motor_right_1,HIGH);
    digitalWrite(motor_right_2,LOW); 
  }
  else if(dir == 'b'){
    digitalWrite(motor_left_1,LOW);
    digitalWrite(motor_left_2,HIGH); 
    digitalWrite(motor_right_1,LOW);
    digitalWrite(motor_right_2,HIGH);
  }
}

// get a random direction to turn:
// either left or right
char get_random_dir(){
  int num = random(0,2);
  if(num){
    return 'r';
  }
  return 'l';
}

int moved_forward = 0;
int saved_start_distance = 0;
void loop(){
 
  auto start_distance = look_around('f');
  
  if(start_distance > 300){
    drive('f');
    if(moved_forward == 0){
      saved_start_distance = start_distance; 
    }
    moved_forward +=1;
  }
  else{
   stop_drive();
   moved_forward = 0;
   if(look_around('r') > 300){
    drive('r');
    delay(1200);
    stop_drive();
   }
   else if(look_around('l') > 300){
    drive('l');
    delay(1200);
    stop_drive();;
   }
   else{
    drive('b');
    delay(1500);
    stop_drive();
    drive(get_random_dir());
    delay(1000);
    stop_drive();
   }
  }

  if(moved_forward > 5){
    auto moving_distance = look_around('f');
    auto distance_diff =  saved_start_distance - moving_distance;

    // if the moving distance does not differ greater than 6 from the starting distance;
    // backup, it is stuck. 
    if (distance_diff < 6){
      drive('b');
      delay(1500);
      stop_drive();
      drive(get_random_dir());
      delay(1000);
      stop_drive();
    }
    moved_forward = 0;
 }
}