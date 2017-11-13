hospital: hospital.c parse.c parse.h structure.c structure.h
	cc -o hospital hospital.c parse.c structure.c

hospital.dbg: hospital.c parse.c parse.h structure.c structure.h
	cc -g -o hospital.dbg hospital.c parse.c structure.c

debug: hospital.dbg

.PHONY: debug
