#include "lexer.h"

static inline char      *get_token_type(s_token         *token)
{
  char                  *token_type = NULL;

  switch (token->type)
  {
    case TK_OTHER:
      token_type = "Other token";
      break;
    default:
      token_type = "Not found";
      break;
  }

  return (token_type);
}

static void             eelex_print_token(s_eelex       *eelex,
                                          s_token       *token)
{
  char                  *token_type = NULL;
  char                  *prefix = NULL;

  if (token == NULL)
  {
    printf("  - Token is NULL\n");
    return;
  }

  token_type = get_token_type(token);

  if (eelex->current_token != NULL && token == eelex->current_token->token)
    prefix = ">>";
  else
    prefix = " -";

  printf("  %sToken\t\t%s\t\t>>%s<<%s\n", prefix, token_type, token->str,
         token->is_after_space ? " (after space)" : "");
}

void                    eelex_debug(s_eelex             *eelex)
{
  s_token_list          *token_list = NULL;

  printf("42sh E_LEX DEBUGER\n");

  printf("  > Input : >>%s<<\n", eelex->input_str);

  if (eelex == NULL)
  {
    printf(">  E_Lex is NULL\n");
    return;
  }

  if (eelex->token_list == NULL)
    printf(">  E_Lex token list is EMPTY\n");

  token_list = eelex->token_list;
  for (; token_list != NULL; token_list = token_list->next)
    eelex_print_token(eelex, token_list->token);
}
