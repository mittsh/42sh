#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "builtin.h"
#include "../masso/masso.h"
#include "../42sh/shell.h"

/**
** @brief               Alias list sorting.
** @param elmt          Current element.
** @param next          Next list element.
*/
typedef struct                  list_sort
{
  char                          *elmt;
  struct list_sort              *next;
}                               s_list_sort;

/**
** @brief               Gets arguments number.
** @param argv          Input arguments values list.
** @return              Returns arguments number.
*/
static inline int               get_argc(char                   **argv)
{
  int                           i;

  for (i = 0; argv[i] != NULL; i++)
    ;
  return (i);
}

/**
** @brief               Adds a value in the sorted list.
** @param list          Input list.
** @param elmt          Input element.
** @return              Returns new list, including new element.
*/
static inline s_list_sort       *list_sort_add(s_list_sort      *list,
                                               char             *elmt)
{
  s_list_sort                   *aux = NULL;
  s_list_sort                   *tmp = list;
  s_list_sort                   *prev = list;

  aux = mmalloc(sizeof (s_list_sort));
  aux->elmt = elmt;
  aux->next = NULL;

  if (NULL == list)
    return (aux);

  while (tmp->next != NULL && strcmp(tmp->elmt, elmt) < 0)
  {
      prev = tmp;
      tmp = tmp->next;
  }

  if (tmp->next == NULL)
    tmp->next = aux;
  else
  {
      prev->next = aux;
      aux->next = tmp;
  }

  return (list);
}

/**
** @brief               Prints one alias value.
** @param key           Alias key.
** @param builtin_fd    IOs streams.
** @return              Returns 1 if not found, 0 in case of success.
*/
static inline int       print_one_alias(char                    *key,
                                        s_builtin_fd            *builtin_fd)
{
  char                  *alias = NULL;

  alias = masso_get(g_shell->alias, key);
  if (NULL == alias)
  {
      fprintf(builtin_fd->fout, "42sh: alias: %s : not found\n", key);
      return (1);
  }
  else
  {
      fprintf(builtin_fd->fout, "alias %s='%s'\n", key, alias);
      return (0);
  }
}

/**
** @brief               Prints all aliases.
** @param builtin_fd    IOs streams.
** @return              void
*/
static inline void      print_all_alias(s_builtin_fd            *builtin_fd)
{
  char                  *key = NULL;
  s_list_sort           *list = NULL;
  s_list_sort           *tmp = NULL;

  for (int i = 0; NULL != (key = masso_getn_key(g_shell->alias, i)); i++)
    list = list_sort_add(list, key);

  tmp = list;
  while (tmp != NULL)
  {
      print_one_alias(tmp->elmt, builtin_fd);
      tmp = tmp->next;
  }

  while (list != NULL)
  {
      tmp = list->next;
      mfree(list);
      list = tmp;
  }
}

/**
** @brief               If alias name and value is set, alias is added, else
**                      all aliases are setted.
** @return              Returns 1 in case of setting, else return value of
**                      alias printing.
*/
static inline int       add_or_print_alias(char                 *alias,
                                           s_builtin_fd         *builtin_fd)
{
  char                  *key = NULL;
  char                  *value = NULL;
  char                  *aux = NULL;

  aux = strchr(alias, '=');
  if (aux == NULL)
    return (print_one_alias(alias, builtin_fd));

  aux[0] = '\0';
  value = aux + 1;
  key = alias;

  masso_set(g_shell->alias, key, mstring_copy(value));

  return (0);
}

int                     builtin_alias(char                      **argv,
                                      s_builtin_fd              *builtin_fd)
{
  int                   res = 0;
  int                   argc;

  if (1 == (argc = get_argc(argv)))
  {
      print_all_alias(builtin_fd);
      return (0);
  }

  for (int i = 1; argv[i] != NULL; i++)
  {
      if (i == 1)
      {
          if (0 == strcmp(argv[i], "-p"))
            print_all_alias(builtin_fd);
          else
            res = res || add_or_print_alias(argv[i], builtin_fd);
      }
      else
        res = res || add_or_print_alias(argv[i], builtin_fd);
  }

  return (res);
}
