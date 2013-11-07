#ifndef MSTREAM_H_
# define MSTREAM_H_

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef enum            mstream_type
{
  MSTREAM_FD,
  MSTREAM_ST
}                       s_mstream_type;

typedef struct          mstream
{
  int                   filedes;
  FILE                  *f;
  s_mstream_type        type;
  struct mstream        *prev;
  struct mstream        *next;
}                       s_mstream;

typedef struct          mstream_mem
{
  s_mstream             *first;
  s_mstream             *last;
}                       s_mstream_mem;

int                     mstream_init(void);

FILE                    *mfdopen(int                            filedes,
                                 const char                     *mode);

FILE                    *mfopen(const char                      *filename,
                                const char                      *mode);

int                     mopen(const char                        *path,
                              int                               oflag,
                              mode_t                            mode);

int                     mpipe(int                               filedes[]);

int                     mfclose(FILE                            *f);

int                     mclose(int                              filedes);

int                     mstream_close(void);

int                     mstream_debug(void);

# include "../42sh/shell.h"

#endif /* !MSTREAM_H_ */
