#include "../../src/eval_expr/eval_expr.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

s_shell                 *g_shell = NULL;

int                     main(int        argc,
                             char       *argv[])
{
  s_tree_expr	        *tree = NULL;
  char			*res = NULL;
  int                   error;

  g_shell = malloc(sizeof (s_shell));
  mmalloc_init();
  mstream_init();

  argc = argc;
  argv = argv;

  res = eval_expr(argv[1], &error);
  printf("%s\n", res);

  mfree(res);

  mstream_close();
  mmalloc_free();
  free(g_shell);

  return (0);
}

