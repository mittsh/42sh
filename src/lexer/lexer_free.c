#include "lexer.h"

/**
** @brief               Frees one token.
** @param token         Input token to free.
** @return              void
*/
static void             lexer_free_token(s_token        *token)
{
  if (token == NULL)
    return;

  if (token->str != NULL)
    mfree(token->str);

  mfree(token);
}

void                    lexer_free(s_lexer              *lexer)
{
  s_token_list          *token_list = NULL;
  s_token_list          *token_list_next = NULL;

  if (lexer == NULL)
    return;

  token_list = lexer->token_list;

  while (token_list != NULL)
  {
    token_list_next = token_list->next;
    lexer_free_token(token_list->token);
    mfree(token_list);
    token_list = token_list_next;
  }

  mfree(lexer);
}
