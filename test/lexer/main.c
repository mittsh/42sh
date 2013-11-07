#include "../../src/lexer/lexer.h"

s_shell                 *g_shell = NULL;

int		main(int		argc,
		     char		*argv[])
{
  s_lexer               *lexer = NULL;
  s_token               *token = NULL;

  g_shell = malloc(sizeof (s_shell));
  mmalloc_init();
  mstream_init();

  for (int i = 1; i < argc; i++)
  {
      lexer = lexer_init();
      lexer_load_str(lexer, argv[i]);
      lexer_action(lexer);
      lexer_debug(lexer);
      lexer_free(lexer);
  }

  mstream_close();
  mmalloc_free();
  free(g_shell);

  return (0);
}
