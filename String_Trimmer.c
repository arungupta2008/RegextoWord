#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char *substring(const char *string, int Start_postion, int End_position) 
{
   char *pointer;
   int c;
	End_position = End_position-Start_postion+1;
   pointer = malloc(End_position+1);
 
   if (pointer == NULL)
   {
      printf("Unable to allocate memory.\n");
      exit(1);
   }
   for (c = 0 ; c < Start_postion; c++) 
      string++; 
 
   for (c = 0 ; c < End_position ; c++)
   {
      *(pointer+c) = *string;      
      string++;   
   }
   //adding EOF
   *(pointer+c) = '\0';
   return pointer;
}
int main()
{
   static const char text[] = "The qu[a-z]ick brown fox jumps over the lazy dog.";
   char a[10], b[5];
   printf("substring = \"%s\"\n",substring(text,6,10) );
   //printf("substring = \"%s\"\n", substring(4, 13, text, sizeof b));
   return 0;
}
/* my output
substring = "quick bro"
substring = "quic"
*/