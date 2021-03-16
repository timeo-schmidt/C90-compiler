make clean && make all
bin/generateAST < c_sandbox
dot -Tpng program_ast.dot > program_ast.png
open program_ast.png
