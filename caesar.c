#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

bool is_valid_key(string s1);

void encrypt(string s2, string ciphertext, int k);

string s;




int main(int argc, string argv[])
{
    if(argc!=2 || !is_valid_key(argv[1]))
    {
        printf("Usage: ./caesar key\n");

        return 1;
        }
        else
        {
             s=get_string("Secret Message: ");

            int k= atoi(argv[1]);

            int n= strlen(s);

            char ciphertext[n+1];

            encrypt(s, ciphertext, k);

            printf("ciphertext:%s\n", ciphertext);

            return 0;
        }
}

        void encrypt(string s2, string ciphertext, int k)
        {
            int i;

          int n=strlen(s2);
          for( i=0; i<n ; i++){

              char ch= s2[i];

              if(isalpha(ch)){

                  char temp= tolower(ch);

                  int pi= temp -'a';

                  char ci= ((pi+k)%26) + 'a';

                  ciphertext[i]= islower(ch)? ci : toupper(ci);
                  }
                  else{
                      ciphertext[i]=ch;
                  }
          }
          ciphertext[i]='\0';

        }



 bool is_valid_key(string s1)
 {
     for(int i=0; i< strlen(s1); i++){

         char ch=s1[i];

         if(!isdigit(ch)){

             return false;

             }
     }
             return true;

     }


