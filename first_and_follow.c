/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0073P
    Vibha Rao         2019A7PS0132P
    Amish Bhat        2019A7PS0140P
    Aniruddha Trivedi 2019A7PS0073P
*******************/

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "first_and_follow.h"

firstAndfollow * populateFirstandFollow(FILE* ptr)
{
    firstAndfollow * ff = (firstAndfollow*)malloc(sizeof(firstAndfollow)*60);
    int no = 0 ;
    char ch = '1';
    int NTno = 0 ;
    int x = 0;
    // char ch ;
   while(feof(ptr)==0){
    //First
   char line[250];int idx=0;
   while(feof(ptr) == 0){
       char c = fgetc(ptr);
       if(c=='\n' || c==EOF)break;
       line[idx++]=c;
   }
   line[idx]='\0';
   char NT[60];int i=0;
   while(line[i] != ' ' && line[i] != '\n'){
       ff[NTno].token[i]=line[i];
       NT[i]=line[i];
       i++;
   }
   ff[NTno].token[i]='\0';
   NT[i]='\0';
  // printf("%s\n",ff[NTno].token);
   i++; // Going over the space or newline
   ff[NTno].First = (first*) malloc(sizeof(first));
   ff[NTno].dollarPres=0;
   ff[NTno].epsPres=0;
   first* first_ptr = ff[NTno].First;
   while(i<idx){
       char token[60];int j=0;
       while(i<idx && line[i] != ' ' && line[i] !='\n'){
           first_ptr->token[j]=line[i];
           token[j]=line[i];
           if(line[i]=='^') ff[NTno].epsPres=1;
           j++;i++;
       }
       first_ptr->token[j]='\0';
       token[j]='\0';
      // printf("%s\n",first_ptr->token);
       i++; // Going over the space or newline
       if(i<idx){
           first_ptr->next = (first*) malloc(sizeof(first));
           first_ptr=first_ptr->next;
       }
   }


 
   //Follow
   char line2[250];int idx2=0;
   while(feof(ptr) == 0){
       char c = fgetc(ptr);
       if(c=='\n' || c==EOF)break;
       line2[idx2++]=c;
   }
   line2[idx2]='\0';
   i=0;
   while(line2[i] != ' ' && line2[i] != '\n'){
       i++;
   }
   i++; // Going over the space or newline
  ff[NTno].Follow = (follow*) malloc(sizeof(follow));
   follow* follow_ptr = ff[NTno].Follow;
   while(i<idx2){
       char token[60];int j=0;
       while(i<idx2 && line2[i] != ' ' && line2[i] !='\n'){
           follow_ptr->token[j]=line2[i];
           token[j]=line2[i];
           if(line2[i]=='$') ff[NTno].dollarPres=1;
           j++;i++;
       }
       follow_ptr->token[j]='\0';
       token[j]='\0';
      // printf("%s\n",follow_ptr->token);
       i++; // Going over the space or newline
       if(i<idx2){
           follow_ptr->next = (follow*) malloc(sizeof(follow));
           follow_ptr=follow_ptr->next;
       }
   }
   //printf("DollarPresent:%d EpsPresent:%d\n",ff[NTno].dollarPres,ff[NTno].epsPres);
   NTno++;
   }
    return ff;
}
// int main() 
// {
//     FILE* input = fopen("FirstandFollowSets.txt", "r");
//     if(input == NULL)
//     {
//         // fprintf(stderr, "Error Opening Grammar File\n");
//         printf("Error Opening Grammar file");
//         return 0;
//     }
//     firstAndfollow* ff =populateFirstandFollow(input);
//     printf("%s\n",ff[1].token);
//     printf("%d %d\n",ff[1].epsPres,ff[1].dollarPres);
//     return 0;
// }