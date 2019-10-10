#ifndef _NEURON
#define _NEURON

#include <vector>
#include <string>

class Neuron {
private:
  double valeur; //Valeur du neurone après calcul
  double d_valeur; //Valeur dérivée
  double erreur;
  std::vector<Neuron*> inputs; //Tableau de pointeur de neurones
  std::vector<double> poids; //Tableau des poids
public:
  Neuron(); //Initialisation du neurone sans inputs ni poids
  Neuron(std::vector<Neuron*>); //Initialisation du neurone avec les inputs et coeficients random (-1 à 1 ou 0 à 1 ?)
  void setInputs(std::vector<Neuron*>); //Actualise inputs et créer des coefficients random
  void setValue(double);
  double getValue();
  void eval(); //Calcul la valeur d'entrée et la stocke
  void setErreur(double);
  double getErreur();
  void updateErreur(); //Met à jour les erreurs des neurones précédents en fonction de "erreur"
  void updatePoids(); //Met à jour les poids en fonction des erreurs
  std::string getJson(); //Permet d'obtenir le json du neurone
};

#endif
