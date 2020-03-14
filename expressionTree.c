#include "expressionTree.h"

/*This function creates new node*/
TreeNode* creatNode(char data)
{
	TreeNode* newNode;
	newNode = (TreeNode*)malloc(sizeof(TreeNode));
	checkMalloc(newNode);
	newNode->data = data;
	newNode->right = NULL;
	newNode->left = NULL;

	return newNode;
}

/*This function checks if the char is digit*/
BOOL isDig(char ch)
{
	return ('0' <= ch && ch <= '9');
}

/*This function checks if all the numbers in the a certain string are one digits numbers */
BOOL isSingelDigNumbers(char* str)
{
	int i = 0;
	char prevChar = str[i++]; //We intialize prevChar to be str[0] than we increase i by one
	while (str[i] != '\0')
	{
		if (isDig(prevChar) && isDig(str[i])) //If a certain charcter and the previous one are both digits - return false
			return FALSE;
		prevChar = str[i];
		i++;
	}
	return TRUE;
}

/*This function check if a charcter is an operator*/
BOOL isOperator(char ch)
{
	return(ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '%');
}

/*This function check is the charcter is an operand, an opertor, or bracket. If not it returns false*/
BOOL isLegalChar(char ch)
{
	return(ch == '(' || ch == ')' || isOperator(ch) || isDig(ch));
}

/*This function check if all the chars in the string we got are valid*/
BOOL isStringCharsValid(char* str)
{
	while (*str != '\0') //While we get to the end of the string we check each char
	{
		if (!isLegalChar(*str))
			return FALSE;
		str++;
	}
	return TRUE;
}

/*This function Checks if each brecket has a matching one*/
BOOL isBracketsValid(char* str)
{
	int bracketsCounter = 0;
	while (*str != '\0') //We scan the whole string and checks we have a matching bracket for each bracket
	{
		if (*str == '(') //We increase the counter for Each bracket that looks like this: '('
			bracketsCounter++;
		if (*str == ')') //We decrease the counter for each bracket that looks like this: ')'
			bracketsCounter--;
		str++;
	}

	if (bracketsCounter == 0) //If the bracket counter at the end is 0, it means each bracket have a mateching closing one
		return TRUE;
	else
		return FALSE;
}

/*This function checks if the string the user enterd is valid according the parmeters we recieved*/
BOOL isValidInput(char* str)
{
	return isSingelDigNumbers(str) && isStringCharsValid(str) && isBracketsValid(str);
}


/*This function finds the index of the main operator in each string.
The function is intizaling two counters - the first one is the brackets counter.
The brackets counter counts how many counters we have in the begining of the expression.
If we have for example two counter, than the second operator in the string will be the root of the
string built from the array*/
int findOperatorIndex(char* str, int left, int right)
{
	int i = left;
	int countBrackets = 0, countOperator = 0;

	while (str[i++] == '(') //For each brackets we have we increase our counter brackets
		countBrackets++;

	while (left <= right)
	{
		if (isOperator(str[left])) //We countt operator
			countOperator++;
		if (countBrackets == countOperator) //If the counters are eqaule it means the index we now scan is the index of the operator we look for
			return left;
		left++;
	}
	return -1; //I there is no operator in the string, return -1
}

/*This function scan an array and returns the index of the first digit if finds*/
int findNumberIndex(char* str, int left, int right)
{
	while (left <= right)
	{
		if (isDig(str[left]))
			return left;
		left++;
	}
	return -1;
}

/*This function build and expression tree recursivly*/
TreeNode* buildExpressionTreeRec(char* str, int left, int right)
{
	TreeNode* t;
	int currOperatorIndex;
	currOperatorIndex = findOperatorIndex(str, left, right);

	if (currOperatorIndex == -1) //If the current index is -1, it means there are no operators left in the sub array
	{
		int numIndex = findNumberIndex(str, left, right);  //We look for a digit to add to the tree
		if (numIndex == -1) //If we couldn't find a digit, it means we got to the end of the tree and we return NULL
			return NULL;
		else //We did find a number
		{
			t = creatNode(str[numIndex]); //We create a node from the number
			return t; //And adds it to the tree
		}
	}
	else //We found an operator
	{
		t = creatNode(str[currOperatorIndex]); //We are creating a node from the opeartor we found
		//And we are making a partition of the string to all that is left to the opeartor, and all that is right to the operator
		t->left = buildExpressionTreeRec(str, left + 1, currOperatorIndex - 1);
		t->right = buildExpressionTreeRec(str, currOperatorIndex + 1, right - 1);
		return t;
	}
}

BOOL buildExpressionTree(char* str, Tree* t)

{
	if (!isValidInput(str)) { //If the string enterd is illegal - return false
		t->root = NULL;
		return FALSE;
	}

	else //The string is legal - we build an expression tree from the string we got
	{
		t->root = buildExpressionTreeRec(str, 0, strlen(str) - 1);
		return TRUE;
	}
}

/*This function checks if the node is a leaf*/
BOOL isLeaf(TreeNode* t)
{
	if (t->left == NULL && t->right == NULL)
		return TRUE;
	return FALSE;
}

double makeDig(char c)
{
	return c - '0';
}

/*This function recieve two numbers and the opertor between them (as char) and calcaultes the arithmetic expression*/
double calcArithmetic(double left, char operator, double right)
{
	switch (operator) //Each case returns a diffent aritmetic expression
	{
	case '+':
		return left + right;
	case '-':
		return left - right;
	case '/':
		return left / right;
	case '*':
		return left * right;
	case '%':
		return (int)left % (int)right;
	default:
		return 0;
	}
}

/*This function calculates the expression in represented by the tree recursivly*/
double calcExpressionRec(TreeNode* t)
{
	if (isLeaf(t)) { //If the node is a leaf, convert the data inside to a digit and return it
		return makeDig(t->data);
	}
	else //Call a function that will calculate an arithmetic expression from the the rest of the tree
		return calcArithmetic(calcExpressionRec(t->left), t->data, calcExpressionRec(t->right));
}

/*This function return the result of the expression represented in the tree*/
double calcExpression(Tree t)
{
	return calcExpressionRec(t.root);
}

/*This function print the tree in order recursivly*/
void printTreeInOrderRec(TreeNode* t)
{
	if (t == NULL)
		return;
	else
	{
		printTreeInOrderRec(t->left);
		printf("%c ", t->data);
		printTreeInOrderRec(t->right);
	}
}

/*This function  calls a function that print the tree recursivly*/
void printTreeInorder(Tree t)
{
	printTreeInOrderRec(t.root);
}

/*This function free the tree recursivly*/
void freeTreeRec(TreeNode* t)
{
	if (t != NULL)
	{
		freeTreeRec(t->left);
		freeTreeRec(t->right);
		free(t);
	}
}

/*This function calls a function that free the tree recursivly*/
void freeTree(Tree t)
{
	freeTreeRec(t.root);
}

/*This function checks that the dynamic allocation was succsessful*/
void checkMalloc(void *p)
{
	if (!p)
	{
		printf("Memmory allocaion error!\n");
		exit(-1);
	}
}
