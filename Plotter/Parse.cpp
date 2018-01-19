// Parse.cpp: implementation of the CParse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Parse.h"
#include "symbol.h"
#include "lex.h"
#include "Stack.h"
#include<math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParse::CParse()
{
}
CParse::~CParse()
{

}
int CParse::InfixToPostfix(CString str)
{
	m_OrgString = str;
	m_OrgString.MakeLower();

	CLex l(m_OrgString.GetBuffer(m_OrgString.GetLength()));
	int t,i = 0;
	double val;
	CStack stack(STACK_SIZE);
	try
	{
		while(1)
		{
			/*val contains the no in case of token: number*/
			t = l.Lex(val);
			if(t == END)
			break;

			switch(t)
			{
			case TOKENERROR:
				nErrorCode = (int)val;
				return TOKENERROR;

			case LEFT_PARENTHESIS:
				stack.Push(LEFT_PARENTHESIS,LEFT_PARENTHESIS);/*push '(' */
				break;

			case RIGHT_PARENTHESIS:
				while(stack.Top().status != LEFT_PARENTHESIS)
				{
					if(stack.IsEmpty())
					{
						nErrorCode = i+1;
						return UNBALANCED_PARENTHESIS;
					}
					post[i].Status = stack.Top().status;
					post[i].op = stack.Pop().op;
					i++;
				}
				if(stack.IsEmpty() == 0 && stack.Top().status==LEFT_PARENTHESIS) stack.Pop();/*clear stack*/
				break;

			/* if operand */
			case DIGIT:
				post[i].Status = DIGIT;
				post[i].value = val;
				i++;
				break;

			/* if operand */
			case VARIABLE_X:
				post[i].Status = VARIABLE_X;
				post[i].value = 0;
				i++;
				break;

			default:  /* if some other functions/operators etc. */
				if(stack.IsEmpty() || Precedence(t) > Precedence(stack.Top().op))
					stack.Push(t,OPERATOR);
				else
				{
					while(stack.IsEmpty()==0 && Precedence(t) <= Precedence(stack.Top().op))
					{
						post[i].Status = OPERATOR;
						post[i].op = stack.Pop().op;
						i++;
					}
					stack.Push(t,OPERATOR);
				}
				break;
			}
		}
		while(stack.IsEmpty() == 0)
		{
			post[i].Status = OPERATOR;
			post[i].op = stack.Pop().op;
			i++;
		}
		m_PostFixSize = i;
		return PARSE_SUCCESS;
	}
	catch(...)
	{
		nErrorCode = i;
		return UNHANDLED_ERROR;
		 
	}
}
int CParse::Precedence(int oper)
{
	switch(oper)
	{
	case PLUS:
	case MINUS:
		return 1;
	case STAR:
	case DIVISION:
		return 2;
	case POWER:
		return 3;
	case UNARY_PLUS:
	case UNARY_MINUS:
		return 4;
	case SIN:
	case COS:
	case TAN:
	case SINH:
	case COSH:
	case TANH:
	case LOG:
	case LOG10:
	case EXP:
	case SQRT:
	case ABS:
		return 5;
	default:
		return 0;
	}
}

template <class T>
T abs(T val)
{
	return val<0?-val:val;
}

int CParse::GetErrorCode()
{
	return nErrorCode;
}
double CParse::Evaluate(double x)
{
	CStack st(STACK_SIZE);
	int i;
	double op1,op2;
	for(i=0;i<m_PostFixSize;i++)
	{
		switch(post[i].Status)
		{
		case VARIABLE_X:
			st.Push((double)x,DIGIT);
			break;
		case DIGIT:
			st.Push(post[i].value,DIGIT);
			break;
		case OPERATOR:
			switch(post[i].op)
			{
			case PLUS:
				op2 = st.Pop().dval;
				op1 = st.Pop().dval;
				st.Push(op1 + op2,DIGIT);
				break;
			case MINUS:
				op2 = st.Pop().dval;
				op1 = st.Pop().dval;
				st.Push(op1 - op2,DIGIT);
				break;
			case STAR:
				op2 = st.Pop().dval;
				op1 = st.Pop().dval;
				st.Push(op1 * op2,DIGIT);
				break;
			case DIVISION:
				op2 = st.Pop().dval;
				op1 = st.Pop().dval;
				st.Push(op1 / op2,DIGIT);
				break;
			case POWER:
				op2 = st.Pop().dval;
				op1 = st.Pop().dval;
				st.Push(pow(op1,op2),DIGIT);
				break;
			case SIN:
				op1 = st.Pop().dval;
				st.Push(sin(op1),DIGIT);
				break;
			case COS:
				op1 = st.Pop().dval;
				st.Push(cos(op1),DIGIT);
				break;
			case TAN:
				op1 = st.Pop().dval;
				st.Push(tan(op1),DIGIT);
				break;
			case SINH:
				op1 = st.Pop().dval;
				st.Push(sinh(op1),DIGIT);
				break;
			case COSH:
				op1 = st.Pop().dval;
				st.Push(cosh(op1),DIGIT);
				break;
			case TANH:
				op1 = st.Pop().dval;
				st.Push(tanh(op1),DIGIT);
				break;
			case ABS:
				op1 = st.Pop().dval;
				st.Push(abs(op1),DIGIT);
				break;
			case LOG:
				op1 = st.Pop().dval;
				st.Push(log(op1),DIGIT);
				break;
			case LOG10:
				op1 = st.Pop().dval;
				st.Push(log10(op1),DIGIT);
				break;
			case EXP:
				op1 = st.Pop().dval;
				st.Push(exp(op1),DIGIT);
				break;
			case SQRT:
				op1 = st.Pop().dval;
				st.Push(sqrt(op1),DIGIT);
				break;
			case UNARY_PLUS://do nothing
				break;
			case UNARY_MINUS:
				op1 = st.Pop().dval;
				st.Push(-op1,DIGIT);
				break;
			}
			break;
		}
	}
	return st.Pop().dval;
}