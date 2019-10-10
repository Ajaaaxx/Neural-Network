#include "neuron.hpp"
#include <iostream>

using namespace std;

int main () {
  Neuron * n1 = new Neuron();
  Neuron * n2 = new Neuron();

  vector<Neuron*> c;
  c.push_back(n1);
  c.push_back(n2);
  Neuron * n3 = new Neuron(c);
  cout << n3->getJson() << endl;
  return 0;
}
