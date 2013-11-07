/**
** @file options_parser.c
** @brief Parser options from argv
** @author maarek_j
** @date Tue Nov  2 00:43:58 2010
*/

#define _SVID_SOURCE 1
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "options_parser.h"

/**
** @brief		Create a list parameter for an option.
** @param list_opt	List of options.
** @param[in] argc	Number of arguments.
** @param[in] argv	List of arguments.
** @param[in] i		Index in the list of arguments.
*/
static inline void	create_param(s_list_options	*list_opt,
				     size_t		argc,
				     char		**argv,
				     size_t		i)
{
  size_t		len;

  len = list_opt->len;
  for (size_t j = i + 1; j < argc; j++)
    if ((argv[j][0] != '-') && (argv[j][0] != '+'))
    {
	list_opt->option[len].param =
	  mrealloc(list_opt->option[len].param,
		  (list_opt->option[len].len + 1) * sizeof (char *));
	list_opt->option[len].param[list_opt->option[len].len++] =
	  mstring_copy(argv[j]);
    }
    else
      break;
}

s_list_options		*options_parser(int		argc,
					char		**argv)
{
  s_list_options	*list_opt;
  size_t		len;

  list_opt = mcalloc(1, sizeof (s_list_options));

  for (int i = 1; i < argc; i++)
  {
      if ((argv[i][0] == '-') || (argv[i][0] == '+'))
      {
	  len = list_opt->len;
	  list_opt->option[len].name =
	    mstring_copy(argv[i] + ((argv[i][1] == '-' ? 2 : 1)));
	  list_opt->option[len].more_or_less = argv[i][0];

	  create_param(list_opt, argc, argv, i);

	  list_opt->len++;
      }
  }

  return (list_opt);
}
