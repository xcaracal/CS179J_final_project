int LASER_OUTPUT = 6;
int BUTTON_INPUT = 7;

// TASK SCHEDULER
typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;
const unsigned short tasksNum = 1;
task tasks[tasksNum];

// Laser task
enum Laser_States { Laser_Init, Laser_Depress, Laser_Press1, Laser_Press2, Laser_Wait };
int Laser_TickFct(int state);

void setup() {
  // Specify pins
  pinMode(LASER_OUTPUT, OUTPUT);
  pinMode(BUTTON_INPUT, INPUT);

  // TASK SCHEDULER
  int i = 0;
  tasks[i].state = Laser_Init;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &Laser_TickFct;
}

void loop() {
  // TASK SCHEDULER
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }
}

// IMPLEMENTATIONS
int Laser_TickFct(int state) {
  switch (state) {
    case Laser_Init:
      state = Laser_Depress;
      break;
    case Laser_Depress:
       if (digitalRead(BUTTON_INPUT) == HIGH) state = Laser_Press1;
      break;
    case Laser_Press1:
      state = Laser_Press2;
      break;
    case Laser_Press2:
      state = Laser_Wait;
      break;
    case Laser_Wait:
      if (digitalRead(BUTTON_INPUT) == LOW) state = Laser_Depress;
      break;
    default:
      state = Laser_Init;
      break;
  }

  switch (state) {
    case Laser_Init:
    case Laser_Depress:
    case Laser_Wait:
      digitalWrite(LASER_OUTPUT, LOW);
      break;
    case Laser_Press1:
    case Laser_Press2:
      digitalWrite(LASER_OUTPUT, HIGH);
      break;
    default:
      break;
  }
  
  return state;
}
