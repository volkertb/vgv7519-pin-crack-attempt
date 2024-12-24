# Copied from https://github.com/xivSolutions/Makefiles/blob/master/simple-example
# Compile an executable named yourProgram from yourProgram.c
# make sure there is a <tab> character on the indented line!
all: vgv7519-pin-cracker.c
	mkdir -p build
	gcc -g -Wall -o build/vgv7519-pin-cracker vgv7519-pin-cracker.c

clean:
	rm -rf build/*
