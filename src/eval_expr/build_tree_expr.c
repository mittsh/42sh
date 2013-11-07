#include <unistd.h>
#include <stdlib.h>
#include "eval_expr.h"

s_tree_expr			*build_tree_expr(e_type_expr	type,
						 char		*value,
						 s_tree_expr	*sl,
						 s_tree_expr	*sr)
{
  s_tree_expr                   *res = NULL;

  if (NULL == (res = mcalloc(1, sizeof (s_tree_expr))))
    return (NULL);

  res->type = type;
  res->value = value;
  res->son_left = sl;
  res->son_right = sr;

  return (res);
}
