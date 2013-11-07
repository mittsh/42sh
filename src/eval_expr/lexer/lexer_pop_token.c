#include "lexer.h"

inline s_token          *eelex_pop_token(s_eelex        *eelex)
{
  s_token               *token = NULL;

  token = eelex_get_token(eelex);

  eelex_eat_token(eelex);

  return (token);
}
