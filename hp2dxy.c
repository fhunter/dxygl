#include <stdio.h>
#include <stdlib.h>

void read_to_eoln() {
	int ch;
	do{
		ch=getchar();
	}while(ch!='\n'||ch!='\r'&&ch>0);
	if(ch>0) ungetchar(ch);
};

int main(void) {
  int ch;
  while((ch=getchar())>=0){
  	switch(ch){
		case 'I':
		case 'i':{
			break;
		};
		case 'P':
		case 'p':{
			break;
		};
		case 'S':
		case 's':{
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
