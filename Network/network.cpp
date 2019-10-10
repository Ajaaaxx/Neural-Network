#include "network.hpp"

Network::Network(){
  
}

void Network::add(Layer* c){
  if(layers.empty()){
    layers.push_back(c);
  }
  else{
    c->relier(layers.back());
    layers.push_back(c);
  }
}

void Network::add(int n) {
  Layer * c = new Layer(n);
  if(layers.empty()){
    layers.push_back(c);
  }
  else{
    c->relier(layers.back());
    layers.push_back(c);
  }
}

std::string Network::getJson() {
  std::string json = "{";

  for (int i = 0; i < layers.size(); i++) {
    json += "\"Layer" + std::to_string(i) + "\" : ";
    json += layers[i]->getJson();
    json += ",";
  }
  json.pop_back();
  json += "}";
  
  return json;
}
