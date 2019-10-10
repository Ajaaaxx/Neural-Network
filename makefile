dnn: layer.o neuron.o network.o main.o
	g++ -o dnn layer.o neuron.o network.o main.o

layer.o: Layer/layer.cpp Layer/layer.hpp
	g++ -Wall -c Layer/layer.cpp

neuron.o: Neuron/neuron.cpp Neuron/neuron.hpp
	g++ -Wall -c Neuron/neuron.cpp

network.o: Network/network.cpp Network/network.hpp
	g++ -Wall -c Network/network.cpp

main.o: main.cpp
	g++ -Wall -c main.cpp

clean: 
	rm -f *.o
