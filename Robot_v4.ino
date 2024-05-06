

// Déclaration des librairie
#include <Pixy2.h>        // Fonctions pour la caméra
#include <ZumoMotors.h>   // Fonctions pour les moteurs

//déclaration du zumo et de la caméra
Pixy2 pixy;               // Déclaration de la caméra
ZumoMotors motors;        // Déclaration des moteurs

// Déclaration des variables
int signature=1;  // La caméra a été configurée pour détecter du jaune sur la signature 1
int LargeurRef=20;  // 20px pour une gommette à 10 cm (8 mm  de diamètre)
int LargeurMesure=0;  // Variable contient la distance réelle entre le mire et le robot
float erreur_Largeur=0; // Ecart entre la mesure et la référence
int PositionRef=158;  // 158px pour une gommette au centre de la caméra
int PositionMesure=0;  // Variable contient la positon sur x de la mire
float erreur_Position=0; // Ecart entre la mesure et la référence
int vitesse = 0;

void setup(void) {
  // Robot à l'arrêt
  motors.setLeftSpeed(0);
  motors.setRightSpeed(0);
  
  Serial.begin(115200); // Initialisation du moniteur série à 115200 bauds
  Serial.print("Lancement du programme...\n");  // Texte à afficher sur le moniteur série
  
  pixy.init(); // Initialisation de la caméra
  //pixy.setLamp(1, 1); // Allumer la lumière de la caméra
}

void loop(void){
  pixy.ccc.getBlocks(); // Lire les données de la caméra
  if(pixy.ccc.blocks[0].m_signature == signature){  // Si la signature a été détéctée
    // Détection de la distance entre le robot et la mire
    LargeurMesure = pixy.ccc.blocks[0].m_width;
    erreur_Largeur=LargeurRef - LargeurMesure;

    // Détection de la position de la mire
    PositionMesure = pixy.ccc.blocks[0].m_x;
    erreur_Position = PositionRef - PositionMesure;
    
    // Chargement de la vitesse des roues
    vitesse=int(15 * erreur_Largeur); // Dimensionnement de la vitesse
    motors.setLeftSpeed(vitesse-erreur_Position);
    motors.setRightSpeed(vitesse+erreur_Position); 
    
    Serial.println("Mire détectée");  // Ecrire sur le moniteur "Mire détectée"
  }
  else {
    // Robot à l'arrêt
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);
    Serial.println("Mire perdue");  // Ecrire sur le moniteur "Mire perdue"
  }
}
