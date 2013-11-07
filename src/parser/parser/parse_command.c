/**
** @author maarek_j
** @date Wed Nov 10 16:18:20 2010
*/
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

#define IS_SHELL_CMD 1
#define IS_FUNCDEC 2
#define IS_SIMPLE_CMD 3

/**
** @brief                       Decides if the next rules is shell_command,
**                              funcdec or simple_cmd
** @param lex                   The lexer to decide.
** @return                      IS_SHELL_CMD, or IS_FUNCDEC, or IS_SIMPLE_CMD.
*/
static inline int               is_shell_func_simple(s_lexer    *lex)
{
  char                          *str = NULL;
  s_token                       *tok = NULL;

  tok = lexer_get_token(lex);

  if (tok == NULL)
    return (-1);

  str = tok->str;
  if ((0 == strcmp(str, "(")) || (0 == strcmp(str, "{")) ||
      (0 == strcmp(str, "while")) || (0 == strcmp(str, "if")) ||
      (0 == strcmp(str, "for")) || (0 == strcmp(str, "until")) ||
      (0 == strcmp(str, "case")))
    return (IS_SHELL_CMD);

  if (0 == strcmp(str, "function"))
    return (IS_FUNCDEC);

  if ((tok = lexer_next_token(lex)) != NULL && 0 == strcmp(tok->str, "("))
    return (IS_FUNCDEC);

  return (IS_SIMPLE_CMD);
}

static inline bool              test_chevron(s_token            *tok)
{
  if (tok == NULL)
    return (false);

  if ((tok != NULL) && ((0 == strcmp(tok->str, ">")) ||
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

static inline bool              is_redir(s_lexer                *lex)
{
  s_token                       *tok = NULL;

  if (NULL == (tok = lexer_get_token(lex)))
    return (false);

  if (true == test_chevron(tok))
    return (true);
  else
    if (tok != NULL && (tok->str[0] >= '0') && (tok->str[0] <= '9'))
    {
        tok = lexer_next_token(lex);
        if (true == test_chevron(tok))
          return (true);
    }

  return (false);
}

/**
** @brief                       Add a redirection in the list of redirection
** @param list                  List to add a redirection, If @a list == NULL,
**                              the return is @a redir.
** @param redir                 The redirection to add the @a list.
** @return                      A list of redirection.
*/
static inline s_list_redir      *add_redir_in_list(s_list_redir *list,
                                                   s_list_redir *redir)
{
  s_list_redir                  *aux = NULL;

  if (list == NULL)
    return (redir);

  aux = list;
  while (aux->next != NULL)
    aux = aux->next;

  aux->next = redir;

  return (list);
}

#define FREE_LIST_REDIR_RETURN(List_redir)                     \
  {                                                            \
    if (List_redir)                                            \
      free_list_redir(List_redir);                             \
    return (NULL);                                             \
  }

s_instr                         *parse_command(s_lexer          *lex)
{
  s_instr                       *instr = NULL;
  int                           what_is;
  s_list_redir                  *list_redir = NULL;

  what_is = is_shell_func_simple(lex);

  if (what_is < 0)
    return (NULL);

  if (IS_SIMPLE_CMD == what_is)
    return (parse_simple_command(lex));

  if (IS_FUNCDEC == what_is)
    instr = parse_funcdec(lex);

  if (IS_SHELL_CMD == what_is)
    instr = parse_shell_command(lex);

  while (true == is_redir(lex))
    list_redir = add_redir_in_list(list_redir,
                                   parse_redirection(lex));
  if (NULL == instr)
    FREE_LIST_REDIR_RETURN(list_redir);

  if (NULL == list_redir)
    return (instr);
  else
    return (build_instr(AST_INSTR_REDIR,
                        build_instr_redir(instr, list_redir)));
}
