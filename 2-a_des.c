#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>

void hex_to_bin(char *,char *);
char* bin_to_hex(char *);
void permutation(char *,char *);
void make_half(char *,char *,char *);
void single_shift(char *,char *);
void double_shift(char *,char *);
void make_key(char *,char *,char *);
void permutation_32(char *,char *);
void permutation_48(char *,char *);
void permutation_64(char *,char *,char *);

void des_round(char *,char *,char *,char *,char *,char *,char *);
void des_round_decry(char *,char *,char *,char *,char *,char *,char *);
void copy(char *,char *);
void permut_48(char *,char *);
void xor(char *,char *,char *);
void xor_32(char *,char *,char *);
void common_permutation(char *,char *);
void hex_to_plain(char *,char *,int);
int switch_case(char );
char SB[32];

char *bin[]={
"0000",
"0001",
"0010",
"0011",
"0100",
"0101",
"0110",
"0111",
"1000",
"1001",
"1010",
"1011",
"1100",
"1101",
"1110",
"1111"
};

char hex[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

int PC1[8][7]= { 57,49,41,33,25,17,9,
1,58,50,42,34,26,18,
10,2,59,51,43,35,27,
19,11,3,60,52,44,36,
63,55,47,39,31,23,15,
7,62,54,46,38,30,22,
14,6,61,53,45,37,29,
21,13,5,28,20,12,4
};

int PC2[8][6]={ 14,17,11,24,1,5,
3,28,15,6,21,10,
23,19,12,4,26,8,
16,7,27,20,13,2,
41,52,31,37,47,55,
30,40,51,45,33,48,
44,49,39,56,34,53,
46,42,50,36,29,32
};

int IP[8][8]={ 58,50,42,34,26,18,10,2,
60,52,44,36,28,20,12,4,
62,54,46,38,30,22,14,6,
64,56,48,40,32,24,16,8,
57,49,41,33,25,17,9,1,
59,51,43,35,27,19,11,3,
61,53,45,37,29,21,13,5,
63,55,47,39,31,23,15,7};

int E_bit[8][6]={ 32,1,2,3,4,5,
4,5,6,7,8,9,
8,9,10,11,12,13,
12,13,14,15,16,17,
16,17,18,19,20,21,
20,21,22,23,24,25,
24,25,26,27,28,29,
28,29,30,31,32,1};

char *look_up[]={
"00",
"01",
"10",
"11"};

int sb_permutation[8][4]={
16,7,20,21,
29,12,28,17,
1,15,23,26,
5,18,31,10,
2,8,24,14,
32,27,3,9,
19,13,30,6,
22,11,4,25};

int s1[4][16]={
14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13};

int s2[4][16]={
15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9};

int s3[4][16]={
10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12};

int s4[4][16]={
7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14};

int s5[4][16]={
2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3};

int s6[4][16]={
12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
10,15,4,2,7,12,9,5,6,1,12,14,0,11,3,8,
9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13};

int s7[4][16]={
4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12};

int s8[4][16]={
13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};

int ip_inverse[8][8]={
40,8,48,16,56,24,64,32,
39,7,47,15,55,23,63,31,
38,6,46,14,54,22,62,30,
37,5,45,13,53,21,61,29,
36,4,44,12,52,20,60,28,
35,3,43,11,51,19,59,27,
34,2,42,10,50,18,58,26,
33,1,41,9,49,17,57,25
};

void main()
{
char input[200],initial_hex[400];
int i,j,k=0,len,r,x,m,temp;
int d,e,f;
char hex_arr[25][16];

char input_hex[16],input_bin[64];
char key_hex[16]={'1','3','3','4','5','7','7','9','9','B','B','C','D','F','F','1'};
char key_bin[64],key_PC1[56];
char ch,*decryption,*encryption,encryption_final[400],decryption_final_hex[400],decryption_final_plain[200];
char encrypted[64],decrypted[64],encry_permut[64],decry_permut[64];
int length,p=-1,q=-1;

char C0[28],D0[28],
C1[28],D1[28],CD1[56],
C2[28],D2[28],CD2[56],
C3[28],D3[28],CD3[56],
C4[28],D4[28],CD4[56],
C5[28],D5[28],CD5[56],
C6[28],D6[28],CD6[56],
C7[28],D7[28],CD7[56],
C8[28],D8[28],CD8[56],
C9[28],D9[28],CD9[56],
C10[28],D10[28],CD10[56],
C11[28],D11[28],CD11[56],
C12[28],D12[28],CD12[56],
C13[28],D13[28],CD13[56],
C14[28],D14[28],CD14[56],
C15[28],D15[28],CD15[56],
C16[28],D16[28],CD16[56];

char L0[32],R0[32],ER0[48];
char K1[48],L1[32],R1[32],ER1[48],F1[48],
K2[48],L2[32],R2[32],ER2[48],F2[48],
K3[48],L3[32],R3[32],ER3[48],F3[48],
K4[48],L4[32],R4[32],ER4[48],F4[48],
K5[48],L5[32],R5[32],ER5[48],F5[48],
K6[48],L6[32],R6[32],ER6[48],F6[48],
K7[48],L7[32],R7[32],ER7[48],F7[48],
K8[48],L8[32],R8[32],ER8[48],F8[48],
K9[48],L9[32],R9[32],ER9[48],F9[48],
K10[48],L10[32],R10[32],ER10[48],F10[48],
K11[48],L11[32],R11[32],ER11[48],F11[48],
K12[48],L12[32],R12[32],ER12[48],F12[48],
K13[48],L13[32],R13[32],ER13[48],F13[48],
K14[48],L14[32],R14[32],ER14[48],F14[48],
K15[48],L15[32],R15[32],ER15[48],F15[48],
K16[48],L16[32],R16[32],ER16[48],F16[48];

//clrscr();

/******************* Input Plain Text *********************/

strcpy(input,"apple");
printf("Plain Text : %s",input);
len = strlen(input);

for(i=0;i<len;i++)
{
while(input[i]!=0)
{
r=input[i]%16;
input[i]=input[i]/16;
if(r>9)
{
x=r-10;
r=65+x;
initial_hex[k]=r;
}
else
initial_hex[k]=r+48;
k++;
}
}
for(i=0;i<k;i=i+2)
{
temp=initial_hex[i];
initial_hex[i]=initial_hex[i+1];
initial_hex[i+1]=temp;
}



d=k/16;
e=k%16;
f=0;

for(i=0;i<=d;i++)
{
if(i<d)
{
for(j=0;j<=15;j++)
hex_arr[i][j]=initial_hex[f++];
}
else if(k%16==0)
break;
else
{
for(j=0;j<=15;j++)
{
if(j<e)
hex_arr[i][j]=initial_hex[f++];
else
{
hex_arr[i][j]='2';
hex_arr[i][++j]='0';
}
}
}

}
if(k%16!=0)
d++;


hex_to_bin(key_hex,key_bin);

printf("\nKey in Hexadecimal used for encryption : ");
for(i=0;i<16;i++)
printf("%c",key_hex[i]);


for(m=0;m<d;m++)
{

for(i=0;i<16;i++)
input_hex[i]=hex_arr[m][i];

/******************* Plain Text in Binary *****************/
hex_to_bin(input_hex,input_bin);


/******************* First Round of Permutation *****************/
permutation(key_bin,key_PC1);


make_half(key_PC1,C0,D0);

/******************** Shifting Begins *********************/
single_shift(C0,C1);
single_shift(D0,D1);

single_shift(C1,C2);
single_shift(D1,D2);

double_shift(C2,C3);
double_shift(D2,D3);

double_shift(C3,C4);
double_shift(D3,D4);

double_shift(C4,C5);
double_shift(D4,D5);

double_shift(C5,C6);
double_shift(D5,D6);

double_shift(C6,C7);
double_shift(D6,D7);

double_shift(C7,C8);
double_shift(D7,D8);

single_shift(C8,C9);
single_shift(D8,D9);

double_shift(C9,C10);
double_shift(D9,D10);

double_shift(C10,C11);
double_shift(D10,D11);

double_shift(C11,C12);
double_shift(D11,D12);

double_shift(C12,C13);
double_shift(D12,D13);

double_shift(C13,C14);
double_shift(D13,D14);

double_shift(C14,C15);
double_shift(D14,D15);

single_shift(C15,C16);
single_shift(D15,D16);

/******************** Shifting Ends *********************/


/*************** 16 Keys Generation Begins **************/

make_key(C1,D1,CD1);
permutation_48(CD1,K1);

make_key(C2,D2,CD2);
permutation_48(CD2,K2);

make_key(C3,D3,CD3);
permutation_48(CD3,K3);

make_key(C4,D4,CD4);
permutation_48(CD4,K4);

make_key(C5,D5,CD5);
permutation_48(CD5,K5);

make_key(C6,D6,CD6);
permutation_48(CD6,K6);

make_key(C7,D7,CD7);
permutation_48(CD7,K7);

make_key(C8,D8,CD8);
permutation_48(CD8,K8);

make_key(C9,D9,CD9);
permutation_48(CD9,K9);

make_key(C10,D10,CD10);
permutation_48(CD10,K10);

make_key(C11,D11,CD11);
permutation_48(CD11,K11);

make_key(C12,D12,CD12);
permutation_48(CD12,K12);

make_key(C13,D13,CD13);
permutation_48(CD13,K13);

make_key(C14,D14,CD14);
permutation_48(CD14,K14);

make_key(C15,D15,CD15);
permutation_48(CD15,K15);

make_key(C16,D16,CD16);
permutation_48(CD16,K16);

/*************** 16 Keys Generation Ends **************/

permutation_64(input_bin,L0,R0);

/************ 16 Rounds of Encryption *****************/

des_round(L1,R1,L0,R0,ER0,K1,F1);

des_round(L2,R2,L1,R1,ER1,K2,F2);
des_round(L3,R3,L2,R2,ER2,K3,F3);
des_round(L4,R4,L3,R3,ER3,K4,F4);
des_round(L5,R5,L4,R4,ER4,K5,F5);
des_round(L6,R6,L5,R5,ER5,K6,F6);
des_round(L7,R7,L6,R6,ER6,K7,F7);
des_round(L8,R8,L7,R7,ER7,K8,F8);
des_round(L9,R9,L8,R8,ER8,K9,F9);
des_round(L10,R10,L9,R9,ER9,K10,F10);
des_round(L11,R11,L10,R10,ER10,K11,F11);
des_round(L12,R12,L11,R11,ER11,K12,F12);
des_round(L13,R13,L12,R12,ER12,K13,F13);
des_round(L14,R14,L13,R13,ER13,K14,F14);
des_round(L15,R15,L14,R14,ER14,K15,F15);
des_round(L16,R16,L15,R15,ER15,K16,F16);

for(i=0;i<32;i++)
{
encrypted[i]=R16[i];
encrypted[i+32]=L16[i];
}
common_permutation(encrypted,encry_permut);

encryption=bin_to_hex(encry_permut);


for(i=0;i<16;i++)
{
encryption_final[++p]=*(encryption+i);

}


/****************** 16 Rounds of Decryption ****************/

des_round_decry(L16,R16,L15,R15,ER15,K16,F16);
des_round_decry(L15,R15,L14,R14,ER14,K15,F15);
des_round_decry(L14,R14,L13,R13,ER13,K14,F14);
des_round_decry(L13,R13,L12,R12,ER12,K13,F13);
des_round_decry(L12,R12,L11,R11,ER11,K12,F12);
des_round_decry(L11,R11,L10,R10,ER10,K11,F11);
des_round_decry(L10,R10,L9,R9,ER9,K10,F10);
des_round_decry(L9,R9,L8,R8,ER8,K9,F9);
des_round_decry(L8,R8,L7,R7,ER7,K8,F8);
des_round_decry(L7,R7,L6,R6,ER6,K7,F7);
des_round_decry(L6,R6,L5,R5,ER5,K6,F6);
des_round_decry(L5,R5,L4,R4,ER4,K5,F5);
des_round_decry(L4,R4,L3,R3,ER3,K4,F4);
des_round_decry(L3,R3,L2,R2,ER2,K3,F3);
des_round_decry(L2,R2,L1,R1,ER1,K2,F2);
des_round_decry(L1,R1,L0,R0,ER0,K1,F1);
for(i=0;i<32;i++)
{
decrypted[i]=L0[i];
decrypted[i+32]=R0[i];
}
common_permutation(decrypted,decry_permut);
//decry_permut[64]='\0';

decryption=bin_to_hex(decry_permut);
// printf("%s\n",decryption);

for(i=0;i<16;i++)
{
decryption_final_hex[++q]=*(decryption+i);
}
}

encryption_final[p+1]='\0';
printf("\n\nEncrypted Output : ");
printf("%s",encryption_final);

decryption_final_hex[q+1]='\0';
printf("\n\nDecrypted Output in Hexadecimal: ");
printf("%s",decryption_final_hex);

hex_to_plain(decryption_final_hex,decryption_final_plain,q+1);

printf("\n\nDecrypted Output in Plain Text: ");
printf("%s\n",decryption_final_plain);

}

void hex_to_bin(char *input,char *in)
{
short i,j,k,lim=0;
for(i=0;i<16;i++)
{
for(j=0;j<16;j++)
{
if(*(input+i)==hex[j])
{
for(k=0;k<4;k++)
{
*(in+lim)=bin[j][k];
lim++;
}
}
}
}
}

char* bin_to_hex(char *bit)
{
char tmp[5],*out;
short lim=0,i,j;
out=(char*)malloc(16*sizeof(char));
for(i=0;i<64;i=i+4)
{
tmp[0]=bit[i];
tmp[1]=bit[i+1];
tmp[2]=bit[i+2];
tmp[3]=bit[i+3];
tmp[4]='\0';
for(j=0;j<16;j++)
{
if((strcmp(tmp,bin[j]))==0)
{
out[lim++]=hex[j];
break;
}
}
}
out[lim]='\0';
return out;
}

void hex_to_plain(char *in,char *out,int t)
{
int i,j=0,z,sum;
char temp[3];


for(i=0;i<t;i=i+2)
{
sum=0;
temp[0]=in[i];
if(temp[0]>=65 && temp[0]<=71)
z=switch_case(temp[0]);
else
z=temp[0]-48;
sum=sum+z*16;

temp[1]=in[i+1];
if(temp[1]>=65 && temp[1]<=71)
z=switch_case(temp[1]);
else
z=temp[1]-48;

sum=sum+z*1;
temp[2]='\0';

*(out+j)=sum;
j++;
}
*(out+j)='\0';

}

int switch_case(char a)
{
switch(a)
{
case 'A':
return(10);
break;

case 'B':
return(11);
break;

case 'C':
return(12);
break;

case 'D':
return(13);
break;

case 'E':
return(14);
break;

case 'F':
return(15);
break;

}
}

void permutation(char *key_bin,char *key_PC1)
{
short i,j,k=0,temp;

for(i=0;i<8;i++)
{
for(j=0;j<7;j++)
{
temp=PC1[i][j]-1;
*(key_PC1+k)=*(key_bin+temp);
k++;
}
}
}

void make_half(char *key_PC1,char *a,char *b)
{
int i,j=0;
for(i=0;i<56;i++)
{
if(i<28)
*(a+i)=*(key_PC1+i);
else
{
*(b+j)=*(key_PC1+i);
j++;
}
}
}

void single_shift(char *p,char *q)
{
int i;
*(q+27)=*(p+0);
for(i=0;i<27;i++)
*(q+i)=*(p+(i+1));
}

void double_shift(char *p,char *q)
{
int i;
*(q+26)=*(p+0);
*(q+27)=*(p+1);
for(i=0;i<26;i++)
*(q+i)=*(p+(i+2));
}

void make_key(char *a,char *b,char *c)
{
int i;
for(i=0;i<28;i++)
*(c+i)=*(a+i);
for(i=28;i<56;i++)
*(c+i)=*(b+(i-28));
}

void permutation_48(char *CD,char *K)
{
short i,j,m=0,temp;

for(i=0;i<8;i++)
{
for(j=0;j<6;j++)
{
temp=PC2[i][j]-1;
*(K+m)=*(CD+temp);
m++;
}
}
}

void permutation_64(char *in,char *L,char *R)
{
int i,j,m=0,temp;
for(i=0;i<4;i++)
{
for(j=0;j<8;j++)
{
temp=IP[i][j]-1;
*(L+m)=*(in+temp);
m++;
}
}
m=0;
for(i=4;i<8;i++)
{
for(j=0;j<8;j++)
{
temp=IP[i][j]-1;
*(R+m)=*(in+temp);
m++;
}
}
}

void des_round(char *L1,char *R1,char *L0,char *R0,char *ER0,char *K1,char *F1)
{
char t[3],tp[5],f[32];
int temp,i,row,column,j,limit=0;
copy(L1,R0);
permut_48(R0,ER0);
/*printf("\nER0 : ");
for(i=0;i<48;i++)
printf("%c",ER0[i]);*/

xor(K1,ER0,F1);

/*printf("\nF1 : ");
for(i=0;i<48;i++)
printf("%c",F1[i]);*/

for(i=0;i<48;i=i+6)
{
t[0]=F1[i];
t[1]=F1[i+5];
t[2]='\0';
for(j=0;j<4;j++)
{
if(strcmp(t,look_up[j])==0)
{
row=j;
/*printf("%d",row);*/
break;
}
}
tp[0]=F1[i+1];
tp[1]=F1[i+2];
tp[2]=F1[i+3];
tp[3]=F1[i+4];
tp[4]='\0';
for(j=0;j<16;j++)
{
if(strcmp(tp,bin[j])==0)
{
column=j;
break;
}
}
switch(i)
{
case 0:
temp=s1[row][column];
break;
case 6:
temp=s2[row][column];
break;
case 12:
temp=s3[row][column];
break;
case 18:
temp=s4[row][column];
break;
case 24:
temp=s5[row][column];
break;
case 30:
temp=s6[row][column];
break;
case 36:
temp=s7[row][column];
break;
case 42:
temp=s8[row][column];
break;
}
for(j=0;j<4;j++)
{
SB[limit]=bin[temp][j];
limit++;
}
}
SB[limit]='\0';
/*printf("\nSB : %s",SB); */
permutation_32(SB,f);
SB[0]='\0';
xor_32(L0,f,R1);
}

void des_round_decry(char *L1,char *R1,char *L0,char *R0,char *ER0,char *K1,char *F1)
{
char tp[5],f[32];
short temp,i,row,column,j,limit=0;
copy(L1,R0);
permut_48(R0,ER0);
xor(K1,ER0,F1);
for(i=0;i<48;i=i+6)
{
tp[0]=F1[i];
tp[1]=F1[i+5];
tp[2]='\0';
for(j=0;j<4;j++)
{
if(strcmp(tp,look_up[j])==0)
{
row=j;
break;
}
}
tp[0]=F1[i+1];
tp[1]=F1[i+2];
tp[2]=F1[i+3];
tp[3]=F1[i+4];
tp[4]='\0';
for(j=0;j<16;j++)
{
if(strcmp(tp,bin[j])==0)
{
column=j;
break;
}
}
switch(i)
{
case 0:
temp=s1[row][column];
break;
case 6:
temp=s2[row][column];
break;
case 12:
temp=s3[row][column];
break;
case 18:
temp=s4[row][column];
break;
case 24:
temp=s5[row][column];
break;
case 30:
temp=s6[row][column];
break;
case 36:
temp=s7[row][column];
break;
case 42:
temp=s8[row][column];
break;
}
for(j=0;j<4;j++)
{
SB[limit]=bin[temp][j];
limit++;
}
}
SB[limit]='\0';
permutation_32(SB,f);
SB[0]='\0';
xor_32(L0,f,R1);
}

void copy(char *L,char *R)
{
int i;
for(i=0;i<32;i++)
*(L+i)=*(R+i);
}

void permut_48(char *R,char *ER)
{
short i,j,m=0,temp;

for(i=0;i<8;i++)
{
for(j=0;j<6;j++)
{
temp=E_bit[i][j]-1;
*(ER+m)=*(R+temp);
m++;
}
}
}

void xor(char *K,char *ER,char *F){
int i,m=0;

for(i=0;i<48;i++)
{
if((*(K+i)=='1' && *(ER+i)=='1') || (*(K+i)=='0' && *(ER+i)=='0'))
{
*(F+m)='0';
m++;
}
else
{
*(F+m)='1';
m++;
}
}
}

void xor_32(char *L0,char *f,char *R1)
{
short i,m=0;
for(i=0;i<32;i++)
{
if((*(L0+i)=='1' && *(f+i)=='1') || (*(L0+i)=='0' && *(f+i)=='0'))
{
*(R1+m)='0';
m++;
}
else
{
*(R1+m)='1';
m++;
}
}
}

void permutation_32(char *SB1,char *f)
{
short i,j,m=0,temp;

for(i=0;i<8;i++)
{
for(j=0;j<4;j++)
{
temp=sb_permutation[i][j]-1;
*(f+m)=*(SB1+temp);
m++;
}
}
}

void common_permutation(char *in,char *out)
{
short i,j,temp,m=0;
for(i=0;i<8;i++)
{
for(j=0;j<8;j++)
{
temp=ip_inverse[i][j]-1;
out[m]=in[temp];
m++;
}
}
}