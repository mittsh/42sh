#include "lexer.h"

s_token                 *lexer_next_token(s_lexer       *lexer)
{
  if (lexer == NULL || lexer->current_token == NULL)
    return (NULL);

  if (lexer->current_token->next == NULL)
    return (NULL);

  return (lexer->current_token->next->token);
}
