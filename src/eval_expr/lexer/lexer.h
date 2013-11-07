#ifndef LEXER_H_
# define LEXER_H_

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>

# include "../../mmalloc/mmalloc.h"

/**
** @brief               Token types.
** @param TK_NEWLINE    New line (i.e. \n).
** @param TK_EOINST     End of instruction (i.e. ;).
** @param TK_OTHER      Other tokens.
*/
typedef enum            token_type
{
  TK_PAREN_BEGIN,
  TK_PAREN_END,
  TK_OPE_HIGH,
  TK_OPE_LOW,
  TK_OPE_ONE,
  TK_OPE_POWER,
  TK_NUM,
  TK_OTHER
}                       e_token_type;

/**
** @brief               Represents a quoted string.
*/
typedef enum            eelex_quoting
{
  QT_SIMPLE = 1,
  QT_DOUBLE = 2,
  QT_BACK = 3
}                       e_eelex_quoting;

/**
** @brief               Represents a token.
** @param str           String token.
** @param type          Type of token.
** @param line          Begin line number.
** @param col           Begin column number.
*/
typedef struct          token
{
    char                *str;
    e_token_type        type;
    unsigned int        line;
    unsigned int        col;
    bool                is_after_space;
}                       s_token;

/**
** @brief               Represents a token list.
** @param token         String token.
** @param next          Next token list item.
**                      NULL when item is the last one.
*/
typedef struct          token_list
{
    s_token             *token;
    struct token_list   *next;
}                       s_token_list;

/**
** @brief               Represents a lexer.
** @param input_str     Input data string.
** @param token_list    List of recognised tokens.
** @param current_token Current matching token.
** @param last_token    Last token list item (used when adding on tail).
*/
typedef struct          eelex
{
    char                *input_str;
    struct token_list   *token_list;
    struct token_list   *current_token;
    struct token_list   *last_token;
    bool                is_last_matched_space;
}                       s_eelex;

/**
** @brief               Initialises a new parser.
** @param               void
** @return              Returns a lexer structure pointer.
*/
s_eelex                 *eelex_init(void);

/**
** @brief               Loads a string in the lexer.
**                      A copy of str is done.
** @param lexer         Target lexer.
** @param str           Input string.
** @return              Returns 1 in case of success, 0 if fails.
*/
int                     eelex_load_str(s_eelex          *eelex,
                                       char             *str);

/**
** @brief               Processes the lexing.
** @param eelex         Target eelex.
** @return              Returns 1 if no error appends, 0 else.
*/
int                     eelex_action(s_eelex            *eelex);

/**
** @brief               Gets the current token list item without eating it.
** @param eelex         Input eelex.
** @return              Returns the current token, NULL if token list is
**                      empty.
*/
s_token                 *eelex_get_token(s_eelex        *eelex);

/**
** @brief               Gets the next token list item without eating it.
** @param eelex         Input eelex.
** @return              Returns the next token, NULL if token list is
**                      empty.
*/
s_token                 *eelex_next_token(s_eelex       *eelex);

/**
** @brief               Eats the current token, if list is not empty.
** @param eelex         Target eelex.
** @return              void
*/
void                    eelex_eat_token(s_eelex         *eelex);

/**
** @brief               Get the current token list item and eats it.
**                      This function is an alias to get and eat token.
**                      inline function
** @param eelex         Input eelex.
** @return              Returns the current token, NULL if token list is empty.
*/
s_token                 *eelex_pop_token(s_eelex        *eelex);

/**
** @brief               Matches a quoted token such as "hello \"world\""
** @param str           Input string to match.
** @return              Token string.
*/
char                    *eelex_match_quotes(char        *str);

/**
** @brief               E_Lex debuger
** @param eelex         Input eelex
** @return              void
*/
void                    eelex_debug(s_eelex             *eelex);

/**
** @brief               Frees all memory allocated for lexing.
** @param eelex         Target eelex.
** @return              void
*/
void                    eelex_free(s_eelex              *eelex);

#endif /* !LEXER_H_ */
