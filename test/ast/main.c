#include "../../src/parser/ast.h"
#include "../../src/parser/parser.h"
#include "../../src/print_ast/print_ast.h"
#include <stdlib.h>
#include <unistd.h>
#include "../../src/mmalloc/mmalloc.h"
#include "../../src/mstream/mstream.h"

s_shell                 *g_shell = NULL;

int                     main(int        argc,
			     char       *argv[])
{
  s_list_instr	        *ast = NULL;
  s_instr               *instr = NULL;
  s_instr               *instr_a = NULL;
  s_instr               *instr_b = NULL;
  s_instr               *instr_c = NULL;
  s_list_instr          *instr_lists[16];
  s_instr               *instrs[16];
  s_list_words          lists_words[16];

  g_shell = malloc(sizeof (s_shell));
  mmalloc_init();
  mstream_init();

  argc = argc;
  argv = argv;

  lists_words[0].word = "echo";
  lists_words[0].next = &lists_words[1];
  lists_words[1].word = "tata";
  lists_words[1].next = NULL;
  instr_a = build_instr(AST_INSTR_CMD, build_instr_cmd(&lists_words[0]));

  lists_words[2].word = "exit";
  lists_words[2].next = NULL;
  instr_c = build_instr(AST_INSTR_CMD, build_instr_cmd(&lists_words[2]));
  instr_b = build_instr(AST_INSTR_NOT, build_instr_not(instr_c));

  instr = build_instr(AST_INSTR_AND, build_instr_and(instr_a, instr_b));

  instr_lists[0] = build_list_instr();
  instr_lists[0]= add_instr_in_list(instr_lists[0], instr, false);




  lists_words[3].word = "true";
  lists_words[3].next = NULL;
  instrs[0] = build_instr(AST_INSTR_CMD, build_instr_cmd(&lists_words[3]));

  instr_lists[1] = build_list_instr();
  instr_lists[1] = add_instr_in_list(instr_lists[1], instrs[0], true);


  instrs[2] = build_instr(AST_INSTR_CMD, build_instr_cmd(NULL));
  instrs[1] = build_instr(AST_INSTR_IF, build_instr_if(instr_lists[1], instr_lists[0], instrs[2]));

  instrs[1] = build_instr(AST_INSTR_WHILE, build_instr_while(instr_lists[1], instr_lists[0]));

  instrs[1] = build_instr(AST_INSTR_UNTIL, build_instr_until(instr_lists[1], instr_lists[0]));

  ast = add_instr_in_list(ast, instrs[1], false);

  print_ast("ast.dot", ast);

  mstream_close();
  mmalloc_free();
  free(g_shell);

  return (0);
}

