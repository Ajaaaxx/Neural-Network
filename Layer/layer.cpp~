#include "couche.hpp"

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
