#include "print_ast.h"

void                    print_instr_brack(s_instr               *instr,
                                          FILE                  *fd)
{
  s_instr_brack         *instr_brack = NULL;

  if (instr == NULL || instr->instr == NULL)
    return;

  instr_brack = instr->instr;

  fprintf(fd, "itm%p [label=\"{...}\" "AST_STYLE_SUB"]\n", getptr(instr));
  fprintf(fd, "itm%p -> itm%p\n", getptr(instr),
          getptr(instr_brack->list_instr));
  print_list_instr(instr_brack->list_instr, fd);
}
