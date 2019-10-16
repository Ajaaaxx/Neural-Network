#include "neuron.hpp"
#include "../json.hpp"
#include <math.h>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;
using json = nlohmann::json;

double sigmoide(double x) {
  return 1.f/(1+std::exp(-x));
}

double d_sigmoide(double x) {
  return sigmoide(x)*(1-sigmoide(x));
}

Neuron::Neuron() {
  valeur = 0;
  d_valeur = 0;
  erreur = 0;
  learning_rate = 0.1;
}

Neuron::Neuron(std::vector<Neuron*> n) {
  valeur = 0;
  d_valeur = 0;
  erreur = 0;
  learning_rate = 0.1;
  
  inputs = n;
  for (int i = 0; i < n.size(); i++) {
    double val;
    do {
      val = ((rand()%201-100.f)/1000.f);
    } while (val == 0);
    poids.push_back(val);
    //std::cout << poids[i] << std::endl;
  }
}

Neuron::Neuron(std::string jsonString, vector<Neuron*> l) { //BUG 0
  valeur = 0;
  d_valeur = 0;
  erreur = 0;
  learning_rate = 0.1;
  
  json j = json::parse(jsonString);
  string n;
  int size = 1;
  stringstream s;
  while (pow(10,size) < l.size()) {
    size++;
  }

  n = "Neuron";
  s.str("");s.clear();
  s << setw(size) << setfill('0') << "0";
  n += s.str();
  
  for (int i = 0; i < l.size();i) {
    poids.push_back(j["inputs"][n]);
    inputs.push_back(l[i]);
    n = "Neuron";
    s.str("");s.clear();
    s << setw(size) << setfill('0') << to_string(++i);
    n += s.str();
  }
}


void Neuron::setInputs(std::vector<Neuron*> n) {
  inputs = n;
  for (int i = 0; i < n.size(); i++) {
    double val = ((rand()%201-100.f)/100.f);
    poids.push_back(val);
    //std::cout << poids[i] << std::endl;
  }
}

double Neuron::getPoids(int i) {
  return poids[i];
}

void Neuron::setPoids(int i, double d) {
  poids[i] = d;
}

void Neuron::setValue(double v) {
  valeur = v;
}

double Neuron::getValue() {
  return valeur;
}

void Neuron::eval() {
  double somme = 0;
  for (int i = 0; i < inputs.size(); i++) {
    somme += inputs[i]->getValue()*poids[i];
  }

  valeur = sigmoide(somme);
  d_valeur = d_sigmoide(somme);
  //valeur = somme<=0?0:1;
  
  //std::cout << "Resultat = " << valeur << std::endl;
}

void Neuron::setErreur(double e) {
  erreur = e;
}

double Neuron::getErreur() {
  return erreur;
}

void Neuron::updateErreur() {
  if (erreur != 0) {
    for (int i = 0; i < inputs.size(); i++) { //Pour chaque neurone de inputs
      inputs[i]->setErreur(inputs[i]->getErreur() + (erreur * poids[i]));
      //std::cout << "E : " << inputs[i]->getErreur() << std::endl;
    }
    //std::cout << std::endl;
  }
}

void Neuron::updatePoids() {
  for (int i = 0; i < inputs.size(); i++) {
    poids[i] += learning_rate*erreur*d_valeur*inputs[i]->getValue();
  }
}

std::string Neuron::getJson() { //BUG 0
  std::string json = "";
  //On initialise le json avec l'adresse et la fonction d'activation
  if (!inputs.empty()) {
    json += "{\"f_activation\" : \"sigmoide\", \"inputs\" : {";
    int size = 1;
    while (pow(10,size) < inputs.size()) {
      size++;
    }
    stringstream s;
    for (int i = 0; i < inputs.size(); i++) {
      s.str("");s.clear();
      s << setw(size) << setfill('0') << std::to_string(i);
      json += "\"Neuron" + s.str() + "\" : " +  std::to_string(poids[i]) + ",";
    }
    json.pop_back(); //Pour enlever la , en trop
    json += "}}";
  } else {
     json += "{\"f_activation\" : \"sigmoide\", \"inputs\" : {}}";
  }
  return json;
}

std::vector<double> Neuron::getDeltaPoids() {
  std::vector<double> dPoids;
  for (int i = 0; i < inputs.size(); i++) {
    dPoids.push_back(learning_rate*erreur*d_valeur*inputs[i]->getValue());
  }
  return dPoids;
}

std::vector<double> Neuron::getPoids() {
  return poids;
}
