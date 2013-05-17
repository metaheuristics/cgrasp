FLAGS = -lpthread -g
#LIBS=-Wall -I GRASP -I DTS -I func -I util -I BFGS -I /usr/local/include -I sprng/include -I .
LIBS=-Wall -I GRASP -I DTS -I func -I util -I BFGS -I /usr/local/include -I . -DREAL_FLOAT
#LIBS=-Wall -I GRASP -I DTS -I func -I util -I BFGS -I /usr/local/include -I .
CC=g++

GRASPObjs = \
MGrasp.o \
main.o

DTSObjs = \
Dts.o \
TabuList.o \
TlElement.o

funcObjs = \
Funcao.o \
Rosenbrock2.o \
Zakharov.o \
SumSquares.o \
Branin.o \
Easom.o \
GoldsteinPrice.o \
Hartmann.o \
Shekel.o \
Shubert.o \
Beale.o \
Booth.o \
Bohachevsky.o \
Hump.o \
Matyas.o \
Schwefel.o \
Colville.o \
Perm.o \
Perm0.o \
PowerSum.o \
Griewank.o \
Rastrigin.o \
Trid.o \
Powell.o \
DixonPrice.o \
Ackley.o \
Levy.o \
Sphere.o
#CECShiftedSphere.o \
#CECShiftedSchwefel.o \
#CECShiftedSchwefelNoise.o \
#CECRotatedRastrigin.o \
#CECRotatedWeierstrass.o \
#CECRotatedExpScaffers.o

BFGSObjs = \
lbfgs.o \
ap.o

utilObjs = \
Util.o

GRASPObjsPre = $(addprefix GRASP/,$(GRASPObjs) )
DTSObjsPre = $(addprefix DTS/,$(DTSObjs) )
funcObjsPre = $(addprefix func/,$(funcObjs) )
BFGSObjsPre  = $(addprefix BFGS/, $(BFGSObjs)  )
utilObjsPre  = $(addprefix util/, $(utilObjs)  )

OBJECTS=$(GRASPObjsPre) $(DTSObjsPre) $(funcObjsPre) $(BFGSObjsPre) $(utilObjsPre)

all:  CGrasp

#CGrasp: $(OBJECTS)
#	$(CC) -g -o CGrasp $(OBJECTS) -L /usr/X11/lib -lm -L./sprng/lib -llcg $(LIBS) $(FLAGS)
# CGrasp: $(OBJECTS)
# 	$(CC) -g -o CGrasp $(OBJECTS) -L /usr/X11/lib -lm $(LIBS) $(FLAGS)
CGrasp: $(OBJECTS)
	$(CC) -g -o CGrasp $(OBJECTS) -lm $(LIBS) $(FLAGS)

.c.o: $<
	$(CC) -g -c $< -o $@ $(LIBS)

.cpp.o: $<
	$(CC) -g -c $< -o $@ $(LIBS)

clean:
	rm -f CGrasp
	rm -f `find . -iname *.o`
	rm -f gap*.txt
