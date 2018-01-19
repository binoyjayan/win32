// Stack.h: interface for the CStack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STACK_H__43EBFFEE_978F_4148_A25F_C50F224B19C1__INCLUDED_)
#define AFX_STACK_H__43EBFFEE_978F_4148_A25F_C50F224B19C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STACK_SIZE 200

struct STACK
{
	short status;
	union
	{
		int op;
		double dval;
	};
};

class CStack  
{	
	int top,max;
	STACK stack[STACK_SIZE];
public:
	CStack(int size);
	virtual ~CStack();
	public:
	short Push(int element,short status)
	{
		if(top==max)return 0;
		top++;
		stack[top].status=status;
		stack[top].op=element;
		return 1;
	}
	short Push(double element,short status)
	{
		if(top==max)return 0;
		top++;
		stack[top].status=status;
		stack[top].dval=element;
		return 1;
	}
	STACK Pop()
	{
		STACK ret;
		if(top<0)
		{
			ret.status=0;
			ret.op=0;
		}
		else
			ret=stack[top--];
		return ret;
	}
	STACK Top()
	{
		return stack[top];
	}
	short IsEmpty()
	{
		if(top == -1)
			return 1;
		return 0;
	}

};

#endif // !defined(AFX_STACK_H__43EBFFEE_978F_4148_A25F_C50F224B19C1__INCLUDED_)
