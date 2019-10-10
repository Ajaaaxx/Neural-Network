#include "network.hpp"
#include "../rapidjson/document.h"
#include <iostream>
#include <fstream>

using namespace rapidjson;
using namespace std;

Network::Network(string file){
  fstream fs;
  fs.open(file);
  fs.seekg(0,fs.end);
  int length = fs.tellg();
  fs.seekg(0,fs.beg);
  char* buffer = new char[length];
  fs.read(buffer,length);
  Document config;
  config.Parse(buffer); 
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
