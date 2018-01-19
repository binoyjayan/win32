// Lex.cpp: implementation of the CLex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lex.h"
#include "symbol.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLex::CLex(char *st)
{
	s = st;
	m_index = 0;
	prev = '(';
}

CLex::~CLex()
{

}
int CLex::Lex(double &value)
{
	value = 0;
	char ch;
	int i,over;
	/*Ignore white spaces including tabs*/
	while( s[m_index] == ' ' || s[m_index] == '\t')
		m_index++;

	switch(s[m_index])
	{
	case '\0':
		return END;
	case '+':
		m_index++;
		if(prev == '(' || prev == '-' || prev == '*' || prev == '/')
		{
			prev=s[m_index-1];
			return UNARY_PLUS;
		}
		else
		{
			prev=s[m_index-1];
			return PLUS;
		}
	case '-':
		m_index++;
		if(prev == '(' || prev == '+' || prev == '*' || prev == '/')
		{
			prev=s[m_index-1];
			return UNARY_MINUS;
		}
		else
		{
			prev=s[m_index-1];
			return MINUS;
		}
	case '*':
		prev=s[m_index];
		m_index++;		
		return STAR;
	case '/':
		prev=s[m_index];
		m_index++;		
		return DIVISION;
	case '^':
		prev=s[m_index];
		m_index++;
		return POWER;
	case 'x':
	case 'X':
		prev=s[m_index];
		m_index++;
		return VARIABLE_X;
	case '(':
		prev=s[m_index];
		m_index++;
		return LEFT_PARENTHESIS;
	case ')':
		prev=s[m_index];
		m_index++;
		return RIGHT_PARENTHESIS;
	default:
		
		i=0;
		over = 0;		//decimal point is not encountered
		memset(t,0,50);//Initialize temporary buffer
		prev=s[m_index];
		ch = s[m_index];//Digit or alphabet
		if(ch >= '0' && ch <= '9' || s[m_index] == '.')
		{
			while((s[m_index] >= '0' && s[m_index] <= '9') || s[m_index] == '.')
			{
				if( s[m_index]== '.')
				{
					if(!over)
						over = 1;
					else
						break;
				}

				t[i++] = s[m_index++];
			}
			t[i] = 0;//terminate temporary string
			value = atof(t);
			return DIGIT;
		}
		else if(ch >= 'a' && ch <= 'z')
		{
			while(s[m_index] >= 'a' && s[m_index] <= 'z')
			{
				t[i++] = s[m_index++];
			}
			t[i] = 0;//terminate temporary string containing function name

			if(strcmp(t,"sin")  == 0)return SIN;
			if(strcmp(t,"cos")  == 0)return COS;
			if(strcmp(t,"tan")  == 0)return TAN;
			if(strcmp(t,"sinh") == 0)return SINH;
			if(strcmp(t,"cosh") == 0)return COSH;
			if(strcmp(t,"tanh") == 0)return TANH;
			if(strcmp(t,"ln")   == 0)return LOG;
			if(strcmp(t,"exp")  == 0)return EXP;
			if(strcmp(t,"sqrt") == 0)return SQRT;
			if(strcmp(t,"log")  == 0)return LOG10;
			if(strcmp(t,"abs")  == 0)return ABS;
			
			value =m_index;
			return TOKENERROR;
		}
		else
		{
			value = m_index;//error occcured here
			return TOKENERROR;
		}

	}
	return 0;
}
