/**
** @file		free_tree_expr.c
** @brief		Free a tree binary.
** @author		maarek_j
**
*/

#include <unistd.h>
#include <stdlib.h>
#include "eval_expr.h"

void			free_tree_expr(s_tree_expr	*tree)
{
  if (tree)
  {
      mfree(tree->value);
      free_tree_expr(tree->son_left);
      free_tree_expr(tree->son_right);
      mfree(tree);
  }
}
