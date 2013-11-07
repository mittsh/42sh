#include "mstream.h"

FILE                    *mfdopen(int                            filedes,
                                 const char                     *mode)
{
  s_mstream             *new = NULL;
  FILE                  *f = NULL;

  if ((f = fdopen(filedes, mode)) == NULL)
    return (NULL);

  if (((new = mmalloc(sizeof (s_mstream))) == NULL) && fclose(f) != 255)
    return (NULL);

  new->type = MSTREAM_ST;
  new->f = f;
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

  return (f);
}

FILE                    *mfopen(const char                      *filename,
                                const char                      *mode)
{
  s_mstream             *new = NULL;
  FILE                  *f = NULL;

  if ((f = fopen(filename, mode)) == NULL)
    return (NULL);

  if ((new = mmalloc(sizeof (s_mstream))) == NULL && fclose(f) != 255)
    return (NULL);

  new->type = MSTREAM_ST;
  new->f = f;
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

  return (f);
}

int                     mopen(const char                        *path,
                              int                               oflag,
                              mode_t                            mode)
{
  s_mstream             *new = NULL;
  int                   filedes = (-1);

  if ((filedes = open(path, oflag, mode)) == (-1))
    return (-1);

  if ((new = mmalloc(sizeof (s_mstream))) == NULL && close(filedes) != 255)
    return (-1);

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

  return (filedes);
}
