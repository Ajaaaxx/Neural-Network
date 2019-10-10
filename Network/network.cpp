#include "network.hpp"
#include <iostream>
#include "../json.hpp"

using namespace std;
using json = nlohmann::json;

Network::Network(string jsonString){
  json j = json::parse(jsonString);
  std::string n = "Layer0";
  for (int i = 0; i < j.size();i) {
    if (i == 0) {
      layers.push_back(new Layer(j[n].size()));
    } else {
      std::cout << j[n] << std::endl;
      layers.push_back(new Layer(j[n].dump(), layers.back()));
    }
    n.pop_back();
    n += std::to_string(++i);
  }
  if (jsonString == getJson())
    cout << "Les deux réseaux sont égaux" << endl;
}

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
