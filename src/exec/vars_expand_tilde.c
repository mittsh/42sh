#include "vars.h"

/**
** @brief               Matches ~+ and expands it.
** @param str           Input string.
** @param i             Input/output position pointer.
** @param dynstr        Target dynamic string.
** @return              Returns 1 if found, 0 else.
*/
static inline int       match_tilde_plus(char                   **str,
                                         int                    *i,
                                         s_dynamic_string       *dynstr)
{
  if (*(*str + 1) == '+' && (*(*str + 2) == '/' || *(*str + 2) == '\0'))
  {
    dynamic_string_pushs(dynstr, masso_get(g_shell->vars, "PWD"));
    *str += 1;
    *i += 2;
    return (1);
  }

  return (0);
}

/**
** @brief               Matches ~- and expands it.
** @param str           Input string.
** @param i             Input/output position pointer.
** @param dynstr        Target dynamic string.
** @return              Returns 1 if found, 0 else.
*/
static inline int       match_tilde_less(char                   **str,
                                         int                    *i,
                                         s_dynamic_string       *dynstr)
{
  if (*(*str + 1) == '-' && (*(*str + 2) == '/' || *(*str + 2) == '\0'))
  {
    dynamic_string_pushs(dynstr, masso_get(g_shell->vars, "OLDPWD"));
    *str += 1;
    *i += 2;
    return (1);
  }

  return (0);
}

/**
** @brief               Matches ~ and expands it.
** @param str           Input string.
** @param i             Input/output position pointer.
** @param dynstr        Target dynamic string.
** @return              Returns 1 if found, 0 else.
*/
static inline int       match_tilde_simple(char                 **str,
                                           int                  *i,
                                           s_dynamic_string     *dynstr)
{
  if (*(*str + 1) == '/' || *(*str + 1) == '\0')
  {
    dynamic_string_pushs(dynstr, masso_get(g_shell->vars, "HOME"));
    i += 1;
    return (1);
  }

  return (0);
}

char                    *vars_expand_tilde(char                 *str)
{
  s_dynamic_string      *dynstr = NULL;
  int                   i = 0;
  char                  *res = NULL;
  char                  *old = str;

  dynstr = dynamic_string_init();

  for (; *str != '\0'; str++)
  {
    if (i == 0 && *str == '~')
    {
      if (match_tilde_plus(&str, &i, dynstr))
        continue;
      if (match_tilde_less(&str, &i, dynstr))
        continue;
      if (match_tilde_simple(&str, &i, dynstr))
        continue;
    }
    dynamic_string_push(dynstr, *str);
    i++;
  }

  res = dynstr->str;

  mfree(dynstr);
  mfree(old);

  return (res);
}
