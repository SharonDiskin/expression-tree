#include "expressionTree.h"

void main()

{
	char str[SIZE];
	Tree tr;
	double res;
	BOOL expressionOK;

	printf("Please enter the expression: ");
	gets(str);
	expressionOK = buildExpressionTree(str, &tr);
	if (expressionOK == TRUE)
	{
		res = calcExpression(tr);
		printf("%s = %.2f", str, res);
	}

	else
		printf("The input expression is not valid\n");
	freeTree(tr);
}
