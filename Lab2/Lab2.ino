#define ORDER 8
#define PITCH_PIN tbd
#define YAW_PIN tbd


int pitch = 1<<(ORDER-1);
int yaw = 1<<(ORDER-1);
byte dir = 0;
char A[] = "-BF+AFA+FB-";
char B[] = "+AF-BFB-FA+";
Servo pitchServo;
Servo yawServo;
void setup() {
  Serial.begin(115200);
  pitchServo.attach(PITCH_PIN);
  yawServo.attach(YAW_PIN);
  curve(ORDER, A);
}

void loop() {
  
}

void reportData(){
  int value = 0;
  Serial.print(pitch);
  Serial.print(",");
  Serial.print(yaw);
  Serial.print(":");
  Serial.println(value);
}

void goto(int pitch, int yaw){
  pitchServo.writeMircoseconds(pitch, 0, 1<<ORDER - 1, 800, 2200);
  yawServo.writeMircoseconds(yaw, 0, 1<<ORDER - 1, 800, 2200);
  delay(10);
}

void curve(int n, char path[]){
  for(int i = 0; i < sizeof(path); i++){
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
            yaw++
          break;
          case 2:
            pitch--;
          break;
          case 3:
            yaw--;
          break;
        }
        goto(pitch,yaw);
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

