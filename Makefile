CPPFLAGS += -std=c++17 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include

$(OBJS): %.o : %.cpp

src/parser/parser.tab.cpp src/parser/parser.tab.hpp : src/parser/parser.y
	bison -v -d src/parser/parser.y -o src/parser/parser.tab.cpp

src/lexer/lexer.yy.cpp : src/lexer/lexer.flex src/parser/parser.tab.hpp
	flex -o src/lexer/lexer.yy.cpp  src/lexer/lexer.flex

bin/print_canonical : src/parser/testing/print_canonical.o src/lexer/lexer.yy.o src/parser/parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/print_canonical $^

bin/c_compiler : src/compiler/compiler.o src/lexer/lexer.yy.o src/parser/parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/compiler $^

bin/compiler : src/compiler/compiler.cpp
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/compiler $^

clean :
	rm -rf src/*.o
	rm -rf src/compiler/*.o
	rm -rf src/parser/*.o
	rm -rf src/parser/*.output
	rm -rf bin/*
	rm -rf src/*/*.tab.cpp
	rm -rf src/*/*.yy.cpp
	rm -rf bin/*
	rm -rf test/test_run_results/*
