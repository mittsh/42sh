#include "print_ast.h"

void                    print_instr_for(s_instr                 *instr,
                                        FILE                    *fd)
{
  s_instr_for           *instr_for = NULL;
  s_dynamic_string      *dynstr = NULL;
  s_list_words          *list_words = NULL;

  if (instr == NULL || instr->instr == NULL)
    return;

  instr_for = instr->instr;

  dynstr = dynamic_string_init();

  dynamic_string_pushs(dynstr, "for ");
  dynamic_string_pushs(dynstr, instr_for->var_name);
  dynamic_string_pushs(dynstr, " in");

  list_words = instr_for->list_words;

  for (; list_words != NULL; list_words = list_words->next)
  {
    dynamic_string_push(dynstr, ' ');
    dynamic_string_pushs(dynstr, list_words->word);
  }

  fprintf(fd,
          "itm%p [label=\"%s\" style=filled color=\".7 .3 1.0\"]\n",
          getptr(instr),
          dynstr->str);
  fprintf(fd,
          "itm%p -> itm%p [color=green label=\"Body\" fontsize=10]\n",
          getptr(instr), getptr(instr_for->list_instr));

  print_list_instr(instr_for->list_instr, fd);

  dynamic_string_free(dynstr);
}
