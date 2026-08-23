
res: main.cpp
	g++ --std=20 $< -o $@


run: clean res
	./res.exe


clean:
	del res*


.PHONY: run clean

