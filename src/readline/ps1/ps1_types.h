#ifndef PS1_TYPES_H_
# define PS1_TYPES_H_

# include "../../mmalloc/mmalloc.h"

typedef struct          s_ps1_datas
{
  char                  hostname[1024];
  char                  hostname_short[1024];
  char                  date[200];
  char                  uid[1024];
  char                  cwd[1024];
  char                  base_cwd[1024];
}                       s_ps1_datas;

typedef struct          s_ps1
{
  char                  *str;
  int                   position;
  bool                  noprint;
}                       s_ps1;

#endif /* !PS1_TYPES_H_ */
