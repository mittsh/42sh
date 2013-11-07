#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

static inline s_list_words      *add_word(char                  *word,
                                          s_list_words          *list_words)
{
  s_list_words                  *tmp = NULL;
  s_list_words                  *new = NULL;

  new = mmalloc(sizeof (s_list_words));
  new->word = mstring_copy(word);
  new->next = NULL;

  if (NULL == list_words)
  {
    list_words = new;
    return (list_words);
  }

  tmp = list_words;
  while (tmp->next != NULL)
    tmp = tmp->next;

  tmp->next = new;
  return (list_words);
}

static inline s_list_words      *get_list_words(s_lexer         *lex)
{
  s_token                       *tok = NULL;
  s_list_words                  *list_words = NULL;

  while ((NULL != (tok = lexer_get_token(lex))) &&
         (0 != strcmp(tok->str, ";")) && (tok->type != TK_NEWLINE))
  {
      lexer_eat_token(lex);
      list_words = add_word(tok->str, list_words);
  }

  return (list_words);
}

#define FREE_LIST_WORDS_RETURN(List_words)                           \
  {                                                                  \
    if (List_words)                                                  \
      free_list_words(List_words);                                   \
    return (NULL);                                                   \
  }

s_instr                         *parse_rule_for(s_lexer         *lex)
{
  s_token                       *tok = NULL;
  char                          *var_name = NULL;
  s_list_words                  *list_words = NULL;
  s_list_instr                  *list_instr = NULL;

  if ((NULL == (tok = lexer_pop_token(lex))) || (strcmp(tok->str, "for")) ||
      (NULL == (tok = lexer_pop_token(lex))))
    return (NULL);

  var_name = mstring_copy(tok->str);

  tok = skip_newline(lex);

  if ((NULL != tok) && (0 == strcmp(tok->str, "in")))
  {
    lexer_eat_token(lex);

    list_words = get_list_words(lex);

    if ((NULL == (tok = lexer_pop_token(lex))) ||
        ((strcmp(tok->str, ";")) && (tok->type != TK_NEWLINE)))
      FREE_LIST_WORDS_RETURN(list_words);

    while ((NULL != (tok = lexer_get_token(lex))) && (tok->type == TK_NEWLINE))
      lexer_eat_token(lex);
  }

  if (NULL == (list_instr = parse_do_group(lex)))
    FREE_LIST_WORDS_RETURN(list_words);

  return (build_instr(AST_INSTR_FOR,
                      build_instr_for(var_name, list_words, list_instr)));
}
