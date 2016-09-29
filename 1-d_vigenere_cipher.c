#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <process.h>

void vigenereCipher(char *,char *);
void encipher();
void decipher();

int main()
{
     int choice;
     clrscr();
     //loop takes choice from user and calles appropriate function
     while(1)
     {
	  printf("\n1. Encrypt Text ");
	 // printf("\n2. Decrypt Text :");
	  printf("\n2. Exit ");
	  printf("\nEnter Your Choice : ");
	  scanf("%d",&choice);
	  fflush(stdin);
	  if(choice == 1)
	    encipher();
	  else if(choice == 2)
	    exit(0);
	 /* else if(choice == 2)
	       decipher();*/
	  else
	       printf("\nPlease Enter Valid Option.");
     }

     return(0);
}

void encipher()
{
     unsigned int i,j;
     char input[257],key[33];
     printf("\nEnter Text to be Encrypted [Max. 256 characters/ only alphabets]:");
     gets(input);
     printf("\nEnter Encryption Key [Max. 32 Characters/ only aphabets]:");
     gets(key);
     for(i=0,j=0;i<strlen(input);i++,j++)
     {
	  //repeat the key if you are at end of it.
	  if(j>=strlen(key))
	  {
	       j=0;
	  }
	  //actual logic -> character from input + character from key % 26 is encrypted charater
	  printf("%c",65+(((toupper(input[i])-65)+(toupper(key[j])-65))%26));
     }

}

