#include "ps1_checker.h"

static inline void      check_upper_h(s_ps1              ps1_st,
                                      bool               *escaped,
                                      bool               *checked,
                                      char               *hostname)
{
  if (ps1_st.str[ps1_st.position] == 'H' && *checked == false &&
      ps1_st.noprint == false)
  {
    printf("%s", (*escaped ? hostname : "H"));
    *escaped = (*escaped ? false : *escaped);
    *checked = true;
  }
}

static inline void      check_h(s_ps1                    ps1_st,
                                bool                     *escaped,
                                bool                     *checked,
                                char                     *hostname_short)
{
  if (ps1_st.str[ps1_st.position] == 'h' && *checked == false &&
      ps1_st.noprint == false)
  {
    printf("%s", (*escaped ? hostname_short : "h"));
    *escaped = (*escaped ? false : *escaped);
    *checked = true;
  }
}

static inline void      check_u(s_ps1                    ps1_st,
                                bool                     *escaped,
                                bool                     *checked,
                                char                     *uid)
{
  if (ps1_st.str[ps1_st.position] == 'u' && *checked == false &&
      ps1_st.noprint == false)
  {
    printf("%s", (*escaped ? uid : "u"));
    *escaped = (*escaped ? false : *escaped);
    *checked = true;
  }
}

static inline void      check_w(s_ps1                    ps1_st,
                                bool                     *escaped,
                                bool                     *checked,
                                char                     *uid)
{
  if (ps1_st.str[ps1_st.position] == 'w' && *checked == false &&
      ps1_st.noprint == false)
  {
    printf("%s", (*escaped ? uid : "w"));
    *escaped = (*escaped ? false : *escaped);
    *checked = true;
  }
}

static inline void      check_upper_w(s_ps1              ps1_st,
                                      bool               *escaped,
                                      bool               *checked,
                                      char               *uid)
{
  if (ps1_st.str[ps1_st.position] == 'W' && *checked == false &&
      ps1_st.noprint == false)
  {
    printf("%s", (*escaped ? uid : "W"));
    *escaped = (*escaped ? false : *escaped);
    *checked = true;
  }
}

static inline void      check_d(s_ps1                    ps1_st,
                                bool                     *escaped,
                                bool                     *checked,
                                char                     *date)
{
  if (ps1_st.str[ps1_st.position] == 'd' && *checked == false &&
      ps1_st.noprint == false)
  {
    printf("%s", (*escaped ? date : "d"));
    *escaped = (*escaped ? false : *escaped);
    *checked = true;
  }
}

void            ps1_checker_3(s_ps1                      ps1_st,
                              bool                       *escaped,
                              bool                       *checked,
                              s_ps1_datas                *ps1_datas)
{
  check_upper_h(ps1_st, escaped, checked, ps1_datas->hostname);

  check_h(ps1_st, escaped, checked, ps1_datas->hostname_short);

  check_u(ps1_st, escaped, checked, ps1_datas->uid);

  check_w(ps1_st, escaped, checked, ps1_datas->cwd);

  check_upper_w(ps1_st, escaped, checked, ps1_datas->base_cwd);

  check_d(ps1_st, escaped, checked, ps1_datas->date);
}
