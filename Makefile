CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include

all : bin/generateAST bin/c_compiler

src/C90_parser.tab.cpp src/C90_parser.tab.hpp : src/C90_parser.y
	bison -v -d src/C90_parser.y -o src/C90_parser.tab.cpp

src/C90_lexer.yy.cpp : src/C90_lexer.flex src/C90_parser.tab.hpp
	flex -o src/C90_lexer.yy.cpp  src/C90_lexer.flex

bin/generateAST : src/generateAST.o src/C90_parser.tab.o src/C90_lexer.yy.o src/implementations/codegen.cpp src/implementations/draw.cpp src/implementations/print.cpp
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/generateAST $^


bin/c_compiler : bin/compiler src/wrapper.sh
	cp src/wrapper.sh bin/c_compiler
	chmod u+x bin/c_compiler

bin/compiler : src/compile.o src/C90_parser.tab.o src/C90_lexer.yy.o src/C90_parser.tab.o src/implementations/codegen.cpp src/implementations/draw.cpp src/implementations/print.cpp
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/compiler $^


clean :
	rm -f program_ast.dot
	rm -f program_ast.png
	rm -rf src/*.o
	rm -rf bin/*
	rm -rf src/*.tab.cpp
	rm -rf src/*.tab.hpp
	rm -rf src/*.output
	rm -rf src/*.yy.cpp
