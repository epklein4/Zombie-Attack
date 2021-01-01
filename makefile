BASE_OBJS = main.o Window.o Entity.o Player.o Tile.o BoundingBox.o \
     MapReader.o Button.o Zombie.o Projectile.o Pathfinder.o

SRC_PATH = src

OBJS = $(addprefix $(SRC_PATH)\, $(BASE_OBJS))
CXX = g++
CXXFLAGS = -g -Iinclude
LDFLAGS = -mwindows
LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

ZombieAttack: $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^ $(LDLIBS)	

clean:
	del $(OBJS)