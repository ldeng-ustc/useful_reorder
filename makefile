test: reorder seq
	time ./reorder
	time ./seq

reorder: main.cpp
	g++ -O2 -o reorder main.cpp

seq: main.cpp
	g++ -O2 -fno-schedule-insns -fno-schedule-insns2 -o seq main.cpp

clean:
	rm reorder seq

.PHONY: clean all
