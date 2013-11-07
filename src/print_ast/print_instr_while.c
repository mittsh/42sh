#include "print_ast.h"

void                    print_instr_while(s_instr               *instr,
                                          FILE                  *fd)
{
  s_instr_while         *instr_while = NULL;

  if (instr == NULL || instr->instr == NULL)
    return;

  instr_while = instr->instr;

  fprintf(fd,
          "itm%p [label=\"while\" "AST_STYLE_COND"]\n",
          getptr(instr));
  fprintf(fd,
          "itm%p -> itm%p [color=black style=dotted"
          " label=\"Condition\" fontsize=10]\n",
          getptr(instr), getptr(instr_while->list_cond));
  fprintf(fd,
          "itm%p -> itm%p [color=green label=\"Body\" fontsize=10]\n",
          getptr(instr), getptr(instr_while->list_instr));

  print_list_instr(instr_while->list_cond, fd);
  print_list_instr(instr_while->list_instr, fd);
}
