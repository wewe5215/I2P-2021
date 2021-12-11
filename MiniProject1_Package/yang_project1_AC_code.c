#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// for lex
#define MAXLEN 256

// Token types
typedef enum {
    UNKNOWN, END, ENDFILE,
    INT, ID,
    ADDSUB, MULDIV,
    ASSIGN,
    LPAREN, RPAREN,
    BITAND, BITOR, BITXOR,
    INCDEC
} TokenSet;

TokenSet getToken(void);
TokenSet curToken = UNKNOWN;
char lexeme[MAXLEN];

// Test if a token matches the current token
int match(TokenSet token);
// Get the next token
void advance(void);
// Get the lexeme of the current token
char *getLexeme(void);


// for parser
#define TBLSIZE 64

// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code

//#define PRINTERR 1
#define PRINTERR 0

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define error(errorNum) { \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    err(errorNum); \
}

// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR, VARINV, IDOVER
} ErrorType;

// Structure of the symbol table
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;

// Structure of a tree node
typedef struct _Node {
    TokenSet data;
    int val;
    int depth;
    char lexeme[MAXLEN];
    struct _Node *left;
    struct _Node *right;
} BTNode;

// The symbol table
Symbol table[TBLSIZE];

// Initialize the symbol table with builtin variables
void initTable(void);

// Get the value of a variable
int getval(char *str);

// Get N-th of a variable
int getNthReg(char *str);

// Set the value of a variable
int setval(char *str, int val);

// Make a new node according to token type and lexeme
BTNode *makeNode(TokenSet tok, const char *lexe);

// Free the syntax tree
void freeTree(BTNode *root);

BTNode *factor(void);

BTNode *assign_expr(void);

BTNode *or_expr(void);
BTNode *or_expr_tail(BTNode *left);
BTNode *xor_expr(void);
BTNode *xor_expr_tail(BTNode *left);
BTNode *and_expr(void);
BTNode *and_expr_tail(BTNode *left);
BTNode *addsub_expr(void);
BTNode *addsub_expr_tail(BTNode *left);
BTNode *muldiv_expr(void);
BTNode *muldiv_expr_tail(BTNode *left);
BTNode *unary_expr(void);

void statement(void);

// Print error message and exit the program
void err(ErrorType errorNum);

// for codeGen
//
extern void initRegister(void);

// Evaluate the syntax tree
extern int evaluateTree(BTNode *root);

//
void getCurrentsbc(void);

// Print the syntax tree in prefix
extern void printPrefix(BTNode *root);

//
extern void setExitValue(void);

/*============================================================================================
lex implementation
============================================================================================*/

TokenSet getToken(void)
{
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t');

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while ((isdigit(c) || isalpha(c) || c == '_') && i < MAXLEN) {
            if(!isdigit(c))
                error(VARINV);
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {// change to ++ --
        lexeme[0] = c;
        c = fgetc(stdin);
        if(c == lexeme[0]){
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        } else {
            ungetc(c, stdin);
            lexeme[1] = '\0';
            return ADDSUB;
        }
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (c == '&') {
        strcpy(lexeme, "&");
        return BITAND;
    } else if (c == '|') {
        strcpy(lexeme, "|");
        return BITOR;
    } else if (c == '^') {
        strcpy(lexeme, "^");
        return BITXOR;
    } else if (isalpha(c) || c == '_') { //change to longer var
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while(isalpha(c) || isdigit(c) || c == '_') {
            if(i >= MAXLEN)
                error(VARINV);
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    } else {
        return UNKNOWN;
    }
}

void advance(void) {
    curToken = getToken();
}

int match(TokenSet token) {
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void) {
    return lexeme;
}

/*============================================================================================
parser implementation
============================================================================================*/

int sbcount = 0;
int IDcounter = 0;
//ID -> or_expr
char prevStr[256];
int prevToken = UNKNOWN;

//remember left right switched 2021/4/22 02:37
//remember left right not switched 2021/4/22 02:39
//how to buildTree?

void initTable(void) {
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}

int getval(char *str) {
    int i = 0;
    int newFlag = 1;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;

    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    if(newFlag)
        error(NOTFOUND);

//    strcpy(table[sbcount].name, str);
//    table[sbcount].val = 0;
//    sbcount++;
    return 0;
}

int getNthReg(char* str){
    int i = 0;
    int newFlag = 1;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return i;

    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    if(newFlag)
        error(NOTFOUND);

//    strcpy(table[sbcount].name, str);
//    table[sbcount].val = 0;
//    sbcount++;
    return 0;
}

int setval(char *str, int val) {
    int i = 0;

    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            return val;
        }
    }

    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return val;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->depth = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// factor              := INT | ID | INCDEC ID | LPAREN assign_expr RPAREN
BTNode *factor(void){
    BTNode* node = NULL;

    if(match(INT)){
        //printf("INT\n");
        node = makeNode(INT, getLexeme());
        advance();
    } else if (match(ID)){
        //printf("ID\n");
        node = makeNode(ID, getLexeme());
        advance();
    } else if (match(INCDEC)){
        //printf("INCDEC\n");
        char* inc_or_dec = getLexeme();

        if(inc_or_dec[0] == '+')
            inc_or_dec = "1";
        else if(inc_or_dec[0] == '-')
            inc_or_dec = "-1";
        else
            error(UNDEFINED);

        advance();
        if(match(ID)){
            //printf("ID\n");
            node = makeNode(ASSIGN, "=");
            node->left = makeNode(ID, getLexeme());
            node->right = makeNode(ADDSUB, "+");
            node->right->left = makeNode(ID, getLexeme());
            node->right->right = makeNode(INT, inc_or_dec);

            node->right->depth = 1;
            node->depth = 2;
            advance();
        } else {
            error(SYNTAXERR);
        }
    } else if (match(LPAREN)){
        //printf("LPAREN\n");
        advance();
        IDcounter = 0;
        node = assign_expr();
        if(match(RPAREN)){
            //printf("RPAREN\n");
            advance();
        } else
            error(MISPAREN);
    } else if (prevToken != UNKNOWN){
        node = makeNode(prevToken, prevStr);

        prevToken = UNKNOWN;
        memset(prevStr, 0, sizeof(prevStr));
    } else {
        error(NOTNUMID);
    }
    return node;
}

// unary_expr          := ADDSUB unary_expr | factor
BTNode *unary_expr(void){
    BTNode* node = NULL;

    if(match(ADDSUB) && prevToken == UNKNOWN){
        //printf("POSINEGA\n");
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = makeNode(INT, "0");
        node->right = unary_expr();
        node->depth = node->left->depth > node->right->depth ? node->left->depth + 1 : node->right->depth + 1;
    } else {
        node = factor();
    }

    return node;
}

// muldiv_expr_tail    := MULDIV unary_expr muldiv_expr_tail | NiL
BTNode *muldiv_expr_tail(BTNode* left){
    BTNode* node = NULL;

    if(match(MULDIV)){
        //printf("MULDIV\n");
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = unary_expr();
        node->depth = node->left->depth > node->right->depth ? node->left->depth + 1 : node->right->depth + 1;
        return muldiv_expr_tail(node);
    } else {
        node = left;
    }

    return node;
}

// muldiv_expr         := unary_expr muldiv_expr_tail
BTNode *muldiv_expr(void){
    BTNode* node = unary_expr();
    return muldiv_expr_tail(node);
}

// addsub_expr_tail    := ADDSUB muldiv_expr addsub_expr_tail | NiL
BTNode *addsub_expr_tail(BTNode* left){
    BTNode* node = NULL;

    if(match(ADDSUB)){
        //printf("ADDSUB\n");
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = muldiv_expr();
        node->depth = node->left->depth > node->right->depth ? node->left->depth + 1 : node->right->depth + 1;
        return addsub_expr_tail(node);
    } else {
        node = left;
    }

    return node;
}

// addsub_expr         := muldiv_expr addsub_expr_tail
BTNode *addsub_expr(void){
    BTNode* node = muldiv_expr();
    return addsub_expr_tail(node);
}

// and_expr_tail       := AND addsub_expr and_expr_tail | NiL
BTNode *and_expr_tail(BTNode* left){
    BTNode* node = NULL;

    if(match(BITAND)){
        //printf("BITAND\n");
        node = makeNode(BITAND, getLexeme());
        advance();
        node->left = left;
        node->right = addsub_expr();
        node->depth = node->left->depth > node->right->depth ? node->left->depth + 1 : node->right->depth + 1;
        return and_expr_tail(node);
    } else {
        node = left;
    }

    return node;
}

// and_expr            := addsub_expr and_expr_tail
BTNode *and_expr(void){
    BTNode* node = addsub_expr();
    return and_expr_tail(node);
}

// xor_expr_tail       := XOR and_expr xor_expr_tail | NiL
BTNode *xor_expr_tail(BTNode* left){
    BTNode* node = NULL;

    if(match(BITXOR)){
        //printf("BITXOR\n");
        node = makeNode(BITXOR, getLexeme());
        advance();
        node->left = left;
        node->right = and_expr();
        node->depth = node->left->depth > node->right->depth ? node->left->depth + 1 : node->right->depth + 1;
        return xor_expr_tail(node);
    } else {
        node = left;
    }

    return node;
}

// xor_expr            := and_expr xor_expr_tail
BTNode *xor_expr(void){
    BTNode* node = and_expr();
    return xor_expr_tail(node);
}

// or_expr_tail        := OR xor_expr or_expr_tail | NiL
BTNode *or_expr_tail(BTNode* left){
    BTNode* node = NULL;

    if(match(BITOR)){
        //printf("BITOR\n");
        node = makeNode(BITOR, getLexeme());
        advance();
        node->left = left;
        node->right = xor_expr();
        node->depth = node->left->depth > node->right->depth ? node->left->depth + 1 : node->right->depth + 1;
        return or_expr_tail(node);
    } else {
        node = left;
    }

    return node;
}

// or_expr             := xor_expr or_expr_tail
BTNode *or_expr(void){
    BTNode* node = xor_expr();
    return or_expr_tail(node);
    //return node;
}

// assign_expr         := ID ASSIGN assign_expr | or_expr
BTNode *assign_expr(void){
    BTNode* node = NULL, *left = NULL;
    //static int IDcounter = 0;

    if(match(ID)){
        //printf("ID\n");
        strcpy(prevStr, getLexeme());
        prevToken = ID;

        //left = makeNode(ID, getLexeme());
        IDcounter++;
        advance();
        if(match(END) || match(ENDFILE) || match(RPAREN)){
            left = makeNode(ID, prevStr);
            node = left;

            memset(prevStr, 0, sizeof(prevStr));
            prevToken = UNKNOWN;
        } else if(match(UNKNOWN) || match(ID) || match(INT) || match(LPAREN) || match(INCDEC)){
            err(SYNTAXERR);
        } else {
            if(match(ASSIGN)){
                //printf("ASSIGN\n");
                //No. 13
                /*if(IDcounter > 1){
                    error(IDOVER);
                }*/
                IDcounter = 0;
                left = makeNode(ID, prevStr);
                node = makeNode(ASSIGN, getLexeme());

                memset(prevStr, 0, sizeof(prevStr));
                prevToken = UNKNOWN;

                advance();
                node->left = left;
                node->right = assign_expr();
                node->depth = node->left->depth > node->right->depth ? node->left->depth + 1 : node->right->depth + 1;
            } else {
                //another way
                //curToken = ID;
                //for(int i = strlen(lexeme) - 1; i >= 0; i--)
                //    ungetc(lexeme[i], stdin);
                //strcpy(lexeme, getLexeme());
                //node = or_expr();
                node = or_expr();
            }
        }
    } else {
        node = or_expr();
    }
    return node;
}

// statement           := END | assign_expr END
void statement(void) {
    BTNode *retp = NULL;

    if (match(ENDFILE)) {
        //setExitValue();
        printf("MOV r0 [0]\nMOV r1 [4]\nMOV r2 [8]\nEXIT 0\n");
        //printf("EXIT 0\n");
        exit(0);
    } else if (match(END)) {
        advance();
    } else {
        retp = assign_expr();
        if (match(END)) {
            IDcounter = 0;
            getCurrentsbc();
            evaluateTree(retp);
            //printf("x: %d\ny: %d\nz: %d\n",table[0].val, table[1].val, table[2].val);
            //printf("%d\n", evaluateTree(retp));
            //printf("Prefix traversal: ");
            //printPrefix(retp);
            //printf("\n");
            freeTree(retp);
            advance();
        } else {
            error(SYNTAXERR);
        }
    }
}

void err(ErrorType errorNum) {
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTNUMID:
                fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                fprintf(stderr, "variable not defined\n");
                break;
            case RUNOUT:
                fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                fprintf(stderr, "syntax error\n");
                break;
            case VARINV:
                fprintf(stderr, "invalid variable name\n");
                break;
            case IDOVER:
                fprintf(stderr, "too many variables\n");
                break;
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }
    }
    printf("EXIT 1\n");
    exit(0);
}


/*============================================================================================
codeGen implementation
============================================================================================*/

#define SIZEOF_TEMPMEM 64
#define REGIS_COUNT 8

//BTNode regis[8];
//0: used, 1: value
int regis[REGIS_COUNT][2];

int IDonright = 0;
int nowDivideRight = 0;

int nowReg = 0;
extern int sbcount;
int curSb;

int tempMem[SIZEOF_TEMPMEM][2];
int tempReg = 0;

void initRegister(void){
    for(int i = 0; i < 8; i++){
        regis[i][0] = regis[i][1] = 0;
    }
    nowReg = 0;
}

//return value = r0-r7
int evaluateTree(BTNode *root) {
    int retval = 0;
    //int lv = 0, rv = 0;
    int i;
    int leftR = -1, rightR = -1;
    /*for(int i = 0; i < 8; i++){
        printf("r%d val = %d\n", i, regis[i].val);
    }*/

    if (root != NULL) {
        switch (root->data) {
            case ID:
                if(nowDivideRight == 1)
                    IDonright = 1;
                //if register full
                //save to memory
                //then accept new

                //how to accept new?

                if(nowReg >= REGIS_COUNT){

                    tempMem[tempReg][1] = regis[tempReg % REGIS_COUNT][1];
                    tempMem[tempReg][0] = 1;

                    regis[tempReg % REGIS_COUNT][1] = 0;
                    regis[tempReg % REGIS_COUNT][0] = 0;
                    printf("MOV [%d] r%d\n", curSb * 4, tempReg);

                    curSb++;
                    nowReg--;
                    tempReg++;
                }

                //if register not full
                for(i = 0; i < REGIS_COUNT; i++){
                    if(regis[i][0] == 0){
                        regis[i][1] = getval(root->lexeme);
                        regis[i][0] = 1;
                        printf("MOV r%d [%d]\n", i, getNthReg(root->lexeme) * 4);
                        leftR = i;
                        nowReg++;
                        break;
                    }
                }


                retval = leftR;
                break;

            case INT:
                //if register full
                //save to memory
                //then accept new

                //how to accept new?

                if(nowReg >= REGIS_COUNT){

                    tempMem[tempReg][1] = regis[tempReg % REGIS_COUNT][1];
                    tempMem[tempReg][0] = 1;

                    regis[tempReg % REGIS_COUNT][1] = 0;
                    regis[tempReg % REGIS_COUNT][0] = 0;
                    printf("MOV [%d] r%d\n", curSb * 4, tempReg);

                    curSb++;
                    nowReg--;
                    tempReg++;
                }

                //if register not full

                for(i = 0; i < REGIS_COUNT; i++){
                    if(regis[i][0] == 0){
                        regis[i][1] = atoi(root->lexeme);
                        regis[i][0] = 1;
                        printf("MOV r%d %d\n", i, regis[i][1]);

                        leftR = i;
                        nowReg++;
                        break;
                    }
                }

                retval = leftR;
                break;

            case ASSIGN:

                rightR = evaluateTree(root->right);
                setval(root->left->lexeme, regis[rightR][1]);

                printf("MOV [%d] r%d\n", getNthReg(root->left->lexeme) * 4, rightR);

                retval = rightR;
                break;

            case ADDSUB:
            case MULDIV:
            case BITAND:
            case BITOR:
            case BITXOR:

                if(root->left->depth >= root->right->depth){
                    leftR = evaluateTree(root->left);
                    if(strcmp(root->lexeme, "/") == 0)
                        nowDivideRight = 1;
                    rightR = evaluateTree(root->right);
                } else {
                    if(strcmp(root->lexeme, "/") == 0)
                        nowDivideRight = 1;
                    rightR = evaluateTree(root->right);
                    leftR = evaluateTree(root->left);
                }



                /*if(rightR == -1 || leftR == -1){
                    err(SYNTAXERR);
                }*/

                if (strcmp(root->lexeme, "+") == 0) {

                    regis[leftR][1] += regis[rightR][1];

                    regis[rightR][1] = 0;
                    regis[rightR][0] = 0;
                    nowReg--;

                    printf("ADD r%d r%d\n", leftR, rightR);
                    retval = leftR;

                } else if (strcmp(root->lexeme, "-") == 0) {

                    regis[leftR][1] -= regis[rightR][1];

                    regis[rightR][1] = 0;
                    regis[rightR][0] = 0;
                    nowReg--;

                    printf("SUB r%d r%d\n", leftR, rightR);
                    retval = leftR;

                } else if (strcmp(root->lexeme, "*") == 0) {

                    regis[leftR][1] *= regis[rightR][1];

                    regis[rightR][1] = 0;
                    regis[rightR][0] = 0;
                    nowReg--;

                    printf("MUL r%d r%d\n", leftR, rightR);
                    retval = leftR;

                } else if (strcmp(root->lexeme, "/") == 0) {

                    if (regis[rightR][1] == 0 && !IDonright)
                        error(DIVZERO);
                    IDonright = nowDivideRight = 0;
                    /*if(regis[rightR].val == 0)
                        regis[leftR].val = 0;
                    else
                        regis[leftR].val /= regis[rightR].val;*/

                    regis[rightR][1] = 0;
                    regis[rightR][0] = 0;
                    nowReg--;

                    printf("DIV r%d r%d\n", leftR, rightR);
                    retval = leftR;

                } else if (strcmp(root->lexeme, "&") == 0) {

                    regis[leftR][1] &= regis[rightR][1];

                    regis[rightR][1] = 0;
                    regis[rightR][0] = 0;
                    nowReg--;

                    printf("AND r%d r%d\n", leftR, rightR);
                    retval = leftR;

                } else if (strcmp(root->lexeme, "|") == 0) {
                    regis[leftR][1] |= regis[rightR][1];

                    regis[rightR][1] = 0;
                    regis[rightR][0] = 0;
                    nowReg--;

                    printf("OR r%d r%d\n", leftR, rightR);
                    retval = leftR;

                } else if (strcmp(root->lexeme, "^") == 0) {

                    regis[leftR][1] ^= regis[rightR][1];

                    regis[rightR][1] = 0;
                    regis[rightR][0] = 0;
                    nowReg--;

                    printf("XOR r%d r%d\n", leftR, rightR);
                    retval = leftR;

                }

                //printf("nowval: %d\n",regis[leftR].val);
                //judge if used extra memory
                if(curSb > sbcount && regis[(tempReg-1) % REGIS_COUNT][0] == 0){
                    tempReg--;
                    curSb--;
                    regis[tempReg % REGIS_COUNT][0] = 1;
                    regis[tempReg % REGIS_COUNT][1] = tempMem[tempReg][1];
                    //printf("r%d val = %d\n", tempReg, regis[tempReg].val);
                    printf("MOV r%d [%d]\n", tempReg % REGIS_COUNT, curSb * 4);

                    tempMem[tempReg][0] = 0;
                    tempMem[tempReg][1] = 0;
                    nowReg++;
                }

                break;

            default:
                retval = 0;
        }
    }

    return retval;
}

void getCurrentsbc(void){
    curSb = sbcount;
}

void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}

/*============================================================================================
main
============================================================================================*/

int main() {
    //freopen("input.txt", "w", stdout);
    initTable();
    while (1) {
        initRegister();
        statement();

    }
    return 0;
}
