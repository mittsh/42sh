#include "ps1.h"

static inline void      check_s(char                     c,
                                bool                     *escaped,
                                bool                     *checked,
                                char                     *shell)
{
  if (c == 's' && *checked == false)
  {
    printf("%s", (*escaped ? shell : "s"));
    *escaped = (*escaped ? false : *escaped);
    *checked = true;
  }
}

void                    print_ps1(char                   *ps1,
                                  s_ps1_datas            *ps1_datas)
{
  bool                  escaped = false;
  bool                  checked;
  char                  *shell = NULL;
  char                  number[4] = "\0\0\0\0";
  s_ps1                 ps1_st;

  ps1_st.str = ps1;
  ps1_st.noprint = false;

  for (unsigned int i = 0; i < strlen(ps1); i++)
  {
    checked = false;
    ps1_st.position = i;

    ps1_checker_1(ps1_st, &escaped, &checked, number);
    ps1_checker_2(ps1_st, &escaped, &checked);
    ps1_checker_3(ps1_st, &escaped, &checked, ps1_datas);

    shell = masso_get(g_shell->vars, "0");
    check_s(ps1[i], &escaped, &checked, shell);

    if (checked == false)
    {
      printf("%s%c", escaped ? "\\" : "", ps1[i]);
      escaped = false;
    }
  }
}
