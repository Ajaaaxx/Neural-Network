dnn: layer.o neuron.o network.o main.o
	g++ -g -o dnn layer.o neuron.o network.o main.o

layer.o: Layer/layer.cpp Layer/layer.hpp
	g++ -Wall -g -c Layer/layer.cpp

neuron.o: Neuron/neuron.cpp Neuron/neuron.hpp
	g++ -Wall -g -c Neuron/neuron.cpp

network.o: Network/network.cpp Network/network.hpp
	g++ -Wall -g -c Network/network.cpp

main.o: main.cpp
	g++ -Wall -g -c main.cpp

clean: 
	rm -f *.o
