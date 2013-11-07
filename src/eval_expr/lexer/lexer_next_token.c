#include "lexer.h"

s_token                 *eelex_next_token(s_eelex       *eelex)
{
  if (eelex == NULL || eelex->current_token == NULL)
    return (NULL);

  if (eelex->current_token->next == NULL)
    return (NULL);

  return (eelex->current_token->next->token);
}
