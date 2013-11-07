#include "vars.h"

/**
** @brief               Expands variable from begin and end pointers.
** @param begin         Statring string.
** @param end           Ending string.
** @param dynstr        Target dynamic string.
** @return              void
*/
void                    vars_expand_action(char                 *begin,
                                           char                 *str,
                                           s_dynamic_string     *dynstr)
{
  char                  *varname = NULL;
  char                  *varvalue = NULL;

  if (*(begin + 1) == '{' && *(str - 1) == '}')
    varname = mstring_fromflags(begin + 2, str - 1);
  else
    varname = mstring_fromflags(begin + 1, str);

  varvalue = masso_get(g_shell->vars, varname);
  if (varvalue == NULL)
    varvalue = "";
  dynamic_string_pushs(dynstr, varvalue);
}

/**
** @brief               Frees value and returns value.
** @param old           Old string.
** @param dynstr        Target dynamic string.
** @return              Returns output string.
*/
static inline char      *free_and_return(char                   *old,
                                         s_dynamic_string       *dynstr)
{
  char                  *res = NULL;

  res = dynstr->str;

  mfree(dynstr);
  mfree(old);

  return (res);
}

char                    *vars_expand(char                       *str)
{
  int                   state = 0;
  char                  *begin = NULL;
  s_dynamic_string      *dynstr = NULL;
  char                  *old = str;

  dynstr = dynamic_string_init();

  for (; *str != '\0'; str++)
  {
    if (state == 0 && *str == '$' &&
        (*(str + 1) != '\0' && *(str + 1) != ' ') && (state = 1) == 1)
      begin = str;

    if (state == 1 && *str != '$' && (*str == ' ' || *str == '(' ||
        *str == ')' || *(str - 1) == '}') && (state = 0) == 0)
    {
      if (str == begin + 1)
        dynamic_string_push(dynstr, '$');
      else
        vars_expand_action(begin, str, dynstr);
    }

    if (state == 0)
      dynamic_string_push(dynstr, *str);
  }

  if (state == 1)
    vars_expand_action(begin, str, dynstr);

  return (free_and_return(old, dynstr));
}
