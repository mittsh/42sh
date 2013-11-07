#include "lexer.h"

static void             eelex_free_token(s_token        *token)
{
  if (token == NULL)
    return;

  if (token->str != NULL)
    mfree(token->str);

  mfree(token);
}

void                    eelex_free(s_eelex              *eelex)
{
  s_token_list          *token_list = NULL;
  s_token_list          *token_list_next = NULL;

  if (eelex == NULL)
    return;

  token_list = eelex->token_list;

  while (token_list != NULL)
  {
    token_list_next = token_list->next;
    eelex_free_token(token_list->token);
    mfree(token_list);
    token_list = token_list_next;
  }

  if (eelex->input_str != NULL)
    mfree(eelex->input_str);

  mfree(eelex);
}
