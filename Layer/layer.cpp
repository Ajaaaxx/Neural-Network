#include "layer.hpp"

Layer::Layer() {

}

Layer::Layer(std::vector<Neuron*> n) {
  neurones = n;
}

Layer::Layer(std::vector<Neuron*> n, Neuron * b) {
  neurones = n;
  biais = b;
}

Layer::Layer(int i) {
  for (int x = 0; x < i; x++) {
    neurones.push_back(new Neuron());
  }
}

void Layer::ajouterNeuron(Neuron * n) {
  neurones.push_back(n);
}

void Layer::ajouterBiais(Neuron * n) {
  if (biais != NULL) //A vérifier
    delete biais;
  biais = n;
}

std::vector<Neuron*> Layer::getNeurons() {
  return neurones;
}

void Layer::relier(Layer * c) {
  for (int j = 0; j < neurones.size(); j++) { //Pour chaque neurone de la couche actuelle
    neurones[j]->setInputs(c->getNeurons());
  }
}

void Layer::eval() {
  for (int i = 0; i < neurones.size(); i++) {
    neurones[i]->eval();
  }
}

void Layer::resetErreur() {
  for (int i = 0; i < neurones.size(); i++) {
    neurones[i]->setErreur(0);
  }
}

void Layer::updateErreur() {
  for (int i = 0; i < neurones.size(); i++) {
    neurones[i]->updateErreur();
  }
}

void Layer::updatePoids() {
  for (int i = 0; i < neurones.size(); i++) {
    neurones[i]->updatePoids();
  }
}

std::string Layer::getJson() {
  std::string json = "{";
  for (int i = 0; i < neurones.size(); i++) {
    json += "\"Neuron" + std::to_string(i) + "\" : "; 
    json += neurones[i]->getJson();
    json += ",";
  }
  json.pop_back();
  json += "}";
  
  return json;
}
