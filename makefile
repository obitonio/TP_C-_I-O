RM = rm
COMP = g++
EDL = g++
RMFLAGS = -f
CPPFLAGS = -DMAP #-g (debug)

FILE1 = Trajet
H1= $(FILE1).h
CPP1 = $(FILE1).cpp
OBJ1 = $(FILE1).o

FILE2 = TrajetSimple
H2= $(FILE2).h
CPP2 = $(FILE2).cpp
OBJ2 = $(FILE2).o

FILE3 = TrajetCompose
H3= $(FILE3).h
CPP3 = $(FILE3).cpp
OBJ3 = $(FILE3).o

FILE4 = Collection
H4= $(FILE4).h
CPP4 = $(FILE4).cpp
OBJ4 = $(FILE4).o

FILE5 = Catalogue
H5= $(FILE5).h
CPP5 = $(FILE5).cpp
OBJ5 = $(FILE5).o

EXE = main
CPP = $(EXE).cpp
OBJ = $(EXE).o

CLEAN = clean

.PHONY : clean

all : $(EXE)

$(OBJ1) : $(CPP1) $(H1)
	$(COMP) $(CPPFLAGS) -c $(CPP1)

$(OBJ2) : $(CPP2) $(H2)
	$(COMP) $(CPPFLAGS) -c $(CPP2)

$(OBJ3) : $(CPP3) $(H3)
	$(COMP) $(CPPFLAGS) -c $(CPP3)

$(OBJ4) : $(CPP4) $(H4)
	$(COMP) $(CPPFLAGS) -c $(CPP4)

$(OBJ5) : $(CPP5) $(H5)
	$(COMP) $(CPPFLAGS) -c $(CPP5)

$(OBJ) : $(CPP) $(H6)
	$(COMP) $(CPPFLAGS) -c $(CPP)

$(EXE) : $(OBJ) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5)
	$(EDL) $(EDLFLAGS) -o $(EXE) $(OBJ) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5)

$(CLEAN) :
	$(RM) $(RMFLAGS) $(OBJ) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5) $(EXE)
