
g++ Parse.cpp -o Parse -lxerces-c


xsd cxx-tree vector_battle_regular_20.xsd

g++ -lxerces-c -c vector_battle_regular_20.hxx vector_battle_regular_20.cxx
g++ Parse.cpp -o Parse vector_battle_regular_20.o -lxerces-c
