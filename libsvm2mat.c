/*1. Function: 将稀疏数据集重新填充后，第一列为数据标签，标签和数据特征在一个文件中。
Format: -1 0.2 0.5 1.2 ...
1  0.4 0.1 1.4 ...
Author：Chuang Zhang.
Date: Nov. 11, 2016.
Location: CS, Tianjin University.
Language: C.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define max_num 1000 //bytes for each line
#define max_feature 17 // max_num of features
int main(int argc, char*argv[]){
    FILE *f1=NULL, *f2=NULL, *f3=NULL;
    char *p1;
    char str[max_num];

    char *index;
    char *value;
    char *deli = " :\n";
    int flag = 1;
    int count =0;
    int curdx =0;
    int i=0;
    if((f1 = fopen("heart_scale","r"))==NULL){
        printf("cannot open data file");//libsvm data file
        exit(0);
    }
    if((f2 = fopen("procedata.txt","a+"))==NULL){
        printf("cannot open data file");//mat data: label fea1 fea2 ...
        exit(0);
    }
    if((f3 = fopen("label.txt","a+"))==NULL){
        printf("cannot open data file");// label 
        exit(0);
    }
    while(!feof(f1)&&(fgets(str,max_num,f1)!=NULL)){
        p1 = strtok(str,deli); //label
        if(p1!=NULL){
            fprintf(f2,"%s ",p1);
            fprintf(f3,"%s\n",p1);
        }
        while((p1 = strtok(NULL, deli))){
            if(flag == 1){
                index = p1;
                count ++;
                curdx = atoi(index);
                while(curdx > count){
                    count ++;
                    fprintf(f2,"%d ",0);
                }
                flag = 0;
            }
            else {
                value = p1;
                fprintf(f2,"%s ",value);
                flag = 1;
            }
        }
        while(count < max_feature){
            count ++ ;
            fprintf(f2,"%d ",0);
        }
        fputc('\n',f2);
        count = 0;
        flag = 1;
    }
    fclose(f1);
    fclose(f2);
    return 0;
}
