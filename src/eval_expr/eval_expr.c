/**
** @author maarek_j
*/

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "eval_expr.h"
#include "lexer/lexer.h"
#include "../42sh/error.h"

/**
** @brief               Matches a numerical expression.
** @param tree          Input tree node.
** @param error         Error return value.
** @return              Returns 0 if fail, numeric value else.
*/
static long long int		parc_prof(s_tree_expr	        *tree,
                                          int                   *error);

/**
** @brief               Matches left expression.
*/
#define PARC_LEFT()                             \
  parc_prof(tree->son_left, error)

/**
** @brief               Matches right expression.
*/
#define PARC_RIGHT()                            \
  parc_prof(tree->son_right, error)

/**
** @brief               Evaluates division.
** @param tree          Input tree node.
** @param error         Error return value.
** @return              Returns numerical value of the operation.
*/
static inline long long int     eval_div(s_tree_expr	        *tree,
                                         int                    *error)
{
  long long int                 y;
  long long int                 x;

  x = PARC_LEFT();
  y = PARC_RIGHT();

  if (y == 0)
  {
    *error = ERROR_EVALEXPR;
    return (0);
  }

  return (x / y);
}

/**
** @brief               Evaluates a binary operator expression.
** @param tree          Input tree node.
** @param error         Error return value.
** @return              Returns numerical value of the operation.
*/
static inline long long int	eval_bin(s_tree_expr      	*tree,
                                         int                    *error)
{
  if (!tree)
    return (0);

  if (0 == strcmp(tree->value, "**"))
    return (powl(PARC_LEFT(), PARC_RIGHT()));
  if (0 == strcmp(tree->value, "&&"))
    return (PARC_LEFT() && PARC_RIGHT());
  if (0 == strcmp(tree->value, "||"))
    return (PARC_LEFT() || PARC_RIGHT());
  if (tree->value[0] == '&')
    return (PARC_LEFT() & PARC_RIGHT());
  if (tree->value[0] == '|')
    return (PARC_LEFT() | PARC_RIGHT());
  if (tree->value[0] == '^')
    return (PARC_LEFT() ^ PARC_RIGHT());
  if (tree->value[0] == '+')
    return (PARC_LEFT() + PARC_RIGHT());
  if (tree->value[0] == '*')
    return (PARC_LEFT() * PARC_RIGHT());
  if (tree->value[0] == '-')
    return (PARC_LEFT() - PARC_RIGHT());
  if (tree->value[0] == '/')
    return (eval_div(tree, error));

  return (0);
}

/**
** @brief               Evaluates an unary operator expression.
** @param tree          Input tree node.
** @param error         Error return value.
** @return              Returns numerical value of the operation.
*/
static inline long long int	eval_one(s_tree_expr  	        *tree,
                                         int                    *error)
{
  if (!tree)
    return (0);

  if (tree->value[0] == '+')
    return (PARC_LEFT());
  if (tree->value[0] == '-')
    return (- PARC_LEFT());
  if (tree->value[0] == '~')
    return (- PARC_LEFT() - 1);
  if (tree->value[0] == '!')
  {
      if (0 == PARC_LEFT())
	return (1);
      else
	return (0);
  }

  return (0);
}

static long long int		parc_prof(s_tree_expr           *tree,
                                          int                   *error)
{
  if (NULL == tree)
    return (0);
  else
    if (tree->type == EXPR_TYPE_NUM)
      return (atoi(tree->value));
    else
      if (tree->type == EXPR_TYPE_BIN)
	return (eval_bin(tree, error));
      else
	return (eval_one(tree, error));

  return (0);
}

/**
** @brief               Do not matches dollar expression.
** @param str           Input string.
** @return              Returns input string without dollars.
*/
static inline char              *skip_dollar(char                *str)
{
  size_t                        len;
  size_t                        i;
  char                          *res = NULL;

  if (!str)
    return (NULL);

  len = strlen(str);
  res = mcalloc(len + 1, sizeof (char));
  for (i = 0; i < len; i++)
    if (str[i] != '$')
      sprintf(res, "%s%c", res, str[i]);

  res = mrealloc(res, (i + 1) * sizeof (char));

  return (res);
}

/**
** @brief               Frees all allocated heap memory from calling function.
*/
#define FREE_ALL()                                              \
  mfree(str2);                                                  \
  eelex_free(lex);                                              \
  free_tree_expr(tree)

char                            *eval_expr(char                 *str,
                                           int                  *error)
{
  s_eelex                       *lex = NULL;
  s_tree_expr                   *tree = NULL;
  char                          *res = NULL;
  char                          *str2 = NULL;
  long long int                 res_int;

  lex = eelex_init();
  str2 = skip_dollar(str);

  if (0 == eelex_load_str(lex, str2))
    return (NULL);
  eelex_action(lex);

  tree = parse_input_expr(lex);
  *error = ERROR_NONE;
  res_int = parc_prof(tree, error);

  if (*error != ERROR_NONE)
    return (NULL);

  res = mcalloc(200 , sizeof (char));
  sprintf(res, "%lld", res_int);

  FREE_ALL();

  return (res);
}
