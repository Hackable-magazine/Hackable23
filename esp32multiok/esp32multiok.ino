#define LED 2

TaskHandle_t tache1;
TaskHandle_t tache2;

unsigned long previousMillis = 0;

void codeTache(void *arg) {
  while(true) {
    Serial.print(">> ici la tâche 1 sur le coeur ");
    Serial.println(xPortGetCoreID());
    delay(2000);
  }
}

void codeTacheLed(void *arg) {
  while(true) {
    digitalWrite(LED, LOW);
    delay(100);
    digitalWrite(LED, HIGH);
    delay(150);
    digitalWrite(LED, LOW);
    delay(100);
    digitalWrite(LED, HIGH);
    Serial.print(">> ici la tâche 2 sur le coeur ");
    Serial.println(xPortGetCoreID());
    delay(1000);
  }
}

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);

  xTaskCreatePinnedToCore(
    codeTache,  // fonction utilisée pour la tâche
    "tache1",   // nom de la tache (16 car. max)
    1000,       // taille de la pile pour la tâche
    NULL,       // arguments pour la fonction 
    1,          // priorité
    &tache1,    // handler pour la tâche
    0);         // coeur à utiliser

/*
  xTaskCreatePinnedToCore(
    codeTacheLed, // fonction utilisée pour la tâche
    "tacheled",   // nom de la tache (16 car. max)
    1000,         // taille de la pile pour la tâche
    NULL,         // arguments pour la fonction 
    1,            // priorité
    &tache2,      // handler pour la tâche
    1);           // coeur à utiliser
*/

/*
  vTaskPrioritySet(&tache1, 1);
  vTaskPrioritySet(&tache2, 1);
*/
}


void loop() {
  unsigned long currentMillis = millis();

  Serial.print("Loop sur coeur ");
  Serial.println(xPortGetCoreID());
  Serial.print("Nombre de taches : ");
  Serial.println(uxTaskGetNumberOfTasks());
  delay(3000);

  if (currentMillis - previousMillis >= 15000) {
    Serial.println("Kill");
    if(tache1 != NULL) {
      vTaskDelete(tache1);
      tache1 = NULL;
    }
    previousMillis = currentMillis;
  }

/*
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(150);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(3000);
*/
}
