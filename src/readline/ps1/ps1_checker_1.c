#include "ps1_checker.h"

static int              my_power(int                   number,
                                 int                   power)
{
  int                   result = number;

  if (power == 0)
    return (1);
  if (power == 1)
    return (number);

  for (int i = 1; i < power; i++)
    result *= number;

  return (result);
}

static char             *oct_to_dec(char             *oct_num)
{
  char                  *dec_num = NULL;
  int                   dec_num_int = 0;
  unsigned int          len;

  len = strlen(oct_num);
  dec_num = mmalloc(sizeof (char) * len);

  bzero(dec_num, len);

  for (int i = len - 1; i >= 0; i--)
    dec_num_int += (oct_num[i] - '0') * my_power(8, len - i - 1);

  snprintf(dec_num, 3, "%i", dec_num_int);

  return (dec_num);
}

static bool             is_octal(char               *number)
{
  for (unsigned int i = 0; i < strlen(number); i++)
  {
    if (number[i] - '0' > 7)
      return (false);
  }
  return (true);
}

static inline void      print_nnn(char              *number,
                                  bool              *escaped)
{
  char                  *dec_number = NULL;
  int                   dec_number_int;

  if (is_octal(number))
  {
    dec_number = oct_to_dec(number);
    dec_number_int = atoi(dec_number);

    if (dec_number_int < 128 && dec_number_int > 0)
      printf("%c", dec_number_int);
    else
      printf("\\%s", number);
    mfree(dec_number);
  }
  else
    printf("%s%s", *escaped ? "\\" : "", number);
  bzero(number, 4);
  *escaped = false;
}

static inline void      check_numbers(s_ps1         ps1_st,
                                      bool          *escaped,
                                      bool          *checked,
                                      char          *number)
{
  char                  c;

  c = ps1_st.str[ps1_st.position];

  if (c >= '0' && c <= '9')
  {
    if (*escaped)
    {
      number[strlen(number)] = c;
      if (strlen(number) == 3 || ps1_st.str[ps1_st.position + 1] == '\0')
        print_nnn(number, escaped);
    }
    else
      printf("%c", c);
    *checked = true;
  }
  else
  {
    if (*escaped && strlen(number))
      print_nnn(number, escaped);
  }
}

static inline void      check_backslash(s_ps1       ps1_st,
                                        bool        *escaped,
                                        bool        *checked)
{
  if (ps1_st.str[ps1_st.position] == '\\' && *checked == false &&
      ps1_st.noprint == false)
  {
    printf("%s", *escaped ? "\\" : "");
    *escaped = (*escaped ? false : true);
    *checked = true;
  }
}

static inline void      check_opbrk(s_ps1           ps1_st,
                                    bool            *escaped,
                                    bool            *checked)
{
  if (ps1_st.str[ps1_st.position] == '[' && *checked == false)
  {
    if (*escaped)
    {
      ps1_st.noprint = true;
      *checked = true;
      *escaped = false;
    }
    else
      if (ps1_st.noprint == false)
      {
        printf("%c", '[');
        *checked = true;
      }
  }
}

static inline void      check_clbrk(s_ps1           ps1_st,
                                    bool            *escaped,
                                    bool            *checked)
{
  if (ps1_st.str[ps1_st.position] == ']' && *checked == false)
  {
    if (*escaped)
    {
      ps1_st.noprint = false;
      *checked = true;
      *escaped = false;
    }
    else
      if (ps1_st.noprint == false)
      {
        printf("%c", ']');
        *checked = true;
      }
  }
}

void            ps1_checker_1(s_ps1                 ps1_st,
                              bool                  *escaped,
                              bool                  *checked,
                              char                  *number)
{
  check_backslash(ps1_st, escaped, checked);

  check_opbrk(ps1_st, escaped, checked);

  check_clbrk(ps1_st, escaped, checked);

  check_numbers(ps1_st, escaped, checked, number);
}
