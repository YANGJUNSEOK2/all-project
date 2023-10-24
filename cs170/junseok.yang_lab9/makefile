OUTPUT=lab9
OUTPUTD=$(OUTPUT)_d
SOURCE=driver.cpp
HEADER=SmartPointer.h
UNITTESTS=0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
MEMTESTS=mem0 mem1 mem2 mem3 mem4 mem5 mem6 mem7 mem8 mem9 mem10 mem11 mem12 mem13 mem14

COMPILER=g++
GCCFLAGS=-Werror -Wall -Wextra -pedantic -Wold-style-cast -Woverloaded-virtual -Wsign-promo  -Wctor-dtor-privacy -Wnon-virtual-dtor -Wreorder -std=c++17
DR_MEMORY_OPTIONS = -batch -brief
DIFF_OPTIONS = -y --strip-trailing-cr --suppress-common-lines -b

all : unitTests memTests
unitTests : $(UNITTESTS)
memTests : $(MEMTESTS)

$(OUTPUT) : $(SOURCE) $(HEADER)
	$(COMPILER) -o $(OUTPUT) $(SOURCE) $(GCCFLAGS) -O2
$(OUTPUTD) : $(SOURCE) $(HEADER)
	$(COMPILER) -o $(OUTPUTD) $(SOURCE) $(GCCFLAGS) -g

$(UNITTESTS): $(OUTPUT)
	@echo "running test $@"
	$(OUTPUT) $@ > studentout$@.txt
	diff $(DIFF_OPTIONS) targetout$@.txt studentout$@.txt > difference$@.txt

$(MEMTESTS): $(OUTPUTD)
	@echo "running mem test $@"
	drmemory $(DR_MEMORY_OPTIONS) -- $(OUTPUTD) $(subst mem,,$@) 2>difference$@.txt>cat difference$@.txt

clean :
	rm $(OUTPUT) $(OUTPUTD) student* difference*
