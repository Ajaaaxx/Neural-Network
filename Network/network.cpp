#include "network.hpp"

Network::Network(){
    input = NULL;
    output = NULL;
}

void Network::add(Couche* c){
    if(couches.empty()){
        couches.push_back(c);
        input = c;
        output = c;
    }
    else{
        couches.back()->relier(c);
        couches.push_back(c);
        output = c;
    }
}

