#ifndef MAIN_H_
# define MAIN_H_

# include <stdlib.h>
# include <unistd.h>
# include <getopt.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <fcntl.h>

# include "../readline/readline.h"
# include "../builtin/builtin.h"
# include "../options_parser/options_parser.h"
# include "../parser/ast.h"
# include "../parser/parser.h"
# include "../exec/exec.h"
# include "../print_ast/print_ast.h"
# include "../masso/masso.h"

/**
** @brief               Represents Shell's main options
** @param version       1 if printing version mode.
** @param printast      1 if AST printer is activated.
** @param command_input 1 if command input mode.
** @param command_line  Command line input string.
** @param norc          1 if norc option is activated.
*/
typedef struct          main_options
{
  int                   version;
  int                   printast;
  int                   command_input;
  char                  *command_line;
  int                   norc;
}                       s_main_options;

#endif /* !MAIN_H_ */
