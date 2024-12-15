# Quick'n'dirty makefile, don't ask...

IMAGE = "zoo_mania_prv3.d64"

all: disk

prg:
	cl65 -Osir -o zoo.prg -C zoo.cfg zoo.c zoo_ass.s
#	cl65 -o zoo.prg -C zoo.cfg zoo.c zoo_ass.s
	cp zoo.hi.bin zoo.hi

disk: prg
	c1541 -format zoomania,zm d64 zoo.d64
	c1541 zoo.d64 -write zoo.prg
	c1541 zoo.d64 -write zoo.hi

dist: prg
	exomizer sfx sys -q -n -o zoo_exo.prg zoo.prg
	c1541 -format zoomania,zm d64 $(IMAGE)
	c1541 $(IMAGE) -write zoo_exo.prg "zoo mania prv3"
	c1541 $(IMAGE) -write zoo.hi
	
clean: 
	rm -f *~ zoo_ass.o zoo.o zoo.prg zoo_exo.prg zoo.d64 $(IMAGE)
