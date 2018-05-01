include Sources.mk
CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lGL -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -L . -lsteam_api
SOURCES=main.cpp $(ROSALILA_SHOOTER_SOURCES) $(ROSALILA_SOURCES)
OBJECTS=$(SOURCES:.cpp=.o)
ifeq ($(API),secret)
  LDFLAGS += -lcurl -pthread -lz -I secret_include
  CFLAGS += -DSECRET
  SOURCES += RosalilaShooter/Menus/StageSecretSelect.cpp
  OBJECTS += libsecret.a
endif
ifeq ($(API),steam)
  CFLAGS += -DSTEAM
endif
EXECUTABLE=Flatshot

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) -DSTEAM

.cpp.o:
	$(CC) $< -o $@ $(CFLAGS)

clean:
	-find . -name '*.o' -exec rm -r {} \;
	-rm -f $(EXECUTABLE)
