#include <stdbool.h>
#include "lexer.h"

static char             *eelex_get_separator(char       *str)
{
  if (*str == '*' && *(str + 1) == '*')
    return (str + 2);

  if (*str == '&' && *(str + 1) == '&')
    return (str + 2);

  if (*str == '|' && *(str + 1) == '|')
    return (str + 2);

  if (*str == '-' || *str == '+' || *str == '*' || *str == '/' ||
      *str == '^' || *str == ' ' || *str == '!' || *str == '~' ||
      *str == '(' || *str == ')' || *str == '\t' || *str == '&' || *str == '|')
    return (str + 1);

  return (str);
}

static inline bool	is_num(char			*str)
{
  for (int i = 0; str[i] != '\0'; i++)
    if (str[i] < '0' || str[i] > '9')
      return (false);

  return (true);
}

static e_token_type     eelex_get_token_type(char       *token_str)
{
  if (*token_str == '(')
    return (TK_PAREN_BEGIN);
  if (*token_str == ')')
    return (TK_PAREN_END);

  if ((token_str[0] == '*') && (token_str[1] == '*'))
    return (TK_OPE_POWER);

  if ((*token_str == '!') || (*token_str == '~'))
    return (TK_OPE_ONE);

  if (*token_str == '*' || *token_str == '/')
    return (TK_OPE_HIGH);

  if (*token_str == '-' || *token_str == '+')
    return (TK_OPE_LOW);

  if (true == is_num(token_str))
    return (TK_NUM);

  return (TK_OTHER);
}

static inline void      eelex_push_tk_ls(s_eelex        *eelex,
                                         s_token_list   *token_list_item)
{
  if (eelex->token_list == NULL)
    eelex->token_list = token_list_item;
  if (eelex->last_token != NULL)
    eelex->last_token->next = token_list_item;
  eelex->last_token = token_list_item;
}

/**
** @brief               Adds a new token in the lexer list.
**                      Warning ! This function supposes that lexer is well
**                      defined (no test is done) as well as token_str which
**                      is not copied.
** @param eelex         Target lexer.
** @param token_str     Input token string.
** @param line          Token line.
** @param col           Token column.
** @return              Returns 1 if success, 0 else.
*/

static inline int       eelex_push_token(s_eelex        *eelex,
                                         char           *token_str,
                                         unsigned int   line,
                                         unsigned int   col)
{
  s_token_list          *token_list_item = NULL;
  s_token               *token = NULL;

  if (strlen(token_str) == 0 || *token_str == ' ' || *token_str == '\t')
  {
      mfree(token_str);
      eelex->is_last_matched_space = true;
      return (0);
  }

  if ((token = mmalloc(sizeof (s_token))) == NULL)
    return (0);

  if ((token_list_item = mmalloc(sizeof (s_token_list))) == NULL)
  {
      mfree(token);
      return (0);
  }

  token->str = token_str;
  token->type = eelex_get_token_type(token_str);
  token->line = line;
  token->col = col;
  token->is_after_space = eelex->is_last_matched_space;

  token_list_item->token = token;
  token_list_item->next = NULL;

  eelex_push_tk_ls(eelex, token_list_item);

  eelex->is_last_matched_space = false;

  return (1);
}

static char             *eelex_strmake(char             *begin,
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

int                     eelex_action(s_eelex            *eelex)
{
  char                  *str = NULL;
  unsigned int          line = 1;
  unsigned int          col = 0;
  char                  *cur_token = NULL;
  char                  *end_separator = NULL;

  if (eelex == NULL || eelex->input_str == NULL)
    return (0);

  str = eelex->input_str;
  cur_token = str;

  while (*str != '\0')
    if ((end_separator = eelex_get_separator(str)) != str ||
        (end_separator = eelex_match_quotes(str)) != str)
    {
	col = str - (eelex->input_str);
	eelex_push_token(eelex, eelex_strmake(cur_token, str), line, col);
	eelex_push_token(eelex, eelex_strmake(str, end_separator), line, col);
	str = end_separator;
	cur_token = str;
    }
    else
      str = end_separator + 1;

  eelex_push_token(eelex, eelex_strmake(cur_token, str), line, col);

  eelex->current_token = eelex->token_list;

  return (0);
}
