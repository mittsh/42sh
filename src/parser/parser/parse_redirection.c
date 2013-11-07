/**
** @author maarek_j
** @date Sun Nov  7 18:38:14 2010
*/
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "../ast.h"
#include "../../lexer/lexer.h"

static inline bool              test_chevron(s_token            *tok)
{
  if ((tok) && ((0 == strcmp(tok->str, ">")) ||
                (0 == strcmp(tok->str, "<")) ||
                (0 == strcmp(tok->str, ">>")) ||
                (0 == strcmp(tok->str, "<<")) ||
                (0 == strcmp(tok->str, "<<-")) ||
                (0 == strcmp(tok->str, ">&")) ||
                (0 == strcmp(tok->str, "<&")) ||
                (0 == strcmp(tok->str, ">|")) ||
                (0 == strcmp(tok->str, "<>"))))
    return (true);
  else
    return (false);
}

static inline e_redir_type      type_redir(s_token              *tok)
{
  if ((0 == strcmp(tok->str, ">")) ||
      (0 == strcmp(tok->str, ">|")))
    return (AST_REDIR_OUT_TRUNC);

  if (0 == strcmp(tok->str, "<"))
    return (AST_REDIR_INPUT);

  if (0 == strcmp(tok->str, ">>"))
    return (AST_REDIR_OUT_APPEND);

  if ((0 == strcmp(tok->str, "<<")) ||
      (0 == strcmp(tok->str, "<<-")))
    return (AST_REDIR_HERE_DOC);

  if (0 == strcmp(tok->str, ">&"))
    return (AST_REDIR_OUTPUT_DUP);

  if (0 == strcmp(tok->str, "<&"))
    return (AST_REDIR_INPUT_DUP);

  if (0 == strcmp(tok->str, "<>"))
    return (AST_REDIR_RDWR);

  return (-1);
}

s_list_redir                    *parse_redirection(s_lexer      *lex)
{
  s_list_redir                  *list_redir = NULL;
  s_token                       *tok = NULL;
  s_token                       *word = NULL;
  s_token                       *ionumber = NULL;

  if (NULL == (tok = lexer_pop_token(lex)))
    return (NULL);

  if (false == test_chevron(tok) && (ionumber = tok) == tok)
      if (false == (test_chevron(tok = lexer_pop_token(lex))))
        return (NULL);

  if (NULL == (word = lexer_pop_token(lex)))
    return (NULL);

  list_redir = mcalloc(1, sizeof (s_list_redir));
  list_redir->type = type_redir(tok);
  list_redir->word = mstring_copy(word->str);
  if (list_redir->type == AST_REDIR_INPUT ||
      list_redir->type == AST_REDIR_RDWR)
    list_redir->ionumber = mstring_copy("0");
  else
    list_redir->ionumber = mstring_copy("1");
  if (ionumber)
    list_redir->ionumber = mstring_copy(ionumber->str);
  list_redir->next = NULL;

  return (list_redir);
}

