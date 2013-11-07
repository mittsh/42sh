#ifndef CHECKER_H_
# define CHECKER_H_

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdarg.h>
# include <strings.h>

# include "ps1_types.h"
# include "../../mmalloc/mmalloc.h"

void            ps1_checker_1(s_ps1         ps1_st,
                              bool          *escaped,
                              bool          *checked,
                              char          *number);

void            ps1_checker_2(s_ps1         ps1_st,
                              bool          *escaped,
                              bool          *checked);

void            ps1_checker_3(s_ps1         ps1_st,
                              bool          *escaped,
                              bool          *checked,
                              s_ps1_datas   *ps1_datas);

#endif /* !CHECKER_H_ */
