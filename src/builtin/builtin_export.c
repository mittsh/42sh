#include "builtin.h"

/**
** @brief               Registers an environment variable.
** @param str           Input affectation string.
** @param display_output Is true when output displaying is activated.
** @param builtin_fd    IOs streams.
** @return              void
*/
static void             builtin_export_register(char            *str,
                                                bool            display_output,
                                                s_builtin_fd    *builtin_fd)
{
  char                  *name = NULL;
  char                  *value = NULL;
  char                  *begin = str;

  for (; *str != '\0'; str++)
    if (*str == '=')
    {
      name = mstring_fromflags(begin, str);
      begin = str + 1;
    }

  if (name != NULL)
  {
    value = mstring_fromflags(begin, str);
    masso_set(g_shell->vars, name, value);
  }
  else
  {
    name = mstring_fromflags(begin, str);
    value = masso_get(g_shell->vars, name);
    if (value == NULL)
      value = "";
  }

  setenv(name, value, 1);

  if (display_output == true)
    fprintf(builtin_fd->fout, "%s=%s\n", name, value);

  mfree(name);
}

int                     builtin_export(char                     **argv,
                                       s_builtin_fd             *builtin_fd)
{
  bool                  display_output = false;

  if (argv == NULL || *argv == NULL)
    return (1);

  argv++;

  if (*argv != NULL && strcmp(*argv, "-p") == 0)
  {
    display_output = true;
    argv++;
  }

  if (*argv == NULL)
    return (1);

  builtin_export_register(*argv, display_output, builtin_fd);

  return (0);
}
