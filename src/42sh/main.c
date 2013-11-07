#include "main.h"

s_shell                 *g_shell = NULL;

/**
** @brief               Macro : prints a string and returns it.
*/
#define PRINTF_AND_RETURN(Str)                        \
  {                                                   \
    printf(Str);                                      \
    return (0);                                       \
  }

/**
** @brief               Executes a command line, with or without printing AST.
** @param is_print_ast  1 if AST printer is activated, 0 else.
** @param str           Input command.
** @return              Returns execution return value.
*/
static int              exec_command_line(int                   is_print_ast,
                                          char                  *str)
{
  int                   res = 0;
  int                   error = 0;
  int                   i = 0;
  char                  png[512];

  if (str != NULL)
  {
      g_shell->lex = lexer_init();

      if (0 == lexer_load_str(g_shell->lex, str))
        return (res);
      lexer_action(g_shell->lex);
  }

  while (NULL != lexer_get_token(g_shell->lex))
  {
      g_shell->ast = parse_input(g_shell->lex);

      sprintf(png, "ast%i.png", i);
      if (is_print_ast == 1)
          print_ast(png, g_shell->ast);

      res = exec_list_instr(g_shell->ast, NULL, &error);
      free_list_instr(g_shell->ast);
      i++;
  }

  lexer_free(g_shell->lex);

  return (res);
}

/**
** @brief               Parses one option for option parser.
** @param option_index  Option index pointer.
** @param main_option   Writes options on that structure.
** @param arv           Input arguments values.
** @param argc          Input arguments number.
** @return              Returns 1 if execution succes.
*/
static int              parse_one_option(int                    *option_index,
                                         s_main_options         *main_option,
                                         char                   **argv,
                                         int                    argc)
{
  int                   c = 0;
  struct option         long_options[] =
    {
      {"version", no_argument, 0, 'V'},
      {"ast-print", no_argument, 0, 'A'},
      {"norc", no_argument, 0, 'N'},
      {"command-input", required_argument, 0, 'c'},
      {0, 0, 0, 0}
    };

  c = getopt_long(argc, argv, "VANc:", long_options, option_index);

  if (c == (-1))
    return (0);

  if (c == 'V')
    main_option->version = 1;

  if (c == 'A')
    main_option->printast = 1;

  if (c == 'N')
    main_option->norc = 1;

  if (c == 'c')
  {
    main_option->command_line = optarg;
    main_option->command_input = 1;
    return (2);
  }

  return (1);
}

/**
** @brief               Executes a Shell script from standard input.
** @param is_print_ast  1 when AST printer is activated, 0 else.
** @return              Returns execution return value.
*/
static int              exec_from_stdin(int                     is_print_ast)
{
  char                  buf[129];
  s_dynamic_string      *dynstr = NULL;
  int                   len = 0;
  int                   res = 0;

  dynstr = dynamic_string_init();

  while ((len = read(STDIN_FILENO, buf, 128)) > 0)
  {
    buf[len] = '\0';
    dynamic_string_pushs(dynstr, buf);
  }

  if (dynstr->len != 0)
    res = exec_command_line(is_print_ast, dynstr->str);

  dynamic_string_free(dynstr);

  return (res);
}

/**
** @brief               Executes a command line, with or without printing AST,
**                      from a file.
** @param is_print_ast  1 if AST printer is activated, 0 else.
** @param filename      Input filename.
** @return              Returns execution return value.
*/
static int              exec_from_file(int                      is_print_ast,
                                       char                     *filename)
{
  char                  buf[129];
  s_dynamic_string      *dynstr = NULL;
  int                   len = 0;
  int                   fd = 0;
  int                   res = 0;

  fd = mopen(filename, O_RDONLY, 0);

  if (fd <= 0)
  {
    fprintf(stderr, "%s: %s: No such file or directory\n", "42sh", filename);
    return (127);
  }

  dynstr = dynamic_string_init();

  while ((len = read(fd, buf, 128)) > 0)
  {
    buf[len] = '\0';
    dynamic_string_pushs(dynstr, buf);
  }

  if (dynstr->len != 0)
    res = exec_command_line(is_print_ast, dynstr->str);

  dynamic_string_free(dynstr);

  mclose(fd);

  return (res);
}

/**
** @brief               Inits 42sh options.
** @param main_option   Target main_option structure.
** @return              void
*/
static inline void      set_main_options(s_main_options         *main_option)
{
  main_option->version = 0;
  main_option->printast = 0;
  main_option->command_line = NULL;
  main_option->command_input = 0;
  main_option->norc = 0;
}

/**
** @brief               Initialises Shell and all structures such as
**                      mmalloc, mstream, variables, functions, aliases,
**                      history queue, and registers environment variables.
** @param envp          Shell's environment.
** @return              void
*/
static inline void      init_shell(char                         *envp[])
{
  g_shell = malloc(sizeof (s_shell));

  mmalloc_init();
  mstream_init();

  g_shell->vars = masso_init();
  g_shell->func = masso_init();
  g_shell->alias = masso_init();
  g_shell->queue_history = history_load();
  g_shell->term_mode = 0;
  g_shell->return_value = 0;
  masso_set(g_shell->vars, "0", mstring_copy("42sh"));
  vars_register_env(envp);
}

/**
** @brief               42sh main function.
** @param argc          Input arguments number.
** @param argv          Input arguments values.
** @param envp          Shell's environment.
*/
int                     main(int                                argc,
                             char                               *argv[],
                             char                               *envp[])
{
  int                   option_index = 0;
  s_main_options        main_option;
  int                   opt = 1;
  int                   optl = 0;
  int                   res = 0;

  init_shell(envp);
  set_main_options(&main_option);

  while (opt)
    optl += (opt = parse_one_option(&option_index, &main_option, argv, argc));

  if (main_option.version)
    PRINTF_AND_RETURN("Version 1.0\n")

  if (main_option.command_input)
    res = exec_command_line(main_option.printast, main_option.command_line);
  if (!main_option.command_input && argv[optl + 1] != NULL)
    exec_from_file(main_option.printast, argv[optl + 1]);
  if (!main_option.command_input && argv[optl + 1] == NULL)
  {
    if (isatty(STDIN_FILENO))
      readline_interactive(main_option.printast);
    else
      res = exec_from_stdin(main_option.printast);
  }

  free_shell(g_shell);

  return (res);
}
