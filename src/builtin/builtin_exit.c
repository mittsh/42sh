#include "builtin.h"

int                     builtin_exit(void)
{
  int                   return_value;

  return_value = g_shell->return_value;

  if (g_shell->term_mode == 1)
    tcsetattr(STDIN_FILENO, TCSANOW, &(g_shell->term_old));

  free_list_instr(g_shell->ast);
  lexer_free(g_shell->lex);

  free_shell(g_shell);

  exit(return_value);

  return (0);
}
