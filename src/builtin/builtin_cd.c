#include <unistd.h>
#include <stdlib.h>
#include "builtin.h"

int                     builtin_cd(char                         **argv,
                                   s_builtin_fd                 *builtin_fd)
{
  char                  str[1024];
  char                  *target = NULL;
  char                  *home = NULL;

  if ((home = getenv("HOME")) == NULL)
    home = "/";

  if ((target = argv[1]) == NULL)
    target = home;

  getcwd(str, 1024);
  setenv("OLDPWD", str, 1);
  masso_set(g_shell->vars, "OLDPWD", mstring_copy(str));

  if (chdir(target) == 0)
  {
    getcwd(str, 1024);
    setenv("PWD", str, 1);
    masso_set(g_shell->vars, "PWD", mstring_copy(str));
    return (0);
  }
	else
  {
    fprintf(builtin_fd->ferr, "%s: No such file or directory\n", argv[1]);
    return (1);
  }
}
