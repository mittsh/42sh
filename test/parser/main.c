#include "../../src/parser/ast.h"
#include "../../src/parser/parser.h"
#include "../../src/print_ast/print_ast.h"
#include <stdlib.h>
#include <unistd.h>

s_shell                 *g_shell = NULL;

int                     main(int        argc,
                             char       *argv[])
{
  t_ast                 *ast = NULL;
  char                  str[] =
    "myfunc() { "
        "echo HelloWorld ;"
        "echo Again ;"
        "python plop.py | cat -n | wc -l;"
        "while [ var -ne 0; var -ne 42 ] "
        "do "
          "echo bobo ;"
          "ls folder ;"
        "done "
    "} ;"
    "case plop in "
      "cas1) "
        "echo boom;\n\n\n\n\n\n"
          ";;\n\n\n"
      "cas2 | cas3 | case4 )\n\n\n"
        "ls boom; "
    "esac;"
    "(echo joseph; echo list) > stdout.txt 2> stderr.txt;"
    "{echo joseph; echo list};"
    "pipe1 | pipe2 | pipe3;"
    "if echo pipe | ls pipe2 then "
      "if echo true || echo false; then "
        "echo tata; "
        "cd directory;"
      "fi;"
      "cd directory;"
    "fi;"
    "if echo true && echo false; then "
      "echo ift; "
    "elif true; then "
      "echo elift; "
    "else "
      "echo elset; "
    "fi;"
    "if echo true || echo false \n"
    "then \n"
    "  echo joseph \n"
    "  echo false \n"
    "fi;"
    "for i in 1 2 3 4 5 6 7 8 9; do "
    "  echo $i ;"
    "  echo $i ;"
    "  echo $i ;"
    "  echo $i ;"
    "done;"
    ;
  s_lexer               *lex = NULL;

  g_shell = malloc(sizeof (s_shell));
  mmalloc_init();
  mstream_init();

  argc = argc;
  argv = argv;

  lex = lexer_init();
  lexer_load_str(lex, str);
  lexer_action(lex);
  ast = parse_input(lex);

  print_ast("ast.png", ast);

  lexer_free(lex);
  free_list_instr(ast);

  mstream_close();
  mmalloc_free();
  free(g_shell);

  return (0);
}


