/**
** @file get_option.c
** @brief Defines the function get_option
** @author maarek_j
** @date Tue Nov  2 00:44:43 2010
**
** The function get_option search a list of option, if an option
** exists, and give this option.
*/

#define _SVID_SOURCE 1
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "options_parser.h"

int			get_option(s_option		*opt,
				   const s_list_options	*list_opt,
				   const char		*str_name)
{
  size_t		i = 0;

  if (list_opt == NULL)
    return (-2);

  while ((i != list_opt->len) &&
	 (strcmp(list_opt->option[i].name, str_name) != 0))
    i++;

  if (i == list_opt->len)
    return (-1);

  *opt = list_opt->option[i];

  return (0);
}

