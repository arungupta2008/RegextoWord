#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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

void dotest(const char* const input)
{
    char* ex = expand(input);
    printf("input : '%s'\noutput: %s\n\n", input, ex);

    if (ex)
        free(ex);
}

int main (int argc, char *argv[])
{
	 printf("%s",expand("[a-z]"));
	//dotest("[%^&a-cA-R0-9]"); // from the original post
    //dotest("a-z or 0-9 or a-b-c or a-z0-9"); // from the original post
    //dotest("This is some e-z test in 5-7 steps; this works: a-b-c. This works too: b-k-c-e. Likewise 8-4-6"); // from my C++ answer
    //dotest("-x-s a-9 9- a-k-9 9-a-c-7-3"); // assorted torture tests

    return 0;
}