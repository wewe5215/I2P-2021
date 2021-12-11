//
//  main.c
//  mini project1
//
//  Created by 朱季葳 on 2021/4/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXLEN 256

// Token types
typedef enum {
    UNKNOWN, END, ENDFILE,
    INT, ID,
    ADDSUB, MULDIV,
    ASSIGN,
    LPAREN, RPAREN,
    INCDEC,
    XOR,OR,AND
} TokenSet;
int r[8][2];//0是標記用的，1是值
// Test if a token matches the current token
extern int match(TokenSet token);

// Get the next token
extern void advance(void);

// Get the lexeme of the current token
extern char *getLexeme(void);
static TokenSet getToken(void);
static TokenSet curToken = UNKNOWN;
static char lexeme[MAXLEN];
#define TBLSIZE 64

// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code
#define PRINTERR 1

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define error(errorNum) { \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    erro(errorNum); \
}

// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
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
    char lexeme[MAXLEN];
    struct _Node *left;
    struct _Node *right;
} BTNode;

// The symbol table
extern Symbol table[TBLSIZE];

// Initialize the symbol table with builtin variables
extern void initTable(void);

// Get the value of a variable
extern int getval(char *str);

// Set the value of a variable
extern int setval(char *str, int val);

// Make a new node according to token type and lexeme
extern BTNode *makeNode(TokenSet tok, const char *lexe);

// Free the syntax tree
extern void freeTree(BTNode *root);

extern BTNode *factor(void);
extern BTNode *term(void);
extern BTNode *term_tail(BTNode *left);
extern BTNode *expr(void);
extern BTNode *expr_tail(BTNode *left);
extern BTNode *or_expr_tail(BTNode *left);
extern BTNode *xor_expr_tail(BTNode *left);
extern BTNode *and_expr_tail(BTNode *left);
extern BTNode *addsub_expr_tail(BTNode *left);
extern BTNode *muldiv_expr_tail(BTNode *left);
extern BTNode *assign_expr(void);
extern BTNode *or_expr(void);
extern BTNode *xor_expr(void);
extern BTNode *and_expr(void);
extern BTNode *addsub_expr(void);
extern BTNode *muldiv_expr(void);
extern BTNode *unary_expr(void);
extern void statement(void);

// Print error message and exit the program
extern void erro(ErrorType errorNum);
int sbcount = 0;
int count_val=0;
Symbol table[TBLSIZE];
// Evaluate the syntax tree
extern int evaluateTree(BTNode *root);

// Print the syntax tree in prefix
extern void printPrefix(BTNode *root);
int flag2=0;
int main() {
    initTable();
//    printf(">> ");
    while (1) {
        statement();
    }
    return 0;
}
TokenSet getToken(void)
{
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t');

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN)
        {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
//        printf("%s\n",lexeme);
        return INT;
    }
    else if (c == '+' || c == '-') {
        lexeme[0]=c;
        if((c=fgetc(stdin))==lexeme[0]){
            lexeme[1]=lexeme[0];
            lexeme[2]='\0';
            ungetc(c, stdin);
            return INCDEC;
        }
        else
        {
        //lexeme[0] = c;
        lexeme[1] = '\0';
        ungetc(c, stdin);
        return ADDSUB;
        }
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if(c == '&')  {
        lexeme[0]=c;
        lexeme[1]='\0';
        return AND;
    }else if(c =='|'){
        lexeme[0]=c;
        lexeme[1]='\0';
        return OR;
    }else if(c=='^'){
        lexeme[0]=c;
        lexeme[1]='\0';
        return XOR;
    }else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c)||c=='_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while ((isdigit(c)||isalpha(c)||c=='_') && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    }
        
    return UNKNOWN;
    
}

void advance(void) {
//    printf("adv\n");
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
void initTable(void) {
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}



BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    if(tok==ASSIGN)flag2=1;
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
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

// factor := INT | ADDSUB INT |
//                ID  | ADDSUB ID  |
//                ID ASSIGN expr |
//                LPAREN expr RPAREN |
//                ADDSUB LPAREN expr RPAREN
//factor  := INT | ID | INCDEC ID | LPAREN assign_expr RPAREN
BTNode *factor(void) {
    BTNode *retp = NULL, *left = NULL;

    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        retp->val=atoi(retp->lexeme);
        advance();
//        printf("%d\n",curToken);
    }
    else if (match(ID))
    {
        left = makeNode(ID, getLexeme());
        left->val=getval(left->lexeme);
        advance();
//        printf("%s\n",left->lexeme);
        retp = left;
    }
    else if (match(INCDEC))
    {
        int flag=0;
        char *str=getLexeme();
        if(strcmp(str, "++")==0)flag=1;
        else flag=0;
        advance();
        if(match(ID))
        {
            retp->left=makeNode(ID, getLexeme());
            retp->val=getval(retp->lexeme);
            if(flag)retp->val+=1;
            else retp->val-=1;
            advance();
        }
        else
        {
            error(NOTNUMID);
        }
    }
    else if (match(LPAREN))
    {
//        printf("111");
        advance();
        retp = assign_expr();
        advance();
        if (match(RPAREN))
            advance();
        else
            error(MISPAREN);
    }
    else
    {
//        printf("~~~~");
        error(SYNTAXERR);
    }
    return retp;
}

// term := factor term_tail
/*BTNode *term(void) {
    BTNode *node = factor();
    return term_tail(node);
}

// term_tail := MULDIV factor term_tail | NiL
BTNode *term_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = factor();
        return term_tail(node);
    }
    else {
        return left;
    }
}

// expr := term expr_tail
BTNode *expr(void) {
    BTNode *node = term();
    return expr_tail(node);
}*/
//assign_expr := ID ASSIGN assign_expr | or_expr
extern BTNode *assign_expr(void)
{
    BTNode *node=NULL,*left=NULL;
    if(match(ID))
    {
//        count_val++;
        left=makeNode(ID, getLexeme());
//        printf("%s\n",left->lexeme);
        left->val=getval(left->lexeme);
        advance();
        if(match(ASSIGN))
        {
            
            node=makeNode(ASSIGN, getLexeme());
            node->left=left;
            advance();
            node->right=assign_expr();
//            printf("%s %s %s\n",left->lexeme,node->lexeme,node->right->lexeme);
            
        }
       /* else if(count_val>1)
        {
           printf("!!!!!");
            error(SYNTAXERR);
        }*/
        else if(match(ADDSUB)||match(MULDIV)||match(AND)||match(XOR)||match(OR))
        {
            curToken = ID;
            for(int i = strlen(lexeme)-1; i >= 0; i--){
                ungetc(lexeme[i], stdin);
            }
            strcpy(lexeme, left->lexeme);
//            printf("%s\n",left->lexeme);
            freeTree(left);
//            advance();
//            printf("%s\n",getLexeme());
            node=or_expr();
        }
        else
        {
            return left;
        }
       
        
    }
    else
        node=or_expr();
    return node;
}
extern BTNode *or_expr(void)
{
    BTNode *node=xor_expr();
    return or_expr_tail(node);
}
extern BTNode *xor_expr(void)
{
    BTNode *node=and_expr();
    return xor_expr_tail(node);
}
extern BTNode *and_expr(void)
{
    BTNode *node=addsub_expr();
    return and_expr_tail(node);
}
extern BTNode *addsub_expr(void)
{
    BTNode *node=muldiv_expr();
    return addsub_expr_tail(node);
}
extern BTNode *muldiv_expr(void)
{
    BTNode *node=unary_expr();
    return muldiv_expr_tail(node);
}
extern BTNode *unary_expr(void)
{
    BTNode *node;
    if(match(ADDSUB))
    {
        char* str=getLexeme();
        node=makeNode(ADDSUB, str);
        node->left=makeNode(INT, "0");
        advance();
        node->right=unary_expr();
        return node;
    }
    else node=factor();
    
    return node;
}
// expr_tail := ADDSUB term expr_tail | NiL
/*BTNode *expr_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(ADDSUB))
    {
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = term();
        return expr_tail(node);
    }
    else
    {
        return left;
    }
}*/
//or_expr_tail:= OR xor_expr or_expr_tail | NiL
extern BTNode *or_expr_tail(BTNode *left)
{
    BTNode *node=NULL;
    if(match(OR))
    {
        node=makeNode(OR, getLexeme());
        advance();
        node->left=left;
        node->right=xor_expr();
        return or_expr_tail(node);
    }
    else
        return left;
}
//xor_expr_tail       := XOR and_expr xor_expr_tail | NiL
extern BTNode *xor_expr_tail(BTNode *left)
{
    BTNode *node=NULL;
    if(match(XOR))
    {
        node=makeNode(XOR, getLexeme());
        advance();
        node->left=left;
        node->right=and_expr();
        return xor_expr_tail(node);
    }
    else
        return left;
}
//and_expr_tail       := AND addsub_expr and_expr_tail | NiL
extern BTNode *and_expr_tail(BTNode *left)
{
    BTNode *node=NULL;
    if(match(AND))
    {
        node=makeNode(AND, getLexeme());
        advance();
        node->left=left;
        node->right=addsub_expr();
        return and_expr_tail(node);
    }
    else
        return left;
       
}
//addsub_expr_tail    := ADDSUB muldiv_expr addsub_expr_tail | NiL
extern BTNode *addsub_expr_tail(BTNode *left)
{
    BTNode* node=NULL;
    if(match(ADDSUB))
    {
//        printf("HI\n");
        node=makeNode(ADDSUB, getLexeme());
        advance();
        node->left=left;
        node->right=muldiv_expr();
        //printf("%s\n",node->right->lexeme);
        return addsub_expr_tail(node);
    }
    else
        return left;
}
//muldiv_expr_tail    := MULDIV unary_expr muldiv_expr_tail | NiL
extern BTNode *muldiv_expr_tail(BTNode *left)
{
    BTNode* node=NULL;
    if(match(MULDIV))
    {
        node=makeNode(MULDIV, getLexeme());
        advance();
        node->left=left;
        node->right=unary_expr();
        return muldiv_expr_tail(node);
    }
    else
        return left;
}
// statement := ENDFILE | END | expr END statement           := END | assign_expr END
void statement(void) {
    BTNode *retp = NULL;
    
    if (match(ENDFILE)) {
//        printf("x %d\ny %d\nz %d\n",table[0].val, table[1].val, table[2].val);
        printf("MOV r0 [0]\nMOV r1 [4]\nMOV r2 [8]\nEXIT 0\n");
        exit(0);
    } else if (match(END)) {
//        printf(">> ");
        advance();
    } else {
        retp = assign_expr();
        if (match(END)) {
            count_val=0;
            flag2=0;
//            printf("%s\n",retp->left->lexeme);
            evaluateTree(retp);
//            printf("Prefix traversal: ");
//            printPrefix(retp);
            printf("\n");
            freeTree(retp);
//            printf(">> ");
            advance();
        } else {
//            printf("===\n");
            error(SYNTAXERR);
        }
    }
}

void erro(ErrorType errorNum) {
    printf("EXIT 1\n");
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
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }
    }
    exit(0);
}

int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0;
    int i,j;
    if (root != NULL) {
        switch (root->data) {
            case ID:
            case INT:
                for(i=0;i<8;i++)
                {
                    if(!r[i][0])//看哪個還沒用到
                    {
                        r[i][0]=1;
                        if(root->data==ID)
                        {
                            
                            for(j=0;j<sbcount;j++)
                            {
                                if(!strcmp(table[j].name, root->lexeme))
                                {
                                    r[i][1]=table[j].val;
                                    break;
                                }
                            }
                            printf("MOV r%d [%d]\n",i,j*4);
                        }
                        else
                       {
                        r[i][1]=root->val;
                        printf("MOV r%d %d\n",i,r[i][1]);
                       }
                        retval=i;//register val
                        break;
                    }
                    
                }
                break;
            case ASSIGN:
                
                rv = evaluateTree(root->right);//right value
//                printf("%d\n",root->left->val);
                r[rv][0]=0;
                retval = setval(root->left->lexeme, rv);//左邊丟到右邊
                printf("MOV [%d] r%d\n",retval*4,rv);
                break;
            case ADDSUB:
            case MULDIV:
            case OR:
            case XOR:
            case AND:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+") == 0) {
                    printf("ADD r%d r%d\n",lv,rv);
                    r[rv][0]=0;//release
                    r[lv][1]=r[rv][1]+r[lv][1];
                    retval = lv;
                } else if (strcmp(root->lexeme, "-") == 0) {
                    printf("SUB r%d r%d\n",lv,rv);
                    r[rv][0]=0;
                    r[lv][1]=r[lv][1]-r[rv][1];
                    retval = lv ;
                } else if (strcmp(root->lexeme, "*") == 0) {
                    printf("MUL r%d r%d\n",lv,rv);
                    r[rv][0]=0;
                    r[lv][1]=r[lv][1]*r[rv][1];
                    retval = lv ;
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if (r[rv][1] == 0&&root->right->data!=ID)
                    {
                        error(DIVZERO);
                    }
                    else if(r[rv][1]!=0||root->right->data==ID)
                    {
                        printf("DIV r%d r%d\n",lv,rv);
                        r[rv][0]=0;
                        r[lv][1]=r[lv][1]/r[rv][1];
                        retval = lv ;
                                                                    

                    }
                    
                }
                else if (strcmp(root->lexeme, "&") == 0) {
                   
                    printf("AND r%d r%d\n",lv,rv);
                    r[rv][0]=0;
                    r[lv][1]=r[lv][1]&r[rv][1];
                    retval = lv ;
                }
                else if (strcmp(root->lexeme, "|") == 0) {
                   
                    printf("OR r%d r%d\n",lv,rv);
                    r[rv][0]=0;
                    r[lv][1]=r[lv][1]|r[rv][1];
                    retval = lv ;
                }
                else if (strcmp(root->lexeme, "^") == 0) {
                   
                    printf("XOR r%d r%d\n",lv,rv);
                    r[rv][0]=0;
                    r[lv][1]=r[lv][1]^r[rv][1];
                    retval = lv ;
                }
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}
int getval(char *str) {
    int i = 0;
    int found=0;
    int val=0;
    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
        {
           val= table[i].val;
           found=1;
            break;
        }
            
    if(!found)
    {
        if(flag2)
        {
            error(NOTFOUND);
        }
        else
        {
            
            if (sbcount >= TBLSIZE)
            {
                error(RUNOUT);
            }
            else
            {
                strcpy(table[sbcount].name, str);
                table[sbcount].val = 0;
                val=table[sbcount].val;
                sbcount++;
            }
        }
    }
    
    return val;
}

int setval(char *str, int val) {
    int i = 0;int retval;
    for (i = 0; i < sbcount; i++) {//偵測有沒有一樣的，有就更新值
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = r[val][1];
            retval=i;
            break;
        }
    }
    return retval;
}
void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}
