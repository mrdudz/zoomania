# Quick'n'dirty makefile, don't ask...

IMAGE = "zoo_mania.d64"

all: zoo.d64

zoo.prg: zoo.c zoo_ass.s zoo-hiscore.c zoo-title.c zoo.cfg
	cl65 -o zoo.prg -C zoo.cfg zoo.c zoo_ass.s
#	cl65 -o zoo.prg zoo.c zoo_ass.s

zoo.d64: zoo.prg
	c1541 -format zoomania,zm d64 zoo.d64 \
		-write zoo.prg "zoo mania" \
		-write "zoo.hi.bin" "zoo.hi"

dist: zoo.prg
	exomizer sfx sys -q -n -o zoo_exo.prg zoo.prg
	c1541 -format zoomania,zm d64 $(IMAGE) \
		-write zoo_exo.prg "zoo mania" \
		-write "zoo.hi.bin" "zoo.hi"
	
test:	zoo.d64
	x64sc zoo.d64

clean:
	$(RM) zoo_ass.o zoo.o zoo.prg zoo_exo.prg zoo.d64 $(IMAGE)
