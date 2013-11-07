#include "exec.h"

int                     exec_instr_for(s_instr                  *instr,
                                       s_list_dup               *list_dup,
                                       int                      *error)
{
  s_list_words          *list_words = NULL;
  s_instr_for           *instr_for = NULL;
  int                   res = 0;

  if (instr == NULL || instr->instr == NULL)
    return (-1);

  instr_for = instr->instr;

  list_words = instr_for->list_words;
  for (; list_words != NULL; list_words = list_words->next)
  {
    masso_set(g_shell->vars, instr_for->var_name,
              mstring_copy(list_words->word));
    res = exec_list_instr(instr_for->list_instr, list_dup, error);
    if (*error != ERROR_NONE)
      return (res);
  }
  return (res);
}
