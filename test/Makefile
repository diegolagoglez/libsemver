
CXXFLAGS	:= -I../include -L../lib -lsemver

all:
	@echo 'Usage: make <target file with no extension>'

.PHONY: clean

clean:
	rm -f *.o
	find . -executable -type f -exec rm -f {} \;
