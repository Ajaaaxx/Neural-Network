#include "network.hpp"
#include <iostream>
#include "../json.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
using json = nlohmann::json;

Network::Network(){

}

void Network::load(std::string file) {
  std::string jsonString;
  std::ifstream in(file);
  std::stringstream buffer;
  buffer << in.rdbuf();
  jsonString = buffer.str();
  
  json j = json::parse(jsonString);
  //std::cout << jsonString  << std::endl;
  std::string n;

  int size = 1;
  stringstream s;
  while (pow(10,size) < j.size()) {
    size++;
  }
  
  n = "Layer";
  s.str("");s.clear();
  s << setw(size) << setfill('0') << "0";
  n += s.str();
  
  for (int i = 0; i < j.size();i) {
    if (i == 0) {
      layers.push_back(new Layer(j[n].size()));
    } else {
      layers.push_back(new Layer(j[n].dump(), layers.back()));
    }
    n = "Layer";
    s.str("");s.clear();
    s << setw(size) << setfill('0') << to_string(++i);
    n += s.str();;
  }
}

void Network::save(std::string file) {
  std::ofstream out(file);
  string jsonS = getJson();
  out << jsonS;
  out.close();
}

Layer * Network::get(int i) {
  return layers[i];
}

void Network::add(Layer* c){
  if(layers.empty()){
    layers.push_back(c);
  }
  else{
    c->relier(layers.back());
    layers.push_back(c);
  }
}

void Network::add(int n) {
  Layer * c = new Layer(n);
  if(layers.empty()){
    layers.push_back(c);
  }
  else{
    c->relier(layers.back());
    layers.push_back(c);
  }
}

std::string Network::getJson() {
  std::string json = "{";
  stringstream s;
  int size = 1;
  while (pow(10,size) < layers.size()) {
    size++;
  }
  for (int i = 0; i < layers.size(); i++) {
    s.str("");s.clear();
    s << setw(size) << setfill('0') << std::to_string(i);
    json += "\"Layer" + s.str() + "\" : ";
    json += layers[i]->getJson();
    json += ",";
  }
  json.pop_back();
  json += "}";
  
  return json;
}

void Network::setInputs(vector<double> d) { //Permet de mettre les entrées
  assert(d.size() == layers[0]->getNeurons().size());
  for (int i = 0; i < d.size(); i++) {
    layers[0]->getNeurons()[i]->setValue(d[i]);
  }
}
void Network::setResult(vector<double> d) { //Permet de mettre les sorties attendues
  assert(d.size() == layers.back()->getNeurons().size());
  for (int i = 0; i < d.size(); i++) {
    layers.back()->getNeurons()[i]->setErreur(d[i]-layers.back()->getNeurons()[i]->getValue());
  }
}

void Network::resetErreur() {
  for (int i = 0; i < layers.size(); i++) {
    layers[i]->resetErreur();
  }
}

double Network::train(vector<double> in, vector<double> out) {
  //double somme = 0;
  setInputs(in);
  for (int i = 1; i < layers.size(); i++) {
    layers[i]->eval();
  }
  setResult(out);
  for (int i = layers.size()-1; i > 0; i--) {
    layers[i]->updateErreur();
    layers[i]->updatePoids();
  }
  //std::cout << "Résultat attendu : " << out[0] << endl << "Résultat obtenu : " << layers.back()->getNeurons()[0]->getValue() << endl << endl;
  /*
  for (int i = 0; i < layers.back()->getNeurons().size(); i++) {
    somme += layers.back()->getNeurons()[i]->getErreur();
  }
  */
  resetErreur();
  //return (somme/layers.back()->getNeurons().size());
  return 0;
}

double Network::test(vector<double> in, vector<double> out) {
  double somme = 0;
  setInputs(in);
  for (int i = 1; i < layers.size(); i++) {
    layers[i]->eval();
  }
  setResult(out);
  for (int i = layers.size()-1; i > 0; i--) {
    layers[i]->updateErreur();
    //layers[i]->updatePoids();
  }
  //std::cout << "Résultat attendu : " << out[0] << endl << "Résultat obtenu : " << layers.back()->getNeurons()[0]->getValue() << endl << endl;
  for (int i = 0; i < layers.back()->getNeurons().size(); i++) {
    somme += layers.back()->getNeurons()[i]->getErreur();
  }
  resetErreur();
  return (somme/layers.back()->getNeurons().size());
}

void Network::afficheTout() {
  for (int i = 0; i < layers.size(); i++) {
    std::cout << "Couche " << i << std::endl;
    for (int j = 0; j < layers[i]->getNeurons().size(); j++) {
      std::cout << "Neurone " << j << std::endl;
      for (int k = 0; k < layers[i]->getNeurons()[j]->getPoids().size(); k++) {
	std::cout << "Input " << k << " : " << layers[i]->getNeurons()[j]->getPoids()[k] << std::endl;
      }
    }
  }
}

void Network::afficheToutErreur() {
  for (int i = 0; i < layers.size(); i++) {
    std::cout << "Couche " << i << std::endl;
    for (int j = 0; j < layers[i]->getNeurons().size(); j++) {
      std::cout << "Erreur Neurone " << j << " : " << layers[i]->getNeurons()[j]->getErreur() << std::endl;
    }
  }
}
