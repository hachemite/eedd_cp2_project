// Initialisation des variables :
int m1a = 9;
int m1b = 10;
int m2a = 11;
int m2b = 12;
char val;
const int trigPin1 = 7;
const int echoPin1 = 4;
long duration1;



int distance1;
// m1a, m1b, m2a, m2b : Définissent les broches de contrôle des deux moteurs.
// val : Variable pour stocker les valeurs reçues via Bluetooth.
// trigPin1, echoPin1 : Broches pour le capteur à ultrasons.
// duration1 : Stocke la durée du signal ultrasonique.
// distance1 : Stocke la distance mesurée par le capteur à ultrasons.

//Configuration initiale :
void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(m1a, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m2b, OUTPUT);
  Serial.begin(9600);
}

// pinMode() : Configure les broches comme entrées ou sorties.
// Serial.begin(9600) : Initialise la communication série à 9600 bauds pour recevoir les
//commandes via Bluetooth. (La communication série est une méthode de transfert de données
//entre un ordinateur et un périphérique ou entre deux microcontrôleurs).
//Boucle principale :
void loop() {
  while (Serial.available() > 0) {
    val = Serial.read();
    Serial.println(val);
  }
  // Serial.available() : Vérifie s'il y a des données disponibles pour être lues depuis le port série.
  // Serial.read() : Lit les données reçues et les stocke dans val.
  // Serial.println(val) : Affiche la valeur lue pour le débogage.

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance1);

  // digitalWrite() : Envoie un signal d'impulsion pour déclencher le capteur à ultrasons.
  // pulseIn() : Mesure la durée de l'impulsion renvoyée par l'écho du capteur.
  // distance1 = duration1 * 0.034 / 2 : Calcule la distance en cm en utilisant la durée de
  // l'impulsion.

  if (val == 'F') {
    if (distance1 < 30) {
      digitalWrite(m1a, LOW);
      digitalWrite(m1b, LOW);
      digitalWrite(m2a, LOW);
      digitalWrite(m2b, LOW);
      delay(1000);
    }
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);
  } else if (val == 'B') {
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, HIGH);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, HIGH);
  } else if (val == 'L') {
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);
  } else if (val == 'R') {
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);
  } else if (val == 'S')



  {
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);
  } else if (val == 'I') {
    digitalWrite(m1a, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);
  } else if (val == 'J') {
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, HIGH);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, LOW);
  } else if (val == 'G') {
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, HIGH);
    digitalWrite(m2b, LOW);
  } else if (val == 'H') {
    digitalWrite(m1a, LOW);
    digitalWrite(m1b, LOW);
    digitalWrite(m2a, LOW);
    digitalWrite(m2b, HIGH);
  }
}
// if(val == 'F') : Si la commande reçue est 'F', le fauteuil avance.
// if(distance1 < 30) : Si un obstacle est détecté à moins de 30 cm, le fauteuil s'arrête pour éviter la collision.
// else if(val == 'B') : Si la commande reçue est 'B', le fauteuil recule.
// else if(val == 'L') : Si la commande reçue est 'L', le fauteuil tourne à gauche.
// else if(val == 'R') : Si la commande reçue est 'R', le fauteuil tourne à droite.
// else if(val == 'S') : Si la commande reçue est 'S', le fauteuil s'arrête.
// else if(val == 'I') : Si la commande reçue est 'I', le fauteuil avance à droite.
// else if(val == 'J') : Si la commande reçue est 'J', le fauteuil recule à droite.
// else if(val == 'G') : Si la commande reçue est 'G', le fauteuil avance à gauche.
// else if(val == 'H') : Si la commande reçue est 'H', le fauteuil recule à gauche.