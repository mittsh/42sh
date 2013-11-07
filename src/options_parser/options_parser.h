#ifndef OPTIONS_PARSER_H_
# define OPTIONS_PARSER_H_

# include "../mmalloc/mmalloc.h"

/**
** @file options_parser.h
** @brief Parsing options from argv
** @author maarek_j
** @date Tue Nov  2 00:42:57 2010
*/

/**
** @struct		s_option
** @brief		Represents an option
*/
typedef struct		s_option
{
  char			*name;
  /*!< Name's option */

  char			more_or_less;
  /*!< Indicates wether the option invoked with '+' or '-' */

  char			**param;
  /*!< List of parameters associated with option */

  size_t		len;
  /*!< The number of parameters associated. */
}			s_option;

/**
** @def MAX_OPTIONS
** @brief Maximum number of options.
*/
# define MAX_OPTIONS 100

/**
** @struct		s_list_options
** @brief		A list of options
*/
typedef struct		s_list_options
{
  struct s_option	option[MAX_OPTIONS];
  /*!< List of options. */
  size_t		len;
  /*!< Number of options */
}			s_list_options;

/**
** @brief		Check a line of argument.
** @param[in] argc	A number argument.
** @param[in] argv	A line argument.
** @return		The function returns a structure *s_option.
*/
s_list_options		*options_parser(int			argc,
					char			**argv);

/**
** @brief		Search an option in the options list.
** @param[out] opt	It is option finding.
** @param[in] list_opt	It is the options list, the option will be
**			search in this list.
** @param[in] str_name	The name option to search.
** @return		0 if OK, -1 if not found, -2 if error.
*/
int			get_option(s_option			*opt,
				   const s_list_options		*list_opt,
				   const char			*str_name);

/**
** @brief		Frees a list of options.
** @param[in] list_opt	List to free.
*/
void			free_list_options(s_list_options	*list_opt);

#endif /* !OPTIONS_PARSER_H_ */
