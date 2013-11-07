#include "lexer.h"

/**
** @brief               Matches en opened quote.
** @param str           Input string.
** @param type          Input token type.
** @return              Returns new offset.
*/
static char             *lexer_quote_open_eat(char              *str,
                                              e_lexer_quoting   type)
{
  switch (type)
  {
    case QT_SIMPLE:
    case QT_DOUBLE:
    case QT_BACK:
      return (str + 1);
      break;
    default:
      return (str);
      break;
  }
}

/**
** @brief               Gets opened quote type.
** @param str           Input string.
** @return              Returns quoting type.
*/
static e_lexer_quoting  lexer_quote_open(char                   *str)
{
  if (*str == '\'')
    return (QT_SIMPLE);

  if (*str == '"')
    return (QT_DOUBLE);

  return (0);
}

/**
** @brief               Ends the token matching.
** @param str           Input string.
** @param type          Quoting type.
** @return              Returns end offset.
*/
static char             *lexer_quote_match_end(char             *str,
                                               e_lexer_quoting  type)
{
  int                   state = 0;

  switch (type)
  {
    case QT_SIMPLE:
      for (; *str != '\0' && *str != '\''; str++)
        ;
      return (str);
    case QT_DOUBLE:
      for (; *str != '\0'; str++)
      {
        if (state == 0)
        {
          if (*str == '\\')
            state = 1;
          if (*str == '"')
            break;
        }
        else
          state = 0;
      }
      break;
    default:
      break;
  }

  return (str);
}

char                    *lexer_match_quotes(char                *str)
{
  e_lexer_quoting       type;

  if ((type = lexer_quote_open(str)) == 0)
    return (str);

  str = lexer_quote_open_eat(str, type);

  str = lexer_quote_match_end(str, type);

  return (str + 1);
}
