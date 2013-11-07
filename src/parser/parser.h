#ifndef PARSER_H_
# define PARSER_H_

/**
** @file                parser.h
** @brief               This file contains the functions about parser.
** @author              maarek_j
*/

# include <stdbool.h>
# include "../lexer/lexer.h"
# include "ast.h"
# include "../mmalloc/mmalloc.h"

# define ENOTFOUND -100

/**
** @brief               Parses a string.
** @param lexer         The lexer
** @return              An ast if OK, else return NULL if error.
*/
t_ast                   *parse_input(s_lexer                    *lex);

/**
** @brief               list: and_or ((';'|'&') and_or)* [';'|'&']
** @param lex           The lexer.
*/
s_list_instr            *parse_list(s_lexer                     *lex);

/**
** @brief               and_or: pipeline (('&&'|'||') ('\n')* pipeline)*
** @param lex           The lexer.
*/
s_instr                 *parse_and_or(s_lexer                   *lex);

/**
** @brief               pipeline: ['!'] command ('|' ('\n')* command)*
** @param lex           The lexer.
*/
s_instr                 *parse_pipeline(s_lexer                 *lex);

/**
** @brief               command:        simple_command
**                                      | shell_command (redirection)*
**                                      | funcdec (redirection)*
** @param lex           The lexer.
*/
s_instr                 *parse_command(s_lexer                  *lex);

/**
** @brief               simple_command: (prefix)+
**                                      | (prefix)* (element)+
** @param lex           The lexer.
*/
s_instr                 *parse_simple_command(s_lexer           *lex);

/**
** @brief               shell_command:  '{' compound_list '}'
**                                      | '(' compound_list ')'
**                                      | rule_for | rule_while | rule_until
**                                      | rule_case | rule_if
** @param lex           The lexer.
*/
s_instr                 *parse_shell_command(s_lexer            *lex);

/**
** @brief               funcdec:
**                      ['function'] WORD '(' ')' ('\n')* shell_command
** @param lex           The lexer.
*/
s_instr                 *parse_funcdec(s_lexer                  *lex);

/**
** @brief               redirection:
**                                      | [IONUMBER] '>' WORD
**                                      | [IONUMBER] '<' WORD
**                                      | [IONUMBER] '>>' WORD
**                                      | [IONUMBER] '<<' HEREDOC
**                                      | [IONUMBER] '<<-' HEREDOC
**                                      | [IONUMBER] '>&' WORD
**                                      | [IONUMBER] '<&' WORD
**                                      | [IONUMBER] '>|' WORD
**                                      | [IONUMBER] '<>' WORD
** @param lex           The lexer.
*/
s_list_redir            *parse_redirection(s_lexer              *lex);

/**
** @brief               prefix: ASSIGMENT_WORD | redirection
** @param lex           The lexer.
*/
s_instr                 *parse_prefix(s_lexer                   *lex);

/**
** @brief               element:        WORD | redirection
** @param lex           The lexer.
*/
s_instr                 *parse_element(s_lexer                  *lex);

/**
** @brief               compound_list: ('\n')* and_or ((';'|'&'|'\n')
**                                 ('\n')* and_or)* [('&'|';'|'\n') ('\n')*]
** @param lex           The lexer.
*/
s_list_instr            *parse_compound_list(s_lexer            *lex);

/**
** @brief               rule_for: 'for' WORD ('\n')*
**                              ['in' (WORD)* (';'|'\n') ('\n')*] do_group
** @param lex           The lexer.
*/
s_instr                 *parse_rule_for(s_lexer                 *lex);

/**
** @brief               rule_while: 'while' compound_list do_group
** @param lex           The lexer.
*/
s_instr                 *parse_rule_while(s_lexer               *lex);

/**
** @brief               rule_until: 'until' compound_list do_group
** @param lex           The lexer.
*/
s_instr                 *parse_rule_until(s_lexer               *lex);

/**
** @brief               rule_case: 'case' WORD ('\n')* 'in' ('\n')*
**                                      [case_clause] 'esac'
** @param lex           The lexer.
*/
s_instr                 *parse_rule_case(s_lexer                *lex);

/**
** @brief               rule_if:        'if' compound_list 'then'
**                                      compound_list [else_clause] 'fi'
** @param lex           The lexer.
*/
s_instr                 *parse_rule_if(s_lexer                  *lex);

/**
** @brief               else_clause:    'else' compound_list
**                      | 'elif' compound_list 'then' compound_list
**                         [else_clause]
** @param lex           The lexer.
  */
s_instr                 *parse_else_clause(s_lexer              *lex);

/**
** @brief               do_group: 'do' compound_list 'done'
** @param lex           The lexer.
*/
s_list_instr            *parse_do_group(s_lexer                 *lex);

/**
** @brief               case_clause: case_item (';;' ('\n')* case_item)*
**                                      [;;] ('\n')*
** @param lex           The lexer.
*/
s_list_c_items          *parse_case_clause(s_lexer              *lex);

/**
** @brief               case_item: ['('] WORD ('|' WORD)* ')'
**                      ( ('\n')* | compound_list )
** @param lex           The lexer.
*/
s_list_c_items          *parse_case_item(s_lexer                *lex);

/**
** @brief                       Skip the newline token (TK_NEWLINE)
** @param lex           The lexer.
** @return                      Returns the token following a line break.
*/
s_token                 *skip_newline(s_lexer                   *lex);

/**
** @brief                       The function says if the tok is a keyword.
**                                      IF THEN ELSE FI FOR DO DONE {} () ...
** @param[in] tok       The token.
** @return                      True if the @a tok is a keyword.
*/
bool                    is_keyword(s_token                      *tok);

/**
** @brief                       The function says if the tok is a end keyword.
**                                      THEN ELSE FI DO DONE {} () ...
** @param[in] tok       The token.
** @return                      True if the @a tok is a end keyword.
*/
bool                    is_end_keyword(s_token                  *tok);

#endif /* !PARSER_H_ */
