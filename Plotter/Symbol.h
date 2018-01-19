#define END							0
#define PLUS						1
#define MINUS						2
#define STAR						3
#define DIVISION					4
#define POWER						5

#define VARIABLE_X					6
#define LEFT_PARENTHESIS			7
#define RIGHT_PARENTHESIS			8

#define DIGIT						9	
#define SIN							10
#define COS							11
#define TAN							12
#define SINH						13
#define COSH						14
#define TANH						15

#define LOG							16
#define EXP							17
#define SQRT						18
#define LOG10						19

#define OPERATOR					20

#define UNARY_PLUS					21
#define UNARY_MINUS					22

#define ABS							23

#define PARSE_SUCCESS				 1
#define TOKENERROR					-1
#define UNBALANCED_PARENTHESIS		-2
#define UNHANDLED_ERROR				-3