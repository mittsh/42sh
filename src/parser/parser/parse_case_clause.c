#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

#define TK_NL TK_NEWLINE

#define IF_CLAUSE                                       \
  {                                                     \
    if (NULL == list_c_items)                           \
      return (NULL);                                    \
    else                                                \
    {                                                   \
        lexer_eat_token(lex);                           \
        return (list_c_items);                          \
    }                                                   \
  }

static inline s_list_c_items    *parse_add_c_item(s_lexer               *lex,
                                                  s_list_c_items        *lc_it)
{
  s_list_c_items                *lc_its = NULL;

  if (NULL == (lc_it = parse_case_item(lex)))
    return (NULL);

  lc_its = add_item_in_list_items(lc_its,
                                  lc_it->list_words,
                                  lc_it->list_instr);

  return (lc_its);
}

#define FREE_LCITEMS_RETURN(List_c_items)                      \
  {                                                            \
    if (List_c_items)                                          \
      free_list_c_items(List_c_items);                         \
    return (NULL);                                             \
  }

s_list_c_items                  *parse_case_clause(s_lexer              *lex)
{
  s_token                       *tok = NULL;
  s_list_c_items                *list_c_items = NULL;

  if (NULL == (list_c_items = parse_add_c_item(lex, list_c_items)))
    return (NULL);

  while (((NULL != (tok = lexer_get_token(lex))) && (!strcmp(tok->str, ";;"))))
  {
      lexer_eat_token(lex);
      while ((NULL != (tok = lexer_get_token(lex))) && (tok->type == TK_NL))
        lexer_eat_token(lex);
      if (tok == NULL)
        FREE_LCITEMS_RETURN(list_c_items);
      if ((NULL == (list_c_items = parse_add_c_item(lex, list_c_items))) ||
          ((NULL != lexer_next_token(lex)) &&
           !strcmp(lexer_next_token(lex)->str, "esac")))
        IF_CLAUSE;
  }

  if (tok == NULL)
    FREE_LCITEMS_RETURN(list_c_items);

  if (!strcmp(tok->str, ";;"))
    lexer_eat_token(lex);
  while ((NULL != (tok = lexer_get_token(lex))) && (tok->type == TK_NEWLINE))
    lexer_eat_token(lex);

  return (list_c_items);
}
