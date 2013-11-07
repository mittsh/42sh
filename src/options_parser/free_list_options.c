/**
** @file free_list_options.c
** @brief Define the function free_list_options
** @author maarek_j
** @date Tue Nov  2 00:46:28 2010
**
** The function free_list_options frees a list_options
**
*/

#define _SVID_SOURCE 1
#include <stdlib.h>
#include <unistd.h>

#include "options_parser.h"

void		free_list_options(s_list_options	*list_opt)
{
  for (size_t i = 0; i < list_opt->len; i++)
  {
    for (size_t j = 0; j < list_opt->option[i].len; j++)
      mfree(list_opt->option[i].param[j]);
    mfree(list_opt->option[i].name);
    mfree(list_opt->option[i].param);
  }

  mfree(list_opt);
}
