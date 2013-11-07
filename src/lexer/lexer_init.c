#include "lexer.h"

s_lexer                 *lexer_init(void)
{
  s_lexer               *lexer = NULL;

  if ((lexer = mmalloc(sizeof (s_lexer))) == NULL)
    return (NULL);

  lexer->input_str = NULL;
  lexer->token_list = NULL;
  lexer->current_token = NULL;
  lexer->last_token = NULL;
  lexer->is_last_matched_space = false;

  return (lexer);
}
