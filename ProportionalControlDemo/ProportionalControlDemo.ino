
//Joystick Pins
int x_key = A0;                                               
int y_key = A1;                                               
int x_pos;
int y_pos;
int y_start;
int y_end;

//Motor Pins
int EN_A = 11;      //Enable pin for first motor
int IN1 = 9;       //control pin for first motor
int IN2 = 8;       //control pin for first motor
int IN3 = 7;        //control pin for second motor
int IN4 = 6;        //control pin for second motor
int EN_B = 10;      //Enable pin for second motor
//Initializing variables to store data
int motor_speed;
int motor_speed1;

const int cnMaxMotorSpeed = 0;
int16_t cnTargetReading = 570;

void setup ( ) {
  Serial.begin (9600); //Starting the serial communication at 9600 baud rate
  //Initializing the motor pins as output
  pinMode(EN_A, OUTPUT);
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);  
  pinMode(IN4, OUTPUT);
  pinMode(EN_B, OUTPUT);

  //Initializng the joystick pins as input
  pinMode (x_key, INPUT) ;                     
  pinMode (y_key, INPUT) ;     

  y_start = 800;
  y_end = 1000;
  y_pos = y_start;

  digitalWrite(IN1, 1);
  digitalWrite(IN3, 1);

  digitalWrite(IN2, 1);
  digitalWrite(IN4, 1);
  
  analogWrite(EN_A, 0);
  analogWrite(EN_B, 0);  

  unsigned long lnRand1 = \
    ((unsigned long) analogRead(A1)) + \
    ((unsigned long) analogRead(A2))*256 + \
    ((unsigned long) analogRead(A3))*256*256 + \
    ((unsigned long) analogRead(A4))*256*256*256;

  randomSeed(lnRand1);
  cnTargetReading = random(275,750);
}

void loop(void)
{
  ProportionalLoop();
}
int gnMotorSpeed = 200;
int32_t cnTimeScale = 75;
float cnCWScalar = 0.0;
float cnCCWScalar = 0.0;
int lnMotorSpeed = 0;
void testloop () 
{
  float lnCWSpeed = (float) gnMotorSpeed * cnCWScalar;
  lnMotorSpeed = round(lnCWSpeed);
  //Serial.print("Clockwise at ");
  //Serial.println(lnMotorSpeed);
  analogWrite(EN_A,lnMotorSpeed);
  digitalWrite(IN1,1); // Clockwise output shaft when facing from motor side
  digitalWrite(IN2,0);
  delay(10*cnTimeScale);

  analogWrite(EN_A,0);
  delay(100*1);
  float lnCCWSpeed = (float) gnMotorSpeed * cnCCWScalar;
  lnMotorSpeed = round(lnCCWSpeed);
  //Serial.print("Counter-Clockwise at ");
  //Serial.println(lnMotorSpeed);
  analogWrite(EN_A,lnMotorSpeed);
  digitalWrite(IN1,0);  // Counter-clockwise output shaft
  digitalWrite(IN2,1);
  delay(10*cnTimeScale);  
  analogWrite(EN_A,0);
  delay(100*1);

  //if (gnMotorSpeed >= 10)
  //  gnMotorSpeed = gnMotorSpeed - 10;
}


float lnPropGain = 20.0;

void ProportionalLoop(void)
{
  int lnSensorValue = analogRead(A0);
  int16_t lnError = lnSensorValue - cnTargetReading;
  int16_t lnControlCommand = round(((float) lnError) * lnPropGain);
  Serial.print("Target = ");
  Serial.print(cnTargetReading);
  Serial.print(", Sensed = ");
  Serial.print(lnSensorValue);
  Serial.print(", Error = ");
  Serial.print(lnError);
  Serial.print(", Command = ");
  Serial.println(lnControlCommand);
  
  bool lbMotorDirectionCW = (lnControlCommand >= 0);
  bool lbMotorEnabled = true;
  uint16_t lnMotorCommand = abs(lnControlCommand);
  if (lnMotorCommand > 255)
    lnMotorCommand = 255;

  if ((lnMotorCommand < 3) | (lnSensorValue > 800) | (lnSensorValue < 223))
  {
    lnMotorCommand = 0;
    lbMotorEnabled = false;
  }

  if (lbMotorEnabled == true)
  {
    analogWrite(EN_A,lnMotorCommand);
    digitalWrite(IN1,lbMotorDirectionCW); // when true, Clockwise output shaft when facing from motor side
    digitalWrite(IN2,!lbMotorDirectionCW);
    Serial.print("Motor command ");
    Serial.print(lnMotorCommand); 
    Serial.print(" direction ");
    if (lbMotorDirectionCW == true)
      Serial.println("CW");
    else
      Serial.println("CCW");
  }
  else
  {
    analogWrite(EN_A,0);
    digitalWrite(IN1,1);
    digitalWrite(IN2,1);
    Serial.println("Motor Disabled");
  }

  delay(50);
  
}
    
    

  //     motor_speed1 = map(y_pos, 600, 1023, 0, 255);
