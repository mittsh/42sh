#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "builtin.h"
#include "../masso/masso.h"
#include "../42sh/shell.h"

/**
** @brief               Gets arguments number.
** @param argv          Input arguments values list.
** @return              Returns arguments number.
*/
static inline int       get_argc(char                           **argv)
{
  int                   i;

  for (i = 0; argv[i] != NULL; i++)
    ;
  return (i);
}

/**
** @brief               Removes an alias.
** @param key           Alias name/key.
** @param builtin_fd    IOs streams.
** @return              Returns 0 in case of success, 0 else.
*/
static inline int       del_alias(char                          *key,
                                  s_builtin_fd                  *builtin_fd)
{
  char                  *value = NULL;

  value = masso_get(g_shell->alias, key);
  if (NULL == value)
  {
      fprintf(builtin_fd->fout, "bash: unalias: %s: not found\n", key);
      return (1);
  }
  else
  {
      masso_unlink(g_shell->alias, key);
      mfree(value);
      return (0);
  }

  return (0);
}

/**
** @brief               Unaliases all aliases.
** @param builtin_fd    IOs streams.
** @return              void
*/
static inline void      unalias_all(s_builtin_fd                *builtin_fd)
{
  char                  *key;

  for (int i = 0; NULL != (key = masso_getn_key(g_shell->alias, i)); i++)
    del_alias(key, builtin_fd);
}

int                     builtin_unalias(char                    **argv,
                                        s_builtin_fd            *builtin_fd)
{
  int                   res = 0;
  int                   argc;

  if (1 == (argc = get_argc(argv)))
  {
      fprintf(builtin_fd->fout,
              "unalias: usage: unalias [-a] name [name ...]\n");
      return (2);
  }

  if (0 == strcmp(argv[1], "-a"))
  {
      unalias_all(builtin_fd);
      return (0);
  }

  for (int i = 1; argv[i] != NULL; i++)
    res = res || del_alias(argv[i], builtin_fd);

  return (res);
}

