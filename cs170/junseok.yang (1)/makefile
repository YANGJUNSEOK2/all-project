OUTPUT=lab5
OUTPUTD=$(OUTPUT)_d
SOURCE=driver.cpp List.cpp
HEADER=List.h
UNITTESTS=0 1 2 3 4 5 6 7 8 9
MEMTESTS=mem0 mem1 mem2 mem3 mem4 mem5 mem6 mem7 mem8 mem9
COMPILER=g++

GCCFLAGS=-Werror -Wall -Wextra -pedantic -Wold-style-cast -Woverloaded-virtual -Wsign-promo  -Wctor-dtor-privacy -Wnon-virtual-dtor -Wreorder
DR_MEMORY_OPTIONS = -batch -brief
DIFF_OPTIONS = -y --strip-trailing-cr --suppress-common-lines -b

all : unitTests memTests
unitTests : $(UNITTESTS)
memTests : $(MEMTESTS)

$(OUTPUT) : $(SOURCE)
	$(COMPILER) -o $(OUTPUT) $(SOURCE) $(GCCFLAGS) -O2
$(OUTPUTD) : $(SOURCE)
	$(COMPILER) -o $(OUTPUTD) $(SOURCE) $(GCCFLAGS) -g

$(UNITTESTS): $(OUTPUT)
	@echo "running test $@"
	./$(OUTPUT) $@ > studentout$@.txt
	diff $(DIFF_OPTIONS) targetout$@ studentout$@.txt > difference$@.txt

$(MEMTESTS): $(OUTPUTD)
	@echo "running mem test $@"
	drmemory $(DR_MEMORY_OPTIONS) -- ./$(OUTPUTD) $(subst mem,,$@) 1>/dev/null 2>difference$@.txt
	cat difference$@.txt

clean : 
	rm $(OUTPUT) $(OUTPUTD) student* difference*