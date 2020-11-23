#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>
#include<math.h>

// take input from user
// find number of letters by assuming each word as an array refer ctype.h
// find number of words by finding no. of spaces and then +1
// find number of sentences by counting no. of periods,exclaimation marks and question marks
// input values into CL index formula and round off
//if grade<1 then print below grade 1 and if grade>16 then print grade 16+ otherwise print the value of grade

int get_index(string s);

int main(void){

  string text=get_string("Text:");

  int index=get_index(text);

  if( index<1){
    printf(" Before Grade 1\n");
}
if (index>16){

    printf("Grade 16+\n");
}
else {

    printf("Grade %i\n", index);
}
}

int get_index(string s)
{
    int letters=0,sentences=0,words=0;
int i;
    for(i=0; i< strlen(s); i++){
        char ch=s[i];
        if(isalpha(ch)){
            letters++;
        }

        if(isspace(ch)){

            words++;
        }

        if(ch=='.' || ch=='!' || ch=='?'){

            sentences++;
        }
    }
    words++;
    float L= letters*100.0f/words;
    float S= sentences*100.0f/words;

   return round( 0.0588 * L - 0.296 * S - 15.8);

}