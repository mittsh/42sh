#include "lexer.h"

/**
** @brief               Gets token type string.
** @param token         Input token.
** @return              Returns type string.
*/
static inline char      *get_token_type(s_token         *token)
{
  char                  *token_type = NULL;

  switch (token->type)
  {
    case TK_NEWLINE:
      token_type = "Newline \\n";
      break;
    case TK_EOINST:
      token_type = "Token EOF ;";
      break;
    case TK_OTHER:
      token_type = "Other token";
      break;
    default:
      token_type = "Not found";
      break;
  }

  return (token_type);
}

/**
** @brief               Prints one lexer token.
** @param lexer         Input lexer.
** @param token         Input token.
** @return              void
*/
static void             lexer_print_token(s_lexer       *lexer,
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

  if (lexer->current_token != NULL && token == lexer->current_token->token)
    prefix = ">>";
  else
    prefix = " -";

  printf("  %sToken\t\t%s\t\t>>%s<<%s\n", prefix, token_type, token->str,
         token->is_after_space ? " (after space)" : "");
}

void                    lexer_debug(s_lexer             *lexer)
{
  s_token_list          *token_list = NULL;

  printf("42sh LEXER DEBUGER\n");

  printf("  > Input : >>%s<<\n", lexer->input_str);

  if (lexer == NULL)
  {
    printf(">  Lexer is NULL\n");
    return;
  }

  if (lexer->token_list == NULL)
    printf(">  Lexer token list is EMPTY\n");

  token_list = lexer->token_list;
  for (; token_list != NULL; token_list = token_list->next)
    lexer_print_token(lexer, token_list->token);
}
