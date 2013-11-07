#include <stdio.h>
#include "../eval_expr/eval_expr.h"
#include "vars.h"

/**
** @brief               A shorter name for ERROR_EVALEXPR.
*/
#define ERVLX ERROR_EVALEXPR

/**
** @brief               Pushes result on string.
** @param end           Ending string.
** @param dynstr        Target dynamic string.
** @return              Arithmetic evaluation error value.
*/
static inline int       push_res(char                           *begin,
                                 char                           *end,
                                 s_dynamic_string               *dynstr)
{
  char                  *tmp = NULL;
  char                  *buf = NULL;
  int                   error;

  tmp = mstring_fromflags(begin, end + 1);
  buf = eval_expr(tmp, &error);
  if (error == ERROR_EVALEXPR)
  {
    fprintf(stderr, "42sh: %s: division by 0\n", tmp);
    mfree(tmp);
    return (ERROR_EVALEXPR);
  }
  else
    dynamic_string_pushs(dynstr, buf);

  mfree(tmp);
  mfree(buf);
  return (ERROR_NONE);
}

/**
** @brief               Frees memory, sets error and return result.
** @param dynstr        Target dynamic string.
** @param old           Old string.
** @param error         Error repording pointer.
** @param set_error     Error repording new value.
** @return              Returns output string.
*/
static inline char      *free_return_set(s_dynamic_string       *dynstr,
                                         char                   *old,
                                         int                    *error,
                                         int                    set_error)
{
  char                  *res = NULL;

  res = dynstr->str;
  mfree(dynstr);
  mfree(old);

  *error = set_error;

  return (res);
}

/**
** @brief               Frees a pointer and returns 1 in case of success.
** @param ptr           Target pointer.
** @return              Returns 1 in case of success.
*/
static inline int       freen(void                              *ptr)
{
  mfree(ptr);

  return (1);
}

/**
** @brief               Expands and pushes when state in on 0.
** @param dynstr        Target dynamic string.
** @param c             Target parameter.
** @param state         Target state.
** @return              void
*/
static inline void      expand_auto_push(s_dynamic_string       *dynstr,
                                         char                   c,
                                         int                    state)
{
  if (state == 0)
    dynamic_string_push(dynstr, c);
}

char                    *vars_expand_arithmetic(char            *str,
                                                int             *error)
{
  int                   state = 0;
  s_dynamic_string      *dynstr = NULL;
  char                  *tmp = str;
  int                   ct = 0;
  char                  *begin = NULL;
  char                  *old = str;

  for (dynstr = dynamic_string_init(); *tmp != '\0'; tmp++)
  {
    if (*tmp == '$' && *(tmp + 1) == '(' &&
        state == 0 && (state = 1) && (begin = tmp) && (ct = 0) == 0)
      continue;

    if (*tmp == '(' && state == 1)
      ct++;

    if (*tmp == ')' && state == 1 && (--ct) == 0 && (state = 0) == 0)
    {
      if (ERVLX == (*error = push_res(begin, tmp, dynstr)) && freen(dynstr))
        return (NULL);

      continue;
    }

    expand_auto_push(dynstr, *tmp, state);
  }

  if (state == 1 && ERVLX == (*error = push_res(begin, tmp, dynstr)) &&
      freen(dynstr))
    return (NULL);

  return (free_return_set(dynstr, old, error, ERROR_NONE));
}
