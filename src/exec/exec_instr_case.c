#include "exec.h"

/**
** @brief               Searches a word in the case instruction.
** @param word          Input word.
** @param list          Words list.
** @return              Returns 1 if found, 0 else.
*/
static inline int       search_word(char                        *word,
                                    s_list_words                *list)
{
  for (; list != NULL; list = list->next)
  {
    if (strcmp(word, list->word) == 0)
      return (1);
  }
  return (0);
}

int                     exec_instr_case(s_instr                 *instr,
                                        s_list_dup              *list_dup,
                                        int                     *error)
{
  s_list_c_items        *list_items = NULL;
  s_instr_case          *instr_case = NULL;
  int                   res = 0;

  if (instr == NULL || instr->instr == NULL)
    return (-1);

  instr_case = instr->instr;

  list_items = instr_case->list_c_items;
  for (; list_items != NULL; list_items = list_items->next)
  {
    if (search_word(instr_case->word, list_items->list_words))
    {
      res = exec_list_instr(list_items->list_instr, list_dup, error);
      if (error != ERROR_NONE)
        return (res);
    }
  }

  return (res);
}

