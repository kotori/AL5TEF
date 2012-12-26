# Makefile for Laberinto clone

# !IMPORTANT!
# Source file names, must include them all.
Sources=Collidable.cpp Tile.cpp Map.cpp Character.cpp GameManager.cpp main.cpp

# Final executable name
Executable=AllegroGame

# Compiler flags
CFlags=-c -Wall -g -Iinc -std=c++0x

# Linker flags
LDFlags=

# !IMPORTANT!
# You must change the line below to match your Allegro installation
PkgConfigFlags=`pkg-config --libs --static allegro-static-5.0 allegro_acodec-static-5.0 allegro_audio-static-5.0 allegro_color-static-5.0 allegro_dialog-static-5.0 allegro_font-static-5.0 allegro_image-static-5.0 allegro_main-static-5.0 allegro_memfile-static-5.0 allegro_physfs-static-5.0 allegro_primitives-static-5.0 allegro_ttf-static-5.0 libxml-2.0 zlib glib-2.0 allegro_tiled-5.0`

# Common directories
ObjectDir=../obj/
SourceDir=../src/
BinDir=../bin/

# Required binaries
CC=g++
RM=rm -f
DIR_GUARD=@mkdir -p $(@D)
COMPRESSOR=upx

## DO NOT EDIT ANYTHING UNDER THIS LINE!!!!! ##
Objects=$(Sources:.cpp=.o)
CSources=$(addprefix $(SourceDir),$(Sources))
CObjects=$(addprefix $(ObjectDir),$(Objects))
CExecutable=$(addprefix $(BinDir),$(Executable))

all: $(CSources) $(CExecutable)

$(CExecutable): $(CObjects)
	$(DIR_GUARD)
	$(CC) $(LDFlags) $(CObjects) $(PkgConfigFlags) -o $@

$(ObjectDir)%.o: $(SourceDir)%.cpp
	$(DIR_GUARD)
	$(CC) $(CFlags) $< -o $@

install:
	$(COMPRESSOR) $(CExecutable)

clean:
	$(RM) $(CObjects)
	$(RM) $(CExecutable)

