CCC=g++
#LIBS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11



res: main.cpp
	$(CCC) $< -o $@ 


run: clean res
	./res


clean:
	del res*
