#include "lexer.h"

s_eelex                 *eelex_init(void)
{
  s_eelex               *eelex = NULL;

  if ((eelex = mmalloc(sizeof (s_eelex))) == NULL)
    return (NULL);

  eelex->input_str = NULL;
  eelex->token_list = NULL;
  eelex->current_token = NULL;
  eelex->last_token = NULL;

  return (eelex);
}
