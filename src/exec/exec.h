#ifndef EXEC_H_
# define EXEC_H_

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

# include "../parser/ast.h"
# include "../42sh/shell.h"
# include "../masso/masso.h"
# include "../42sh/error.h"

# include "list_dup.h"
# include "vars.h"

/**
** @brief               Executes a simple command.
** @param instr         Input instruction.
** @param list_dup      Input file descriptor duplication list.
** @param error         Pointer for error value.
** @return              Returns the return value of execution.
*/
int                     exec_instr_cmd(s_instr                  *instr,
                                       s_list_dup               *list_dup,
                                       int                      *error);

/**
** @brief               Executes an 'and' instruction from an 'and' node.
** @param instr         Input instruction.
** @param list_dup      Input file descriptor duplication list.
** @param error         Pointer for error value.
** @return              Returns the return value of execution.
*/
int                     exec_instr_and(s_instr                  *instr,
                                       s_list_dup               *list_dup,
                                       int                      *error);

/**
** @brief               Executes and 'or' instruction from an 'or' node.
** @param instr         Input instruction.
** @param list_dup      Input file descriptor duplication list.
** @param error         Pointer for error value.
** @return              Returns the return value of execution.
*/
int                     exec_instr_or(s_instr                   *instr,
                                      s_list_dup                *list_dup,
                                      int                       *error);

/**
** @brief               Executes a 'not' instruction from a 'not' node.
** @param instr         Input instruction.
** @param list_dup      Input file descriptor duplication list.
** @param error         Pointer for error value.
** @return              Returns the return value of execution.
*/
int                     exec_instr_not(s_instr                  *instr,
                                       s_list_dup               *list_dup,
                                       int                      *error);

/**
** @brief               Executes a pipe instruction, which is an instruction
**                      list, from a 'pipe' node.
** @param instr         Input instruction.
** @param list_dup      Input file descriptor duplication list.
** @param error         Pointer for error value.
** @return              Returns the return value of execution.
*/
int                     exec_instr_pipe(s_instr                 *instr,
                                        s_list_dup              *list_dup,
                                        int                     *error);

/**
** @brief               Executes an 'if' instruction from an 'if' node.
** @param instr         Input instruction.
** @param list_dup      Input file descriptor duplication list.
** @param error         Pointer for error value.
** @return              Returns the return value of execution.
*/
int                     exec_instr_if(s_instr                   *instr,
                                      s_list_dup                *list_dup,
                                      int                       *error);

/**
** @brief               Executes a 'while' instruction from a 'while' node.
** @param instr         Input instruction.
** @param list_dup      Input file descriptor duplication list.
** @param error         Pointer for error value.
** @return              Returns the return value of execution.
*/
int                     exec_instr_while(s_instr                *instr,
                                         s_list_dup             *list_dup,
                                         int                    *error);

/**
** @brief               Executes an 'until' instruction from an 'until' node.
** @param instr         Input instruction.
** @param list_dup      Input file descriptor duplication list.
** @param error         Pointer for error value.
** @return              Returns the return value of execution.
*/
int                     exec_instr_until(s_instr                *instr,
                                         s_list_dup             *list_dup,
                                         int                    *error);

/**
** @brief               Executes a list of instruction, sequentially.
** @param instr         Input instruction.
** @param list_dup      Input file descriptor duplication list.
** @param error         Pointer for error value.
** @return              Returns the return value of the last Executesd
**                      instruction.
*/
int                     exec_list_instr(s_list_instr            *list_instr,
                                        s_list_dup              *list_dup,
                                        int                     *error);

/**
** @brief               Executes a 'for' instruction from a 'for' node.
** @param instr         Input instruction.
** @param list_dup      Input file descriptor duplication list.
** @param error         Pointer for error value.
** @return              Returns the return value of execution.
*/
int                     exec_instr_for(s_instr                  *instr,
                                       s_list_dup               *list_dup,
                                       int                      *error);
/**
** @brief               Executes a 'case' instruction from a 'case' node.
** @param instr         Input instruction.
** @param list_dup      Input file descriptor duplication list.
** @param error         Pointer for error value.
** @return              Returns the return value of execution.
*/
int                     exec_instr_case(s_instr                 *instr,
                                        s_list_dup              *list_dup,
                                        int                     *error);

/**
** @brief               Declare a 'funcdec' instruction, stock the
**                      sub tree in the global variable @a g_shell->func
** @param instr         Input instruction.
** @param list_dup      Input file descriptor duplication list.
** @param error         Pointer for error value.
** @return              Returns the return value of execution.
*/
int                     exec_instr_func(s_instr                 *instr,
                                        s_list_dup              *list_dup,
                                        int                     *error);

/**
** @brief               Executes a redirection node, sets all redirections,
**                      opens file descriptor or file and close then after.
** @param instr         Input instruction.
** @param list_dup      Input file descriptor duplication list.
** @param error         Pointer for error value.
** @return              Returns the return value of execution.
*/
int                     exec_instr_redir(s_instr                *instr,
                                         s_list_dup             *list_dup,
                                         int                    *error);

/**
** @brief               Executes an instruction bracket command.
** @param instr         Input instruction.
** @param list_dup      Input file descriptor duplication list.
** @param error         Pointer for error value.
** @return              Returns the return value of execution.
*/
int                     exec_instr_brack(s_instr                *instr,
                                         s_list_dup             *list_dup,
                                         int                    *error);

/**
** @brief               Executes an instruction, depending from its type.
**                      It only redirects to another function.
** @param instr         Input instruction.
** @param list_dup      Input file descriptor duplication list.
** @param[out] error    Is will be egal to:
**                      - ERROR_NONE
**                      - ERROR_EVALEXPR
** @return              Returns the return value of execution.
*/
int                     exec_instr(s_instr                      *instr,
                                   s_list_dup                   *list_dup,
                                   int                          *error);

/**
** @brief               Executes a function declaratio  node.
** @param argv          Input arguments values.
** @param instr         Input instruction.
** @param list_dup      Input file descriptor duplication list.
*/
int                     exec_func(char                          **argv,
                                  s_list_dup                    *list_dup,
                                  int                           *error);

/**
** @brief               File descriptor list.
** @param fd            Current file descriptor.
** @param next          Next item.
** @param list_dup      Input file descriptor duplication list.
*/
typedef struct          fd_list
{
    int                 fd;
    struct fd_list      *next;
    s_list_dup          *list_dup;
}                       s_fd_list;

/*
** This include is here due do interdependance of exec.h and builtin.h
** Please do not move it.
*/
# include "../builtin/builtin.h"

#endif /* !EXEC_H_ */
