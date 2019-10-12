#include "Network/network.hpp"
#include <stdlib.h> 
#include <time.h>
#include <iostream>

using namespace std;

int main() {
  srand (time(NULL));
  
  Network * reseau = new Network();
  reseau->add(3);
  reseau->add(10);
  reseau->add(10);
  reseau->add(10);
  reseau->add(10);
  reseau->add(1);
  
  for (int i = 0; i < 100000; i++) {
    double a = rand()%2,b = rand()%2, c = rand()%2, result = 1;
    if (c == 1) {
      result = 0.5;
    }
    vector<double> in,out;
    in.push_back(a);
    in.push_back(b);
    in.push_back(c);
    out.push_back(result);
    reseau->train(in,out);
    if (i%1000 == 0) {
      std::cout << "Entrainement n°" << i << std::endl;
    }
  }
  double somme = 0;
  for (int i = 0; i < 1000; i++) {
    double a = rand()%2,b = rand()%2, c = rand()%2, result = 1;
    if (c == 1) {
      result = 0.5;
    }
    vector<double> in,out;
    in.push_back(a);
    in.push_back(b);
    in.push_back(c);
    out.push_back(result);
    somme += reseau->train(in,out);
  }
  cout << "Erreur = " << somme/1000 << endl;
  reseau->save("test.json");
  
  
  std::cout << "On save le réseau" << std::endl;
  std::cout << "On load le réseau" << std::endl;
  Network * test = new Network();
  test->load("test.json");

  somme = 0;
  for (int i = 0; i < 10; i++) {
    double a = rand()%2,b = rand()%2, c = rand()%2, result = 1;
    if (c == 1) {
      result = 0.5;
    }
    vector<double> in,out;
    in.push_back(a);
    in.push_back(b);
    in.push_back(c);
    out.push_back(result);
    somme += test->train(in,out);
  }

  cout << "Nouvelle Erreur = " << somme/10 << endl;
  
  return 0;
}
