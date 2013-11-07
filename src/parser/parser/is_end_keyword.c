/**
** @author maarek_j
** @date Wed Nov 10 14:44:00 2010
*/

#include <stdbool.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

bool                    is_end_keyword(s_token          *tok)
{
  if (NULL == tok)
    return (false);

  if ((0 == strcmp(tok->str, "||")) || (0 == strcmp(tok->str, "&&")) ||
      (0 == strcmp(tok->str, "then")) || (0 == strcmp(tok->str, "fi")) ||
      (0 == strcmp(tok->str, "elif")) || (0 == strcmp(tok->str, "else")) ||
      (0 == strcmp(tok->str, "in")) || (0 == strcmp(tok->str, "do")) ||
      (0 == strcmp(tok->str, "(")) || (0 == strcmp(tok->str, ")")) ||
      (0 == strcmp(tok->str, "{")) || (0 == strcmp(tok->str, "}")) ||
      (0 == strcmp(tok->str, "done")) || (0 == strcmp(tok->str, "case")) ||
      (0 == strcmp(tok->str, "esac")) || (0 == strcmp(tok->str, ";;")) ||
      (0 == strcmp(tok->str, "|")) ||
      (0 == strcmp(tok->str, "&")))
    return (true);
  else
    return (false);

}
