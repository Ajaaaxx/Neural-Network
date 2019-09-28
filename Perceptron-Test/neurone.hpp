#ifndef _NEURONE
#define _NEURONE

#include <vector>

class Neurone {
private:
  double valeur; //Valeur du neurone après calcul
  std::vector<Neurone*> inputs; //Tableau de pointeur de neurones
  std::vector<double> poids; //Tableau des poids
public:
  Neurone(); //Initialisation du neurone sans inputs ni poids
  Neurone(std::vector<Neurone*>); //Initialisation du neurone avec les inputs et coeficients random (-1 à 1 ou 0 à 1 ?)
  void setValue(double);
  double getValue();
  void eval(); //Calcul la valeur d'entrée et la stocke
  void train(float target); //Corrige l'erreur en fonction de target
};

#endif