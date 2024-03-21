#define trigPin A0
#define echoPin 2
#define trigPin1 A1
#define echoPin1 4
#define trigPin2 A2 
#define echoPin2 7

#define in2 3
#define in1 5
#define in4 6
#define in3 9

long duration;
long distance;
long duration1;
long distance1;
long duration2;
long distance2;

#define right distance2
#define left distance1
#define front distance
int min_dist = 20;
int fpath = 0;
int fmaze = 0;
int readp = 0;

char p[1000];

void turnleft() {
  analogWrite(in1, 255);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 255);
  Serial.println("left");
  delay(250);
}

void turnright() {
  analogWrite(in1, 0);
  analogWrite(in2, 255);
  analogWrite(in3, 255);
  analogWrite(in4, 0);
  Serial.println("right");
  delay(250);
}

void straight() {
  analogWrite(in1, 180);
  analogWrite(in2, 0);
  analogWrite(in3, 180);
  analogWrite(in4, 0);
  Serial.println("straight");
}

void stop() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
  delay(10);
}

void move_inch() {
  straight();
  delay(500);
  Serial.println("move inch");
}

void uturn() {
  analogWrite(in1, 255);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 255);
  Serial.println("uturn");
  delay(400);
}

void acknowledgement() {
  analogWrite(in1, 255);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 255);
}

void solve_maze_left() {
  for (int k = 0; k < (readp - 1); k++) {
    for (int i = 0; i < (readp - 1); i++) {
      if (p[i] == 'L' && p[i + 1] == 'U' && p[i + 2] == 'R') {
        p[i] = 'U';
        maze_replace();
      }
      if (p[i] == 'L' && p[i + 1] == 'U' && p[i + 2] == 'S') {
        p[i] = 'R';
        maze_replace();
      }
      if (p[i] == 'R' && p[i + 1] == 'U' && p[i + 2] == 'L') {
        p[i] = 'U';
        maze_replace();
      }
      if (p[i] == 'S' && p[i + 1] == 'U' && p[i + 2] == 'L') {
        p[i] = 'R';
        maze_replace();
      }
      if (p[i] == 'L' && p[i + 1] == 'U' && p[i + 2] == 'L') {
        p[i] = 'S';
        maze_replace();
      }
    }
  }
  fmaze = 1;
  Serial.print("maze solved left");
  acknowledgement();
}

void maze_replace() {
  int j = 0;
  do {
    p[j + 1] = p[j + 3];
    j++;
  } while (p[j + 1] != '\0');
  p[j + 1] = '\0';
  p[j + 2] = '\0';
}

void performcommand() {
  Serial.println(p[fpath]);
  switch (p[fpath]) {
    case 'L':
      turnleft();
      break;
    case 'R':
      turnright();
      break;
    case 'S':
      straight();
      delay(1500);
      break;
  }
  fpath++;
  Serial.print("command performed");
  Serial.println(fpath);
}

void move_back() {
  analogWrite(in1, 0);
  analogWrite(in2, 255);
  analogWrite(in3, 0);
  analogWrite(in4, 255);
}

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);

  delay(1000);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.017;

  delayMicroseconds(20);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.017;

  delayMicroseconds(20);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.017;

  Serial.println(front);
  Serial.println(left);
  Serial.println(right);
  Serial.println("______________");
  // delay(1000);
  straight();
  if ((left > min_dist && right < min_dist && front < min_dist) || (left > min_dist && right > min_dist) || (left > min_dist && front > min_dist)) {
    if (fmaze == 0) {
      turnleft();
      p[readp] = 'L';
      readp++;
      move_inch();
    } else {
      performcommand();
    }
  } else if (right > min_dist && left < min_dist && front < min_dist) {
    if (fmaze == 0) {
      turnright();
      p[readp] = 'R';
      readp++;
    } else {
      performcommand();
    }
  } else if (front > min_dist && right > min_dist && left < min_dist) {
    if (fmaze == 0) {
      straight();
      p[readp] = 'S';
      readp++;
    } else {
      performcommand();
    }
  } else if (left < min_dist && right < min_dist && front < min_dist) {
    uturn();
    p[readp] = 'U';
    readp++;
  } else if (left > min_dist && right > min_dist && front > min_dist) {
    if (fmaze == 0) {
      move_inch();
      if (left > min_dist && right > min_dist && front > min_dist) {
        solve_maze_left();
      } else {
        move_back();
        turnleft();
        p[readp] = 'L';
        move_inch();
      }
    } else {
      performcommand();
    }
  }
}
