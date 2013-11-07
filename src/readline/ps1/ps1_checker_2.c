#include "ps1_checker.h"

static inline void      check_n(s_ps1                    ps1_st,
                                bool                     *escaped,
                                bool                     *checked)
{
  if (ps1_st.str[ps1_st.position] == 'n' && *checked == false &&
      ps1_st.noprint == false)
  {
    printf("%c", (*escaped ? '\n' : 'n'));
    *escaped = (*escaped ? false : *escaped);
    *checked = true;
  }
}

static inline void      check_dollar(s_ps1               ps1_st,
                                     bool                *escaped,
                                     bool                *checked)
{
  if (ps1_st.str[ps1_st.position] == '$' && *checked == false &&
      ps1_st.noprint == false)
  {
    printf("%s", (*escaped ? "$" : ""));
    *escaped = (*escaped ? false : *escaped);
    *checked = true;
  }
}

static inline void      check_a(s_ps1                    ps1_st,
                                bool                     *escaped,
                                bool                     *checked)
{
  if (ps1_st.str[ps1_st.position] == 'a' && *checked == false &&
      ps1_st.noprint == false)
  {
    printf("%c", (*escaped ? 7 : 'a'));
    *escaped = (*escaped ? false : *escaped);
    *checked = true;
  }
}

static inline void      check_e(s_ps1                    ps1_st,
                                bool                     *escaped,
                                bool                     *checked)
{
  if (ps1_st.str[ps1_st.position] == 'e' && *checked == false &&
      ps1_st.noprint == false)
  {
    printf("%c", (*escaped ? 27 : 'e'));
    *escaped = (*escaped ? false : *escaped);
    *checked = true;
  }
}

static inline void      check_r(s_ps1                    ps1_st,
                                bool                     *escaped,
                                bool                     *checked)
{
  if (ps1_st.str[ps1_st.position] == 'r' && *checked == false &&
      ps1_st.noprint == false)
  {
    printf("%c", (*escaped ? '\r' : 'r'));
    *escaped = (*escaped ? false : *escaped);
    *checked = true;
  }
}

void            ps1_checker_2(s_ps1                      ps1_st,
                              bool                       *escaped,
                              bool                       *checked)
{
  check_n(ps1_st, escaped, checked);

  check_dollar(ps1_st, escaped, checked);

  check_a(ps1_st, escaped, checked);

  check_e(ps1_st, escaped, checked);

  check_r(ps1_st, escaped, checked);
}
