dnn: couche.o neurone.o network.o main.o
	g++ -o dnn couche.o neurone.o network.o main.o

couche.o: Couche/couche.cpp Couche/couche.hpp
	g++ -Wall -c Couche/couche.cpp

neurone.o: Neurone/neurone.cpp Neurone/neurone.hpp
	g++ -Wall -c Neurone/neurone.cpp

network.o: Network/network.cpp Network/network.hpp
	g++ -Wall -c Network/network.cpp

main.o: main.cpp
	g++ -Wall -c main.cpp

clean: 
	rm -f *.o