%start ROOT

%token INITIAL
%token PEN_UP
%token PEN_DOWN
%token NUMBER
%token SELECT_PEN

%%

ROOT:
   lineseq { }
;

lineseq: 
