#include "vars.h"

void                    vars_register_env(char                  **envp)
{
  for (; *envp != NULL; envp++)
    vars_register(*envp);
}
