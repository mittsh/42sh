#include "builtin.h"

int                     builtin_vars(s_builtin_fd               *builtin_fd)
{
  s_masso_data          *data = NULL;
  int                   i = 0;
  char                  *key = NULL;
  char                  *value = NULL;

  for (i = 0; i < g_shell->vars->size; i++)
  {
    data = &(g_shell->vars->array[i]);
    key = data->key;
    value = data->value;
    fprintf(builtin_fd->fout, "%s=%s\n", key, value);
  }

  return (0);
}
