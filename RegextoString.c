#include<stdio.h>
#include <string.h>

//this is for malloc exit for now
#include<stdlib.h>
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define DOT_VALIDITY if((dot+1)==strlen(input)){ return final_output_data;}
#define COPY tmp_[1] = '\0'; tmp_[0] = input[dot];
#define YES 1
#define NO 0


//#define COPY strcpy(tmp_,out_int);

//All Functions
// If this is not defined this was creating error "Conflicting types for substring"
char *parseBracket(const char *input , int Start_position, int End_position);
char *substring(const char *string, int Start_postion, int End_position);
int customized_Bracket_checker(const char *input,int position,char bracket_type_open);
char *parseInput(const char *input);
//strlen gives length of characters in bytes dot+1 is taken
/*
Global Variables
*/
//For Space
char *space = " ";
char *or = " or ";
//char final_output_data[2048];

/*
	For Exit from The system if not failure.
*/
void exit_(int val){
	if(val == EXIT_FAILURE){
		printf("\n\nThere is some error in Regex\n\n");
		exit(EXIT_FAILURE);
	}/*else if(val == EXIT_SUCCESS){
		printf("\n\n\n*****\n%s\n*****\n\n\nThank you !! for Using this Regex \n\n",final_output_data);
		exit(EXIT_SUCCESS);
	}*/
}
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


int scanSpecialChar(const char *input){
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
int customized_Bracket_checker_(const char *input,int position,char bracket_type_open){
	int count = 0;
	printf("\n\ndsfsf");
	++position;
	while(input[position] != '\0'){
		/*if(input[position] == '|'){
			return position;
		}*/
		if(input[position] == '(' || input[position] == '[' ){
			position =  customized_Bracket_checker(input,position,input[position]);
			printf("\n End position |%d|",position	);
			printf("\nCurrent Pointer at customized_Bracket_checker_ |%c|",input[position]);
		}
		++position;
		if((input[position] == ')' || input[position] == '|') && count == 0){
			printf("\nCurrent Pointer at customized_Bracket_checker_  current position |%c|",input[position-1]);
			return position-1;
		}
	}
}
int customized_Bracket_checker(const char *input,int position,char bracket_type_open){
	char bracket_type_closed;
	int count=0;
	if(bracket_type_open == '('){
		bracket_type_closed = ')';
	}else if(bracket_type_open == '['){
		bracket_type_closed = ']';
	}
	while(input[position] != '\0'){
		if(input[position] == bracket_type_open){
			++count;
			printf("\nOpen Bracket Found");
			//return position;
		}
		else if(input[position] == '\\'){
			++position;
		}else if(input[position] == bracket_type_closed){
			--count;
			if(count ==0){
				return position;
			}
		}
		++position;
	}
	return 0;
}
/* Function
it takes two strings initial and toadd and concatenate these two strings please enter with space
for Example parsed_output("Arun ","Gupta")
this function expectes either Strings ("arun") or either pointer pointing to any string not
parsed_output(out,input)
not
parsed_output(*out,*input) here out and input are pointing to strings
output would be    Arun Gupta    Character array
*/
char *parsed_output(const char *initial,const char *toadd) {
	printf("\nFirst String to add :: |%s|",initial);
	printf("\nSecond String to add :: |%s|",toadd);
    const size_t initialLength     = strlen(initial);
    const size_t to_be_adddLength = strlen(toadd);
    const size_t totalLength = initialLength + to_be_adddLength;
	char *const strBuf = malloc(totalLength + 1);
    if (strBuf == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(strBuf,initial);
    strcpy(strBuf + initialLength, toadd);
    strcpy(initial,strBuf);
	return strBuf;

}
/*
	Validates Character-Character
	Ex. A-z  it will return true if any start_character < Ens character  only
*/
void Check_range_Validity(const char* s,int dot){
	printf("\nAt Check Validity Function with String |%s| with position %d",s,dot);
	int i=0,j=2;
	// for case \[-z
	if(*(s+dot) == '\\'){
		++i;
		// for case \[-\]
		if(*(s+i+j+dot) == '\\'){
			j = j+i+1;
		}
	// for case A-\]
	}else if(*(s+j+dot) == '\\'){
		j = j+1;
	}
	printf("\n*(s+i+dot) :::|%c|\t *(s+j+dot) :::: |%c|%d|",*(s+i+dot),*(s+j+dot),*(s+j+dot));
	if(*(s+i+dot)>*(s+j+dot)) exit_(EXIT_FAILURE);
	//   if [9-1]or for all or  a-Z||           case Z-a
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
int alpha_range(char c) { printf("\nCharacter ::|%c|",c);return (((c>='a') && (c<='z'))|| ((c>='A') && (c<='Z'))); }
int digit_range(char c) { return (c>='0') && (c<='9'); }
char* expand(const char* s)
{
	printf("\nValues at expand :: |%s|",s);
	printf("\nString At \" expand(const char* s)\"\t|%s|",s);
    char buf[2048];
    const char* in  = s;
    char* out = buf;
	*out++ = *space;
	int dot = 0;

    // parser state
    int (*predicate)(char) = 0; // either: NULL (free state), alpha_range (in alphabetic range), digit_range (in digit range)
    char lower=0,upper=0;       // tracks lower and upper bound of character ranges in the range parsing states

    // init
    *out = 0;
    while (*in)
    {
		printf(" \nwhile (*in)  %c\n",*in);
		if(*in == '\\'){
			++in;
			++dot ;
		}
        if (!predicate)
        {
				printf("\npredicate ::|%c|",predicate);
				// free parsing state
				if (in[1] == '-' && in[2] != '\0')
				{

					printf(" \n(in[1] == '-')  %c\n",in[1]);
					printf(" \nalpha_range(in[2]) |%c|%d|\n",in[2],in[2]);
					Check_range_Validity(s,dot);
					printf(" \nwhile (*in)%c\n",*in);
					lower = upper = *in++;
					dot++;
					predicate = &alpha_range;
				}
				//else if (digit_range(*in) && (in[1] == '-') && digit_range(in[2]))
				//{
				//	Check_range_Validity(s,dot);
				//	lower = upper = *in++;
				//	++dot;
				//	predicate = &digit_range;
				//}
				else {
					*out++ = *space;
					*out++ = *in;
				}//here *in means value pointed by *in is putted in to *out++
		}else{
			// in a range
			printf(" \n(*in < lower) lower = *in;  %c\n",*in);
			if (*in < lower) lower = *in;
			if (*in > upper) upper = *in;
			printf(" \n(in[1] == '-' && predicate(in[2]))  |%c|     |%c|\n",in[1],in[2]);
			if (in[1] == '-' && predicate(in[2])) {
				in++;
				dot++;// more coming
			}else
			{
				// end of range mode, dump expansion
				char c;
				*out++ = *space;
				for (c=lower; c<=upper; ){
					printf("%c",c);
					*out++ = c++;
					*out++ = *space;
				}
				predicate = 0;
			}
		}
        in++;
		dot++;
    }
	printf("\n|%s|\n",buf);
    *out = 0; // null-terminate buf
    return strdup(buf);
}

/*
	Parses lower bracket :D  Example      (Arun|sdfdsf|sfsdf|adfsdf)
	 [ Arun sdfdsf sfsdf adfsdf ]
*/
char* parseBracket_lower(const char* s){
	char buffer[2048];
    const char* in  = s;
    char* out = buffer;
    int dot=0;
	int end_position=0;
	printf("\n\n|%s|\n\n",s);
	printf("\n Going to parseInput again String  :: |%c| |%c|",*in,*(in+strlen(s)-1));
	parsed_output(&buffer," ");
	return parsed_output(&buffer,parseInput(substring(s,1,(strlen(s)-1-1))));
	*out++ = '[';
	//printf("\nParsed output for internal brackets :: |%s|",*out);
	*out++ = *space;
	//printf("\nParsed output for internal brackets :: |%s|",*out);
	//parsed_output(&buffer," [");
	printf("\nParsed output for internal brackets by buffer:: |%s|",buffer);
	++in;
	while (*in){
		printf("\n parseBracket_lower for Char |%c|",*in);
		if(*in == '('){
			end_position = customized_Bracket_checker(in,0,*in);
			printf("\nEnd Position at parseBracket_lower |%d|",end_position);
			printf("\nParsed output for internal brackets before concatanation :: |%s|",out);
			//printf("\nOut Of Substring at parseBracket_lower  |%s|",substring(in,0,end_position));
			parsed_output(&buffer,parseBracket(in ,0, end_position));
			printf("\nParsed output for internal brackets by out :: |%s| ",out);
			printf("\nParsed output for internal brackets by buffer:: |%s|",buffer);
			//strcpy(buffer,out);
			printf("\nSize of out :: |%d|",strlen(out));
			printf("\nLast Char :: |%c|",buffer[strlen(out)-1]);
			while(end_position != 0){
				++in;
				end_position--;
			}
			printf("\nCharacter pointed by out :: |%c| ",*out);
			printf("\nCharacter pointed by out :: |%c| ",*(out+strlen(out)-1));
			out = (out+strlen(out)-1);
			printf("\nCharacter pointed by out :: |%d| ",&(*out));
			printf("\nCharacter pointed by buffer :: |%d| ",&(buffer[strlen(out)-1]));
			++in;
			out++;
		}else if(*in == '\\'){
			*out++ = *(++in);
			++in;
		}else if(*in == '|'){
			*out++ = *space;
			*out++ = 'o';
			*out++ = 'r';
			*out++ = *space;
			++in;
		}else{
			*out++ = *in;
			++in;
		}
		if(*in == ')'){
			break;
		}
	}
	*out++ = *space;
	*out++ = ']';
	*out++ = '\0';
	printf("\nReply by  parseBracket_lower:: |%s|",out);
	*out = 0; // null-terminate buf // use this line as default it csn reduce the lines

    return strdup(buffer);
}

/*
For Substring with start position and end position
*/
char *substring(const char *string, int Start_postion, int End_position)
{
	printf("\nValues at substring with start %d  and  End position %d:: |%s|",Start_postion,End_position,string);
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
	printf("\nOutput of Substring |%s|",pointer);
	return pointer;
}


/*
implementing [ ] set of characters
[AEIOUY] or  (A|E|I|O|U|Y) or  [A-Z] but it's not allowd
Wrong  (Arun|Ankush) means either Arun or Ankush
but [Arun] means substring containing  A or r or u or n

*/
char *parseBracket(const char *input , int Start_position, int End_position){
	char except[25] = "Except these Characters ";
	char buf[2048];
    char* out = buf;
	printf("\nValues at parseBracket with start %d  and  End position %d:: |%s|",Start_position,End_position,input);
	if(input[Start_position] == '['){
		// 45 -
		// [ 				A-Z 			]
		//Start_position			End_position
		//int i = input[Start_position+1];
		//char *intermediate_output
		//printf("\n\n\n****\n%s\n*****\n\n",expand(substring(input,Start_position,End_position)));
		parsed_output(&buf,"[ ");
		printf("\n|%s|\n",buf);
		if(input[Start_position+1] == '^'){
			printf("\nNegation found");
			parsed_output(&buf,&except);
			printf("\nOutput of parsed_output at parseBracket |%s|",out);
			parsed_output(&buf,expand(substring(input,Start_position+2,End_position-1)));
		}else{
			// Here () is detected
			parsed_output(&buf,expand(substring(input,Start_position+1,End_position-1)));
		}
		printf("\n|%s|\n",buf);
		out = parsed_output(&buf,"] ");
		//*out = 0; // null-terminate buf
		printf("\n|%s|\n",buf);
		//return strdup(buf);
		return out;
	}
	if(input[Start_position] == '('){
		// 45 -
		//(A|B|C|D|)
		//Start_position			End_position
		//int i = input[Start_position+1];
		//char *intermediate_output
		//printf("\n\n\n****\n%s\n*****\n\n",expand(substring(input,Start_position,End_position)));
		return parseBracket_lower(substring(input,Start_position,End_position));
	}
}

char *parseInput(const char *input){
	//printf("\nparseInput(const char *input)   %s\n",input);
	//char *input_tmp = strdup(buf);
	//here we are going to implement the behaviour or PerlREGEX
	//char buf[2048];
	char final_output_data[2048];
	int change = NO;
	//char *space = " ";
        char* out = final_output_data;
	*out++ = *space;
	char tmp_[2],*out_int;
	//strcpy (str2,str1);
	if(scanSpecialChar(input)){
	printf("\nRegex Returns true if given String contains this sub-string \"%s\"\n",parsed_output(out,input));
	return input;
	}else{
		int dot = 0;
		printf("\nGoing to handle special Char first\n");
		while(*input){
			out_int = NULL;
			printf("\nCurrent Charecter |%c|\n", input[dot]);
			//parseInput(input);
			//is ^ char Present ?
			if(input[dot] == '^'){
				parsed_output(&final_output_data," Substring starts with ");
				//out = final_output_data;
				//printf("\n At ^  %s",parsed_output(out," Substring starts with "));
				printf("\n At ^  |%s|\n",&out);
				DOT_VALIDITY;
				++dot;
			}
			if(input[dot] == '(' || input[dot] == '['){
				int end_position;
				out = parsed_output(&final_output_data," and ");
				printf("\nBracket Type %c ",input[dot]);
				end_position = customized_Bracket_checker(input,dot,input[dot]);
				if(end_position != 0){
					printf("\nEnd bracket is found at position %d",end_position);

					//printf("\n\n\n****\n%s\n*****\n\n",parseBracket(input ,dot, end_position));
					out = parsed_output(&final_output_data,parseBracket(input ,dot, end_position));
					//printf("\n\n\n****\n%s\n*****\n\n",out);
					//final_output_data = out;
					//strcpy(final_output_data,out);
					//start from here
					//printf("\n\n\n****\n%s\n*****\n\n",final_output_data);
					//printf("Parsed Braket values\n");
				}else{
					printf("\nEnd bracket is not found");
					exit_(EXIT_FAILURE);
				}
				dot = end_position;
				DOT_VALIDITY;
				++dot;

			}if(input[dot] == '|' ){
				out = parsed_output(&final_output_data," or ");
				change = YES;
				//strcpy(out_int,&or);
				//int end_position;
				//end_position = customized_Bracket_checker_(input,dot,input[dot]);
				//out = parsed_output(&final_output_data,parseInput(substring(input,dot+1,end_position)));
			}
			//if String is simple String
			if(input[dot] == '\\')   // here "\\" means it will check in String whether it have  something \ in the string :D remmeber
				++dot;
			//printf("\nCurrent Position %d :: current Character  %c\n",dot,input[dot]);
			//tmp = &input[dot];
			printf("\nfdgdfg");
			//if(out_int == NULL)
			//strcpy(out_int,input[dot]);
			//printf("\nfdgdfg");
			if(change == NO){
				COPY;
			out = parsed_output(out,&tmp_);
			strcpy(final_output_data,out);
			}
			change = NO;
			DOT_VALIDITY;
			++dot;
			/*if(input[dot] == 36){
				printf("Regex Contains this regex only");
			}*/
			//is $ char present ?
			//End of File (EOF)
			if(input[dot] == '\0'){
				break;
			}
		}
		//strcpy(final_output_data,out);
		//exit_(EXIT_SUCCESS);
		return final_output_data;


	}
}

main(){
/*
http://www.cs.tut.fi/~jkorpela/perl/regexp.html

http://www.troubleshooters.com/codecorn/littperl/perlreg.htm

http://www.troubleshooters.com/codecorn/littperl/perlreg.htm


http://regexpal.com/
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

/* *************************************************
//	Taking Input
//************************************************* */
	char user_input[255];
	//fgets(user_input, 255, stdin);
	//printf("|%s|",user_input);
	//it also takes the \n as a input
	char *input = read_line (user_input, 255, stdin);
	if(strlen(input)==0){
		printf("\nPlease Enter The Correct String \n");
		exit(EXIT_FAILURE);
	}
	printf("\n*****%s*****\n",user_input);
	printf("\n*****%s*****\n",input);
	//char input_ = '\0';
	//printf("\nNull == |%c|\n",input_);
//*************************************************
//	Taking Input End (max Regex input size is 254 byte or characters )
//*************************************************
// For Testing purpose
//input = parsed_output(input,"  Gupta");
//printf("\n\n\n%s\n\n\n",input);
//printf("\n\n\n%s\n\n\n",parseBracket("[a-c]",0,4));
//printf("\n\n\n%s\n\n\n",expand("[a-z]"));

//Test cases for customized_Bracket_checker_
//printf("\n\nasda\t%d\n\n",customized_Bracket_checker_("Arun|janana|",4,'|'));
//printf("\n\nasda\t%d\n\n",customized_Bracket_checker_("Arun|janana(dfdsf|DSfdsf)|",4,'|'));
//printf("\n\nasda\t%d\n\n",customized_Bracket_checker_("Arun|janana(dfdsf|DSfdsf)dsfdsf|",4,'|'));
//printf("\n\nasda\t%d\n\n",customized_Bracket_checker_("Arun|janana(dfdsf|DSfds[|]fdfdsfsdf)|(dfsdf)sdfdsfdsf|",4,'|'));
printf("\nOutput Result\n\n\n%s\n\n\n\n",parseInput(input));
printf("**************************");
printf("\nWelcome to Regex to Word");
printf("\n**************************");
printf("\n1. Everything inside the [] only one charected can by used");
printf("\n	For Ex. [D A Y]");
printf("\n	Only one charecter can be picked ");
printf("\n2. \"or\" and \"and\" are just used for your understanding");
printf("\n**************************");
printf("\nPlease if you wanna  give me some feed back mail me on mail@arungupa.co.in\n");




// to Test
//  ^[ariunA-Z]  in the link
// here this means starts with any of these charecters
//for Example either A or B or C or D any but only one charecters
return 0;
}


