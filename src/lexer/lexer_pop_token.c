#include "lexer.h"

inline s_token          *lexer_pop_token(s_lexer        *lexer)
{
  s_token               *token = NULL;

  token = lexer_get_token(lexer);

  lexer_eat_token(lexer);

  return (token);
}
