#include<stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[]){
	
	FILE *fp = NULL;
	int c;

	if(argc != 2){
		fprintf(stderr,"ファイルを指定してください\n");
		exit(1);
	}

	if((fp = fopen(argv[1],"r")) == NULL){
        fprintf(stderr,"ファイルがありません\n");
        exit(1);
    }

	while ((c=fgetc(fp))!=EOF){
		printf("%c",c);

	}
	
	printf("\n");
	
	return 0;
}