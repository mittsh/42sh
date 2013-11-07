#include "builtin.h"

int                     builtin_history(s_queue_history         *hist_q,
                                        s_builtin_fd            *builtin_fd)
{
  s_hqueue              *tmp = NULL;
  int                   i = 0;

  if (!hist_q)
    return (0);

  tmp = hist_q->first;
  while (tmp != NULL)
  {
    fprintf(builtin_fd->fout, "\t%i   %s\n", i++, tmp->element);
    tmp = tmp->next;
  }

  return (0);
}
