#include "lexer.h"

s_token                 *eelex_get_token(s_eelex        *eelex)
{
  if (eelex == NULL || eelex->current_token == NULL)
    return (NULL);

  return (eelex->current_token->token);
}
