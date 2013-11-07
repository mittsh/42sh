/**
** @author maarek_j
** @date Wed Nov 10 14:44:00 2010
*/
#include <stdbool.h>

#include "../ast.h"
#include "../parser.h"
#include "../../lexer/lexer.h"

#define GTIRDR get_instr_redir
#define GTICMD get_instr_cmd
#define BLDLSTR build_instr_cmd

/**
** @brief                       Function decide if the string is a valid Name.
** @param[in] str               str to decide.
** @return                      True if the str is a valid name, false
**                              otherwise
*/
static inline bool              valid_name(char                 *str)
{
  if ((str[0] >= '0') && (str[0] <= '9'))
    return (false);

  for (int i = 1; (str[i] != '\0') && (str[i] != '='); i++)
  {
      if (!((str[i] == '_') ||
          ((str[i] >= 'A') && (str[i] <= 'z')) ||
            ((str[i] >= '0') && (str[i] <= '9'))))
        return (false);
  }

  return (true);
}

/**
** @brief                       Function decide if the token is a WORD
**                              or an ASSIGNMENT_WORD.
** @param[in] tok               Token to decide.
** @return                      1 if @a tok is word, 2 if @a tok is
**                              assigment_word,
**                              0 otherwise.
*/
static inline int               word_or_assignment(s_token      *tok)
{
  if (tok)
  {
    if ((TK_EOINST == tok->type) || (true == is_keyword(tok)))
      return (0);

    if (false == valid_name(tok->str))
      return (1);

    if (NULL == strchr(tok->str, '='))
      return (1);
    else
      return (2);
  }
  else
    return (0);
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

/**
** @brief                       Add a list of word in the list of word @a list
** @param list                  List to add a word , If @a list == NULL,
**                              the return is @a word.
** @param redir                 The word to add the @a list.
** @return                      A list of words.
*/
static inline s_list_words      *add_word_in_list(s_list_words  *list,
                                                  s_list_words  *word)
{
  s_list_words                  *aux = NULL;

  if (list == NULL)
    return (word);

  aux = list;
  while (aux->next != NULL)
    aux = aux->next;

  aux->next = word;

  return (list);
}

static inline s_instr_redir     *get_instr_redir(void           *ptr)
{
  return (ptr);
}

static inline s_instr_cmd       *get_instr_cmd(void             *ptr)
{
  return (ptr);
}

#define FREE_AND_RETURN(List_redir, List_words)         \
  {                                                     \
    if (List_redir)                                     \
      free_list_redir(List_redir);                      \
    if (List_words)                                     \
      free_list_words(List_words);                      \
    return (NULL);                                      \
  }

#define FREE_AUX(Instr_aux)                         \
  if (Instr_aux)                                    \
  {                                                 \
      if (Instr_aux->instr)                         \
        mfree(Instr_aux->instr);                    \
      mfree(Instr_aux);                             \
  }

s_instr                         *parse_simple_command(s_lexer   *lex)
{
  s_instr                       *instr_aux = NULL;
  s_list_redir                  *list_redir = NULL;
  s_list_words                  *list_words = NULL;

  while (lexer_get_token(lex) != NULL &&
         0 != word_or_assignment(lexer_get_token(lex)))
  {
      if (NULL == (instr_aux = parse_prefix(lex)))
        FREE_AND_RETURN(list_redir, list_words);

      if (AST_INSTR_REDIR == instr_aux->type)
        list_redir = add_redir_in_list(list_redir,
                                       (GTIRDR(instr_aux->instr))->list_redir);
      if (AST_INSTR_CMD == instr_aux->type)
        list_words = add_word_in_list(list_words,
                                      (GTICMD(instr_aux->instr))->list_words);
      FREE_AUX(instr_aux);
  }

  if ((NULL == list_redir) && (NULL == list_words))
    FREE_AND_RETURN(list_redir, list_words);

  if (list_redir == NULL)
    return (build_instr(AST_INSTR_CMD, build_instr_cmd(list_words)));
  else
    return (build_instr(AST_INSTR_REDIR,
                        build_instr_redir(build_instr(AST_INSTR_CMD,
                                                      BLDLSTR(list_words)),
                                          list_redir)));
}
