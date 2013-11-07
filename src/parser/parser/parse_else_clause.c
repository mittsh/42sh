/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

#define FREE_LIST_RETURN(List_instr, List_instr2, Instr)       \
  {                                                            \
    if (List_instr)                                            \
      free_list_instr(List_instr);                             \
    if (List_instr2)                                           \
      free_list_instr(List_instr2);                            \
    if (Instr)                                                 \
      free_instr(Instr);                                       \
    return (NULL);                                             \
  }

s_instr                         *parse_else_clause(s_lexer      *lex)
{
  s_list_instr                  *list_cond = NULL;
  s_list_instr                  *list_instr_t = NULL;
  s_instr                       *instr_f = NULL;
  s_token                       *tok;

  if ((NULL == (tok = lexer_get_token(lex))) || (strcmp(tok->str, "else") &&
                                                 strcmp(tok->str, "elif")))
  {
      errno = ENOTFOUND;
      return (NULL);
  }

  lexer_eat_token(lex);

  if (0 == strcmp(tok->str, "else"))
  {
      if (NULL == (list_instr_t = parse_compound_list(lex)))
        return (NULL);
  }
  else
    if (NULL == (list_cond = parse_compound_list(lex)) ||
        (NULL == (tok = lexer_pop_token(lex))) ||
        (strcmp(tok->str, "then")) ||
        (NULL == (list_instr_t = parse_compound_list(lex))) ||
        ((NULL == (instr_f = parse_else_clause(lex))) && (errno != ENOTFOUND)))
      FREE_LIST_RETURN(list_cond, list_instr_t, instr_f);

  return (build_instr(AST_INSTR_IF,
                      build_instr_if(list_cond, list_instr_t, instr_f)));
}
