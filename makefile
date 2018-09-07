
compile: src/evolucion_diferencial.c src/f_utiles.c src/funciones_objetivo.c src/testED.c src/benchmarkOR.c
	gcc -O2 -o testED src/evolucion_diferencial.c src/f_utiles.c src/funciones_objetivo.c src/testED.c src/benchmarkOR.c -lgsl -lgslcblas -lm

# ./testED <numFun> <tamPob> <dim> <maxEvals> <ini> <fin> <CR> <F> <numReps>

VAL_CR=0.9
VAL_F=0.7
VAL_NUM_REP=1
VAL_TAM_POB=200
VAL_MAX_EVAL=300000
EPSILON_INI=1
VAL_P=0.05

valgrindED_1: 
	gcc -g -o testED src/evolucion_diferencial.c src/f_utiles.c src/funciones_objetivo.c src/testED.c src/benchmarkOR.c -lm
	valgrind --leak-check=full ./testED 13 $(VAL_TAM_POB) data/g13.txt $(VAL_MAX_EVAL) $(EPSILON_INI) $(VAL_P) $(VAL_CR) $(VAL_F) $(VAL_NUM_REP)

# Test Function 1: 
runtestED_1: compile
	./testED 1 $(VAL_TAM_POB) data/g1.txt $(VAL_MAX_EVAL) $(EPSILON_INI) $(VAL_P) $(VAL_CR) $(VAL_F) $(VAL_NUM_REP)

runtestED_2: compile
	./testED 2 $(VAL_TAM_POB) data/g2.txt $(VAL_MAX_EVAL) $(EPSILON_INI) $(VAL_P) $(VAL_CR) $(VAL_F) $(VAL_NUM_REP)

runtestED_3: compile
	./testED 3 $(VAL_TAM_POB) data/g3.txt $(VAL_MAX_EVAL) $(EPSILON_INI) $(VAL_P) $(VAL_CR) $(VAL_F) $(VAL_NUM_REP)

runtestED_4: compile
	./testED 4 $(VAL_TAM_POB) data/g4.txt $(VAL_MAX_EVAL) $(EPSILON_INI) $(VAL_P) $(VAL_CR) $(VAL_F) $(VAL_NUM_REP)

runtestED_5: compile
	./testED 5 $(VAL_TAM_POB) data/g5.txt $(VAL_MAX_EVAL) $(EPSILON_INI) $(VAL_P) $(VAL_CR) $(VAL_F) $(VAL_NUM_REP)

runtestED_6: compile
	./testED 6 $(VAL_TAM_POB) data/g6.txt $(VAL_MAX_EVAL) $(EPSILON_INI) $(VAL_P) $(VAL_CR) $(VAL_F) $(VAL_NUM_REP)

runtestED_7: compile
	./testED 7 $(VAL_TAM_POB) data/g7.txt $(VAL_MAX_EVAL) $(EPSILON_INI) $(VAL_P) $(VAL_CR) $(VAL_F) $(VAL_NUM_REP)

runtestED_8: compile
	./testED 8 $(VAL_TAM_POB) data/g8.txt $(VAL_MAX_EVAL) $(EPSILON_INI) $(VAL_P) $(VAL_CR) $(VAL_F) $(VAL_NUM_REP)

runtestED_9: compile
	./testED 9 $(VAL_TAM_POB) data/g9.txt $(VAL_MAX_EVAL) $(EPSILON_INI) $(VAL_P) $(VAL_CR) $(VAL_F) $(VAL_NUM_REP)

runtestED_10: compile
	./testED 10 $(VAL_TAM_POB) data/g10.txt $(VAL_MAX_EVAL) $(EPSILON_INI) $(VAL_P) $(VAL_CR) $(VAL_F) $(VAL_NUM_REP)

runtestED_11: compile
	./testED 11 $(VAL_TAM_POB) data/g11.txt $(VAL_MAX_EVAL) $(EPSILON_INI) $(VAL_P) $(VAL_CR) $(VAL_F) $(VAL_NUM_REP)

runtestED_12: compile
	./testED 12 $(VAL_TAM_POB) data/g12.txt $(VAL_MAX_EVAL) $(EPSILON_INI) $(VAL_P) $(VAL_CR) $(VAL_F) $(VAL_NUM_REP)

runtestED_13: compile
	./testED 13 $(VAL_TAM_POB) data/g13.txt $(VAL_MAX_EVAL) 10 $(VAL_P) $(VAL_CR) $(VAL_F) $(VAL_NUM_REP)

