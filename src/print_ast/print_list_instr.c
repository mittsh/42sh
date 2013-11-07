#include "print_ast.h"

void                    print_list_instr(s_list_instr           *list_instr,
                                         FILE                   *fd)
{
  s_list_instr_item     *item = NULL;

  if (list_instr == NULL)
    return;

  fprintf(fd, "itm%p [label=\"Instruction list\" "AST_STYLE_INSTRLIST"]\n",
          getptr(list_instr));

  for (item = list_instr->first; item != NULL; item = item->next)
  {
    fprintf(fd, "itm%p -> itm%p\n", getptr(list_instr), getptr(item->elmt));
    print_instr(item->elmt, fd);
  }
}
