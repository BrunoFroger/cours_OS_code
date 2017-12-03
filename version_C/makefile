all: OS\
	libs

libs: libs/obj/libs_updated

libs/obj/libs_updated:
	@(cd libs && make)

OS: OS/bin/os

OS/bin/os:
	@(cd OS && make)

