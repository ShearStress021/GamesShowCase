CCC=g++
LIBS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11



res: main.cpp
	$(CCC) $< -o main $(LIBS)


run: clean res
	./main


clean:
	rm -rf main
