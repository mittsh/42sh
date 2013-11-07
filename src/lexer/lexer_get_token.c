#include "lexer.h"

s_token                 *lexer_get_token(s_lexer        *lexer)
{
  if (lexer == NULL || lexer->current_token == NULL)
    return (NULL);

  return (lexer->current_token->token);
}
