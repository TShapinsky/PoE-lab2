#include <Servo.h>

#define ORDER 8
#define PITCH_PIN 5
#define YAW_PIN 3
#define DEPTH_PIN A0


int pitch = 0;//1<<(ORDER-1);
int yaw = 0;//1<<(ORDER-1);
byte dir = 0;
char A[] = "-BF+AFA+FB-";
char B[] = "+AF-BFB-FA+";
Servo pitchServo;
Servo yawServo;

void curve(int n, char path[]);
void setup() {
  Serial.begin(115200);
  pitchServo.attach(PITCH_PIN);
  yawServo.attach(YAW_PIN);
  curve(ORDER, A);
  pinMode(DEPTH_PIN, INPUT);
}

void loop() {
  
}

void reportData(){
  int value = analogRead(DEPTH_PIN);
  Serial.print("[");
  Serial.print(pitch);
  Serial.print(";");
  Serial.print(yaw);
  Serial.print(";");
  Serial.print(value);
  Serial.println("]");
}

void gotoPoint(int pitch, int yaw){
  int pitchMicro = map(pitch, 0, 1<<(ORDER+2) - 1, 1400, 2200);
  int yawMicro = map(yaw, 0, 1<<(ORDER+2) - 1, 1200, 2000);
  /*Serial.print("[");
  Serial.print(pitchMicro);
  Serial.print(";");
  Serial.print(yawMicro);
  Serial.println("]");*/
  pitchServo.writeMicroseconds(pitchMicro);
  yawServo.writeMicroseconds(yawMicro);
  delay(10);
}

void curve(int n, char path[]){
  for(int i = 0; i < strlen(path); i++){
    char c = path[i];
    switch(c){
      case 'A':
        if (n > 0){
          curve(n-1,A);
        }
        break;
      case 'B':
        if(n > 0){
          curve(n-1, B);
        }
        break;
      case 'F':
        dir = (dir+4)%4;
        switch(dir){
          case 0:
            pitch++;
          break;
          case 1:
            yaw++;
          break;
          case 2:
            pitch--;
          break;
          case 3:
            yaw--;
          break;
        }
        gotoPoint(pitch,yaw);
        reportData();
      break;
      case '-':
        dir++;
      break;
      case '+':
        dir--;
      break;
    }
  }
}

