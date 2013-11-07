#ifndef LEXER_H_
# define LEXER_H_

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>

# include "../dynamic_string/dynamic_string.h"

/**
** @brief               Token types.
** @param TK_NEWLINE    New line (i.e. \n).
** @param TK_EOINST     End of instruction (i.e. ;).
** @param TK_OTHER      Other tokens.
*/
typedef enum            token_type
{
  TK_NEWLINE,
  TK_EOINST,
  TK_OTHER
}                       e_token_type;

/**
** @brief               Quoting types.
** @param QT_SIMPLE     Simple quoting.
** @param QT_DOUBLE     Double quoting.
** @param QT_BACK       TODO.
*/
typedef enum            lexer_quoting
{
  QT_SIMPLE = 1,
  QT_DOUBLE = 2,
  QT_BACK = 3
}                       e_lexer_quoting;

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
    char                *pos;
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
typedef struct          lexer
{
    char                *input_str;
    struct token_list   *token_list;
    struct token_list   *current_token;
    struct token_list   *last_token;
    bool                is_last_matched_space;
}                       s_lexer;

/**
** @brief               Initialises a new parser.
** @param               void
** @return              Returns a lexer structure pointer.
*/
s_lexer                 *lexer_init(void);

/**
** @brief               Loads a string in the lexer.
**                      A copy of str is done.
** @param lexer         Target lexer.
** @param str           Input string.
** @return              Returns 1 in case of success, 0 if fails.
*/
int                     lexer_load_str(s_lexer          *lexer,
                                       char             *str);

/**
** @brief               Processes the lexing.
** @param lexer         Target lexer.
** @return              Returns 1 if no error appends, 0 else.
*/
int                     lexer_action(s_lexer            *lexer);

/**
** @brief               Gets the current token list item without eating it.
** @param lexer         Input lexer.
** @return              Returns the current token, NULL if token list is
**                      empty.
*/
s_token                 *lexer_get_token(s_lexer        *lexer);

/**
** @brief               Gets the next token list item without eating it.
** @param lexer         Input lexer.
** @return              Returns the next token, NULL if token list is
**                      empty.
*/
s_token                 *lexer_next_token(s_lexer       *lexer);

/**
** @brief               Eats the current token, if list is not empty.
** @param lexer         Target lexer.
** @return              void
*/
void                    lexer_eat_token(s_lexer         *lexer);

/**
** @brief               Get the current token list item and eats it.
**                      This function is an alias to get and eat token.
**                      inline function
** @param lexer         Input lexer.
** @return              Returns the current token, NULL if token list is empty.
*/
s_token                 *lexer_pop_token(s_lexer        *lexer);

/**
** @brief               Matches a quoted token such as "hello \"world\""
** @param str           Input string to match.
** @return              End of token string.
*/
char                    *lexer_match_quotes(char        *str);

/**
** @brief               Matches an arithmetic expression such as $((...))
** @param str           Input string to match.
** @return              End of token string.
*/
char                    *lexer_match_arithmetic(char            *str);

/**
** @brief               Matches a comment token.
** @param str           Input string to match.
** @return              End of token string.
*/
char                    *lexer_match_comment(char               *str);

/**
** @brief               Matches a complex variable name such as ${VARNAME}
** @param str           Input string to match.
** @return              End of token string.
*/
char                    *lexer_match_vars(char                  *str);

/**
** @brief               Lexer debuger
** @param lexer         Input lexer
** @return              void
*/
void                    lexer_debug(s_lexer             *lexer);

/**
** @brief               Frees all memory allocated for lexing.
** @param lexer         Target lexer.
** @return              void
*/
void                    lexer_free(s_lexer              *lexer);

#endif /* !LEXER_H_ */
