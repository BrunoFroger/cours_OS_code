
all: obj/stdio_OS.a
	touch obj/libs_updated


obj/stdio_OS.a: src/stdio_OS.c\
	inc/stdio_OS.h
	ar r $@ src/stdio_OS.c 

clean:
	rm -f obj/*.a obj/libs_updated
