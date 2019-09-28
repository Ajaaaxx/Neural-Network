#ifndef _COUCHE
#define _COUCHE

#include "../Neurone/neurone.hpp"

class Couche {
private:
  std::vector<Neurone*> neurones;
  Neurone * biais; //Inutiliser pour le moment
public:
  Couche(); //Couche vide sans neurones ni biais
  Couche(std::vector<Neurone*>); //Couche initialisée avec les neurones
  Couche(std::vector<Neurone*>,Neurone *); //Couche initialisée avec les neurones et le biais
  Couche(int); //Couche avec i neurones
  void ajouterNeurone(Neurone *);
  void ajouterBiais(Neurone *);
  std::vector<Neurone*> getNeurones();
  void relier(Couche *); //Pour le moment => fully connected
  void eval(); //Evalue tous les neurones de la couche
  void resetErreur();
  void updateErreur();
  void updatePoids();
};

#endif
