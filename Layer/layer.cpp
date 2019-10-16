#include "layer.hpp"
#include "../json.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

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
  json j = json::parse(jsonString);
  std::string n;
  int size = 1;
  stringstream s;
  while (pow(10,size) < j.size()) {
    size++;
  }
  
  n = "Neuron";
  s.str("");s.clear();
  s << setw(size) << setfill('0') << "0";
  n += s.str();
  
  for (int i = 0; i < j.size();i) {
    neurones.push_back(new Neuron(j[n].dump(), c->getNeurons())); //Erreur
    n = "Neuron";
    s.str("");s.clear();
    s << setw(size) << setfill('0') << to_string(++i);
    n += s.str();
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

std::vector<std::vector<double>> Layer::getDeltaPoids() {
  std::vector<std::vector<double>> dPoids;
  for (int i = 0; i < neurones.size(); i++) {
    dPoids.push_back(neurones[i]->getDeltaPoids());
  }
  return dPoids;
}

std::string Layer::getJson() {
  std::string json = "{";
  int size = 1;
  while (pow(10,size) < neurones.size()) {
    size++;
  }
  stringstream s;
  for (int i = 0; i < neurones.size(); i++) {
    s.str("");s.clear();
    s << setw(size) << setfill('0') << std::to_string(i);
    json += "\"Neuron" + s.str() + "\" : "; 
    json += neurones[i]->getJson();
    json += ",";
  }
  json.pop_back();
  json += "}";
  
  return json;
}
