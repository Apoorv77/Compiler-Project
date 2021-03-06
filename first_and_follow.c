/************************
        |GROUP 19|
    Apoorv Badar      2019A7PS0060P
    Parth Bisen       2019A7PS0113P
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
   //printf("%s\n",ff[NTno].token);
   i++; // Going over the space or newline
   ff[NTno].First = (first*) malloc(sizeof(first));
   ff[NTno].dollarPres=0;
   ff[NTno].epsPres=0;
   first* first_ptr = ff[NTno].First , *prev = NULL;
   while(i<idx){
       char token[60];int j=0;
       while(i<idx && line[i] != ' ' && line[i] !='\n'){
        //    printf("%c\n",line[i]);
        
        if(line[i]=='^'){
            ff[NTno].epsPres=1;
            break;
        }

           first_ptr->token[j]=line[i];
           token[j]=line[i];
           
          //if(line[i]=='$') ff[NTno].dollarPres=1;
           j++;i++;
       }
       
       first_ptr->token[j]='\0';
       token[j]='\0';
       if(ff[NTno].epsPres == 1){
           if(prev == NULL)ff[NTno].First= NULL;
           else prev->next = NULL;
       }
      // printf("%s\n",first_ptr->token);
       i++; // Going over the space or newline
       if(i<idx){
           prev = first_ptr;
           first_ptr->next = (first*) malloc(sizeof(first));
           first_ptr=first_ptr->next;
           first_ptr->next = NULL;
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
   //going over non-terminal
   while(line2[i] != ' ' && line2[i] != '\n'){
       i++;
   }
   i++; // Going over the space or newline
  ff[NTno].Follow = (follow*) malloc(sizeof(follow));
   follow* follow_ptr = ff[NTno].Follow ,*pre = NULL;
   while(i<idx2){
       char token[60];int j=0;
       while(i<idx2 && line2[i] != ' ' && line2[i] !='\n'){
            if(line2[i] == '$'){
            ff[NTno].dollarPres=1;
            break;
           }
           follow_ptr->token[j]=line2[i];
           token[j]=line2[i];
           j++;i++;
       }
       
       follow_ptr->token[j]='\0';
       token[j]='\0';
       if(ff[NTno].dollarPres == 1){
          if(pre == NULL)ff[NTno].Follow= NULL;
           else pre->next = NULL;
       }
      //printf("%s\n",follow_ptr->token);
       i++; // Going over the space or newline
       if(i<idx2){
           pre = follow_ptr;
           follow_ptr->next = (follow*) malloc(sizeof(follow));
           follow_ptr=follow_ptr->next;
           follow_ptr->next = NULL;
       }
   }
   //printf("DollarPresent:%d EpsPresent:%d\n",ff[NTno].dollarPres,ff[NTno].epsPres);
   NTno++;
   }
    return ff;
}
void print_fnf(firstAndfollow* fnf){
     for(int i=0;i<52;i++){
        printf("%s eps:%d dollar:%d\n",fnf[i].token,fnf[i].epsPres,fnf[i].dollarPres);
        first* temp = fnf[i].First;
        while(temp != NULL){
            printf(" %s",temp->token);
            temp = temp->next;
        }
        printf("\n");
        follow* t = fnf[i].Follow;
        while(t != NULL){
            printf(" %s",t->token);
            t = t->next;
        }
        printf("\n");
    }
    printf("Done\n");
}

// int main() 
// {
//     FILE* input = fopen("FirstAndFollow.txt", "r");
//     if(input == NULL)
//     {
//         // fprintf(stderr, "Error Opening Grammar File\n");
//         printf("Error Opening Grammar file");
//         return 0;
//     }
//     firstAndfollow* fnf =populateFirstandFollow(input);
//     for(int i=0;i<52;i++){
//         printf("%s eps:%d dollar:%d\n",fnf[i].token,fnf[i].epsPres,fnf[i].dollarPres);
//         first* temp = fnf[i].First;
//         while(temp != NULL){
//             printf(" %s",temp->token);
//             temp = temp->next;
//         }
//         printf("\n");
//         follow* t = fnf[i].Follow;
//         while(t != NULL){
//             printf(" %s",t->token);
//             t = t->next;
//         }
//         printf("\n");
//     }
//     printf("Done\n");
//     return 0;
// }