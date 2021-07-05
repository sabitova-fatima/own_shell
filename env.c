#include "minishell.h"

int   env_len(char **env)
{
   int len;

   len = 0;
   while (env[len])
      len++;
   return (len - 1);
}

int  print_sorted_env(char **env)
{
   int i;
   int j;
   int len;
   char *temp;

   temp = (char*)malloc(100);
   len = env_len(env);
   i = 0;
   while (i < len)
   {
      j = i + 1;
      while (j < len)
      {
         if (strcmp(env[i], env[j]) > 0)
         {
            temp = env[i];
            env[i] = env[j];
            env[j] = temp;
         }
         j++;
      }
   i++;
   }
   i = 0;
   while (env[i])
      printf("%s\n", env[i++]);
   return (1);
}
