#include "print_ast.h"

void                    print_instr_cmd(s_instr                 *instr,
                                        FILE                    *fd)
{
  s_instr_cmd           *instr_cmd = NULL;
  s_dynamic_string      *dynstr = NULL;
  s_list_words          *list_words = NULL;

  if (instr == NULL || instr->instr == NULL)
    return;

  instr_cmd = instr->instr;

  dynstr = dynamic_string_init();

  list_words = instr_cmd->list_words;
  for (; list_words != NULL; list_words = list_words->next)
  {
    if (list_words != instr_cmd->list_words)
      dynamic_string_push(dynstr, ' ');
    dynamic_string_pushs(dynstr, list_words->word);
  }

  fprintf(fd, "itm%p [label=\"%s\" "AST_STYLE_CMD"]\n",
          getptr(instr), dynstr->str);

  dynamic_string_free(dynstr);
}
