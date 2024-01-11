#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc,char *argv[]){

	FILE *fp = NULL;

	if(argc < 2){
		fprintf(stderr,"ファイルを指定してください\n");
		exit(1);
	}

	if((fp = fopen(argv[1],"r")) == NULL){
        fprintf(stderr,"ファイルがありません\n");
        exit(1);
    }

	fclose(fp);

	return 0;
}