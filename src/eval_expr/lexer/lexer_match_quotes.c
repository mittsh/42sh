#include "lexer.h"

static char             *eelex_quote_open_eat(char              *str,
                                              e_eelex_quoting   type)
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

static e_eelex_quoting  eelex_quote_open(char                   *str)
{
  if (*str == '\'')
    return (QT_SIMPLE);

  if (*str == '"')
    return (QT_DOUBLE);

  return (0);
}

static char             *eelex_quote_match_end(char             *str,
                                               e_eelex_quoting  type)
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

char                    *eelex_match_quotes(char                *str)
{
  e_eelex_quoting       type;

  if ((type = eelex_quote_open(str)) == 0)
    return (str);

  str = eelex_quote_open_eat(str, type);

  str = eelex_quote_match_end(str, type);

  return (str + 1);
}
