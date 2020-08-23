
// Tuning and Behavior Parameters

// Constants
const int32_t cnControlPeriod_us = 50000; // 50msec = 20Hz control

// Functions
int32_t GetSensorMeasurement_CountsX16k(int32_t inMeasurementTime_ms, int32_t inDelayBetweenMeasurements_us);
void PIDController(void); // Work on globals for now
void GetNextMotorCommand(void); // Calculate motor command based on PID output and artificial momentum, dampening, etc
void SetSafeMotorSpeed(void);  // Final motor command, applying any shutdown commands

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

  digitalWrite(IN1, 0);
  digitalWrite(IN3, 0);

  digitalWrite(IN2, 0);
  digitalWrite(IN4, 0);
  
  analogWrite(EN_A, 0);
  analogWrite(EN_B, 0);  

}

int gnMotorSpeed = 255;

void loop () 
{
  Serial.println(gnMotorSpeed);
  analogWrite(EN_A,gnMotorSpeed);
  digitalWrite(IN1,1);
  digitalWrite(IN2,0);
  delay(300);

  analogWrite(EN_A,0);
  delay(1700);
  
  analogWrite(EN_A,gnMotorSpeed);
  digitalWrite(IN1,0);
  digitalWrite(IN2,1);
  delay(300);  
  analogWrite(EN_A,0);
  delay(1700);

  if (gnMotorSpeed >= 10)
    gnMotorSpeed = gnMotorSpeed - 10;
}

  //     motor_speed1 = map(y_pos, 600, 1023, 0, 255);
