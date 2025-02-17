const int PWM_MOTOR_A = 3; //PWMA 
const int PWM_MOTOR_B = 5; //PWMB

const int MOTOR_A_INPUT1 = 2; // AI1
const int MOTOR_A_INPUT2 = 4; // AI2
const int MOTOR_B_INPUT1 = 6; // BI1
const int MOTOR_B_INPUT2 = 9; // BI2

//This are the constant values for the JOYSTICK DEADZONE
//This should be costumized as per the TEAMS preference
const int LEFT_DEADZONE = 128;
const int RIGHT_DEADZONE = 128;
const int UP_DEADZONE = 128;
const int DOWN_DEADZONE = 128;

//value reading when the deadzone is at the origin
const int ORIGIN = 255;
const int MAX_DIST = 145;

void turn(int x, int y){

  int motor_power, steer, power_opposite_side, power_turning_side;

  //power of the motor will be determined by the distance bewteen joystick and origin
  motor_power = (int)(sqrt(pow((x - ORIGIN),2) + pow((y - ORIGIN),2)));
  
  steer = (int)(sqrt(pow((x - ORIGIN),2)));

  power_opposite_side = (int)(motor_power*(((steer/MAX_DIST)+1)/2)); 
  power_turning_side = (int)(motor_power*(((steer/MAX_DIST)-1)/2)); 

  if(y > ORIGIN + UP_DEADZONE){

    //adjust to move forward
    digitalWrite(MOTOR_A_INPUT1,LOW);
    digitalWrite(MOTOR_A_INPUT2,HIGH);

    digitalWrite(MOTOR_B_INPUT1,LOW);
    digitalWrite(MOTOR_B_INPUT2,HIGH);

    if(x > ORIGIN + RIGHT_DEADZONE){
      analogWrite(PWM_MOTOR_A, power_opposite_side);
      analogWrite(PWM_MOTOR_B, power_turning_side);
    } 
    else if( x < ORIGIN - LEFT_DEADZONE){
      analogWrite(PWM_MOTOR_A, power_opposite_side);
      analogWrite(PWM_MOTOR_B, power_turning_side);

    }
  }
  else if(y < ORIGIN - DOWN_DEADZONE){
    //adjust to move backward
    digitalWrite(MOTOR_A_INPUT2,LOW);
    digitalWrite(MOTOR_A_INPUT1,HIGH);

    digitalWrite(MOTOR_B_INPUT2,LOW);
    digitalWrite(MOTOR_B_INPUT1,HIGH);


    if(x > ORIGIN + RIGHT_DEADZONE){
      analogWrite(PWM_MOTOR_A, power_opposite_side);
      analogWrite(PWM_MOTOR_B, power_turning_side);
    } 
    else if( x < ORIGIN - LEFT_DEADZONE){
      analogWrite(PWM_MOTOR_A, power_opposite_side);
      analogWrite(PWM_MOTOR_B, power_turning_side);

    }
  }

  delay(100);
  
}


void setup() {
  pinMode(PWM_MOTOR_A, OUTPUT);
  pinMode(PWM_MOTOR_B, OUTPUT);

  
  pinMode(MOTOR_A_INPUT1, OUTPUT);
  pinMode(MOTOR_A_INPUT2, OUTPUT);

  pinMode(MOTOR_B_INPUT1, OUTPUT);
  pinMode(MOTOR_B_INPUT2, OUTPUT);

  
  digitalWrite(MOTOR_A_INPUT1, LOW);
  digitalWrite(MOTOR_A_INPUT2, LOW);

  digitalWrite(MOTOR_B_INPUT1, LOW);
  digitalWrite(MOTOR_B_INPUT2, LOW);
}

void loop() {

  //instert random reading values here

}
