#ifndef PS1_H_
# define PS1_H_

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdarg.h>
# include <strings.h>

# include "ps1_types.h"
# include "../../masso/masso.h"
# include "../../42sh/main.h"
# include "ps1_checker.h"
# include "../../mmalloc/mmalloc.h"

void                    print_ps1(char                   *ps1,
                                  s_ps1_datas            *ps1_datas);

#endif /* !PS1_H_ */
