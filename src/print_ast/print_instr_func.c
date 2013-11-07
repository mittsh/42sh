#include "print_ast.h"

void                    print_instr_func(s_instr                *instr,
                                         FILE                   *fd)
{
  s_instr_func          *instr_func = NULL;

  if (instr == NULL || instr->instr == NULL)
    return;

  instr_func = instr->instr;

  fprintf(fd, "itm%p [label=\"Function %s\" "AST_STYLE_FUNCTION"]\n",
          getptr(instr),
          instr_func->name);

  fprintf(fd, "itm%p -> itm%p\n", getptr(instr),
          getptr(instr_func->list_instr));
  print_list_instr(instr_func->list_instr, fd);
}
