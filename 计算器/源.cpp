#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
char token;
char geta();
void match(char ttoken);
void error();
double exp();
double term();
double power();
double factor();

int main()
{
	double result;
	for (;;)
	{
		token = geta();
		if (token == 'q')
			break;
		result = exp();
		if (token=='\n')
			printf("Result is:%g\n\n", result);
		else
			error();
	}
	return 0;
}

char geta()
{
	char temp;
	do 
	temp = getchar();
	while (isblank(temp));
	return temp;
}

void match(char ttoken)
{
	if (ttoken == token)
		token = geta();
	else
		error();

}

void error()
{
	printf("Error!\n");
	exit(EXIT_FAILURE);
}

double exp()
{
	double temp;
	temp = term();
	while(token=='+'||token=='-')
		switch (token)
		{
		case '+':
			match('+');
			temp += term();
			break;
		case '-':
			match('-');
			temp -= term();
			break;
		}
	return temp;
}

double term()
{
	double temp;
	temp = power();
	while(token=='*'||token=='/')
		switch (token)
		{
		case '*':
			match('*');
			temp *= power();
			break;
		case '/':
			match('/');
			temp /= power();
			break;
		}
	return temp;
}

double power()
{
	double temp;
	temp = factor();
	while (token == '^')
	{
		match('^');
		temp = pow(temp, factor());
	}
	return temp;
}

double factor()
{
	double temp;
	if (token == '(')
	{
		match('(');
		temp = exp();
		match(')');
	}
	else if (isdigit(token) || token == '-' || token == '+')
	{
		ungetc(token, stdin);
		scanf("%lf", &temp);
		token = geta();
	}
	else
		error();
	return temp;
}