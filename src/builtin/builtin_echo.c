#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "builtin.h"

/**
** @brief               Gets arguments number.
** @param argv          Input arguments values list.
** @return              Returns arguments number.
*/
static inline int       get_argc(char                       **argv)
{
  int                   i;

  for (i = 0; argv[i] != NULL; i++)
    ;
  return (i);
}

/**
** @brief               Tires to print an excaped character.
** @param char          Input character.
** @param builtin_fd    IOs streams.
** @return              Returns (-1) if 'c' is found else 0.
*/
static inline int       if_print_escap(char                   ch,
                                       s_builtin_fd           *builtin_fd)
{
  if (ch == 'c')
    return (-1);
  if (ch == 'a')
    fprintf(builtin_fd->fout, "\a");
  if (ch == 'b')
    fprintf(builtin_fd->fout, "\b");
  if (ch == 'e')
    fprintf(builtin_fd->fout, "\033");
  if (ch == 'f')
    fprintf(builtin_fd->fout, "\f");
  if (ch == 'n')
    fprintf(builtin_fd->fout, "\n");
  if (ch == 'r')
    fprintf(builtin_fd->fout, "\r");
  if (ch == 't')
    fprintf(builtin_fd->fout, "\t");
  if (ch == 'v')
    fprintf(builtin_fd->fout, "\v");
  if (ch == '\\')
    fprintf(builtin_fd->fout, "\\");
  return (0);
}

/**
** @brief               Checks if a characted is escaped.
** @param ch            Input character.
** @return              Returns true in case of success.
*/
static inline bool      is_escaped(char                       ch)
{
  if (ch == 'b' || ch == 'c' || ch == 'e' ||
      ch == 'f' || ch == 'n' || ch == 'r' ||
      ch == 't' || ch == 'v' || ch == '\\' ||
      ch == 'a')
    return (true);
  else
    return (false);
}

/**
** @brief               Prints with excaped characters.
** @param argv          Input arguments values.
** @param builtin_fd    IOs streams.
** @return              Returns 0 in case of success (-1) else.
*/
static inline int       print_escaped(char                    *argv,
                                      s_builtin_fd            *builtin_fd)
{
  int                   i;

  for (i = 0; argv[i] != '\0'; i++)
  {
    if (argv[i] == '\\')
    {
      if (argv[i] != '\0' )
      {
        if (is_escaped(argv[i + 1]))
        {
          if (-1 == if_print_escap(argv[i + 1], builtin_fd))
          {
            fflush(builtin_fd->fout);
            return (-1);
          }
        }
        else
          fprintf(builtin_fd->fout, "%c", argv[i + 1]);
        i++;
      }
    }
    else
      fprintf(builtin_fd->fout, "%c", argv[i]);
  }
  fflush(builtin_fd->fout);
  return (0);
}

/**
** @brief               Gets builtin echo parameters.
** @param argv          Input arguments values.
** @param opt           Option structure.
** @return              Return the return value of get_argc.
*/
static inline int       echo_get_opt(char                     **argv,
                                     struct s_echo_opt        *opt)
{
  int                   i = 0;
  int                   j = 0;

  for (i = 1; i < get_argc(argv); i++)
  {
      if (argv[i][0] == '-')
      {
          for (j = 1;
               argv[i][j] == 'e' || argv[i][j] == 'n' || argv[i][j] == 'E';
               j++)
          {
              if (argv[i][j] == 'e')
                opt->eflag = true;
              if (argv[i][j] == 'n')
                opt->nflag = true;
              if (argv[i][j] == 'E')
                opt->eeflag = true;
          }
          if ((argv[i][j] != '\0') || (j == 1))
              break;
      }
      else
        break;
  }
  opt->dec = i;

  return (get_argc(argv));
}

/**
** @brief               Prints all echo arguments.
** @param opt           Echo options structure.
** @param argv          Input arguments values.
** @param optind        Input options.
** @param builtin_fd    IOs streams.
** @return              Returns the return value of printing, 0 if success.
*/
static inline int       print_all(struct s_echo_opt           *opt,
                                  char                        **argv,
                                  int                         optind,
                                  s_builtin_fd                *builtin_fd)
{
  int                   i;
  int                   argc;

  argc = get_argc(argv);

  if (opt->eflag == false)
  {
    for (i = optind; i < argc - 1; i++)
      fprintf(builtin_fd->fout, "%s ", argv[i]);
    if (argv[i])
      fprintf(builtin_fd->fout, "%s", argv[i]);
  }
  else
  {
    for (i = optind; i < argc - 1; i++)
    {
      if (print_escaped(argv[i], builtin_fd) == -1)
        return (-1);
      fprintf(builtin_fd->fout, " ");
    }
    if (argv[i])
      if (print_escaped(argv[i], builtin_fd) == -1)
        return (-1);
  }
  return (0);
}

int                     builtin_echo(char                     **argv,
                                     s_builtin_fd             *builtin_fd)
{
  int                   argc;
  struct s_echo_opt     opt;

  opt.eflag = false;
  opt.nflag = false;
  opt.eeflag = false;
  opt.dec = 0;
  argc = echo_get_opt(argv, &opt);

  if (-1 == print_all(&opt, argv, opt.dec, builtin_fd))
    return (0);

  if (opt.nflag == false)
    fprintf(builtin_fd->fout, "\n");

  fflush(builtin_fd->fout);

  return (0);
}
