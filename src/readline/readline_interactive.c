#include "readline.h"

#include "../parser/parser.h"
#include "../lexer/lexer.h"
#include "../parser/ast.h"
#include "../exec/exec.h"
#include "../print_ast/print_ast.h"
#include "../builtin/history.h"

static inline void      get_terminal_status(void)
{
  struct termios        term;

  tcgetattr(STDIN_FILENO, &term);
  g_shell->term_old = term;
  term.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
  g_shell->term_mode = 1;
}

void                    readline_interactive(int                is_print_ast)
{
  s_dynamic_string      *dynstr = NULL;
  int                   error = 0;

  get_terminal_status();

  while (1)
  {
    dynstr = dynamic_string_init();

    g_shell->queue_history = history_add_line(g_shell->queue_history, "");

    if (readline_prompt(dynstr) == false)
      continue;

    g_shell->queue_history->cur = g_shell->queue_history->last;
    history_update(g_shell->queue_history, dynstr->str);

    g_shell->lex = lexer_init();

    if (0 != lexer_load_str(g_shell->lex, dynstr->str))
    {
        lexer_action(g_shell->lex);
        g_shell->ast = parse_input(g_shell->lex);
    }

    dynamic_string_free(dynstr);

    if (is_print_ast == 1)
      print_ast("ast.png", g_shell->ast);

    g_shell->return_value = exec_list_instr(g_shell->ast, NULL, &error);

    free_list_instr(g_shell->ast);

    lexer_free(g_shell->lex);
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &(g_shell->term_old));
}
