#include "readline.h"

static char             *print_default_ps1(void)
{
  char                  *ps1 = NULL;

  if (NULL == (ps1 = masso_get(g_shell->vars, "PS1")))
  {
    printf("$ ");
    fflush(stdout);
    return (NULL);
  }
  return (ps1);
}

static void             init_hostname(char               *hostname)
{
  bzero(hostname, 1024);
  gethostname(hostname, 1023);
}

static void             shorten_hostame(char             *hostname_short,
                                        char             *hostname)
{
  bzero(hostname_short, 1024);

  for (unsigned int i = 0; i < strlen(hostname); i++)
  {
    if (hostname[i] != '\0' && hostname[i] != '.')
      hostname_short[i] = hostname[i];
  }
}

static void             set_date(char                     *date)
{
  time_t                t;
  struct tm             *current_time;

  t = time(NULL);
  current_time = localtime(&t);

  if (current_time == NULL)
  {
    perror("localtime");
    return;
  }

  bzero(date, 200);

  strftime(date, 10, "%a %b %d", current_time);
}

static void             set_uid(char                      *username)
{
  struct passwd         pw;
  struct passwd         *pwdptr = NULL;
  struct passwd         *tempPwdPtr = NULL;
  uid_t                 uid;
  char                  pwdbuffer[1024];
  int                   pwdlinelen = 0;

  pwdptr = &pw;
  pwdlinelen = sizeof(pwdbuffer);

  uid = geteuid();
  if (getpwuid_r(uid, pwdptr, pwdbuffer, pwdlinelen, &tempPwdPtr) == 0)
  {
    bzero(username, 1024);
    strcpy(username, pw.pw_name);
  }
  else
    username = NULL;
}

static void             set_base_cwd(char                *base_cwd,
                                     char                *cwd)
{
  int                   i;

  bzero(base_cwd, 1024);

  if (strlen(cwd) == 1 && cwd[0] == '/')
    base_cwd[0] = '/';

  for (i = strlen(cwd) - 1; i >= 0; i--)
  {
    if (cwd[i] == '/')
    {
      i++;
      break;
    }
  }

  for (unsigned int j = i; j < strlen(cwd); j++)
    base_cwd[j - i] = cwd[j];
}

static s_ps1_datas      *init_ps1_datas(void)
{
  s_ps1_datas           *ps1_datas = NULL;

  ps1_datas = mmalloc(sizeof (s_ps1_datas));

  init_hostname(ps1_datas->hostname);
  shorten_hostame(ps1_datas->hostname_short, ps1_datas->hostname);
  set_date(ps1_datas->date);
  set_uid(ps1_datas->uid);

  bzero(ps1_datas->cwd, 1024);
  getcwd(ps1_datas->cwd, 1024);

  set_base_cwd(ps1_datas->base_cwd, ps1_datas->cwd);

  return (ps1_datas);
}

void                    readline_print_ps1(void)
{
  char                  *ps1       = NULL;
  s_ps1_datas           *ps1_datas = NULL;

  if (NULL == (ps1 = print_default_ps1()))
    return;

  if (NULL == (ps1_datas = init_ps1_datas()))
    print_default_ps1();

  print_ps1(ps1, ps1_datas);

  mfree(ps1_datas);

  fflush(stdout);
}
