#include "minishell.h"

void print_sorted_env(char **env)
{
   int i;
   int j;
   int len;
   char *temp;
   temp = (char*)malloc(100);

   len = 0;

   while (env[len])
      len++;
   len--;
   for(i=0;i<len;i++)
      for(j=i+1;j<len;j++){
         if(strcmp(env[i],env[j])>0){
            temp = env[i];
            env[i] = env[j];
            env[j] = temp;
         }
      }
   
   i = 0;
   while(env[i])
      printf("%s\n", env[i++]);
}