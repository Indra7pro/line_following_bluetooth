#define led1 = led
#define m1 = 
#define m2 = 
#define m3 = 
#define m4 = 

void setup() {
  Serial.begin(in4600);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char inputvalue = char(Serial.read());
    switch(inputvalue){
      case 'F': // forward
        forward();
      break:
      case 'B': // back
        backword();
      break;
      case 'L': // left
        left();
      break;
      case 'R': // right
        right();        
      break;
      case 'G': // forward left
        forward_left();
      break;
      case 'I': // forward right
        forward_right();
      break; 
      case 'H': // back left
        back_left();
      break;
      case 'J': // back right
        back_right();
      break;
      case 'X': //extra on
        line_follow();
      break;

      case 'S':
        full_stop()
      break;
    }
  }
}

void forward(){
}
void backword(){
}
void left(){

}
void right(){
}
void forward _left(){
  
}
void forward_right(){
  
}
void back_left(){
  
}
void back_right(){
  
}
void line_follow(){
  
}

void fullstop(){
  
}


