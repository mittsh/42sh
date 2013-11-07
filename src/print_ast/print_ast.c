#include "print_ast.h"

static void             ast_dot_make(char                       *filename)
{
  pid_t                 pid = 0;
  int                   status = 0;

  if ((pid = fork()) == 0)
  {
    execlp("dot", "dot", "-Tpng", "ast.dot", "-o", filename, NULL);
  }
  else
  {
    waitpid(pid, &status, 0);
  }
}

int                     print_ast(char                          *filename,
                                  t_ast                         *ast)
{
  FILE                  *dotfile;

  dotfile = mfopen("ast.dot", "w+");
  fprintf(dotfile, "digraph ast {\n");

  print_list_instr(ast, dotfile);

  fprintf(dotfile, "}\n");

  mfclose(dotfile);

  filename = filename;
  ast_dot_make(filename);

  return (0);
}

