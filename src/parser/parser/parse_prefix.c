/**
** @author maarek_j
** @date Wed Nov 10 13:23:43 2010
*/
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

static inline bool      test_chevron(s_token            *tok)
{
  if ((tok) && ((0 == strcmp(tok->str, ">")) ||
                (0 == strcmp(tok->str, "<")) ||
                (0 == strcmp(tok->str, ">>")) ||
                (0 == strcmp(tok->str, "<<")) ||
                (0 == strcmp(tok->str, "<<-")) ||
                (0 == strcmp(tok->str, ">&")) ||
                (0 == strcmp(tok->str, "<&")) ||
                (0 == strcmp(tok->str, ">|")) ||
                (0 == strcmp(tok->str, "<>"))))
    return (true);
  else
    return (false);
}

static inline bool      is_number(s_token               *tok)
{
  int                   i = 0;

  if (!tok)
    return (false);

  i = strlen(tok->str);
  i--;
  while (i >= 0)
  {
      if ((tok->str[i] < '0') || (tok->str[i] > '9'))
        break;
      i--;
  }

  return (i == -1);
}

static inline bool     must_redir(s_token               *tok,
                                  s_token               *tok_next)
{
  if (!tok)
    return (false);

  if (true == test_chevron(tok))
    return (true);

  if (false == is_number(tok))
    return (false);

  if (!tok_next)
    return (false);

  if (false == test_chevron(tok_next))
    return (false);

  if (true == tok_next->is_after_space)
    return (false);

  return (true);
}

#define FREE_LIST_WORDS(List_words)                            \
    if (List_words)                                            \
      free_list_words(List_words);                             \

s_instr                 *parse_prefix(s_lexer           *lex)
{
  s_list_words          *list_words = NULL;
  s_token               *tok = NULL;
  s_token               *tok_next = NULL;

  if (NULL == (tok = lexer_get_token(lex)))
    return (NULL);

  tok_next = lexer_next_token(lex);

  if (true == must_redir(tok, tok_next))
    return (build_instr(AST_INSTR_REDIR,
                        build_instr_redir(NULL,
                                          parse_redirection(lex))));

  if (tok)
  {
      lexer_eat_token(lex);
      list_words = mmalloc(sizeof (s_list_words));
      list_words->word = mstring_copy(tok->str);
      list_words->next = NULL;
      return (build_instr(AST_INSTR_CMD,
                          build_instr_cmd(list_words)));
  }

  FREE_LIST_WORDS(list_words);
  return (NULL);
}
