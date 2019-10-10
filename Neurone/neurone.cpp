#include "neurone.hpp"
#include <math.h>

double sigmoide(double x) {
  return 1.f/(1+std::exp(-x));
}

double d_sigmoide(double x) {
  return sigmoide(x)*(1-sigmoide(x));
}

Neurone::Neurone() {
  valeur = 0;
  d_valeur = 0;
  erreur = 0;
}

Neurone::Neurone(std::vector<Neurone*> n) {
  inputs = n;
  for (int i = 0; i < n.size(); i++) {
    double val = ((rand()%201-100.f)/100.f);
    poids.push_back(val);
    //std::cout << poids[i] << std::endl;
  }
}

void Neurone::setInputs(std::vector<Neurone*> n) {
  inputs = n;
  for (int i = 0; i < n.size(); i++) {
    double val = ((rand()%201-100.f)/100.f);
    poids.push_back(val);
    //std::cout << poids[i] << std::endl;
  }
}

void Neurone::setValue(double v) {
  valeur = v;
}

double Neurone::getValue() {
  return valeur;
}

void Neurone::eval() {
  double somme = 0;
  for (int i = 0; i < inputs.size(); i++) {
    somme += inputs[i]->getValue()*poids[i];
  }

  valeur = sigmoide(somme);
  d_valeur = d_sigmoide(somme);
  //valeur = somme<=0?0:1;
  
  //std::cout << "Resultat = " << valeur << std::endl;
}

void Neurone::setErreur(double e) {
  erreur = e;
}

double Neurone::getErreur() {
  return erreur;
}

void Neurone::updateErreur() {
  if (erreur != 0) {
    for (int i = 0; i < inputs.size(); i++) { //Pour chaque neurone de inputs
      inputs[i]->setErreur(inputs[i]->getErreur() + (erreur * poids[i]));
      //std::cout << "E : " << inputs[i]->getErreur() << std::endl;
    }
    //std::cout << std::endl;
  }
}

void Neurone::updatePoids() {
  double learning_rate = 0.5;
  for (int i = 0; i < inputs.size(); i++) {
    poids[i] += learning_rate*erreur*d_valeur*inputs[i]->getValue();
  }
}
