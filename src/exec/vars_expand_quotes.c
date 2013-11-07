#include "vars.h"

/**
** @brief               Frees memory and returns value.
** @param dynstr        Target dynamic string.
** @param old           Old string pointer.
** @return              Returns result value from dynstr.
*/
static inline char      *free_memory_return(s_dynamic_string    *dynstr,
                                            char                *old)
{
  char                  *res = NULL;

  res = dynstr->str;
  mfree(dynstr);
  mfree(old);

  return (res);
}

char                    *vars_expand_quotes(char                *str,
                                            int                 *mode)
{
  s_dynamic_string      *dynstr = NULL;
  char                  *tmp = NULL;
  int                   state = 0;
  char                  *old = str;

  *mode = 0;

  if (*str == '"')
    *mode = 1;
  if (*str == '\'')
    *mode = 2;

  dynstr = dynamic_string_init();

  for (tmp = str; *tmp != '\0'; tmp++)
  {
    if (*mode != 0 && (tmp == str || *(tmp + 1) == '\0'))
      continue;

    if (*mode == 1 && (*tmp == '\\') && state == 0 && (state = 1) == 1)
      continue;

    if (*mode == 1 && (*tmp != '\\' && *tmp != '"') && state == 1)
      dynamic_string_push(dynstr, '\\');
    if (state == 1)
      state = 0;

    dynamic_string_push(dynstr, *tmp);
  }

  return (free_memory_return(dynstr, old));
}
