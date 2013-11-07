#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../masso/masso.h"
#include "history.h"
#include "../42sh/shell.h"

/**
** @brief               Gets maximum history length.
** @return              Returns maximum history length.
*/
static inline size_t    get_nbsave_history(void)
{
  char                  *str = NULL;

  if (NULL == (str = getenv("HISTFILESIZE")))
    if (NULL == (str = masso_get(g_shell->vars, "HISTFILESIZE")))
      return (0);

  return (atoi(str) - 1);
}

/**
** @brief               Gets history file path.
** @return              Returns history file path.
*/
static inline char      *path_history_file(void)
{
  char                  *path_file;

  path_file = mstring_copy(getenv("HOME"));
  path_file = mrealloc(path_file, (strlen(path_file) + 20) * sizeof (char));
  path_file = strcat(path_file, "/.42sh_history");

  return (path_file);
}

void                    history_save(s_queue_history            *hist_q)
{
  FILE                  *f = NULL;
  char                  *path_file = NULL;
  s_hqueue              *tmp = NULL;
  size_t                i = 0;

  if (NULL == hist_q)
    return;

  path_file = path_history_file();

  if (NULL == (f = mfopen(path_file, "w")))
  {
    mfree(path_file);
    return;
  }

  if (0 == (i = get_nbsave_history()))
    i = hist_q->len - 1;

  tmp = hist_q->last;
  for (; (i < hist_q->len) && (i > 0); i--)
    tmp = tmp->prev;

  while (tmp)
  {
    fprintf(f, "%s\n", tmp->element);
    tmp = tmp->next;
  }

  mfclose(f);
  mfree(path_file);
}
