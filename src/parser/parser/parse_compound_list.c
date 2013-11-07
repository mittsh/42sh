/**
** @author maarek_j
** @date Wed Nov 10 14:44:00 2010
*/

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

#define FREE_LIST_RETURN(List_instr)                           \
  {                                                            \
    if (List_instr)                                            \
      free_list_instr(List_instr);                             \
    return (NULL);                                             \
  }

s_list_instr            *parse_compound_list(s_lexer    *lex)
{
  s_token               *tok = NULL;
  s_instr               *instr = NULL;
  s_list_instr          *list_instr = NULL;

  if (NULL == (tok = skip_newline(lex)) || NULL == (instr = parse_and_or(lex)))
    return (NULL);

  list_instr = add_instr_in_list(list_instr, instr,
                                 (0 == strcmp(tok->str, "&")) ? true : false);

  while ((NULL != (tok = lexer_get_token(lex))) &&
         ((TK_EOINST == tok->type) || (0 == strcmp(tok->str, "&")) ||
          (TK_NEWLINE == tok->type)))
  {
      lexer_eat_token(lex);
      tok = skip_newline(lex);

      if (true == is_end_keyword(lexer_get_token(lex)))
        return (list_instr);

      if (NULL == (instr = parse_and_or(lex)))
        return (NULL);

      if (0 == strcmp(tok->str, "&"))
        list_instr = add_instr_in_list(list_instr, instr, true);
      else
        list_instr = add_instr_in_list(list_instr, instr, false);

      tok = skip_newline(lex);
  }

  return (list_instr);
}
