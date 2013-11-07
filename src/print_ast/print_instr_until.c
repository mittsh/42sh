#include "print_ast.h"

void                    print_instr_until(s_instr               *instr,
                                          FILE                  *fd)
{
  s_instr_until         *instr_until = NULL;

  if (instr == NULL || instr->instr == NULL)
    return;

  instr_until = instr->instr;

  fprintf(fd,
          "itm%p [label=\"until\" "AST_STYLE_COND"]\n",
          getptr(instr));
  fprintf(fd,
          "itm%p -> itm%p [color=black style=dotted"
          " label=\"Condition\" fontsize=10]\n",
          getptr(instr), getptr(instr_until->list_cond));
  fprintf(fd,
          "itm%p -> itm%p [color=green label=\"Body\" fontsize=10]\n",
          getptr(instr), getptr(instr_until->list_instr));

  print_list_instr(instr_until->list_cond, fd);
  print_list_instr(instr_until->list_instr, fd);
}
