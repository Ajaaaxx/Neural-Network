#ifndef _NETWORK
#define _NETWORK

#include "../Layer/layer.hpp"

class Network{
private:
  std::vector<Layer*> layers;

public:
  Network();
  //Network(std::string);
  Layer * get(int i);
  void add(Layer* c);
  void add(int n); //Ajout d'une couche de n neurones en fully connected
  void load(std::string file);
  void save(std::string file);
  std::string getJson();
  void setInputs(std::vector<double> d); //Permet de mettre les entrées
  void setResult(std::vector<double> d); //Permet de mettre les sorties attendues
  void resetErreur();
  double train(std::vector<double> i, std::vector<double> o); //i : inputs, o : outputs attendus, retourne la valeur de l'erreur
  double test(std::vector<double> i, std::vector<double> o);
  void afficheTout(); //Affiche tous les coefs de toutes les couches
  void afficheToutErreur();
};

#endif
