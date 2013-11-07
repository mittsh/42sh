#ifndef PRINT_AST_H_
# define PRINT_AST_H_

# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../parser/ast.h"
# include "../dynamic_string/dynamic_string.h"

/**
** @brief               AST printer style for logic operators.
*/
# define AST_STYLE_LOGIC                                        \
  "style=filled color=\"1.0 .3 .7\" fontname=\"Helvetica\" fontsize=12 "

/**
** @brief               AST printer style for pipe operator.
*/
# define AST_STYLE_PIPE                                         \
  "style=filled color=\".7 1.0 1.0\" fontname=\"Helvetica\"  fontsize=12 "

/**
** @brief               AST printer style for subpatterns such as brackets
**                      or parenthesis.
*/
# define AST_STYLE_SUB                                          \
  "style=filled color=\".3 1.0 .7\" fontname=\"Helvetica\"  fontsize=12 "

/**
** @brief               AST printer style for conditionnals instructions such
**                      as if, while, until, for...
*/
# define AST_STYLE_COND                                         \
  "style=filled color=\".7 .3 1.0\" fontname=\"Helvetica\"  fontsize=12 "

/**
** @brief               AST printer style for simple commands.
*/
# define AST_STYLE_CMD                                          \
  "shape=box fontname=\"Helvetica\"  fontsize=12 "

/**
** @brief               AST printer style for instructions lists.
*/
# define AST_STYLE_INSTRLIST                                    \
  "style=filled,dotted shape=box "                              \
  "fontname=\"Helvetica\" fontsize=9"

/**
** @brief               AST printer style for redirections.
*/
# define AST_STYLE_REDIRECTION                                  \
  "style=filled,dotted "                                        \
  "fontname=\"Helvetica\" fontsize=9"

/**
** @brief               AST printer style for functions declarations.
*/
# define AST_STYLE_FUNCTION                                     \
  "style=filled,dotted "                                        \
  "fontname=\"Helvetica\" fontsize=9"

/**
** @brief               This function creates a png file corresponding to ast
**                      in the file @a filename.
**                      It also created 'ast.dot' file.
** @param[in] filename	Path to png file.
** @param[in] ast	ast to print.
** @return		1 if OK, 0 otherwise
*/
int                     print_ast(char                  *filename,
                                  t_ast                 *ast);

/**
** @brief               Prints an instruction depending to its type.
** @param instr         Input instruction.
** @param fd            Output file descriptor.
** @return              void
*/
void                    print_instr(s_instr                     *instr,
                                    FILE                        *fd);

/**
** @brief               Prints a simple instruction.
** @param instr         Input instruction.
** @param fd            Output file descriptor.
** @return              void
*/
void                    print_instr_cmd(s_instr                 *instr,
                                        FILE                    *fd);

/**
** @brief               Prints an 'and' instruction.
** @param instr         Input instruction.
** @param fd            Output file descriptor.
** @return              void
*/
void                    print_instr_and(s_instr                 *instr,
                                        FILE                    *fd);

/**
** @brief               Prints an 'or' instruction.
** @param instr         Input instruction.
** @param fd            Output file descriptor.
** @return              void
*/
void                    print_instr_or(s_instr                  *instr,
                                       FILE                     *fd);

/**
** @brief               Prints a 'pipe' instruction.
** @param instr         Input instruction.
** @param fd            Output file descriptor.
** @return              void
*/
void                    print_instr_pipe(s_instr                *instr,
                                         FILE                   *fd);

/**
** @brief               Prints a 'not' instruction.
** @param instr         Input instruction.
** @param fd            Output file descriptor.
** @return              void
*/
void                    print_instr_not(s_instr                 *instr,
                                        FILE                    *fd);

/**
** @brief               Prints a bracket (i.e. {}) instruction.
** @param instr         Input instruction.
** @param fd            Output file descriptor.
** @return              void
*/
void                    print_instr_brack(s_instr               *instr,
                                          FILE                  *fd);

/**
** @brief               Prints a parenthesis instruction.
** @param instr         Input instruction.
** @param fd            Output file descriptor.
** @return              void
*/
void                    print_instr_paren(s_instr               *instr,
                                          FILE                  *fd);

/**
** @brief               Prints an instruction list.
** @param instr         Input instruction.
** @param fd            Output file descriptor.
** @return              void
*/
void                    print_list_instr(s_list_instr           *list_instr,
                                         FILE                   *fd);

/**
** @brief               Prints an 'if' instruction.
** @param instr         Input instruction.
** @param fd            Output file descriptor.
** @return              void
*/
void                    print_instr_if(s_instr                  *instr,
                                       FILE                     *fd);

/**
** @brief               Prints a 'while' instruction.
** @param instr         Input instruction.
** @param fd            Output file descriptor.
** @return              void
*/
void                    print_instr_while(s_instr               *instr,
                                          FILE                  *fd);

/**
** @brief               Prints an 'until' instruction.
** @param instr         Input instruction.
** @param fd            Output file descriptor.
** @return              void
*/
void                    print_instr_until(s_instr               *instr,
                                          FILE                  *fd);

/**
** @brief               Prints a 'for' instruction.
** @param instr         Input instruction.
** @param fd            Output file descriptor.
** @return              void
*/
void                    print_instr_for(s_instr                 *instr,
                                        FILE                    *fd);

/**
** @brief               Prints a 'case' instruction.
** @param instr         Input instruction.
** @param fd            Output file descriptor.
** @return              void
*/
void                    print_instr_case(s_instr                *instr,
                                         FILE                   *fd);

/**
** @brief               Prints a redirection instruction.
** @param instr         Input instruction.
** @param fd            Output file descriptor.
** @return              void
*/
void                    print_instr_redir(s_instr               *instr,
                                          FILE                  *fd);

/**
** @brief               Prints an function declaration instruction.
** @param instr         Input instruction.
** @param fd            Output file descriptor.
** @return              void
*/
void                    print_instr_func(s_instr                *instr,
                                         FILE                   *fd);

/**
** @brief               Gets the pointer over another one.
** @param ptr           Input pointer.
** @return              Returns this pointer.
*/
void                    *getptr(void                            *ptr);

#endif /* !PRINT_AST_H_ */
