#include "couche.hpp"
#include <stdlib.h> 
#include <time.h>
#include <iostream>

Couche::Couche() {

}

Couche::Couche(std::vector<Neurone*> n) {
  neurones = n;
}

Couche::Couche(std::vector<Neurone*> n, Neurone * b) {
  neurones = n;
  biais = b;
}

Couche::Couche(int i) {
  for (int x = 0; x < i; x++) {
    neurones.push_back(new Neurone());
  }
}

void Couche::ajouterNeurone(Neurone * n) {
  neurones.push_back(n);
}

void Couche::ajouterBiais(Neurone * n) {
  if (biais != NULL) //A vérifier
    delete biais;
  biais = n;
}

std::vector<Neurone*> Couche::getNeurones() {
  return neurones;
}

void Couche::relier(Couche * c) {
  for (int j = 0; j < neurones.size(); j++) { //Pour chaque neurone de la couche actuelle
    neurones[j]->setInputs(c->getNeurones());
  }
}

void Couche::eval() {
  for (int i = 0; i < neurones.size(); i++) {
    neurones[i]->eval();
  }
}

void Couche::resetErreur() {
  for (int i = 0; i < neurones.size(); i++) {
    neurones[i]->setErreur(0);
  }
}

void Couche::updateErreur() {
  for (int i = 0; i < neurones.size(); i++) {
    neurones[i]->updateErreur();
  }
}

void Couche::updatePoids() {
  for (int i = 0; i < neurones.size(); i++) {
    neurones[i]->updatePoids();
  }
}

int main() {
  srand (time(NULL));
 
  Couche * c1 = new Couche(3);
  Couche * c2 = new Couche(2);
  Couche * c3 = new Couche(1);
  c2->relier(c1);
  c3->relier(c2);

  for (int i = 0; i < 100000; i++) {
    int a = rand()%2,b = rand()%2, c = rand()%2, result = 1;
    if (c == 1) {
      result = 0;
    }
    
    c1->getNeurones()[0]->setValue(a);
    c1->getNeurones()[1]->setValue(b);
    c1->getNeurones()[2]->setValue(c);

    c2->eval();
    c3->eval();

    c3->getNeurones()[0]->setErreur(result-c3->getNeurones()[0]->getValue());
    
    //  Condition nécessaire avant de rétropropager l'erreur :
    //  Les erreurs de couches précédentes doivent être réinitialiser à 0
    
    c2->resetErreur();
    c3->updateErreur(); //Rétropropagation de l'erreur à la couche 2

    c1->resetErreur();
    c2->updateErreur();

    c3->updatePoids();
    c2->updatePoids();

    std::cout << "Erreur " << i << " : " << c3->getNeurones()[0]->getErreur() << std::endl;
  }
  
  return 0;
}
