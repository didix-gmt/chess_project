EXEC = echecs

SRC = main.cpp board.cpp game.cpp
HDRS = board.hpp piece.hpp pawn.hpp knight.hpp bishop.hpp rook.hpp queen.hpp king.hpp utils.hpp game.hpp

OBJ = $(SRC:.cpp=.o)

# Options de compilation
CXX = g++

CXXFLAGS = -Wall -Wextra -g -std=c++17 #-fanalyzer

all: $(EXEC)

# Création de l'exécutable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Règle de compilation des fichiers .cpp en .o
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Génère la documentation avec Doxygen
doc:
	doxygen Doxyfile

test%: all
	../test-level.sh $* ./$(EXEC)

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJ) $(EXEC)
	rm -f test.log
	rm -rf docs
