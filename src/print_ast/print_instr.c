#include "print_ast.h"

#define INSTR instr
#define FD fd

#define CASE_PRINT(TYPEMAJ, TYPE)                       \
  case AST_INSTR_ ## TYPEMAJ:                           \
  print_instr_ ## TYPE(INSTR, FD);                      \
  break

void                    print_instr(s_instr                     *instr,
                                    FILE                        *fd)
{
  if (instr == NULL)
    return;

  switch (instr->type)
  {
	  CASE_PRINT(AND, and);
	  CASE_PRINT(OR, or);
	  CASE_PRINT(NOT, not);
	  CASE_PRINT(BRACK, brack);
	  CASE_PRINT(PAREN, paren);
	  CASE_PRINT(PIPE, pipe);
	  CASE_PRINT(REDIR, redir);
	  CASE_PRINT(FUNC, func);
	  CASE_PRINT(IF, if);
	  CASE_PRINT(FOR, for);
	  CASE_PRINT(WHILE, while);
	  CASE_PRINT(UNTIL, until);
	  CASE_PRINT(CASE, case);
	  CASE_PRINT(CMD, cmd);
    default:
      fprintf(fd, "itm%p [label=\"Instruction not found\"]", getptr(instr));
      break;
  }
}
