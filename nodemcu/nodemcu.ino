#include "wifi.h"
#include "screen.h"
#include "status.h"
#include "task.h"

const unsigned short tasksNum = 4;
task tasks[tasksNum];

void setup() {
  // Task Scheduler
  int i = 0;
  tasks[i].state = 0;
  tasks[i].period = 500;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &screenTickFct;
  i++;
  tasks[i].state = ShootLow;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &shootTickFct;
  i++;
  tasks[i].state = ReloadLow;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &reloadTickFct;
  i++;
  tasks[i].state = AliveIdle;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &aliveTickFct;
  // put your setup code here, to run once:
  setup_wifi();
  _ID = generate();
  Serial.begin(9600);
  Serial.print("ID is:");
  Serial.println(_ID);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  pinMode(shootPin, INPUT);
  pinMode(reloadPin, INPUT);
  pinMode(alivePin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned short i;
  for(i = 0; i < tasksNum; i++) {
    if( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis();
    }
  }
}
