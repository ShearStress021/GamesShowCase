res: main.cpp
	g++ $< -o $@


run: clean res
	./res


clean:
	del res*
