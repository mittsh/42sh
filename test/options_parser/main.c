#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../../src/options_parser/options_parser.h"

s_shell                 *g_shell = NULL;

int			main(int	argc,
			     char	*argv[])
{
  s_list_options	*list_opt;
  s_option		opt;

  g_shell = malloc(sizeof (s_shell));
  mmalloc_init();

  list_opt = options_parser(argc, argv);
  printf("option_parser()\n");
  for (size_t i = 0; i < list_opt->len; i++)
  {
      printf("name:%s\n", list_opt->option[i].name);
      printf("m-l:%c\n", list_opt->option[i].more_or_less);
      for (size_t j = 0; j < list_opt->option[i].len; j++)
  	printf("\t%s\n", list_opt->option[i].param[j]);
  }

  if (0 == get_option(&opt, list_opt, "help"))
  {
      printf ("\nget_option(%s)\n", "help");
      printf("find:%i\n", get_option(&opt, list_opt, "help"));
      printf("name:%s\n", opt.name);
      printf("m-l:%i\n", opt.more_or_less);
      for (size_t j = 0; j < opt.len; j++)
	printf("\t%s\n", opt.param[j]);
  }

  if (0 == get_option(&opt, list_opt, "o"))
  {
      printf ("\nget_option(%s)\n", "o");
      printf("find:%i\n", get_option(&opt, list_opt, "o"));
      printf("name:%s\n", opt.name);
      printf("m-l:%i\n", opt.more_or_less);
      for (size_t j = 0; j < opt.len; j++)
	printf("\t%s\n", opt.param[j]);
  }

  if (0 == get_option(&opt, list_opt, "c"))
  {
      printf ("\nget_option(%s)\n", "c");
      printf("find:%i\n", get_option(&opt, list_opt, "c"));
      printf("name:%s\n", opt.name);
      printf("m-l:%i\n", opt.more_or_less);
      for (size_t j = 0; j < opt.len; j++)
	printf("\t%s\n", opt.param[j]);
  }

  if (0 == get_option(&opt, list_opt, "norc"))
  {
      printf ("\nget_option(%s)\n", "norc");
      printf("find:%i\n", get_option(&opt, list_opt, "norc"));
      printf("name:%s\n", opt.name);
      printf("m-l:%i\n", opt.more_or_less);
      for (size_t j = 0; j < opt.len; j++)
	printf("\t%s\n", opt.param[j]);
  }

  if (0 == get_option(&opt, list_opt, "ast-printer"))
  {
      printf ("\nget_option(%s)\n", "ast-printer");
      printf("find:%i\n", get_option(&opt, list_opt, "ast-printer"));
      printf("name:%s\n", opt.name);
      printf("m-l:%i\n", opt.more_or_less);
      for (size_t j = 0; j < opt.len; j++)
	printf("\t%s\n", opt.param[j]);
  }

  if (0 == get_option(&opt, list_opt, "version"))
  {
      printf ("\nget_option(%s)\n", "version");
      printf("find:%i\n", get_option(&opt, list_opt, "version"));
      printf("name:%s\n", opt.name);
      printf("m-l:%i\n", opt.more_or_less);
      for (size_t j = 0; j < opt.len; j++)
	printf("\t%s\n", opt.param[j]);
  }


  printf ("\nget_option(\"NULL\")\n");
  printf("find:%i\n", get_option(&opt, NULL, "version"));

  printf("\nfree_list_options()\n");
  free_list_options(list_opt);
  printf("OK\n");

  mmalloc_free();
  free(g_shell);

  return (0);
}
