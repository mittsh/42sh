#include "../../src/mmalloc/mmalloc.h"
#include "../../src/42sh/shell.h"

s_shell                 *g_shell = NULL;

int                     main(void)
{
  void                  *m[10];

  g_shell = malloc(sizeof (s_shell));

  mmalloc_init();

  m[0] = mcalloc(1, sizeof (char));
  m[1] = mmalloc(sizeof (long int));
  m[2] = mmalloc(sizeof (int));
  m[3] = mmalloc(sizeof (int));
  m[4] = mcalloc(5, sizeof (int));
  m[5] = mcalloc(5, sizeof (int));
  m[6] = mcalloc(5, sizeof (int));

  mmalloc_debug();

  m[0] = mrealloc(m[0], sizeof (long int));

  mmalloc_debug();

  mfree(m[2]);

  mmalloc_debug();

  mmalloc_free();

  free(g_shell);

  return (0);
}
