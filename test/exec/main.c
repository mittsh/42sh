#include "../../src/parser/ast.h"
#include "../../src/parser/parser.h"
#include "../../src/print_ast/print_ast.h"
#include "../../src/exec/exec.h"
#include "../../src/42sh/shell.h"
#include <stdlib.h>
#include <unistd.h>

int                     main(int        argc,
			     char       *argv[])
{
  t_ast		        *ast = NULL;
  int             res = 0;

  if (argv[1] == NULL)
    return (1);

  argc = argc;

  ast = parse_input(argv[1]);

  print_ast("ast.dot", ast);

  printf("BEGIN EXECUTION\n");

  res = exec_list_instr(ast, NULL);

  return (res);
}

