# Quick'n'dirty makefile, don't ask...

.SILENT:

IMAGE = "zoo_mania_final.d64"

all: disk

prg:
	cl65 -Osi --standard cc65 -o zoo.prg -C zoo.cfg zoo.c zoo_ass.s
	cp zoo.hi.bin zoo.hi

disk: prg
	c1541 -format zoomania,zm d64 zoo.d64
	c1541 zoo.d64 -write zoo.prg
	c1541 zoo.d64 -write zoo.hi
	c1541 zoo.d64 -list

dist: prg
	exomizer sfx sys -q -n -o zoo_exo.prg zoo.prg
	c1541 -format "zoomania final,zm" d64 $(IMAGE)
	c1541 $(IMAGE) -write zoo_exo.prg "zoo mania"
	c1541 $(IMAGE) -write zoo.hi
	c1541 $(IMAGE) -list
	rm -f zoo_ass.o zoo.o zoo.prg zoo_exo.prg zoo.hi

test: dist
	x64 $(IMAGE)
	
clean: 
	rm -f *~ zoo_ass.o zoo.o zoo.prg zoo_exo.prg zoo.d64 zoo.hi $(IMAGE)
