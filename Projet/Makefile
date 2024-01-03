# Nom du programme final
TARGET = a.out

# Compilateur
CXX = g++

# Options de compilation
CXXFLAGS = -Wall -std=c++11

# List des fichiers source
SOURCES = jeuCasseBrique.cpp EcranASCII.cpp CasseBrique.cpp

# List des fichiers objet (générés à partir des fichiers source)
OBJECTS = $(SOURCES:.cpp=.o)

# Règle principale pour la compilation du programme
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# Règle générique pour la compilation des fichiers source en fichiers objet
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJECTS) $(TARGET)


