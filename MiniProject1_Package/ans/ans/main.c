//
//  main.c
//  ans
//
//  Created by 朱季葳 on 2021/4/22.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLEN 256
#define TBLSIZE 65535

typedef enum {UNKNOWN, END, INT, ID, ADDSUB, MULDIV, ASSIGN, XOR, AND, OR,
    LPAREN, RPAREN, ENDFILE} TokenSet;
typedef enum {MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTEXIST} ErrorType;

typedef struct {
    char name[MAXLEN];
    int val;
} Symbol;

typedef struct _Node {
    char lexeme[MAXLEN];
    TokenSet data;
    int val;
    struct _Node *left, *right;
} BTNode;

Symbol table[TBLSIZE];
extern Symbol table[TBLSIZE];

int r[8][2];
int value;

extern int getval(void);
extern int setval(char *str, int val);
extern int match (TokenSet token);
extern int evaluateTree(BTNode *root);
extern void printPrefix(BTNode *root);
extern void advance(void);
extern void freeTree(BTNode *root);
extern void statement(void);
extern void error(ErrorType errorNum);
extern BTNode* makeNode(TokenSet tok, const char *lexe);
extern BTNode* factor(void);
extern BTNode* term(void);
extern BTNode* term_tail(BTNode *left);
extern BTNode* expr(void);
extern BTNode* expr_tail(BTNode *left);
static TokenSet getToken(void);
static TokenSet lookahead = UNKNOWN;
extern char* getLexeme(void);
static char lexeme[MAXLEN];
int sbcount = 3;
/*
 Something like Python
 >> y = 2
 >> z = 2
 >> x = 3*y + 4/(2*z)
 
 */

/*
 the only type: integer
 everything is an expression
 statement   := END | expr END
 expr        := term expr_tail
 expr_tail   := ADDSUB term expr_tail | NIL
 term        := factor term_tail
 term_tail := MULDIV factor term_tail | NIL
 factor      := INT | ADDSUB INT | ADDSUB ID | ID ASSIGN expr | ID | LPAREN expr RPAREN
 */

int main() {
    //printf(">> ");
    
    strcpy(table[0].name, "x");
    strcpy(table[1].name, "y");
    strcpy(table[2].name, "z");

    while (1) {
        value = 0;
        statement();
    }
    return 0;
}

/*statement   := ENDFILE | END | expr END*/
void statement(void) {
    BTNode* retp;
    
    if (match(ENDFILE)) {
        printf("MOV r0 [0]\nMOV r1 [4]\nMOV r2 [8]\n");
        printf("EXIT 0\n");
        exit(0);
    } else if (match(END)) {
        //printf(">> ");
        advance();
    } else {
        retp = expr();
        if (match(END)) {
            if (retp->lexeme[0] != '=') {
                error(NOTNUMID);
            }
            
            evaluateTree(retp);
//            printPrefix(retp); printf("\n");
            freeTree(retp);
            
            //printf(">> ");
            advance();
        }
    }
}

void advance(void) {
    lookahead = getToken();
}

/*  expr        := term expr_tail*/
BTNode* expr(void) {
    BTNode *node;
    
    node = term();
    
    return expr_tail(node);
}
/*  expr_tail   := ADDSUB term expr_tail | NIL*/
BTNode* expr_tail(BTNode *left) {
    BTNode *node;
    
    if (match(ADDSUB) || match(XOR) || match(AND) || match(OR)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();
        
        node->left = left;
        node->right = term();
        
        return expr_tail(node);
    }
    else
        return left;
}

/*  term        := factor term_tail*/
BTNode* term(void) {
    BTNode *node;
    node = factor();
    
    return term_tail(node);
}
/*term_tail := MULDIV factor term_tail | NIL*/
BTNode* term_tail(BTNode *left) {
    BTNode *node;
    
    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();
        
        node->left = left;
        node->right = factor();
        return term_tail(node);
    }
    else
        return left;
}

//factor := INT | ADDSUB INT | ADDSUB ID | ID ASSIGN expr | ID | LPAREN expr RPAREN
BTNode* factor(void) {
    BTNode* retp = NULL;
    char tmpstr[MAXLEN];
    
    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        retp->val = getval();
        advance();
    } else if (match(ID)) {
        BTNode* left = makeNode(ID, getLexeme());
        left->val = getval();
        strcpy(tmpstr, getLexeme());
        advance();
        if (match(ASSIGN)) {
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->right = expr();
            retp->left = left;
        } else
            retp = left;
    } else if (match(ADDSUB)) {
        strcpy(tmpstr, getLexeme());
        advance();
        if (match(ID) || match(INT)) {
            retp = makeNode(ADDSUB, tmpstr);
            if (match(ID))
                retp->right = makeNode(ID, getLexeme());
            else
                retp->right = makeNode(INT, getLexeme());
            retp->right->val = getval();
            retp->left = makeNode(INT, "0");
            retp->left->val = 0;
            advance();
        } else
            error(NOTNUMID);
    }
    
    else if (match(LPAREN)) {
        advance();
        retp = expr();
        if (match(RPAREN))
            advance();
        else
            error(MISPAREN);
    } else
        error(NOTNUMID);
    return retp;
}

TokenSet getToken(void) {
    int i;
    char c;
    
    while ((c = fgetc(stdin)) == ' ' || c == '\t');  // ©ø≤§™≈•’¶r§∏
    
    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return ADDSUB;
    } else if (c == '^') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return XOR;
    } else if (c == '&') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return AND;
    } else if (c == '|') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return OR;
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
    } else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isalpha(c) || isdigit(c) || c == '_') {
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
    else
        return UNKNOWN;
}

int match(TokenSet token) {
    if (lookahead == UNKNOWN) advance();
    return token == lookahead;
}

char* getLexeme(void) {
    return lexeme;
}

int evaluateTree(BTNode *root) {
    int i, j;
    int retval = 0, lv, rv;
    if (root != NULL) {
        switch (root->data) {
            case ID:
            case INT:
                for (i = 0; i < 8; i++) {
                    if (!r[i][0]) {
                        r[i][0] = 1;
                        if (root->data == ID) {
                            for(j = 0; j < sbcount; j++) {
                                if(!strcmp(table[j].name, root->lexeme)) {
                                    r[i][1] = table[j].val;
                                    break;
                                }
                            }
                            printf("MOV r%d [%d]\n", i, j * 4);
                        }
                        else {
                            r[i][1] = root->val;
                            printf("MOV r%d %d\n", i, root->val);
                        }
                        retval = i;
                        break;
                    }
                }
                break;
            case ADDSUB:
            case MULDIV:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+") == 0) {
                    printf("ADD r%d r%d\n", lv, rv);
                    r[rv][0] = 0;
                    r[lv][1] = r[lv][1] + r[rv][1];
                    return lv;
                }
                else if (strcmp(root->lexeme, "-") == 0) {
                    printf("SUB r%d r%d\n", lv, rv);
                    r[rv][0] = 0;
                    r[lv][1] = r[lv][1] - r[rv][1];
                    return lv;
                }
                else if (strcmp(root->lexeme, "*") == 0) {
                    printf("MUL r%d r%d\n", lv, rv);
                    r[rv][0] = 0;
                    r[lv][1] = r[lv][1] * r[rv][1];
                    return lv;
                }
                else if (strcmp(root->lexeme, "/") == 0) {
                    printf("DIV r%d r%d\n", lv, rv);
                    r[rv][0] = 0;
                    r[lv][1] = r[lv][1] / r[rv][1];
                    return lv;
                }
                else if (strcmp(root->lexeme, "^") == 0) {
                    printf("XOR r%d r%d\n", lv, rv);
                    r[rv][0] = 0;
                    r[lv][1] = r[lv][1] ^ r[rv][1];
                    return lv;
                }
                else if (strcmp(root->lexeme, "&") == 0) {
                    printf("AND r%d r%d\n", lv, rv);
                    r[rv][0] = 0;
                    r[lv][1] = r[lv][1] & r[rv][1];
                    return lv;
                }
                else if (strcmp(root->lexeme, "|") == 0) {
                    printf("OR r%d r%d\n", lv, rv);
                    r[rv][0] = 0;
                    r[lv][1] = r[lv][1] | r[rv][1];
                    return lv;
                }
            case ASSIGN:
                rv = evaluateTree(root->right);
                r[rv][0] = 0;
                retval = setval(root->left->lexeme, rv);
                printf("MOV [%d] r%d\n", retval * 4, rv);
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}

/* print a tree by pre-order. */
void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}

int getval(void) {
    int i, retval, found;
    
    if (match(INT))
        retval = atoi(getLexeme());
    else if (match(ID)) {
        i = 0; found = 0; retval = 0;
        while (i < sbcount && !found) {
            if (strcmp(getLexeme(), table[i].name) == 0) {
                retval = table[i].val;
                found = 1;
                break;
            } else
                i++;
        }
        if (!found) {
            if (value == 1) {
                error(NOTEXIST);
            }
            if (sbcount < TBLSIZE) {
                strcpy(table[sbcount].name, getLexeme());
                table[sbcount].val = 0;
                sbcount++;
            } else
                error(RUNOUT);
        }
    }
    return retval;
}

int setval(char *str, int val) {
    int i, retval;
    i = 0;
    while (i < sbcount) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = r[val][1];
            retval = i;
            break;
        } else
            i++;
    }
    return retval;
}
/* create a node without any child.*/
BTNode* makeNode(TokenSet tok, const char *lexe){
    if (tok == 6)
        value = 1;
    BTNode *node = (BTNode*) malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}
/* clean a tree.*/
void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void error(ErrorType errorNum) {
    printf("EXIT 1\n");
    switch (errorNum) {
        case MISPAREN:
            printf("Mismatched parenthesis\n");
            break;
        case NOTNUMID:
            printf("Number or identifier expected\n");
            break;
        case NOTFOUND:
            printf("%s not defined\n", getLexeme());
            break;
        case RUNOUT:
            printf("Out of memory\n");
            break;
        case NOTEXIST:
            printf("Variable not exist\n");
        default:
            break;
    }
    exit(0);
}
