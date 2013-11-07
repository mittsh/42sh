#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"
#include "../42sh/config.h"

#include "../mmalloc/mmalloc.h"

/**
** @brief               Gets a line. For compatibility with Linux (Fedora
**                      and Ubuntu) and BSD Darwin (Mac OSX).
** @param f             Input file stream.
** @return              Returns line string of null if end-of-file.
*/
#ifdef HAVE_GETLINE
inline static char      *my_getln(FILE	                        *f)
{
  char                  *res = NULL;
  size_t                len = 0;
  int                   read = 0;

  read = getline(&res, &len, f);

  if (read == -1)
  {
    free(res);
    return (NULL);
  }

  if (res)
    res[read - 1] = '\0';

  return (res);
}
#endif /* HAVE_GETLINE */

#ifdef HAVE_FGETLN
inline static char      *my_getln(FILE                          *f)
{
  char                  *res = NULL;
  size_t                len = 0;

  res = fgetln(f, &len);

  if (res)
    res[len - 1] = '\0';

  return (res);
}
#endif /* HAVE_FGETLN */

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

s_queue_history         *history_load(void)
{
  s_queue_history       *queue_history = NULL;
  FILE                  *f = NULL;
  char                  *path_file = NULL;
  char                  *line;

  path_file = path_history_file();

  if (NULL == (f = mfopen(path_file, "r")))
  {
    mfree(path_file);
    return (NULL);
  }

  queue_history = mcalloc(1, sizeof (s_queue_history));
  queue_history->len = 0;

  while (NULL != (line = my_getln(f)))
  {
      history_add_line(queue_history, line);
#ifdef HAVE_GETLINE
      free(line);
#endif /* !HAVE_GETLINE */
  }

  mfclose(f);
  mfree(path_file);

  return (queue_history);
}
