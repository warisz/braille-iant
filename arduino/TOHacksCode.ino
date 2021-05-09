#include <Servo.h>

//Neater stepper motor code, code from uc tronics 
int Pin0 = 13;//definition digital 11 pins as pin to control the IN1 (ULN24L01)
int Pin1 = 12;//definition digital 10 pins as pin to control the IN2 (ULN24L01)
int Pin2 = 11;//definition digital 9 pins as pin to control the IN3 (ULN24L01)
int Pin3 = 10;//definition digital 8 pins as pin to control the IN4 (ULN24L01)

int _step = 512; //the steps per revolution
int _speed = 1; 

int total_steps_taken = 0; 

//set up buttons
int forward_button = 9; //stepper motor forward
int forward_value; //is 1 when not pushed, 0 when pushed

int backward_button = 8; //stepper moto backward
int backward_value; //is 1 when not pushed, 0 when pushed

//microservo setup for the rack and pins
Servo right;
int right_servo = 6;

Servo left;
int left_servo = 5;

int servo_button = 7; //to turn on servo
int servo_val;

//DC motors
//Motor 1
const int motorPin1  = 4; //5
const int motorPin2  = 3; //6
//Motor 2
const int motorPin3  = 30; //10 //2
const int motorPin4  = 31; //9 //1

int motor_button = 2;
int motor_val;

//Number Constants
int right_pos = 160; //retracted position for each servo
int left_pos = 0;

int right_home = 0; //home position for each servo
int left_home = 90; //left home position is 90 so it can move the same direction as the right one

int steps_between_letter = -120; //negative moves the rack outwards, positive is inward
int max_steps = -601; // from testing, -830 should be the MAX or else rack falls off

char current_letter;
int seqDelay = 1000;
int letter_wait = 800;


void setup()
{

  Serial.begin(9600);

  //initialize stepper motor
  pinMode(Pin0, OUTPUT);//Set digital 8 port mode, the OUTPUT for the output
  pinMode(Pin1, OUTPUT);//Set digital 9 port mode, the OUTPUT for the output
  pinMode(Pin2, OUTPUT);//Set digital 10 port mode, the OUTPUT for the output
  pinMode(Pin3, OUTPUT);//Set digital 11 port mode, the OUTPUT for the output

  //button pins, set up pull up resistor
  pinMode(forward_button, INPUT);
  digitalWrite(forward_button, HIGH); 

  pinMode(backward_button, INPUT);
  digitalWrite(backward_button, HIGH); 

  pinMode(servo_button, INPUT);
  digitalWrite(servo_button, HIGH); 

  pinMode(motor_button, INPUT);
  digitalWrite(motor_button, HIGH); 

  //motor pins
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  //microservos
  right.attach(right_servo);
  left.attach(left_servo);
  right.write(right_home);
  left.write(left_home);
}

void loop()
{
  //checking buttons that control the stepper
  forward_value = digitalRead(forward_button);
  backward_value = digitalRead(backward_button);

  while (forward_value == 0)
  {
     Speed(15); //Stepper motor speed = 1 slow  (note:speed from 1 to 15)
     Step(1);//Stepper motor forward 512 steps ---- 360 angle
     forward_value = digitalRead(forward_button);
     total_steps_taken += 1;
     Serial.println(total_steps_taken);
  }

  while (backward_value == 0)
  {
    moveStepperOver();
    //Speed(15); //Stepper motor speed = 1 slow  (note:speed from 1 to 15)
    //Step(-1);//Stepper motor forward 512 steps ---- 360 angle
    backward_value = digitalRead(backward_button);
    total_steps_taken -= 1;
    Serial.println(total_steps_taken);
  }

  servo_val = digitalRead(servo_button);
  while(servo_val == 0)
  {
    retractPin(1, 1, 100);
    servo_val = digitalRead(servo_button);
  }

  motor_val = digitalRead(motor_button);
  while (motor_val == 0)
  {
    //runMotorBackwards();
    runMotor();
    motor_val = digitalRead(motor_button);
  }
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);

  if (Serial.available() > 0) 
  {

    current_letter = Serial.read();
    switch(current_letter){
      //YES THIS IS SYUPER INEFFICIENT could i have done a dictionary? yes. ITS LATE IM TIRED
      case 'a':
        printLetter(1, 0, 0, 0, 0, 0);
        break;
      case 'b':
        printLetter(1, 0, 1, 0, 0, 0);
        break;
      case 'c':
        printLetter(1, 1, 0, 0, 0, 0);
        break;
      case 'd':
        printLetter(1, 1, 0, 1, 0, 0);
        break;
      case 'e':
        printLetter(1, 0, 0, 1, 0, 0);
        break;
      case 'f':
        printLetter(1, 1, 1, 0, 0, 0);
        break;
      case 'g':
        printLetter(1, 1, 1, 1, 0, 0);
        break;
      case 'h':
        printLetter(1, 0, 1, 1, 0, 0);
        break;
      case 'i':
        printLetter(0, 1, 1, 0, 0, 0);
        break;
      case 'j':
        printLetter(0, 1, 1, 1, 0, 0);
        break;
      case 'k':
        printLetter(1, 0, 0, 0, 1, 0);
        break;
      case 'l':
        printLetter(1, 0, 1, 0, 1, 0);
        break;
      case 'm':
        printLetter(1, 1, 0, 0, 1, 0);
        break;
      case 'n':
        printLetter(1, 1, 0, 1, 1, 0);
        break;
      case 'o':
        printLetter(1, 0, 0, 1, 1, 0);
        break;
      case 'p':
        printLetter(1, 1, 1, 0, 1, 0);
        break;
      case 'q':
        printLetter(1, 1, 1, 1, 1, 0);
        break;
      case 'r':
        printLetter(1, 0, 1, 1, 1, 0);
        break;
      case 's':
        printLetter(0, 1, 1, 0, 1, 0);
        break;
      case 't':
        printLetter(0, 1, 1, 1, 1, 0);
        break;
      case 'u':
        printLetter(1, 0, 0, 0, 1, 1);
        break;
      case 'v':
        printLetter(1, 0, 1, 0, 1, 1);
        break;
      case 'w':
        printLetter(0, 1, 1, 1, 0, 1);
        break;
      case 'x':
        printLetter(1, 1, 0, 0, 1, 1);
        break;
      case 'y':
        printLetter(1, 1, 0, 1, 1, 1);
        break;
      case 'z':
        printLetter(1, 0, 0, 1, 1, 1);
        break;
      case '-':
        printLetter(0, 0, 0, 0, 1, 1);
        break;
      case '!':
        printLetter(0, 0, 1, 1, 1, 0);
        break;
      default:
        Serial.println("Error!");
        break;
        
    }

  }
 }


//SEQUENCES
void printLetter(int left1, int right1, int left2, int right2, int left3, int right3)
{
  runMotor();
  stopMotor();
  retractPin(left1, right1, letter_wait);
  delay(seqDelay);
  runMotor();
  stopMotor();
  delay(seqDelay);
  retractPin(left2, right2, letter_wait);
  delay(seqDelay);
  runMotor();
  stopMotor();
  delay(seqDelay);
  retractPin(left3, right3, letter_wait);
  delay(seqDelay);
  runMotorBackwards();
  stopMotor();
  delay(seqDelay);
  moveStepperOver();
}

//*********************************************
//************DC MOTOR FUNCTIONS**************
//*********************************************
void runMotor()
{
    delay(1000);
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    delay(80);

}

void runMotorBackwards()
{
  delay(1000);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    delay(100);
}

void stopMotor()
{
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(1000);
}
//*********************************************
//************SERVO PIN FUNCTIONS**************
//*********************************************

//input to indicate which pins to retract, 0 for no and 1 for retract
void retractPin(int left_state, int right_state, int wait)
{
  if(left_state == 1 && right_state == 1)
  {
    right.write(right_pos);
    delay(1000);
//    right.write(right_home);
//    delay(1000);
    left.write(left_pos);
    delay(1000);
  }
  else if (left_state == 1 && right_state == 0)
  {
    left.write(left_pos);
    right.write(right_home);
  }
  else if (left_state == 0 && right_state == 1)
  {
    left.write(left_home);
    right.write(right_pos);
  }
  else
  {
    right.write(right_home);
    left.write(left_home);
  }
  //right.write((right_pos * right_state) + right_home);
  //left.write(left_pos * left_state);
  delay(wait);
  right.write(right_home);
  left.write(left_home);
  
}

//*********************************************
//**STEPPER MOTOR FUNCTIONS (FROM UC TRONICS)**
//*********************************************

void moveStepperHome()
{
  Speed(15);
  Step(-1 * total_steps_taken);
  total_steps_taken = 0;
}

void moveStepperOver()
{
  //first check if there is space to move over
  if (total_steps_taken + steps_between_letter > max_steps)
  {
    Speed(15);
    Step(steps_between_letter);
    total_steps_taken += steps_between_letter;
  }
  else
  {
    moveStepperHome();
    //call function to move paper
    runMotorBackwards();
  }
}

void Speed(int stepperspeed) 
{
    _speed = 15 - stepperspeed;
    if( _speed<1){
     _speed = 1;
    }
    if( _speed>15){
     _speed = 15;
    }
}
void Step(int _step)//Stepper motor rotation
{
  if(_step>=0){  // Stepper motor forward
    for(int i=0;i<_step;i++){   
      setStep(1, 0, 0, 1);
      delay(_speed); 
      setStep(1, 0, 0, 0);
      delay(_speed);
      setStep(1, 1, 0, 0);
      delay(_speed);
      setStep(0, 1, 0, 0);
      delay(_speed);
      setStep(0, 1, 1, 0);
      delay(_speed);
      setStep(0, 0, 1, 0);
      delay(_speed);
      setStep(0, 0, 1, 1);
      delay(_speed); 
      setStep(0, 0, 0, 1);
      delay(_speed);
    }
  }else{ // Stepper motor backward
     for(int i=_step;i<0;i++){  
      setStep(0, 0, 0, 1);
      delay(_speed);
      setStep(0, 0, 1, 1);
      delay(_speed);
      setStep(0, 0, 1, 0);
      delay(_speed);
      setStep(0, 1, 1, 0);
      delay(_speed);
      setStep(0, 1, 0, 0);
      delay(_speed);
      setStep(1, 1, 0, 0);
      delay(_speed);
      setStep(1, 0, 0, 0);
      delay(_speed);
      setStep(1, 0, 0, 1);
      delay(_speed);
    }
   }
}
void setStep(int a, int b, int c, int d)  
{  
    digitalWrite(Pin0, a);     
    digitalWrite(Pin1, b);     
    digitalWrite(Pin2, c);     
    digitalWrite(Pin3, d);     
}  