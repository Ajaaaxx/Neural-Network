#include "layer.hpp"
#include "../json.hpp"
#include <iostream>

using namespace std;
using json = nlohmann::json;

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

Layer::Layer(std::string jsonString, Layer * c) {
  /*
  std::cout << "Création de la couche" << std::endl;
  std::cout << jsonString << std::endl;
  std::cout << std::endl;
  */
  json j = json::parse(jsonString);
  std::string n = "Neuron0";
  for (int i = 0; i < j.size();i) {
    neurones.push_back(new Neuron(j[n].dump(), c->getNeurons()));
    n.pop_back();
    n += std::to_string(++i);
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
