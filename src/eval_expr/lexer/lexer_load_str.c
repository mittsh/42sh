#include "lexer.h"

int                     eelex_load_str(s_eelex          *eelex,
                                       char             *str)
{
  if (eelex == NULL || str == NULL)
    return (0);

  if (eelex->input_str != NULL)
    return (0);

  if ((eelex->input_str = mmalloc(strlen(str) + 1)) == NULL)
    return (0);

  strcpy(eelex->input_str, str);

  return (1);
}
