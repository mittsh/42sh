/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/
#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

#define FREE_LIST_RETURN(List_instr)                  \
  {                                                   \
    if (List_instr)                                   \
      free_list_instr(List_instr);                    \
    return (NULL);                                    \
  }

s_list_instr                    *parse_list(s_lexer             *lex)
{
  s_instr                       *instr = NULL;
  s_token                       *tok = NULL;
  s_list_instr                  *list_instr = NULL;

  list_instr = build_list_instr();

  if (NULL == (instr = parse_and_or(lex)))
    FREE_LIST_RETURN(list_instr);

  if (NULL == (tok = lexer_get_token(lex)))
    return (list_instr = add_instr_in_list(list_instr, instr, false));

  list_instr = add_instr_in_list(list_instr, instr,
                                 (0 == strcmp(tok->str, "&")) ? true : false);

  tok = lexer_get_token(lex);
  while ((tok != NULL) && ((tok->type == TK_EOINST) ||
                           (0 == strcmp(tok->str, "&"))))
  {
      lexer_eat_token(lex);

      if (NULL == (instr = parse_and_or(lex)))
        return (list_instr);

      list_instr = add_instr_in_list(list_instr, instr,
                                     (!strcmp(tok->str, "&")) ? true : false);
  }

  return (list_instr);
}
