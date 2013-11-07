#include "../../src/mstream/mstream.h"
#include "../../src/42sh/shell.h"

s_shell                 *g_shell = NULL;

int                     main(void)
{
  FILE                  *f[10];
  int                   filedes[10];

  g_shell = malloc(sizeof (s_shell));

  mmalloc_init();
  mstream_init();

  filedes[0] = mopen("/micha", O_RDONLY, 0);

  mstream_debug();

  f[0] = mfopen("/micha", "r+");

  mstream_debug();

  mclose(filedes[0]);

  mstream_debug();

  f[1] = mfdopen(STDOUT_FILENO, "r");

  mstream_debug();

  mfclose(f[1]);

  mstream_debug();

  mstream_close();
  mmalloc_free();

  free(g_shell);

  return (0);
}
