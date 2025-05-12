//--------IR pin-----------
#define ir1 PA0
#define ir2 PA1     //right
#define ir3 PA2
#define ir4 PA3
#define ir5 PA4     //left
#define ir6 PA5

//---------MOTOR PIN--------------
#define ml1 PB7
#define ml2 PB6
#define mr1 PB9
#define mr2 PB8

// Variables
int process_value = 0;
int previous_process_value = 0;

int P, D, I, previousError, error;
float Pvalue, Ivalue, Dvalue;
float Kp = 9000;
float Ki = 0;
float Kd = 5500;

uint8_t multiP = 0;
uint8_t multiI = 1;
uint8_t multiD = 0;

int lsp, rsp;
int base_speed = 60000;
int max_speed = 65535;




void setup() {
  pinMode(mr1, PWM);
  pinMode(mr2, PWM);
  pinMode(ml1, PWM);
  pinMode(ml2, PWM);

  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
  pinMode(ir6, INPUT);

  Serial.begin(9600);

}

void loop() {
  
  int i1 = digitalRead(ir1);
  int i2 = digitalRead(ir2);
  int i3 = digitalRead(ir3);
  int i4 = digitalRead(ir4);
  int i5 = digitalRead(ir5);
  int i6 = digitalRead(ir6);


  if (!i1 && i2 && i3 && i4 && i5 && i6) process_value = 1;
  else if (!i1 && !i2 && i3 && i4 && i5 && i6) process_value = 2;
  else if (i1 && !i2 && i3 && i4 && i5 && i6) process_value = 3;
  else if (i1 && !i2 && !i3 && i4 && i5 && i6) process_value = 4;
  else if (i1 && i2 && !i3 && i4 && i5 && i6) process_value = 5;
  else if (i1 && i2 && !i3 && !i4 && i5 && i6) process_value = 6;
  else if (i1 && i2 && i3 && !i4 && i5 && i6) process_value = 7;
  else if (i1 && i2 && i3 && !i4 && !i5 && i6) process_value = 8;
  else if (i1 && i2 && i3 && i4 && !i5 && i6) process_value = 9;
  else if (i1 && i2 && i3 && i4 && !i5 && !i6) process_value = 10;
  else if (i1 && i2 && i3 && i4 && i5 && !i6) process_value = 11;
  else if (i1 && i2 && i3 && i4 && i5 && i6) process_value = 0;
  else if (!i1 && !i2 && !i3 && !i4 && !i5 && !i6) {
    motor_drive(0, 0);
    return;
  }
  else {
    process_value = previous_process_value;
  }

  if (process_value == 0) {
    if (previousError > 0) {
      motor_drive(60000, -60000);
    } else {
      motor_drive(-60000, 60000);
    }
    return;
  }

  // PID Control
  error = 6 - process_value;

  P = error;
  I = I + error;
  D = error - previousError;
  Pvalue = (Kp / pow(10, multiP)) * P;
  Ivalue = (Ki / pow(10, multiI)) * I;
  Dvalue = (Kd / pow(10, multiD)) * D;

  float PIDvalue = Pvalue + Ivalue + Dvalue;
  previousError = error;

  lsp = base_speed + PIDvalue;
  rsp = base_speed - PIDvalue;

  if (lsp > max_speed) lsp = max_speed;
  if (lsp < -max_speed) lsp = -max_speed;
  if (rsp > max_speed) rsp = max_speed;
  if (rsp < -max_speed) rsp = -max_speed;

  motor_drive(lsp, rsp);

  previous_process_value = process_value;
}

//---------------- Motor Drive ------------------
void motor_drive(float left, float right) {
  if (left > 0) {
    pwmWrite(ml2, left);
    pwmWrite(ml1, 0);
  } else {
    pwmWrite(ml2, 0);
    pwmWrite(ml1, -left);
  }

  if (right > 0) {
    pwmWrite(mr2, right);
    pwmWrite(mr1, 0);
  } else {
    pwmWrite(mr2, 0);
    pwmWrite(mr1, -right);
  }
}


