#include "print_ast.h"

void                    print_instr_or(s_instr                  *instr,
                                       FILE                     *fd)
{
  s_instr_or            *instr_or = NULL;

  if (instr == NULL || instr->instr == NULL)
    return;

  instr_or = instr->instr;

  fprintf(fd, "itm%p [label=\"||\" "AST_STYLE_LOGIC"]\n", getptr(instr));
  fprintf(fd, "itm%p -> itm%p\n", getptr(instr), getptr(instr_or->instr_l));
  fprintf(fd, "itm%p -> itm%p\n", getptr(instr), getptr(instr_or->instr_r));
  print_instr(instr_or->instr_l, fd);
  print_instr(instr_or->instr_r, fd);
}
