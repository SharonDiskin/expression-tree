#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//We are defining a bool type
typedef int BOOL;
#define FALSE 0
#define TRUE 1

#define SIZE 100

/*Structs*/
typedef struct treeNode
{
	char data;
	struct treeNode *left;
	struct treeNode *right;
}TreeNode;

typedef struct tree
{
	TreeNode *root;
}Tree;

/*Functions prototypes*/
TreeNode* creatNode(char data);
BOOL isDig(char ch);
BOOL isSingelDigNumbers(char* str);
BOOL isOperator(char ch);
BOOL isLegalChar(char ch);
BOOL isStringCharsValid(char* str);
BOOL isBracketsValid(char* str);
BOOL isValidInput(char* str);
int findOperatorIndex(char* str, int left, int right);
TreeNode* buildExpressionTreeRec(char* str, int left, int right);
BOOL buildExpressionTree(char* str, Tree* t);
BOOL isLeaf(TreeNode* t);
double makeDig(char c);
double calcArithmetic(double left, char operator, double right);
double calcExpressionRec(TreeNode* t);
double calcExpression(Tree t);
void printTreeInOrderRec(TreeNode* t);
void printTreeInorder(Tree t);
void freeTreeRec(TreeNode* t);
void freeTree(Tree t);
void checkMalloc(void *p);
