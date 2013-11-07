#ifndef SHELL_H_
# define SHELL_H_

# include <sys/ioctl.h>
# include <termios.h>
# include <sys/types.h>
# include "../masso/masso.h"
# include "../builtin/history.h"
# include "../parser/ast.h"
# include "../mmalloc/mmalloc.h"
# include "../mstream/mstream.h"

/**
** @brief               Represents the shell and all it's allocations.
** @param vars          Variables array.
** @param env           Environment variables array.
** @param alias         Aliases array.
** @param func          Functions array.
** @param pwd           Current PWD (not frequently used, use variable $PWD)
** @param term_old      Old terminal state.
** @param term_mode     Current terminal state.
** @param queue_history History queue.
** @param lex           Shell's lexer.
** @param ast           Current abstract syntax tree.
** @param return_value  Shell's return value (used for exit builtin).
** @param mmalloc       Mmalloc library allocation table.
** @param mstream       Mstream library streams or file descriptors table.
*/
typedef struct          shell
{
    s_masso             *vars;
    s_masso             *env;
    s_masso             *alias;
    s_masso             *func;
    char                *pwd;
    struct termios      term_old;
    int                 term_mode;
    s_queue_history     *queue_history;
    void                *lex;
    t_ast               *ast;
    int                 return_value;
    s_mmalloc_mem       *mmalloc;
    s_mstream_mem       *mstream;
}                       s_shell;

/**
** @brief               Represents the 42SHell.
*/
extern s_shell          *g_shell;

/**
** @brief               Free all shell structures.
** @param shell         Input shell structure.
** @return              void
*/
void                    free_shell(s_shell              *shell);

#endif /* !SHELL_H_ */
