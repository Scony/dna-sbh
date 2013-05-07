all: src
	make -C src
	cp src/positive.out .
	cp src/negative.out .

clean: 
	make -C src clean
	rm -f positive.out negative.out *~

.PHONY: all clean
