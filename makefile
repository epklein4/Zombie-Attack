
OBJS = main.o Window.o Entity.o Player.o Tile.o BoundingBox.o MapReader.o Button.o Zombie.o
CPP = g++
CPPFLAGS = -c
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows

ZombieAttack: $(OBJS)
	$(CPP) -o ZombieAttack $(OBJS) $(LDFLAGS)

main.o: main.cpp
	$(CPP) $(CPPFLAGS) main.cpp

Window.o: Window.cpp
	$(CPP) $(CPPFLAGS) Window.cpp

Entity.o: Entity.cpp
	$(CPP) $(CPPFLAGS) Entity.cpp

Player.o: Player.cpp
	$(CPP) $(CPPFLAGS) Player.cpp

Tile.o: Tile.cpp
	$(CPP) $(CPPFLAGS) Tile.cpp

BoundingBox.o: BoundingBox.cpp
	$(CPP) $(CPPFLAGS) BoundingBox.cpp

MapReader.o: MapReader.cpp
	$(CPP) $(CPPFLAGS) MapReader.cpp

Button.o: Button.cpp
	$(CPP) $(CPPFLAGS) Button.cpp

Zombie.o: Zombie.cpp
	$(CPP) $(CPPFLAGS) Zombie.cpp

clean:
	del *.o