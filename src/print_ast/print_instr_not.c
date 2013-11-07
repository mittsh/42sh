#include "print_ast.h"

void                    print_instr_not(s_instr                 *instr,
                                        FILE                    *fd)
{
  s_instr_not           *instr_not = NULL;

  if (instr == NULL || instr->instr == NULL)
    return;

  instr_not = instr->instr;

  fprintf(fd, "itm%p [label=\"!\" "AST_STYLE_LOGIC"]\n", getptr(instr));
  fprintf(fd, "itm%p -> itm%p\n", getptr(instr), getptr(instr_not->instr));
  print_instr(instr_not->instr, fd);
}
