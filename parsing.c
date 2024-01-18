#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char token[3];
FILE *fp = NULL;
char variable_declaration='2';

char identifier[3];
char var[3];
char read[3];
char print [3];
char println[3];
char divdiv[3];
char repeat[3];
char integer [3];
char real[3];
char string[3];
char plus[3];
char minus[3];
char multi[3];
char division[3];
char percent[3];
char open[3];
char close[3];
char semicoron[3];
char comma[3];
char at[3];
char equal[3];

int flag_eof=0;
int flag_dec_equal=0;
int flag_debag=0;
int c;

void get_token(){
	int cnt=0;

	//token初期化
	for(int i=0;i<3;i++){
		token[i]='\0';
	}

	//tokenに読み込む
	c=fgetc(fp);
	while(c!='\n' && c!=EOF){
		token[cnt++]=c;
		c=fgetc(fp);
	}

	if(c==EOF){
		flag_eof=1;
	}
}

void call(){
	get_token();
	if(flag_debag==1) printf("\n%s\n",token);
	if(strcmp(token,identifier)==0){
		if(flag_debag==1) printf("call_identidier\n");
	}else{
		fprintf(stderr,"call_identifier_error\n");
		exit(1);
	}

	get_token();
	if(flag_debag==1) printf("\n%s\n",token);
	if(strcmp(token,open)==0){
		if(flag_debag==1) printf("call_open\n");
	}else{
		fprintf(stderr,"call_open_error\n");
		exit(1);
	}

	get_token();
	if(flag_debag==1) printf("\n%s\n",token);
	if(strcmp(token,close)==-0){
		if(flag_debag==1) printf("call_close\n");
	}else if(strcmp(token,identifier)==0){
		if(flag_debag==1) printf("call_identifier\n");
		get_token();
		if(flag_debag==1) printf("\n%s\n",token);
		if(strcmp(token,close)==0){
			if(flag_debag==1) printf("call_close\n");
		}else{
			fprintf(stderr,"call_close_error\n");
			exit(1);
		}
	}else{
		fprintf(stderr,"call_error\n");
		exit(1);
	}
}

void element(){
	if(strcmp(token,open)==0){

		if(flag_debag==1) printf("element_open\n");

		get_token();
		if(flag_debag==1) printf("\n%s\n",token);

		if(strcmp(token,plus)==0 || strcmp(token,minus)==0 || strcmp(token,open)==0 
		|| strcmp(token,integer)==0 || strcmp(token,real)==0 
		|| strcmp(token,identifier)==0 || strcmp(token,at)==0){

			formula();

		}else{
			fprintf(stderr,"element_formula_error\n");
			exit(1);
		}

		get_token();
		if(flag_debag==1) printf("\n%s\n",token);

		if(strcmp(token,close)!=0){
			fprintf(stderr,"element_close_error\n");
			exit(1);
		}
		if(flag_debag==1) printf("element_close\n");
	}else if(strcmp(token,integer)==0){
		if(flag_debag==1) printf("element_integer\n");
	}else if(strcmp(token,real)==0){
		if(flag_debag==1) printf("element_real\n");
	}else if(strcmp(token,identifier)==0){
		if(flag_debag==1) printf("element_identifier\n");
	}else if(strcmp(token,at)==0){
		if(flag_debag==1) printf("element_at\n");
		call();
	}else{
		fprintf(stderr,"element_error\n");
		exit(1);
	}
}

void term(){
	if(strcmp(token,open)==0 || strcmp(token,integer)==0 || strcmp(token,real)==0 || strcmp(token,identifier)==0 || strcmp(token,at)==0){
		element();
	}else{
		fprintf(stderr,"term_element_error1\n");
		exit(1);
	}
	get_token();
	if(flag_debag==1) printf("\n%s\n",token);
	if(strcmp(token,multi)==0 || strcmp(token,division)==0 || 
	strcmp(token,divdiv)==0 || strcmp(token,percent)==0){
		if(flag_debag==1) printf("term_mul_div_per\n");
		get_token();
		if(flag_debag==1) printf("\n%s\n",token);
		if(strcmp(token,open)==0 || strcmp(token,integer)==0 || 
		strcmp(token,real)==0 || strcmp(token,identifier)==0 || strcmp(token,at)==0){
			element();
		}else{
			fprintf(stderr,"term_element_error2\n");
			exit(1);
		}
	}
	
}

void formula(){
	int flag=0;
	if(strcmp(token,plus)==0 || strcmp(token,minus)==0){
		if(flag_debag==1) printf("formula_plus_minus\n");
		get_token();
		if(flag_debag==1) printf("\n%s\n",token);
		if(strcmp(token,open)==0 || strcmp(token,integer)==0 || 
		strcmp(token,real)==0 || strcmp(token,identifier)==0 || strcmp(token,at)==0){
			term();
		}else{
			fprintf(stderr,"formula_term_error1\n");
			exit(1);
		}
		while(flag==0){
			get_token();
			if(flag_debag==1) printf("\n%s\n",token);
			if(strcmp(token,plus)==0 || strcmp(token,minus)==0){
				if(flag_debag==1) printf("formula_plus_minus\n");
				term();
			}else{
				flag=1;
			}
		}
	}else {
		if(strcmp(token,open)==0 || strcmp(token,integer)==0 || 
		strcmp(token,real)==0 || strcmp(token,identifier)==0 || strcmp(token,at)==0){
			term();
		}else{
			fprintf(stderr,"formula_term_error2\n");
			exit(1);
		}

		if(strcmp(token,plus)==0 || strcmp(token,minus)==0){
			flag=1;
		}

		while(flag==1){
			if(strcmp(token,plus)==0 || strcmp(token,minus)==0){
				if(flag_debag==1) printf("formula_plus_minus\n");
				get_token();
				if(flag_debag==1) printf("\n%s\n",token);
				term();
				//get_token();
				//if(flag_debag==1) printf("\n%s\n",token);
			}else{
				flag=0;
			}
		}
	}
}

void declaration(){
	int flag_vname=0;
	int flag_formula=0;
	get_token();
	if(flag_debag==1) printf("\n%s\n",token);
	if(strcmp(token,identifier)==0){
		flag_vname=1;
		if(flag_debag==1) printf("declaration_identifier\n");
	}
	if(flag_vname==0){
		fprintf(stderr,"declaration_vname_error\n");
		exit(1);
	}
	get_token();
	if(flag_debag==1) printf("\n%s\n",token);
	if(strcmp(token,equal)==0){
		if(flag_debag==1) printf("declaration_equal\n");
		//flag_dec_equal=1;
		get_token();
		if(flag_debag==1) printf("\n%s\n",token);
		if(strcmp(token,plus)==0 || strcmp(token,minus)==0 || strcmp(token,open)==0 
		|| strcmp(token,integer)==0 || strcmp(token,real)==0 
		|| strcmp(token,identifier)==0 || strcmp(token,at)==0){
			flag_formula=1;
		}
		if(flag_formula=0){
			fprintf(stderr,"declaration_formula_error\n");
			exit(1);
		}
		formula();
	}
}

void substitution(){
	get_token();
	if(flag_debag==1) printf("\n%s\n",token);
	if(strcmp(token,equal)==0){
		if(flag_debag==1) printf("substitution_equal\n");
		get_token();
		if(flag_debag==1) printf("\n%s\n",token);
		formula();
	}else{
		fprintf(stderr,"substitution_equal_error\n");
		exit(1);
	}
}

void input(){
	get_token();
	if(flag_debag==1) printf("\n%s\n",token);
	if(strcmp(token,open)==0){
		if(flag_debag==1) printf("input_open\n");
		get_token();
		if(flag_debag==1) printf("\n%s\n",token);
		if(strcmp(token,identifier)==0){
			if(flag_debag==1) printf("input_identifier\n");
			get_token();
			if(flag_debag==1) printf("\n%s\n",token);
			if(strcmp(token,close)==0){
				if(flag_debag==1) printf("input_close\n");
			}else{
				fprintf(stderr,"input_close_error\n");
				exit(1);
			}
		}else{
			fprintf(stderr,"input_identifier_error\n");
			exit(1);
		}
	}else{
		fprintf(stderr,"input_open_error\n");
		exit(1);
	}
}

void output_line(){
	int flag=0;
	if(strcmp(token,string)==0){
		if(flag_debag==1) printf("output_line_string\n");
		get_token();
		if(flag_debag==1) printf("\n%s\n",token);
	}else{
		formula();
	}

	//get_token();
	//if(flag_debag==1) printf("\n%s\n",token);
	if(strcmp(token,comma)==0){
		flag=1;
	}
	while(flag==1){
		if(strcmp(token,comma)==0){
			if(flag_debag==1) printf("output_line_comma\n");
			get_token();
			if(flag_debag==1) printf("\n&s\n",token);
			output_line();
		}else{
			flag=0;
		}
	}
}

void interpretation(){//解釈単位
	int flag_dec=0;//変数宣言

	//変数宣言のfirst集合check
	if(strcmp(token,var)==0){
		if(flag_debag==1) printf("interpretation_var\n");
		declaration();
	}

	if(strcmp(token,identifier)==0){
		if(flag_debag==1) printf("interpretation_identifier1\n");
		substitution();
	}
	
	if(strcmp(token,read)==0){
		if(flag_debag==1) printf("interpretation_read\n");
		input();
		get_token();
		if(flag_debag==1) printf("\n%s\n",token);
	}

	if(strcmp(token,repeat)==0){
		if(flag_debag==1) printf("interpretation_repeat\n");
		get_token();
		if(flag_debag==1) printf("\n%s\n",token);
		if(strcmp(token,plus)==0 || strcmp(token,minus)==0 || strcmp(token,open)==0 
		|| strcmp(token,integer)==0 || strcmp(token,real)==0 
		|| strcmp(token,identifier)==0 || strcmp(token,at)==0){
			formula();
			if(strcmp(token,identifier)==0){
				substitution();
				get_token();
				if(flag_debag==1) printf("\n%s\n",token);
			}else{
				fprintf(stderr,"interpretation_formula_error\n");
				exit(1);
			}
		}else{
			fprintf(stderr,"interpretation_formula_error\n");
			exit(1);
		}
	}

	if(strcmp(token,print)==0 || strcmp (token,println)==0){
		if(flag_debag==1) printf("interpretation_print\n");
		get_token();
		if(flag_debag==1) printf("\n%s\n",token);
		if(strcmp(token,open)==0){
			if(flag_debag==1) printf("interpretation_open\n");
			get_token();	
			if(flag_debag==1) printf("\n%s\n",token);
			if(strcmp(token,close)==0){
				if(flag_debag==1) printf("interpretation_close\n");
				get_token();
				if(flag_debag==1) printf("\n%s\n",token);
			}else if(strcmp(token,plus)==0 || strcmp(token,minus)==0 || strcmp(token,open)==0 || 
			strcmp(token,integer)==0 || strcmp(token,real)==0 || strcmp(token,identifier)==0 || 
			strcmp(token,at)==0 || strcmp(token,string)==0){
				output_line();
				if(strcmp(token,close)==0){
					if(flag_debag==1) printf("interpretation_close\n");
					get_token();
					if(flag_debag==1) printf("\n%s\n",token);
				}else{
					fprintf(stderr,"interpretation_close_error\n");
					exit(1);
				}
			}else{
				fprintf(stderr,"interpretation_output_line_error\n");
				exit(1);
			}
		}else{
			fprintf(stderr,"interpretation_open_error\n");
			exit(1);
		}
	}
}

void program(){
	int flag;
	while(flag_eof==0){
		flag=0;

		get_token();
		if(flag_debag==1) printf("\n%s\n",token);

		if(flag_eof==1){
			return;
		}

		if(strcmp(token,identifier)==0 || strcmp(token,var)==0 || 
		strcmp(token,read)==0 ||strcmp(token,print)==0 || 
		strcmp(token,println)==0 || strcmp(token,repeat)==0 ){
			flag=1;
		}

		if(flag==0){
			fprintf(stderr,"program_error\n");
			exit(1);
		}
		interpretation();
		if(strcmp(token,semicoron)!=0){
			fprintf(stderr,"program_semicoron_error\n");
			exit(1);
		}
		if(flag_debag==1) printf("program_semicoron\n");
		if(flag_debag==1) printf("---------------------------\n");
	}
	
}

int main(int argc,char *argv[]){

	char *option="-d";

	if(argc < 2){
		fprintf(stderr,"select the file\n");
		exit(1);
	}

	if((fp = fopen(argv[1],"r")) == NULL){
        fprintf(stderr,"file not found\n");
        exit(1);
    }

	if(argc>2){
		if(strcmp(argv[2],option)==0){
			flag_debag=1;
		}else{
			fprintf(stderr,"options are different\n");
			exit(1);
		}
	}

	if(flag_debag==1) printf("\n");

	identifier[0]='1';
	var[0]='2';
	read[0]='3';
	print[0]='4';
	println[0]='5';
	divdiv[0]='6';
	repeat[0]='7';
	integer[0]='9';
	real[0]='1';
	real[1]='0';
	string[0]='1';
	string[1]='1';
	plus[0]='1';
	plus[1]='2';
	minus[0]='1';
	minus[1]='3';
	multi[0]='1';
	multi[1]='4';
	division[0]='1';
	division[1]='5';
	percent[0]='1';
	percent[1]='6';
	open[0]='1';
	open[1]='7';
	close[0]='1';
	close[1]='8';
	semicoron[0]='1';
	semicoron[1]='9';
	comma[0]='2';
	comma[1]='0';
	at[0]='2';
	at[1]='1';
	equal[0]='2';
	equal[1]='2';

	/*if(strcmp(token,var)==0){
		printf("var_ok\n");
	}
	get_token();

	if(strcmp(token,identifier)==0){
		printf("identifier_ok\n");
	}
	get_token();

	if(strcmp(token,semicoron)==0){
		printf("semicoron_ok\n");
	}*/



	program();

	if(flag_eof==0){
		fprintf(stderr,"入力が残っています\n");
		exit(1);
	}

	fclose(fp);

	return 0;
}