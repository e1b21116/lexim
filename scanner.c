#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc,char *argv[]){
	
	FILE *fp = NULL;
	char word[100];
	char var[4]="var";
	char read[5]="read";
	char print[6]="print";
	char println[8]="println";
	char div[4]="div";
	char repeat[7]="repeat";
	int length = 0;
	int flag_period=0;
	int flag_dq=0;
	int flag_line;
	int line=1;
	int c;

	if(argc < 2){
		fprintf(stderr,"ファイルを指定してください\n");
		exit(1);
	}

	if((fp = fopen(argv[1],"r")) == NULL){
        fprintf(stderr,"ファイルがありません\n");
        exit(1);
    }

	while ((c=fgetc(fp))!=EOF){
		if(c=='#'){
			while((c=fgetc(fp))!='\n'){
			}
		}else if(isalpha(c)){

			while(isalpha(c)||isdigit(c)){
				word[length++]=c;
				c=fgetc(fp);
			}

			word[length]='\0';

			ungetc(c,fp);

			if(strcmp(word,var)==0){
				printf("2\tTK_VAR\t\t%s\n",word);
			}else if(strcmp(word,read)==0){
				printf("3\tTK_READ\t\t%s\n",word);
			}else if(strcmp(word,print)==0){
				printf("4\tTK_PRINT\t%s\n",word);
			}else if(strcmp(word,println)==0){
				printf("5\tTK_PRINTLN\t%s\n",word);
			}else if(strcmp(word,div)==0){
				printf("6\tTK_DIV\t%s\n",word);
			}else if(strcmp(word,repeat)==0){
				printf("7\tTK_REPEAT\t%s\n",word);
			}else{
				printf("1\tTK_IDENTIFIER\t%s\n",word);
			}

		}else if(isdigit(c)){

			while(isdigit(c)||c=='.'){
				if(c=='.'){
					flag_period++;
				}
				if(flag_period==2){
					fprintf(stderr,"数値に間違いがあります\n");
					exit(1);
				}
				word[length++]=c;
				c=fgetc(fp);
			}

			word[length]='\0';
			ungetc(c,fp);

			if(flag_period==0) printf("9\tTK_INTEGER\t%s\n",word);
			if(flag_period==1) printf("10\tTK_DOUBLE\t%s\n",word);

			flag_period=0;

		}else if(c=='"'){
			c=fgetc(fp);
			while(c!='"'){
				word[length++]=c;
				c=fgetc(fp);
				if(c==EOF){
					fprintf(stderr,"文字列後の \" がありません\n");
					exit(1);
				}
				word[length]='\0';
			}

			printf("11\tTK_STRING\t%s\n",word);

			
		}else if(c==':'){
			word[length++]=c;
			if((c=fgetc(fp))=='='){
				word[length++]=c;
				word[length]='\0';
				printf("22\tTK_COLON_EQUAL\t%s\n",word);
			}else{
				ungetc(c,fp);
			}
		}else if(c=='+'){
			printf("12\tTK_PLUS\t\t%c\n",c);
		}else if(c=='-'){
			printf("13\tTK_MINUS\t%c\n",c);
		}else if(c=='*'){
			printf("14\tTK_ASTERRISK\t%c\n",c);
		}else if(c=='/'){
			printf("15\tTK_SLASH\t%c\n",c);
		}else if(c=='%'){
			printf("16\tTK_PERCENT\t%c\n",c);
		}else if(c=='('){
			printf("17\tTK_L_PER\t%c\n",c);
		}else if(c==')'){
			printf("18\tTK_R_PER\t%c\n",c);
		}else if(c==';'){
			printf("19\tTK_SEMICOLON\t%c\n",c);
		}else if(c==','){
			printf("20\tTK_COMMA\t%c\n",c);
		}else if(c=='@'){
			printf("21\tTK_AT\t\t%c\n",c);
		}

		

		while(length>=0){
			word[length--]='\0';
		}
		length=0;
	}
	
	printf("\n");
	
	return 0;
}