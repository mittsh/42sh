#include "lexer.h"

/**
** @brief               Gets lexer separator.
** @param str           Input string.
** @return              Returns new string offset;
*/
static char             *lexer_get_separator(char       *str)
{
  if (*str == '<' && *(str + 1) == '<' && *(str + 2) == '-')
    return (str + 3);

  if (*str == '>' && *(str + 1) == '|')
    return (str + 2);

  if (*str == '<' && *(str + 1) == '>')
    return (str + 2);

  if ((*str == '>' || *str == '<') && *(str + 1) == '&')
    return (str + 2);

  if (*str == '>' && *(str + 1) == '>')
    return (str + 2);

  if (*str == '$' && (*(str + 1) == '{' || *(str + 1) == '('))
    return (str + 2);

  if (*str == '<' && *(str + 1) == '<')
    return (str + 2);

  if (*str == ';' && *(str + 1) == ';')
    return (str + 2);

  if (*str == '(' || *str == ')' || *str == '{' || *str == '}' ||
      *str == '\n' || *str == ';' || *str == ' ' || *str == '\t' ||
      *str == '<' || *str == '>')
    return (str + 1);

  return (str);
}

/**
** @brief               Gets token type.
** @param token_str     Input token string.
** @return              Returns token type.
*/
static e_token_type     lexer_get_token_type(char       *token_str)
{
  if (*token_str == '\n')
    return (TK_NEWLINE);
  if (*token_str == ';' && *(token_str + 1) == '\0')
    return (TK_EOINST);

  return (TK_OTHER);
}

/**
** @brief               Pushes token on lexer list.
** @param lexer         Input lexer.
** @param token_list_item Input token list items.
** @return              void
*/
static inline void      lexer_push_tk_ls(s_lexer        *lexer,
                                         s_token_list   *token_list_item)
{
  if (lexer->token_list == NULL)
    lexer->token_list = token_list_item;
  if (lexer->last_token != NULL)
    lexer->last_token->next = token_list_item;
  lexer->last_token = token_list_item;
}

/**
** @brief               Adds a new token in the lexer list.
**                      Warning ! This function supposes that lexer is well
**                      defined (no test is done) as well as token_str which
**                      is not copied.
** @param lexer         Target lexer.
** @param token_str     Input token string.
** @param line          Token line.
** @param col           Token column.
** @return              Returns 1 if success, 0 else.
*/

static inline int       lexer_push_token(s_lexer        *lexer,
                                         char           *token_str)
{
  s_token_list          *token_list_item = NULL;
  s_token               *token = NULL;

  if (strlen(token_str) == 0 || *token_str == ' ' || *token_str == '\t' ||
      *token_str == '#')
  {
    lexer->is_last_matched_space = true;
    mfree(token_str);
    return (0);
  }

  if ((token = mmalloc(sizeof (s_token))) == NULL)
    return (0);

  if ((token_list_item = mmalloc(sizeof (s_token_list))) == NULL)
  {
    mfree(token);
    return (0);
  }

  token->str = mstring_copy(token_str);
  token->type = lexer_get_token_type(token_str);
  token->is_after_space = lexer->is_last_matched_space;

  token_list_item->token = token;
  token_list_item->next = NULL;

  lexer_push_tk_ls(lexer, token_list_item);

  lexer->is_last_matched_space = false;

  mfree(token_str);

  return (1);
}

/**
** @brief               Allocated a new string and pushes string
**                      between two input offsets.
** @param begin         Starting offset.
** @param end           Ending offset.
** @return              Returns allocated string.
*/
static char             *lexer_strmake(char             *begin,
                                       char             *end)
{
  char                  *res = NULL;
  char                  *pos = NULL;

  if (end < begin)
    return (NULL);

  if ((res = mmalloc(end - begin + 1)) == NULL)
    return (NULL);

  pos = res;

  for (; begin != end; begin++)
  {
    *pos = *begin;
    pos++;
  }

  *pos = '\0';

  return (res);
}

/**
** @brief               Lexer gets separator function.
** @param str           Input string.
** @param end           Output string.
** @return              Returns 1 if found, 0 else.
*/
static inline int       get_end_separator(char                  *str,
                                          char                  **end)
{
  int                   res = 0;

  res = ((*end = lexer_match_quotes(str)) != str ||
         (*end = lexer_match_arithmetic(str)) != str ||
         (*end = lexer_match_vars(str)) != str ||
         (*end = lexer_match_comment(str)) != str ||
         (*end = lexer_get_separator(str)) != str);

  return (res);
}

/**
** @brief               Ends lexer action by freeing memory and pushing ending
**                      token.
** @param lexer         Input lexer.
** @param dynstr        Input dynamic string.
** @return              Returns 0.
*/
static inline int       lexer_action_end(s_lexer                *lexer,
                                         s_dynamic_string       *dynstr)
{
  lexer_push_token(lexer, mstring_copy(dynstr->str));

  lexer->current_token = lexer->token_list;

  dynamic_string_free(dynstr);

  return (0);
}

int                     lexer_action(s_lexer            *lexer)
{
  char                  *str = NULL;
  char                  *end_separator = NULL;
  s_dynamic_string      *dynstr = NULL;

  if (lexer == NULL || lexer->input_str == NULL)
    return (0);

  str = lexer->input_str;

  dynstr = dynamic_string_init();

  while (*str != '\0')
    if (get_end_separator(str, &end_separator))
    {
      lexer_push_token(lexer, mstring_copy(dynstr->str));
      lexer_push_token(lexer, lexer_strmake(str, end_separator));
      str = end_separator;
      dynamic_string_free(dynstr);
      dynstr = dynamic_string_init();
    }
    else
    {
      if (*str != '\\')
        dynamic_string_push(dynstr, *str);

      if (*str == '\\' && *(str + 1) != '\0' && str++)
        dynamic_string_push(dynstr, *str);

      str++;
    }

  return (lexer_action_end(lexer, dynstr));
}
