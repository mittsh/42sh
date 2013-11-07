#ifndef EVAL_EXPR_H_
# define EVAL_EXPR_H_

# include "lexer/lexer.h"
# include "../mmalloc/mmalloc.h"

/**
** @file                eval_expr.h
** @brief               This file included an evaluation
**                      function of expression.
**                      The grammar parser is :
**                      - input      ::=  [ope_or]+
**                      - ope_or     ::=  ope_and (['||'] ope_and)*
**                      - ope_and    ::=  ope_or_bit (['&&'] ope_or_bit)*
**                      - ope_or_bit ::=  ope_and_bit (['|' '^'] ope_and_bit)*
**                      - ope_and_bit::=  ope_low (['&'] ope_low)*
**                      - ope_low    ::=  ope_high ([OPE_LOW] ope_high)*
**                      - ope_high   ::=  ope_power ([OPE_HIGH] ope_power)*
**                      - ope_power  ::=  ope_one ([OPE_POWER] ope_one)*
**                      - ope_one    ::=  (OPE_ONE)* paren
**                      - paren      ::=  '(' [ope_or] ')' | NUM
*/
typedef enum            type_expr
{
  EXPR_TYPE_BIN,
  EXPR_TYPE_ONE,
  EXPR_TYPE_NUM
}                       e_type_expr;

/**
** @brief               Arithmetic evaluation abstract tree, seen as a
**                      binary tree.
** @param type          Node type.
** @param value         Node value/label.
** @param son_left      Left son.
** @param son_right     Right son.
*/
typedef struct          tree_expr
{
  e_type_expr           type;
  char                  *value;
  struct tree_expr      *son_left;
  struct tree_expr      *son_right;
}                       s_tree_expr;

/**
** @brief               Evaluates the arithmetic expression
** @param[in] str       String that represents an arithmetic expression
** @param[out] error    Int that represents an error.
**                      - @a error == EXPR_ERROR_NONE if no error
**                      - @a error == EXPR_ERROR if error
** @return              Returns the result of the expression @a str
*/
char                    *eval_expr(char                 *str,
                                   int                  *error);

/*
** ***********************************************
** **                                           **
** **         **Function of parsing**           **
** **                                           **
** ***********************************************
*/

/**
** @brief               Parses an input expression.
** @param lex           Input lexer.
** @return              Returns evaluation abstract tree.
*/
s_tree_expr             *parse_input_expr(s_eelex       *lex);

/**
** @brief               Parses an or node.
** @param lex           Input lexer.
** @return              Returns evaluation abstract tree.
*/
s_tree_expr             *parse_ope_or_expr(s_eelex      *lex);

/**
** @brief               Parses an and node.
** @param lex           Input lexer.
** @return              Returns evaluation abstract tree.
*/
s_tree_expr             *parse_ope_and_expr(s_eelex     *lex);

/**
** @brief               Parses an or bit comparaison node.
** @param lex           Input lexer.
** @return              Returns evaluation abstract tree.
*/
s_tree_expr             *parse_ope_or_bit_expr(s_eelex  *lex);

/**
** @brief               Parses an and bit comparaison node.
** @param lex           Input lexer.
** @return              Returns evaluation abstract tree.
*/
s_tree_expr             *parse_ope_and_bit_expr(s_eelex *lex);

/**
** @brief               Parses a low priority operator node.
** @param lex           Input lexer.
** @return              Returns evaluation abstract tree.
*/
s_tree_expr             *parse_ope_low_expr(s_eelex     *lex);

/**
** @brief               Parses an high priority operator node.
** @param lex           Input lexer.
** @return              Returns evaluation abstract tree.
*/
s_tree_expr             *parse_ope_high_expr(s_eelex    *lex);

/**
** @brief               Parses a power node.
** @param lex           Input lexer.
** @return              Returns evaluation abstract tree.
*/
s_tree_expr             *parse_ope_power_expr(s_eelex   *lex);

/**
** @brief               Parses an input expression.
** @param lex           Input lexer.
** @return              Returns evaluation abstract tree.
*/
s_tree_expr             *parse_ope_one_expr(s_eelex     *lex);

/**
** @brief               Parses a parenthesis node.
** @param lex           Input lexer.
** @return              Returns evaluation abstract tree.
*/
s_tree_expr             *parse_paren_expr(s_eelex       *lex);

/*
** ***********************************************
** **                                           **
** **         **Build of tree_expr**            **
** **                                           **
** ***********************************************
*/

/**
** @brief               Builts expression tree.
** @param type          Expression tree type.
** @param value         Node label.
** @param s1            Left son.
** @param s2            Right son.
** @return              Returns expression node.
*/
s_tree_expr             *build_tree_expr(e_type_expr    type,
                                         char           *value,
                                         s_tree_expr    *sl,
                                         s_tree_expr    *sr);

/**
** @brief               Frees a node.
** @param tree          Input tree node.
** @return              void
*/
void                    free_tree_expr(s_tree_expr      *tree);

#endif /* !EVAL_EXPR_H_ */
