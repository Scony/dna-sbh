EXE=general.out

all: $(EXE)

$(EXE): src
	make -C src
	cp src/a.out $(EXE)

clean: 
	make -C src clean
	rm -f $(EXE) *~
.PHONY: all, clean
