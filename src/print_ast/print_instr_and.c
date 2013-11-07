#include "print_ast.h"

void                    print_instr_and(s_instr                 *instr,
                                        FILE                    *fd)
{
  s_instr_and           *instr_and = NULL;

  if (instr == NULL || instr->instr == NULL)
    return;

  instr_and = instr->instr;

  fprintf(fd, "itm%p [label=\"&&\" "AST_STYLE_LOGIC"]\n", getptr(instr));
  fprintf(fd, "itm%p -> itm%p\n", getptr(instr), getptr(instr_and->instr_l));
  fprintf(fd, "itm%p -> itm%p\n", getptr(instr), getptr(instr_and->instr_r));
  print_instr(instr_and->instr_l, fd);
  print_instr(instr_and->instr_r, fd);
}
