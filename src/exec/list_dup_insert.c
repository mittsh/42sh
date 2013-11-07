#include "exec.h"

s_list_dup              *list_dup_insert(s_list_dup             *list_dup,
                                         int                    fd_in,
                                         int                    fd_out)
{
  s_list_dup            *new_dup = NULL;

  if ((new_dup = mmalloc(sizeof (s_list_dup))) == NULL)
    return (list_dup);

  new_dup->fd_in = fd_in;
  new_dup->fd_out = fd_out;
  new_dup->next = list_dup;

  return (new_dup);
}
