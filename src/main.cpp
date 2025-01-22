#include <TaskScheduler.h>

#define LED_PIN 13 // Broche de la LED

// Création du planificateur
Scheduler runner;

// Prototypes des fonctions
void toggleLED();       // Fonction pour basculer l'état de la LED
void blinkFast();       // Fonction pour clignoter rapidement
void blinkSlow();       // Fonction pour clignoter lentement
void turnOffLED();      // Fonction pour éteindre la LED

// Création des tâches
Task t1(500, TASK_FOREVER, &toggleLED);  // Clignote toutes les 500 ms
Task t2(250, 20, &blinkFast);           // Clignote rapidement (toutes les 250 ms, 20 fois)
Task t3(1000, TASK_FOREVER, &blinkSlow); // Clignote lentement (toutes les 1000 ms)
Task t4(10000, 1, &turnOffLED);          // Éteint la LED après 10 secondes

void setup() {
  pinMode(LED_PIN, OUTPUT); // Configure la broche de la LED comme sortie
  runner.init();            // Initialise le planificateur

  // Ajoute les tâches au planificateur
  runner.addTask(t1);
  runner.addTask(t2);
  runner.addTask(t3);
  runner.addTask(t4);

  // Active les tâches
  t1.enable();
  t2.enable();
  t3.enable();
  t4.enable();
}

int main(void) {
  setup();  // Appelle la fonction de configuration

  while (true) {
    runner.execute(); // Exécute les tâches planifiées
  }

  return 0;
}

// Bascule l'état de la LED
void toggleLED() {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

// Clignote rapidement la LED
void blinkFast() {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

// Clignote lentement la LED
void blinkSlow() {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

// Éteint la LED
void turnOffLED() {
  digitalWrite(LED_PIN, LOW); // Met la LED à l'état éteint
}
