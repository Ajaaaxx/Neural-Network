#ifndef _LAYER
#define _LAYER

#include "../Neuron/neuron.hpp"
#include <string>

class Layer {
private:
  std::vector<Neuron*> neurones;
  Neuron * biais; //Inutiliser pour le moment
public:
  Layer(); //Layer vide sans neurones ni biais
  Layer(std::vector<Neuron*>); //Layer initialisée avec les neurones
  Layer(std::vector<Neuron*>,Neuron *); //Layer initialisée avec les neurones et le biais
  Layer(std::string json, Layer * c); //Init avec json et Couche précédente
  Layer(int); //Layer avec i neurones
  void ajouterNeuron(Neuron *);
  void ajouterBiais(Neuron *);
  std::vector<Neuron*> getNeurons();
  void relier(Layer *); //Pour le moment => fully connected
  void eval(); //Evalue tous les neurones de la couche
  void resetErreur();
  void updateErreur();
  void updatePoids();
  std::string getJson();
};

#endif
