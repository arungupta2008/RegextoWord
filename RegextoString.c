#include<stdio.h>
#include <string.h>


	char *read_line (char *buf, size_t length, FILE *f)
  /**** Read at most 'length'-1 characters from the file 'f' into
        'buf' and zero-terminate this character sequence. If the
        line contains more characters, discard the rest.
   */
{
  char *p;

  if (p = fgets (buf, length, f)) {
    size_t last = strlen(buf) - 1;

    if (buf[last] == '\n') {
      /**** Discard the trailing newline */
      buf[last] = '\0';
    } else {
      /**** There's no newline in the buffer, therefore there must be
            more characters on that line: discard them!
       */
      fscanf (f, "%*[^\n]");
      /**** And also discard the newline... */
      (void) fgetc (f);
    } /* end if */
  } /* end if */
  return p;
} /* end read_line */

main(){
/*
http://www.cs.tut.fi/~jkorpela/perl/regexp.html

To implement 


^ 	beginning of string
$ 	end of string
. 	any character except newline
* 	match 0 or more times
+ 	match 1 or more times
? 	match 0 or 1 times; or: shortest match
| 	alternative
( ) 	grouping; “storing”
[ ] 	set of characters
{ } 	repetition modifier
\ 	quote or special

a*	zero or more a’s
a+	one or more a’s
a?	zero or one a’s (i.e., optional a)
a{m}	exactly m a’s
a{m,}	at least m a’s
a{m,n}	at least m but at most n a’s
repetition? 	same as repetition but the shortest match is taken





*/
//*************************************************
//	Taking Input
//*************************************************
	char user_input[255];
	//fgets(user_input, 255, stdin);
	//printf("|%s|",user_input);
	//it also takes the \n as a input 
char *input = read_line (user_input, 255, stdin);
	printf("\n*****%s*****\n",user_input);
	printf("\n*****%s*****\n",input);
//*************************************************
//	Taking Input End (max Regex input size is 254 byte or characters )
//*************************************************	
if(scanSpecialChar(input)){
	printf("\nInput String can contain only This String : %s\n",input);
}else{
	
}


	
	
return 0;
}