#include "print_ast.h"

static void             print_instr_case_item(s_list_c_items    *list_c_item,
                                              FILE              *fd)
{
  s_list_words          *list_words = NULL;

  list_words = list_c_item->list_words;

  fprintf(fd, "itm%p [label=\"", getptr(list_c_item));
  for (; list_words != NULL; list_words = list_words->next)
  {
    if (list_words != list_c_item->list_words)
      fprintf(fd, " | ");

    fprintf(fd, "%s", list_words->word);
  }
  fprintf(fd, "\"]\n");

  fprintf(fd, "itm%p -> itm%p\n",
          getptr(list_c_item),
          getptr(list_c_item->list_instr));
  print_list_instr(list_c_item->list_instr, fd);
}

void                    print_instr_case(s_instr                *instr,
                                         FILE                   *fd)
{
  s_instr_case          *instr_case = NULL;
  s_list_c_items        *list_c_items = NULL;

  if (instr == NULL || instr->instr == NULL)
    return;

  instr_case = instr->instr;

  fprintf(fd,
          "itm%p [label=\"case %s\" "AST_STYLE_COND"]\n",
          getptr(instr), instr_case->word);

  list_c_items = instr_case->list_c_items;
  for (; list_c_items != NULL; list_c_items = list_c_items->next)
  {
    fprintf(fd, "itm%p -> itm%p\n", getptr(instr), getptr(list_c_items));
    print_instr_case_item(list_c_items, fd);
  }
}
