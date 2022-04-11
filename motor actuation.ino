/**
 * Use of 2 DC motor and a L298N
 */

// Motor 1
const int PIN_ACTIVATE_3_4 = 8;
const int PIN_INPUT_3 = 9;
const int PIN_INPUT_4 = 10;

// Motor 2
const int PIN_ACTIVATE_1_2 = 5;
const int PIN_INPUT_1 = 6;
const int PIN_INPUT_2 = 7;

//Input
String a ="";

bool choice = false;

/**
 * Initialize the pins of a motor
 */
void initMotor(int activationPin, int pin1, int pin2)
{
    pinMode(activationPin, OUTPUT);
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    // Enable the motor driver
    analogWrite(activationPin, 0); 
    
}




int to_move(int potentio, int act_pin) //normalise potentio reading
{
  int spd = 0;
  int abs_spd = 0;
  float reading = 50;

  reading = potentio/10.23;
  if (reading < 45 && reading >1 )
  {
    spd = (-(45 - reading)/45)*160;
  }
  else if (reading > 55  && reading < 99)
  {
    spd = ((reading-55)/45)*160;
  }
  else
  {
    spd = 0;
  }
  abs_spd = abs(spd);
  Serial.print("PWM : ");
  Serial.println(abs_spd);
  analogWrite(act_pin, abs_spd);
 
  delay(20);
  return spd;
 }
 /**
 * Run a motor either clockwise or counter-clockwise
 */

void runMotor(int pin1, int pin2, int spd ) //bidirectional control
{
    Serial.println(spd);
    if (spd>0) {
        // Run the motor clockwise
        Serial.println("direcetion 1");
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
            delay(20);

       
  
    } else {
        // Run the motor counter-clockwise
        Serial.println("direcetion 2");
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
            delay(20);
       
        
    }
   
}





// Main functions

void setup()
{ 
    Serial.begin(9600);
    initMotor(PIN_ACTIVATE_1_2, PIN_INPUT_1, PIN_INPUT_2);
    initMotor(PIN_ACTIVATE_3_4, PIN_INPUT_3, PIN_INPUT_4);
  
   
}

void loop()
{
  //input height 
    int left_paddle = analogRead(A3); //receive potentio reading
    int right_paddle = analogRead(A4);
    int left_speed = 0;
    int right_speed=0;
   
    Serial.print("Left potentiometer ");
    Serial.print(left_paddle);
    Serial.print("\n");
  
    Serial.print("Right potentiometer ");
    Serial.print(right_paddle);
     Serial.print("\n");
     
    left_speed = to_move(left_paddle, PIN_ACTIVATE_1_2);
    right_speed = to_move(right_paddle, PIN_ACTIVATE_3_4);
    Serial.print("Left Paddle speed ");
    Serial.print(left_speed);
    Serial.print("\n");

    Serial.print("Right Paddle speed ");
    Serial.print(right_speed);
    Serial.print("\n");


 
    runMotor(PIN_INPUT_1, PIN_INPUT_2,left_speed);
    runMotor(PIN_INPUT_3, PIN_INPUT_4,right_speed);
    
   
    delay(500);
        //reached
      
      
        
    
 
}
