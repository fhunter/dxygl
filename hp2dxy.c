#include <stdio.h>
#include <stdlib.h>

void read_to_eoln() {
	//This is temporary and wrong
	int ch;
	do{
		ch=getchar();
	}while(ch!='\n'||ch!='\r'&&ch>0);
	if(ch>0) ungetchar(ch);
};

void analise_i() {
};

void analise_p() {
};

void analise_s() {
};

int main(void) {
  int ch;
  while((ch=getchar())>=0){
  	switch(ch){
		case 'I':
		case 'i':{
			analise_i();
			break;
		};
		case 'P':
		case 'p':{
			analise_p();
			break;
		};
		case 'S':
		case 's':{
			analise_s();
			break;
		};
		default:{
			fprintf(stderr,"Unrecognised token\n");
			read_to_eoln();
		}

	};
  };
  return 0;
};
