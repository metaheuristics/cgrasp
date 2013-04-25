FLAGS = -lpthread -g
#LIBS=-Wall -I libGRASP -I libDTS -I libFuncao -I libUtil -I libBFGS -I /usr/local/include -I sprng/include -I .
LIBS=-Wall -I libGRASP -I libDTS -I libFuncao -I libUtil -I libBFGS -I /usr/local/include -I .
CC=g++

libGRASPObjs = \
MGrasp.o \
main.o

libDTSObjs = \
Dts.o \
TabuList.o \
TlElement.o

libFuncaoObjs = \
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

libBFGSObjs = \
lbfgs.o \
ap.o

libUtilObjs = \
Util.o

libGRASPObjsPre = $(addprefix libGRASP/,$(libGRASPObjs) )
libDTSObjsPre = $(addprefix libDTS/,$(libDTSObjs) )
libFuncaoObjsPre = $(addprefix libFuncao/,$(libFuncaoObjs) )
libBFGSObjsPre  = $(addprefix libBFGS/, $(libBFGSObjs)  )
libUtilObjsPre  = $(addprefix libUtil/, $(libUtilObjs)  )

OBJECTS=$(libGRASPObjsPre) $(libDTSObjsPre) $(libFuncaoObjsPre) $(libBFGSObjsPre) $(libUtilObjsPre)

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
