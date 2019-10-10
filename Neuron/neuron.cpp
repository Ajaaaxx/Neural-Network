#include "neuron.hpp"
#include <math.h>

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
}

Neuron::Neuron(std::vector<Neuron*> n) {
  inputs = n;
  for (int i = 0; i < n.size(); i++) {
    double val = ((rand()%201-100.f)/100.f);
    poids.push_back(val);
    //std::cout << poids[i] << std::endl;
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
  double learning_rate = 0.5;
  for (int i = 0; i < inputs.size(); i++) {
    poids[i] += learning_rate*erreur*d_valeur*inputs[i]->getValue();
  }
}

std::string Neuron::getJson() {
  std::string json = "";
  //On initialise le json avec l'adresse et la fonction d'activation
  if (!inputs.empty()) {
    json += "{\"f_activation\" : \"sigmoide\", \"inputs\" : {";
    for (int i = 0; i < inputs.size(); i++) {
      json += "\"Neuron" + std::to_string(i) + "\" : " + "\"" + std::to_string(poids[i]) + "\",";
    }
    json.pop_back(); //Pour enlever la , en trop
    json += "}}";
  } else {
     json += "{\"f_activation\" : \"sigmoide\", \"inputs\" : {}}";
  }
  return json;
}
