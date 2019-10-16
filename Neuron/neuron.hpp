#ifndef _NEURON
#define _NEURON

#include <vector>
#include <string>

class Neuron {
private:
  double valeur; //Valeur du neurone après calcul
  double d_valeur; //Valeur dérivée
  double erreur;
  double learning_rate;
  std::vector<Neuron*> inputs; //Tableau de pointeur de neurones
  std::vector<double> poids; //Tableau des poids
public:
  Neuron(); //Initialisation du neurone sans inputs ni poids
  Neuron(std::vector<Neuron*>); //Initialisation du neurone avec les inputs et coeficients random (-1 à 1 ou 0 à 1 ?)
  Neuron(std::string json, std::vector<Neuron*> l); //Initialisation du neurone via json (autres couches)
  void setInputs(std::vector<Neuron*>); //Actualise inputs et créer des coefficients random
  void setValue(double);
  double getPoids(int i);
  void setPoids(int i, double d);
  double getValue();
  void eval(); //Calcul la valeur d'entrée et la stocke
  void setErreur(double);
  double getErreur();
  void updateErreur(); //Met à jour les erreurs des neurones précédents en fonction de "erreur"
  void updatePoids(); //Met à jour les poids en fonction des erreurs
  std::vector<double> getDeltaPoids(); //Permet d'obtenir le vecteur des poids à ajouter
  std::vector<double> getPoids();
  std::string getJson(); //Permet d'obtenir le json du neurone
};

#endif
