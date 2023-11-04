/* Justin Roderick
 * COP 3402
 * Professor Montagne
 * Sep 30, 2023
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Max size of identifiers
#define maxCharForIdentifiers 11
#define MAX_SYMBOL_TABLE_SIZE 500
#define CODE_SIZE 500

// FilePtr for writing
static FILE * fp;


// Struct for the tokens
struct currToken{
    int type;
    char lexeme[maxCharForIdentifiers];
    struct currToken *next;
};
// Struct for symbol table
typedef struct{
    int kind; //onst = 1, var = 2, proc = 3
    char name[10]; // name up to 11 chars
    int val; // number (ASCII value)
    int level; // L level
    int addr; // M address
    int mark // to indicate unavailable or deleted
}symbol;

typedef struct{
    int type;
    char value[maxCharForIdentifiers];
}token;

// struct for Assembly code
typedef struct{
    int op;
    int L;
    int M;
}ISA;


// Proc, call, else, and ifel are commented out
// All static arrays used by the program in the HW document
typedef enum { oddsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
    multsym = 6, slashsym = 7, /*ifelsym = 8,*/ eqlsym = 9, neqsym = 10, lessym = 11,
    leqsym = 12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16,
    commasym = 17, semicolonsym = 18, periodsym = 19, becomessym = 20,
    beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26,
    /*callsym = 27,*/ constsym = 28, varsym = 29, /*procsym = 30,*/ writesym = 31,
    readsym = 32  /*, elsesym = 33*/
}tokenType;

char *reserveWords [] = {"const", "var", /*"procedure",*/ /*"call",*/ "begin", "end", "if", "then", /*"ifel",*/ /*"else",*/ "while", "do", "read", "write"};

int wordTokens [] = { constsym, varsym, /*procsym,*/ /*callsym,*/ beginsym, endsym, ifsym, thensym, /*ifelsym,*/ /*elsesym,*/ whilesym, dosym, readsym, writesym};

char specialSymbols[] = {'+', '-', '*', '/', '(', ')', '=', ',', '.', '<', '>', ';', ':' };

// SYmbol table index
int symbolTableCount = 0;
// code index
int cx = 0;
// token array index
int tokenCount = 0;

// Symbol table
symbol symbolTable[MAX_SYMBOL_TABLE_SIZE];
// Assembly code
//! CODESIZE?
ISA code[CODE_SIZE];

//! 500?
token Tokens[500];
token curr_token;


void getToken(struct currToken* head){
   
   if(head != NULL){
    curr_token.type = head->type;
    strcpy(curr_token.value, head->lexeme);
    head = head->next;
   }
}

// add to symbol table
//For constants, you must store kind, name and value.
//For variables, you must store kind, name, L and M.
void enterToken(int kind, int val, int level, int addr, int mark, char name[11]){
    symbolTable[symbolTableCount].kind = kind;
    symbolTable[symbolTableCount].val = val;
    symbolTable[symbolTableCount].level = level;
    symbolTable[symbolTableCount].addr = addr;
    symbolTable[symbolTableCount].mark = mark;
    strcpy(symbolTable[symbolTableCount].name, name);
    symbolTableCount++;
}

int symbolTableCheck(char name[maxCharForIdentifiers]){
    for(int i=0; i<symbolTableCount; i++){
        if(strcmp(symbolTable[i].name, name)!=0){
            return -1;
        }
        else{
            return 0;
        }
    }
}

void emmit(int op, int L, int M){
    if(cx > CODE_SIZE){
        //error
    }
    else{
        code[cx].op = op;
        code[cx].L = L;
        code[cx].M = M;
        cx++;
    }
}

void error(int x){
    switch (x)
    {
    case 1:
        // Program must end with period
        break;
    case 2:
        //const, var, and read keywords must be followed by identifier
        break;
    case 3:
        //symbol name has already been declared
        break;
    case 4:
        //constants must be assigned with =
        break;
    case 5:
        //constants must be assigned an integer value
        break;
    case 6:
        //constant and variable declarations must be followed by a semicolon
        break;
    case 7:
        //undeclared identifier
        break;
    case 8:
        //only variable values may be altered
        break;
    case 9:
        //assignment statements must use :=
        break;
    case 10:
        //begin must be followed by end
        break;
    case 11:
        //if must be followed by then
        break;
    case 12:
        //while must be followed by do
        break;
    case 13:
        //condition must contain comparison operator
        break;
    case 14:
        //right parenthesis must follow left parenthesis
        break;
    case 15:
        //arithmetic equations must contain operands, parentheses, numbers, or symbols
        break;
    case 16:
        //code too long
        break;
    
    }
}






void program(){
    emmit(7, 0, 3);
    // emmit jump
    // jmp 0 3
    //! CREATE GLOBAL ARRAY OF TOKEN STRUCTS WITH A COUNTER SO GET TOKEN IS EASIER.
    getToken();
    block();
    /*BLOCK
if token != periodsym
error
emit HALT*/

}

void block(){

}

void constDeclaration(){

}

void varDeclaration(){

}

void statment(){

}

void condition(){

}

void relOp(){

}

void expression(){

}

void term(){

}

void factor(){

}


void number(){

}

void ident(){

}








// Function that takes in char and checks if it is a number
bool isDigit(char x){
    if(isdigit(x)){
        return true;
    }
    return false;
}

// Is letter function
bool isLetter(char x){
    if(isalpha(x)){
        return true;
    }
    return false;
}

// Function returns true is the char is one of the special symbols
bool isSpecialCharacter(char x){
    for(int i=0; i<13; i++){
        if(x == specialSymbols[i]){
            return true;
        }
    }
    return false;
}

// Checks is char is a letter, number, specChar, or space.
bool isValidSymbol(char x){
    if(isLetter(x) || isDigit(x) || isSpecialCharacter(x) || (x == ' ')){
        return true;
    }
    return false;
}

// clears all tabs and newlines
void clearSpecialCharacters(int size, char *input){
    for(int i=0; i<size; i++){
        if(input[i] == '\t' || input[i] == '\n' || input[i] == '\r'){
            input[i] = ' ';
        }
    }
}

// Function that clears comments
void clearComments(int size, char *input){

    // Boolean to know when working on a comment
    bool inComment = false;

    for(int i=0; i<size; i++){
        // Detects the start of a comment and sets bool to true
        if((input[i] == '/') && (input[i + 1] == '*')){
            inComment = true;
            input[i] = ' ';
            input[i+1] = ' ';
            i++;
        }
        // Detects the end of comment and sets bool to false
        else if((input[i] == '*') && (input[i + 1] == '/')){
            inComment = false;
            input[i] = ' ';
            input[i+1] = ' ';
            i++;
        }
        // If working inside a comment changes anything to spaces
        else if(inComment){
            input[i] = ' ';
        }
        else if(!inComment){
            continue;
        }
    }
}

// Prints Linked List in correct format
void printLexeme(struct currToken *head){
    fprintf(fp, "\nLexeme Table:\n\n");
    fprintf(fp, "Lexeme\t\tToken Type\n");
    struct currToken *temp = head->next;
    while(temp != NULL){
        // Errors
        if(temp->type == -1){
            fprintf(fp, "Identifier Too Long\n");
        }
        else if(temp->type == -2){
            fprintf(fp, "Number too long\n");

        }
        else if(temp->type == -3){
            fprintf(fp, "Invalid Symbol\n");
        }
        // No errors
        else
        {
            fprintf(fp, "%s\t\t%d\n", temp->lexeme, temp->type);
        }
        temp = temp->next;
    }
    temp = head->next;
    fprintf(fp, "\nToken List:\n");
    while(temp != NULL){
        if((temp->type == 2) || (temp->type == 3)){
            fprintf(fp, "%d %s ", temp->type, temp->lexeme);
        }
        else if((temp->type == -1) || (temp->type == -2) || (temp->type == -3)){

        }
        else{
            fprintf(fp, "%d ", temp->type);
        }
        temp = temp->next;
    }
}

// Linked list function to insert at end
void insertToken(struct currToken *head, int type, char lex[maxCharForIdentifiers])
{

    struct currToken *t;
    struct currToken *temp;
    temp=(struct currToken *) malloc( sizeof(struct currToken));
    temp->type =type;
    strcpy(temp->lexeme, lex);

    temp->next=NULL;
    if(head==NULL){
        head=temp;
    }
    else
    {
        t=head;
        while(t->next!=NULL)
            t=t->next;
        t->next=temp;
    }
}


// Function to seperate the tokens and add to the linked list
void tokenFetcher(int size, char* input, struct currToken* head){
    int ssym[256];
    ssym['+'] = plussym;ssym['-']=minussym; ssym['*']=multsym;
    ssym['/']=slashsym; ssym['(']=lparentsym; ssym[')']=rparentsym;
    ssym['=']=eqlsym; ssym[',']=commasym; ssym['.']=periodsym;
    ssym['#']=neqsym; ssym['<']=lessym; ssym['>']=gtrsym;
    ssym['$']=leqsym; ssym['%']=geqsym; ssym[';']=semicolonsym;


    char aLexeme[maxCharForIdentifiers];
    int state=0;
    int count=0;

    while(count<size){

        char curchar = input[count];
        char nextChar = input[count + 1];

        if(!isValidSymbol(curchar)){
            insertToken(head, -3, "");
            state = -3;
        }

        switch(state){
            case 0: {
                memset(aLexeme, '\0', sizeof(aLexeme));
                if (isDigit(curchar)) {
                    state = numbersym;

                    aLexeme[strlen(aLexeme)] = curchar;

                } else if (isLetter(curchar)) {
                    state = identsym;

                    aLexeme[strlen(aLexeme)] = curchar;

                }
                else if (isSpecialCharacter(curchar)) {

                    if(curchar == ':'){
                        state = becomessym;
                        aLexeme[strlen(aLexeme)] = curchar;

                    }
                    else{
                        state = ssym[curchar];

                        aLexeme[strlen(aLexeme)] = curchar;
                    }
                }

                else {
                }
                break;
            }

            case identsym:{

                if(isLetter(curchar) || isDigit(curchar)){

                    if(strlen(aLexeme) > 11){

                        state = -1;
                        insertToken(head, state, "");
                        while(isLetter(input[count]) || isDigit(input[count])){
                            count++;

                        }
                        state = 0;

                    }
                    aLexeme[strlen(aLexeme)] = curchar;

                    for(int i=0; i< 14; i++){
                        if(strcmp(aLexeme, reserveWords[i])== 0){
                            state = wordTokens[i];
                            count--;
                        }
                    }

                    if(!isLetter(nextChar)){

                    }
                }
                else{
                    insertToken(head, state, aLexeme);
                    state = 0;
                    count--;

                }
                break;
            }

            case numbersym:{

                if(isDigit(curchar)){
                    if(strlen(aLexeme) > 5){
                        state = -2;
                        insertToken(head, state, "");
                        while(isDigit(input[count])){
                            count++;
                        }
                        state = 0;
                    }

                    aLexeme[strlen(aLexeme)] = curchar;
                }
                else{
                    insertToken(head, state, aLexeme);
                    state = 0;
                    count--;
                }
                break;
            }

            case becomessym:{

                if(curchar == '='){
                    //state = becomessym;
                    aLexeme[strlen(aLexeme)] = curchar;
                    insertToken(head, state, aLexeme);
                    state = 0;
                }
                else{
                    printf("invalid symbol");

                }
                break;
            }

            case lessym:{
                if(curchar == '>'){
                    aLexeme[strlen(aLexeme)] = curchar;
                    state = neqsym;
                }
                else if(curchar == '='){
                    aLexeme[strlen(aLexeme)] = curchar;
                    state = leqsym;
                }
                else{
                    insertToken(head, state, aLexeme);
                    state = 0;
                    count--;
                }
                break;
            }

            case gtrsym:{
                if(curchar == '='){
                    aLexeme[strlen(aLexeme)] = curchar;
                    state = geqsym;
                }
                else{
                    insertToken(head, state, aLexeme);
                    state = 0;
                    count--;
                }
                break;
            }

            case plussym:
            case minussym:
            case multsym:
            case slashsym:
            case eqlsym:
            case neqsym:
            case leqsym:
            case geqsym:
            case lparentsym:
            case rparentsym:
            case commasym:
            case semicolonsym:
            case periodsym:{
                insertToken(head, state, aLexeme);
                state = 0;
                count--;
                break;
            }

            
            //case ifelsym:
            case beginsym:
            case endsym:
            case ifsym:
            case thensym:
            case whilesym:
            case dosym:
            //case callsym:
            case constsym:
            case varsym:
            //case procsym:
            case writesym:
            //case elsesym:
            case readsym:{
                if(isLetter(nextChar) || isDigit(nextChar)){
                    state=identsym;
                }
                else{
                    insertToken(head, state, aLexeme);
                    state = 0;
                }
                break;
            }
            
            
            case -3:{
                break;
            }
        }
        count++;
    }
}


int main(int argc, char *argv[]) {

    char *input;
    input = (char*)malloc(1000 * sizeof(char));
    fp = fopen("output.txt", "w");
    fprintf(fp, "Source Program:\n\n");
    FILE *filePointer;
    char *filename;
    int count = 0;
    char x;
    filename = argv[1];
    filePointer = fopen(filename, "r");

    if (!filePointer)
    {
        printf("Failed to open file\n");
        exit(1);
    }
    while (!feof(filePointer)) {
        x = fgetc(filePointer);
        if(x == EOF){
            printf("\n");
            break;
        }
        else{
            input[count] = x;
            count++;
            //fprintf(fp, "%c", x);
        }
    }
    fclose(filePointer);

    clearSpecialCharacters(count, input);

    clearComments(count, input);

    struct currToken * head = (struct currToken*)malloc(sizeof(struct currToken));
    tokenFetcher(count, input, head);
    printLexeme(head);

    fprintf(fp, "\n");
    return 0;
}
