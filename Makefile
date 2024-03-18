CC = g++
CCFLAGS = -O0 -g
MAIN = main
MODUL = Polynomial
RES = r

all: $(RES)

$(MODUL).o: $(MODUL).cpp
	$(CC) $(CCFLAGS) -c $(MODUL).cpp -o $(MODUL).o
$(MAIN).o: $(MAIN).cpp
	$(CC) $(CCFLAGS) -c $(MAIN).cpp -o $(MAIN).o
$(RES): $(MAIN).o $(MODUL).o
	$(CC) $(CCFLAGS) $(MODUL).o $(MAIN).o -o $(RES)

clear:
	rm -rf *.o r
