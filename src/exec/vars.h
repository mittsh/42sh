#ifndef VARS_H_
# define VARS_H_

# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# include "../42sh/shell.h"
# include "../42sh/error.h"
# include "../mstring/mstring.h"
# include "../masso/masso.h"
# include "../dynamic_string/dynamic_string.h"

/**
** @brief               Registers a variable from affectation string.
** @param token         Input token string.
** @return              Returns true is token is an affectation.
*/
bool                    vars_register(char                      *token);

/**
** @brief               Expands variables.
** @param str           Input string.
** @return              Returns expanded string.
*/
char                    *vars_expand(char                       *str);

/**
** @brief               Expands all expansions types for all arguments.
** @param str           Input strings.
** @param error         Error repording pointer.
** @return              Returns expanded string.
*/
char                    **vars_expand_all(char                  *str[],
                                          int                   *error);

/**
** @brief               Registers environment variables.
** @param envp          Input environment.
** @return              void
*/
void                    vars_register_env(char                  **envp);

/**
** @brief               Expands quoting.
** @param str           Input string.
** @param mode          Expansion mode (0 : without quoting, 1 : simple
**                      quoting, 2 : double quoting)
** @return              Returns expanded string.
*/
char                    *vars_expand_quotes(char                *str,
                                            int                 *mode);

/**
** @brief               Expands tilde.
** @param str           Input string.
** @return              Returns expanded string.
*/
char                    *vars_expand_tilde(char                 *str);

/**
** @brief               Expands arithmetic expressions.
** @param str           Input strings.
** @param error         Error repording pointer.
** @return              Returns expanded string.
*/
char                    *vars_expand_arithmetic(char            *str,
                                                int             *error);

#endif /* !VARS_H_ */
