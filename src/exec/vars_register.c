#include "vars.h"

bool                    vars_register(char                      *token)
{
  char                  *name = NULL;
  char                  *value = NULL;
  char                  *str = token;

  for (; *str != '\0'; str++)
    if (*str == '=')
    {
      name = mstring_fromflags(token, str);
      value = mstring_copy(str + 1);
      masso_set(g_shell->vars, name, value);
      if (getenv(name) != NULL)
        setenv(name, value, 1);
      mfree(name);
      return (true);
    }

  return (false);
}
