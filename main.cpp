#include <iostream>
#include "Couche/couche.hpp"
#include <stdlib.h> 
#include <time.h>

using namespace std;

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

/* Version précédente
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

  for (int i = 0; i < 10000; i++) {
    int a = rand()%2,b =   rand()%2, c = rand()%2, result = 1;
    if (c == 1) {
      result = 0;
    }
    
    n1->setValue(a);
    n2->setValue(b);
    n3->setValue(c);

    n4->eval();
    n5->eval();

    out->eval();

    out->setErreur(result-out->getValue());
    
    //  Condition nécessaire avant de rétropropager l'erreur :
    //  Les erreurs de couches précédentes doivent être réinitialiser à 0

    n4->setErreur(0);
    n5->setErreur(0);
    out->updateErreur(); //Rétropropagation de l'erreur à la couche 2

    n1->setErreur(0);
    n2->setErreur(0);
    n3->setErreur(0);
    n4->updateErreur();
    n5->updateErreur();

    out->updatePoids();
    n4->updatePoids();
    n5->updatePoids();

    std::cout << "Erreur " << i << " : " << out->getErreur() << std::endl;
  }
  
  return 0;
}
*/
