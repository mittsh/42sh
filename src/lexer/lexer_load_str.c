#include "lexer.h"

int                     lexer_load_str(s_lexer          *lexer,
                                       char             *str)
{
  if (lexer == NULL || str == NULL)
    return (0);

  if (lexer->input_str != NULL)
    return (0);

  lexer->input_str = str;

  return (1);
}
