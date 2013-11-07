#include "mstream.h"

static inline void      mpipe_insert(s_mstream                  *new,
                                     int                        filedes)
{
  new->type = MSTREAM_FD;
  new->filedes = filedes;
  new->next = NULL;

  if (g_shell->mstream->first == NULL)
  {
    g_shell->mstream->first = new;
    g_shell->mstream->last = new;
    new->next = NULL;
    new->prev = NULL;
  }
  else
  {
    new->prev = g_shell->mstream->last;
    g_shell->mstream->last->next = new;
    g_shell->mstream->last = new;
  }
}

int                     mpipe(int                               filedes[])
{
  s_mstream             *new = NULL;
  s_mstream             *new2 = NULL;
  int                   res = (-1);

  if ((res = pipe(filedes)) == (-1))
    return (-1);

  if ((new = mmalloc(sizeof (s_mstream))) == NULL)
  {
    close(filedes[0]);
    close(filedes[1]);
    return (-1);
  }

  if ((new2 = mmalloc(sizeof (s_mstream))) == NULL)
  {
    mfree(new2);
    close(filedes[0]);
    close(filedes[1]);
    return (-1);
  }

  mpipe_insert(new, filedes[0]);
  mpipe_insert(new2, filedes[1]);

  return (res);
}
