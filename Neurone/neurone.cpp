#include "neurone.hpp"
#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include <math.h>

double sigmoide(double x) {
  return 1.f/(1+std::exp(-x));
}

Neurone::Neurone() {
  valeur = 0;
  erreur = 0;
}

Neurone::Neurone(std::vector<Neurone*> n) {
  inputs = n;
  for (int i = 0; i < n.size(); i++) {
    double val = ((rand()%201-100.f)/100.f);
    poids.push_back(val);
    std::cout << poids[i] << std::endl;
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
  //valeur = somme<=0?0:1;
  
  std::cout << "Resultat = " << valeur << std::endl;
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
      std::cout << "E : " << inputs[i]->getErreur() << std::endl;
    }
    std::cout << std::endl;
  }
}

void Neurone::train(float target) {
  float error = target - valeur;
  for (int i = 0; i < poids.size(); i++) {
    poids[i] += error * inputs[i]->getValue();
  }
  std::cout << "Erreur = " << error << std::endl;
  std::cout << poids[0] << " " << poids[1] << std::endl;
}

int main() {
  srand (time(NULL));
  
  Neurone * n1 = new Neurone();
  Neurone * n2 = new Neurone();
  Neurone * n3 = new Neurone();
  std::vector<Neurone*> c1;
  c1.push_back(n1);
  c1.push_back(n2);
  c1.push_back(n3);

  Neurone * n4 = new Neurone(c1);
  Neurone * n5 = new Neurone(c1);
  std::vector<Neurone*> c2;
  c2.push_back(n4);
  c2.push_back(n5);

  Neurone * out = new Neurone(c2);

  n1->setValue(1);
  n2->setValue(1);
  n3->setValue(1);

  n4->eval();
  n5->eval();

  out->eval();

  out->setErreur(1-out->getValue());
  /*
    Condition nécessaire avant de rétropropager l'erreur :
    Les erreurs de couches précédentes doivent être réinitialiser à 0
   */
  n4->setErreur(0);
  n5->setErreur(0);
  out->updateErreur(); //Rétropropagation de l'erreur à la couche 2

  n1->setErreur(0);
  n2->setErreur(0);
  n3->setErreur(0);
  n4->updateErreur();
  n5->updateErreur();
  
  return 0;
}
