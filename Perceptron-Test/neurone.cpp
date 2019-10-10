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
  
  std::vector<Neurone*> c1;
  c1.push_back(n1);
  c1.push_back(n2);
  
  Neurone * out = new Neurone(c1);

  for (int i = 0; i < 100; i++) {
    int a = rand()%2;
    int b = rand()%2;
    std::cout << a << " " << b << std::endl;
    int target = 0;
    if (a == 1) {
      target = 1;
    }

  //  if (a==1 && b==1)
//	    target = 2;

    n1->setValue(a);
    n2->setValue(b);
    std::cout << "Out : ";
    out->eval();
    out->train(target);
    std::cout << std::endl;
  }
  
  return 0;
}
