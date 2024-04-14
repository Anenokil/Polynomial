CC = g++
CCFLAGS = -O0 -g
MAIN = main
MODULE = Polynomial
RES = r

all: $(RES)

$(MODULE).o: $(MODULE).cpp
	$(CC) $(CCFLAGS) -c $(MODULE).cpp -o $(MODULE).o
$(MAIN).o: $(MAIN).cpp
	$(CC) $(CCFLAGS) -c $(MAIN).cpp -o $(MAIN).o
$(RES): $(MAIN).o $(MODULE).o
	$(CC) $(CCFLAGS) $(MODULE).o $(MAIN).o -o $(RES)

clear:
	rm -rf *.o r
