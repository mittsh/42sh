#include <stdlib.h>
#include <unistd.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

#define BLOCK_CHECK()                                                        \
  while ((NULL != (tok = lexer_get_token(lex))) && (!strcmp(tok->str, "|"))) \
  {                                                                          \
    lexer_eat_token(lex);                                                    \
    if (NULL == (tok = lexer_pop_token(lex)))                                \
      FREE_ALL_RETURN(list_c_item, list_words, list_instr);                  \
                                                                             \
    list_words = add_word(tok->str, list_words);                             \
  }                                                                          \
  if (NULL == tok)                                                           \
    FREE_ALL_RETURN(list_c_item, list_words, list_instr);                    \
                                                                             \
  list_c_item->list_words = list_words;                                      \
                                                                             \
  if ((NULL == (tok = lexer_pop_token(lex))) || (strcmp(tok->str, ")")))     \
    FREE_ALL_RETURN(list_c_item, list_words, list_instr);                    \
                                                                             \
  if ((NULL == (list_instr = parse_compound_list(lex))))                     \
  {                                                                          \
    while ((NULL != (tok = lexer_pop_token(lex))) &&                         \
           (tok->type == TK_NEWLINE))                                        \
      ;                                                                      \
    return (list_c_item);                                                    \
  }                                                                          \
  list_c_item->list_instr = list_instr;

#define FREE_ALL_RETURN(List_c_item, List_words, List_instr)    \
  {                                                             \
    if (List_c_item)                                            \
      free_list_c_items(List_c_item);                           \
    if (List_words)                                             \
      free_list_words(List_words);                              \
    if (List_instr)                                             \
      free_list_instr(List_instr);                              \
  }

static s_list_words       *add_word(char                 *word,
                                    s_list_words         *list_words)
{
  s_list_words            *tmp = NULL;
  s_list_words            *new = NULL;

  new = mmalloc(sizeof (s_list_words));
  new->word = mstring_copy(word);
  new->next = NULL;

  if (NULL == list_words)
    return (new);

  tmp = list_words;

  while (tmp->next != NULL)
    tmp = tmp->next;

  tmp->next = new;

  return (list_words);
}

s_list_c_items            *parse_case_item(s_lexer      *lex)
{
  s_token                 *tok = NULL;
  s_list_c_items          *list_c_item = NULL;
  s_list_words            *list_words = NULL;
  s_list_instr            *list_instr = NULL;

  if (NULL == (list_c_item = mmalloc(sizeof (s_list_c_items))))
    return (NULL);
  list_c_item->list_words = NULL;
  list_c_item->list_instr = NULL;

  if (NULL == (tok = lexer_get_token(lex)))
    FREE_ALL_RETURN(list_c_item, list_words, list_instr);

  if (!strcmp(tok->str, "("))
    lexer_eat_token(lex);

  if ((NULL == (tok = lexer_get_token(lex))) || (!strcmp(tok->str, "esac")))
    FREE_ALL_RETURN(list_c_item, list_words, list_instr);

  list_words = add_word(tok->str, list_words);
  lexer_eat_token(lex);

  BLOCK_CHECK();

  return (list_c_item);
}
