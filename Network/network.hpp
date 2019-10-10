#ifndef _NETWORK
#define _NETWORK

#include "../Layer/layer.hpp"

class Network{
private:
  std::vector<Layer*> layers;

public:
  Network();
  void add(Layer* c);
  void add(int n); //Ajout d'une couche de n neurones en fully connected
  std::string getJson();
};

#endif
