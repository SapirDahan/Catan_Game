#
# * Author: Sapir Dahan
# * ID: 325732972
# * Mail: sapirdahan2003@gmail.com
#

#!make -f

CXX=g++
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=board.cpp catan.cpp player.cpp Hexagon.cpp Intersection.cpp Path.cpp Dice.cpp Card.cpp DevelopmentCard.cpp ResourceCard.cpp SpecialCard.cpp TestCounter.cpp Tests.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

run: demo
	./$^

demo: Demo.o board.o catan.o ResourceCard.o player.o Hexagon.o Intersection.o Path.o Dice.o Card.o DevelopmentCard.o SpecialCard.o
	$(CXX) $(CXXFLAGS) $^ -o demo

test: TestCounter.o Tests.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

#tidy:
#	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

# Using cppcheck instead of tidy, since I use g++ compiler which is better suited for my machine
cppcheck:
	cppcheck $(SOURCES) --enable=all


valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test