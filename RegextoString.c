#include<stdio.h>
#include <string.h>

//this is for malloc exit for now 
#include<stdlib.h>
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0


/* 
For taking input from command line and parsing and putting in to a buffer
*/
char *read_line (char *buf, size_t length, FILE *f){
/**** Read at most 'length'-1 characters from the file 'f' into
        'buf' and zero-terminate this character sequence. If the
        line contains more characters, discard the rest.
   */
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


int scanSpecialChar(char *input){
	int i = 0;
	while(input[i] != '\0'){
		//printf("\nout input[%d] = %c\t%d",i,input[i],input[i]);
		if( !((input[i]>47 && input[i]<58) || (input[i]>64 && input[i]<91)  || (input[i]>96 && input[i]<123) )){
			//printf("\ninput[%d] = %c",i,input[i]);
			return 0;
		}
		++i;
	}
	return 1;
}
int customized_Bracket_checker(char *input,int position,char bracket_type){
	if(bracket_type == 40){
		bracket_type = 41;
	}else if(bracket_type == 91){
		bracket_type = 93;
	}
	while(input[position] != '\0'){
		if(input[position] == bracket_type){
			printf("bracket Found");
			return position;
		}
		else if(input[position] == 92){
			++position;
		}
		++position;
	}
	return 0;
}
/* Function
it takes two strings initial and toadd and concatenate these two strings please enter with space 
for Example parsed_output("Arun ","Gupta")
output would be    Arun Gupta    Character array
*/
char *parsed_output(const char *initial,const char *toadd) {

    const size_t initialLength     = strlen(initial);
    const size_t to_beaddLength = strlen(toadd);
    const size_t totalLength = initialLength + to_beaddLength;
	char *const strBuf = malloc(totalLength + 1);
    if (strBuf == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(strBuf,initial);
    strcpy(strBuf + initialLength, toadd);
	return strBuf;

}


/*
Help Doc
//http://stackoverflow.com/questions/7985661/method-for-expand-a-z-to-abc-xyz-form
//http://stackoverflow.com/questions/5921609/what-is-predicate-in-c
I'm pretty sure I'm overstating the requirements, but

this should be an excellent example of how to do parsing in a robust fashion
use states in an explicit fashion
validate input (!)
this version doesn't assume a-c-b can't happen
It also doesn't choke or even fail on simple input like 'Hello World' (or (char*) 0)
it shows how you can avoid printf("%c", c) each char without using extraneous functions.
I put in some comments as to explain what happens why, but overall you'll find that the code is much more legible anyways, by

staying away from too many short-named variables
avoiding complicated conditionals with un-transparent indexers
avoiding the whole string length business: We only need max lookahead of 2 characters, and *it=='-' or predicate(*it) will just return false if it is the null character. Shortcut evaluation prevents us from accessing past-the-end input characters
ONE caveat: I haven't implemented a proper check for output buffer overrun (the capacity is hardcoded at 2048 chars). I'll leave it as the proverbial exercise for the reader

Last but not least, the reason I did this:

It will allow me to compare raw performance of the C++ version and this C version, now that they perform equivalent functions. Right now, I fully expect the C version to outperform the C++ by some factor (let's guess: 4x?) but, again, let's just see what suprises the GNU compilers have in store for us. More later Update turns out I wasn't far off: github (code + results)

input : 'a-z or 0-9 or a-b-c or a-z0-9'
output: 'abcdefghijklmnopqrstuvwxyz or 0123456789 or abc or abcdefghijklmnopqrstuvwxyz0123456789'

input : 'This is some e-z test in 5-7 steps; this works: a-b-c. This works too: b-k-c-e. Likewise 8-4-6'
output: 'This is some efghijklmnopqrstuvwxyz test in 567 steps; this works: abc. This works too: bcdefghijk. Likewise 45678'

input : '-x-s a-9 9- a-k-9 9-a-c-7-3'
output: '-stuvwx a-9 9- abcdefghijk-9 9-abc-34567'
*/
int alpha_range(char c) { return (((c>='a') && (c<='z'))|| ((c>='A') && (c<='Z'))); }
int digit_range(char c) { return (c>='0') && (c<='9'); }
char* expand(const char* s)
{
	
    char buf[2048];
	char *space = " ";
    const char* in  = s;
    char* out = buf;
	*out++ = *space;
		  		
    // parser state
    int (*predicate)(char) = 0; // either: NULL (free state), alpha_range (in alphabetic range), digit_range (in digit range)
    char lower=0,upper=0;       // tracks lower and upper bound of character ranges in the range parsing states

    // init
    *out = 0;

    while (*in)
    {
		//printf(" \nwhile (*in)  %c\n",*in);
        if (!predicate)
        {
            // free parsing state
            if (alpha_range(*in) && (in[1] == '-') && alpha_range(in[2]))
            {
				//printf(" \n(in[1] == '-')  %c\n",in[1]);
				//printf(" \nalpha_range(in[2]) %c\n",in[2]);
				//printf(" \nwhile (*in)%c\n",*in);
                lower = upper = *in++;
                predicate = &alpha_range;
            }
            else if (digit_range(*in) && (in[1] == '-') && digit_range(in[2]))
            {
                lower = upper = *in++;
                predicate = &digit_range;
            } 
            else {
				*out++ = *space;
				*out++ = *in;
			}//here *in means value pointed by *in is putted in to *out++ 
        } else
        { 
            // in a range
			//printf(" \n(*in < lower) lower = *in;  %c\n",*in);
            if (*in < lower) lower = *in;
            if (*in > upper) upper = *in;
			//printf(" \n(in[1] == '-' && predicate(in[2]))  |%c|     |%c|\n",in[1],in[2]);
            if (in[1] == '-' && predicate(in[2])) 
                in++; // more coming
            else
            {
                // end of range mode, dump expansion
                char c;
				*out++ = *space;
                for (c=lower; c<=upper; ){
					*out++ = c++;
					*out++ = *space;
				}
                predicate = 0;
            }
        }
        in++;
    }

    *out = 0; // null-terminate buf
    return strdup(buf);
}
/*
For Substring with start position and end position
*/

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


/*
implementing [ ] set of characters
[AEIOUY] or  (A|E|I|O|U|Y) or  [A-Z] but it's not allowd 
Wrong  (Arun|Ankush) means either Arun or Ankush 
but [Arun] means substring containing  A or r or u or n

*/
char *parseBracket(const char *input , int Start_position, int End_position){
	if(input[Start_position] == '['){ 
		// 45 -
		// [ 				A-Z 			]
		//Start_position			End_position
		//int i = input[Start_position+1];
		//char *intermediate_output
		printf("\n\n\n****\n%s\n*****\n\n",expand(substring(input,Start_position,End_position)));
		//Start from here 
	}
	char *bracket_parced_output = "arun";
	return bracket_parced_output;
}


main(){
/*
http://www.cs.tut.fi/~jkorpela/perl/regexp.html

http://www.troubleshooters.com/codecorn/littperl/perlreg.htm

http://www.troubleshooters.com/codecorn/littperl/perlreg.htm

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

Goal ::

Example 1.
^(0[1-9]|1[012])[-/.](0[1-9]|[12][0-9]|3[01])[- /.]((19|20)\d\d)$

Let's for above Regex answer should be like that 

Start from the Left and by  telling number of digits (two three ) then after that if we have any fixed char then show that then carry on like this 

let's for above example 
Start with Exact Two Digits then [- or / or .] Exact Two digits [- or / or .] Exact Four Digits End
```
start with (01 to 09 or 10 or 11 or 12) and [- or / or . ] and  (01 to 09 or 10 to 19 or 20 to 29 or 30 or 31) and [- or / or .] and ((19 or 20)and 00-99)  
if connected(we are able to connect things) then 
start with (01 to 12) and [- or / or .] and (01 to 31) and [- or / or .] and end with(1900-2099)
```
Example :
10-12-1201

Range :
$1 --> 01 to 12
$2 --> 01 to 31
$3 --> 1900 to 2099



Example 2.

(i.*s)
String input --> mississippi

Solution :: ississ
```
Solution start with "i" then followed by any character except ("/n" new line) then end with 0 or more "s"
Example : 
```
it will take longest matching string.

Example 3.

(B|b)ill (C|c)linton
```
contains substring like Bill or bill or Clinton or clinton
```


Example 4.

(Clinton|Bush|Reagan)


Example 5.
[A-Z]
```
A-Z
```
Example 6. 

if($string =~ /[^AEIOUYaeiouy]/){print "This string contains a non-vowel"}
```
String not containing any these characters A E I O U Y a e i o u y
```
Except this 

Example 7.
^[A-E]

Example 8. 

^\S+\s+(Clinton|Bush|Reagan)

Example 9.

[\)\s\-]\d{3}-\d{4}[\s\.\,\?]

Example 10.
Most difficult
.{28}(\d\d)-(\d\d)-(\d\d).{8}(.+)$

Example 11.
	
*/
/*
Final Out put String
*/
char *final_output_data;

/* *************************************************
//	Taking Input
//************************************************* */
	char user_input[255];
	//fgets(user_input, 255, stdin);
	//printf("|%s|",user_input);
	//it also takes the \n as a input 
char *input = read_line (user_input, 255, stdin);
	printf("\n*****%s*****\n",user_input);
	printf("\n*****%s*****\n",input);
	//char input_ = '\0';
	//printf("\nNull == |%c|\n",input_);
//*************************************************
//	Taking Input End (max Regex input size is 254 byte or characters )
//*************************************************	
// For Testing purpose
//printf("\n\n\n%s\n\n\n",parsed_output("  Arun  ","Gupta"));
//printf("\n\n\n%s\n\n\n",parseBracket("[a-c]",0,4));
//printf("\n\n\n%s\n\n\n",expand("[a-z]"));
if(scanSpecialChar(input)){
	printf("\nRegex Returns true if given String contains this sub string \"%s\"\n",parsed_output("",input));
}else{
	printf("\nGoing to handle special Char first\n");
	//is ^ char Present ?
	if(input[0] == '^'){
		int end_position;
		if(input[1] == 40 || input[1] == 91){
			printf("\nBracket Type %d || %c ",input[1],input[1]);
			end_position = customized_Bracket_checker(input,1,input[1]);
			if(end_position != 0){
				printf("\nEnd bracket is found at position %d",end_position);
				parseBracket(input ,1, end_position);
				//printf("Parsed Braket values\n");
			}else{
				printf("\nBracket End is not found");
			}
		}
		if(input[end_position+1] == 36){
			printf("Regex Contains this regex only");
		}
	}
	//is $ char present ?
}





	
	
return 0;
}