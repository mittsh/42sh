#include "print_ast.h"

void                    print_instr_pipe(s_instr                *instr,
                                         FILE                   *fd)
{
  s_instr_pipe          *instr_pipe = NULL;

  if (instr == NULL || instr->instr == NULL)
    return;

  instr_pipe = instr->instr;

  fprintf(fd, "itm%p [label=\"|\" "AST_STYLE_PIPE"]\n", getptr(instr));
  fprintf(fd, "itm%p -> itm%p\n",
          getptr(instr), getptr(instr_pipe->list_instr));

  print_list_instr(instr_pipe->list_instr, fd);
}
