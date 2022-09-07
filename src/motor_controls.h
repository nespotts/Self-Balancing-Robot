
typedef struct {
  int enApin;
  int enBpin;
  int in1pin;
  int in2pin;
  int in3pin;
  int in4pin;
} motor_vars;

motor_vars motor = {32,25,30,29,28,27};


// setup motor pins
void motor_setup() {
  pinMode(motor.enApin, OUTPUT);
  pinMode(motor.enBpin, OUTPUT);
  pinMode(motor.in1pin, OUTPUT);
  pinMode(motor.in2pin, OUTPUT);
  pinMode(motor.in3pin, OUTPUT);
  pinMode(motor.in4pin, OUTPUT);

  digitalWrite(motor.enApin, LOW);
  digitalWrite(motor.enBpin, LOW);
  digitalWrite(motor.in1pin, LOW);
  digitalWrite(motor.in2pin, LOW);
  digitalWrite(motor.in3pin, LOW);
  digitalWrite(motor.in4pin, LOW);
}

// command motors - A left, B right
void CommandMotors(int leftMotorSpeed, int rightMotorSpeed) {
  // left speed = D5, A = A0, B = A1
  // right speed = D6, A = A2, B = A3

  // Set Left Motor Direction
  if (leftMotorSpeed < 0) {
    //reverse
    digitalWrite(motor.in1pin, LOW);
    digitalWrite(motor.in2pin, HIGH);
    encoder[0].direction = 1;
  } else if (leftMotorSpeed > 0) {
    //forward
    digitalWrite(motor.in1pin, HIGH);
    digitalWrite(motor.in2pin, LOW);
    encoder[0].direction = 0;
  } else {
    //stop
    digitalWrite(motor.in1pin, LOW);
    digitalWrite(motor.in2pin, LOW);
  }
  
  // Set Right Motor Direction
  if (rightMotorSpeed < 0) {
    //reverse
    digitalWrite(motor.in3pin, HIGH);
    digitalWrite(motor.in4pin, LOW);
    encoder[1].direction = 1;
  } else if (rightMotorSpeed > 0) {
    //forward
    digitalWrite(motor.in3pin, LOW);
    digitalWrite(motor.in4pin, HIGH);
    encoder[1].direction = 0;
  } else {
    //stop
    digitalWrite(motor.in3pin, LOW);
    digitalWrite(motor.in4pin, LOW);
  }

  analogWrite(motor.enApin, fabs(leftMotorSpeed));
  analogWrite(motor.enBpin, fabs(rightMotorSpeed)); 
}