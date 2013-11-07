/**
** @file		parse_ope_one_expr.c
** @brief		ope_one	::=  (OPE_ONE)* paren
** @author		maarek_j
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "eval_expr.h"
#include "lexer/lexer.h"

/**
** @brief               Checks if an operator is a unary one.
** @param tok           Input token.
** @return              Returns true in case of success.
*/
static inline bool	is_ope_one(s_token		*tok)
{
  if (!tok)
    return (false);

  if (TK_OPE_ONE == tok->type)
    return (true);
  if ((0 == strcmp(tok->str, "+")) || (0 == strcmp(tok->str, "-")))
    return (true);
  else
    return (false);
}

/**
** @brief               Represents execution stack.
** @param element       Stack element.
** @param next          Stack next element.
*/
typedef struct		pile
{
  char			*element;
  struct pile		*next;
}			s_pile;

/**
** @brief               Pushes a new element on the stack.
** @param pile          Input stack.
** @param element       Input stack.
** @return              Returns new stack with the new element.
*/
static inline s_pile	*push(s_pile			*pile,
			      char			*element)
{
  s_pile		*aux = NULL;

  aux = mmalloc(sizeof (s_pile));
  aux->element = element;

  if (NULL == pile)
    aux->next = NULL;
  else
    aux->next = pile;

  return (aux);
}

/**
** @brief               Removes last stack element.
** @param pile          Input stack
** @return              Returns new stack with out this element.
*/
static inline char	*pop(s_pile			**pile)
{
  char			*res;
  s_pile		*aux;

  if (NULL == *pile)
    return (NULL);

  res = (*pile)->element;
  aux = *pile;
  *pile = (*pile)->next;
  mfree(aux);

  return (res);
}

s_tree_expr		*parse_ope_one_expr(s_eelex	*lex)
{
  s_token		*tok = NULL;
  s_tree_expr		*res = NULL;
  s_tree_expr		*aux = NULL;
  s_tree_expr		*aux2 = NULL;
  s_pile		*pile = NULL;

  if (NULL == (tok = eelex_get_token(lex)))
    return (NULL);

  if (false == is_ope_one(tok))
    return (parse_paren_expr(lex));

  while (NULL != (tok = eelex_get_token(lex)) &&
	 (true == is_ope_one(tok)))
  {
      pile = push(pile, tok->str);
      eelex_eat_token(lex);
  }
  if (pile)
    aux = build_tree_expr(EXPR_TYPE_ONE, mstring_copy(pop(&pile)), NULL, NULL);
  res = aux;
  while (NULL != pile)
    res = build_tree_expr(EXPR_TYPE_ONE, mstring_copy(pop(&pile)), res, NULL);

  if (NULL == (aux2 = parse_paren_expr(lex)))
    return (NULL);
  aux->son_left = aux2;

  return (res);
}
