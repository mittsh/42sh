#include "lexer.h"

void                    eelex_eat_token(s_eelex         *eelex)
{
  if (eelex == NULL || eelex->current_token == NULL)
    return;

  eelex->current_token = eelex->current_token->next;
}
