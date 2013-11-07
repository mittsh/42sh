#include "lexer.h"

void                    lexer_eat_token(s_lexer         *lexer)
{
  if (lexer == NULL || lexer->current_token == NULL)
    return;

  lexer->current_token = lexer->current_token->next;
}
