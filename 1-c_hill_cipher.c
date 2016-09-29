#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void padding(char plaintext[], int n);
void hillencrypt(char plaintext[], int mat[][10], int n);

int main(){

//Length of matrix dimension
int i , j;
int n = 0;
int mat[10][10];

//Reads file in & error checks
FILE *fptr;
fptr=(fopen("hill.txt","r"));
if(fptr==NULL){
	printf("Error. Cannot find file.\n");
	exit(1);
}

//Starts at the first line of text file
fseek(fptr, 0L, SEEK_SET);

//Read size of matrix
fscanf(fptr, "%d", &n);
for(i=0; i<n; i++)
	for (j=0; j<n; j++)
		fscanf(fptr, "%d", &mat[i][j]);

//Read plaintext message
char plaintext[100];
fscanf(fptr, "%s", plaintext);
fclose(fptr);

//Call encrypt function and pass text & size

hillencrypt(plaintext, mat, n);
return 0;
}

//Padding with x
void padding(char plaintext[], int n){
	int i = 0;
	//get original length of plaintext
	int original = strlen(plaintext);
	//Pads
	int padding = (n - original%n)%n;
	int new = original + padding;

	for (i=original; i<new; i++){
		plaintext[i] = 'x';
	}
	plaintext[new] = '\0';
}

//Takes in plain text, matrix, and size of matrix
void hillencrypt(char plaintext[], int mat[][10], int n){
int i = 0;
int j, k;
char hillcipher[10+1];

padding(plaintext, n);

//Gets length of plaintext & loops through
while (i<strlen(plaintext)){
	for(j=0; j<n; j++){
		int key = 0;
		for (k=0; k<n; k++)
			key = (key+mat[j][k]*(plaintext[i+k]- 'a'))%26; // Rotation
		hillcipher[j] = (char)('a' + key);
	}
	hillcipher[n] = '\0';
	i += n;

	printf("%s", hillcipher);
}}
