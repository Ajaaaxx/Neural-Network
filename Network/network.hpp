#ifndef _NETWORK
#define _NETWORK

#include "../Couche/couche.hpp"

class Network{
    private:
        Couche* input;
        std::vector<Couche*> couches;
        Couche* output;

    public:
        Network();
        void add(Couche* c);
};

#endif