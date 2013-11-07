#include "print_ast.h"

void                    print_instr_paren(s_instr               *instr,
                                          FILE                  *fd)
{
  s_instr_paren         *instr_paren = NULL;

  if (instr == NULL || instr->instr == NULL)
    return;

  instr_paren = instr->instr;

  fprintf(fd, "itm%p [label=\"(...)\" "AST_STYLE_SUB"]\n", getptr(instr));
  fprintf(fd, "itm%p -> itm%p\n", getptr(instr),
          getptr(instr_paren->list_instr));
  print_list_instr(instr_paren->list_instr, fd);
}
