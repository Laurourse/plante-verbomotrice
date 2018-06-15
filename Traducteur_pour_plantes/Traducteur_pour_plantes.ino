//Associer les broches correspondantes au détecteur d'humidité, définir une
//intégrale "Valeur" pour lire les données du détecteur et définir les valeurs
//maximale et minimale du niveau d'humidité
int sensorPin = A0;
int sensorPower = 7;
int sensorValue = 0;
int thresholdUp = 800;
int thresholdDown = 650;

//Ajouter la bibliothèque qui permettra au LCD de fonctionner
//et associer les bonnes broches au LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); 

void setup() {
  Serial.begin(9600);

  //Identifier la prise D7 comme sortie pour alimenter le détecteur d'humidité
  pinMode(sensorPower, OUTPUT); 
  digitalWrite(sensorPower, LOW);

  //Indiquer au microcontrôleur que l'affichage LCD utilisé a 16 caractères de long
  //et 2 caractères de haut, puis effacer l'affichage
  lcd.begin(16, 2);
  lcd.clear();
  
}

void loop() {
  //Imprimer les valeurs du niveau d'humidité sur le monteur série à chaque
  //intervalle de 2 secondes
  Serial.print("Niveau d humidite = ");
  Serial.println(readSensor());
  delay(2000);

  //Définir les conditions d'affichage des 3 messages (trop d'eau, pas assez, correct)
  if(sensorValue <= thresholdDown){
    lcd.setCursor(0,0);
    lcd.print("C'est le deluge!"); //Ce qui s'affiche quand l'humidité est élevée
    delay(2000);
    lcd.clear();
  } else if (sensorValue >= thresholdUp){
    lcd.setCursor(0,0);
    lcd.print("Sors l'arrosoir!"); //Ce qui s'affiche si l'humidité est trop basse
    delay(2000);
    lcd.clear();
  } else {
    lcd.print("Juste un peu..."); //Ce qui s'affiche quand l'humidité est bonne
    delay(2000);
    lcd.clear();
  }
}

//Expliquer au microcontrôleur comment on veut qu'il lise les données envoyées
//par le détecteur d'humidité
int readSensor(){
    digitalWrite(sensorPower, HIGH);
    delay(10);
    sensorValue = analogRead(sensorPin); 
    digitalWrite(sensorPower, LOW);
    return sensorValue;
}

