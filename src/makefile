EXEC = echecs

SRC = $(wildcard *.cpp)
HEADERS = $(wildcard *.hpp)
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
