#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

/* Create an enumeration of possible lval types */
enum { LVAL_NUM, LVAL_ERR };

/* There are 3 error cases: division by 0, unknow operator or 
	number that os too large to be represented with long */
/* Create an Enumeration of possible error types */
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM};

/* lval stants for Lisp Value */
typedef struct lval{
	int type; /* tells exactly which fields are meaningful to acess */
	long num; /* an experssion is either a number */
	int err;  /* or an error*/
}lval;


/* Function Prototypes */
lval eval_op(lval, char*, lval);
lval eval(mpc_ast_t*);
lval lval_num(long);
lval lval_err(int);
void lval_println(lval);


/* Declare a static buffer for user input of maximum size of 2048 characters */
static char input[2048]; /* "static" is used to make the variable local to the current file */


int main(int argc, char** argv){
	/* create some parsers */
	mpc_parser_t* Number = mpc_new("number");
	mpc_parser_t* Operator = mpc_new("operator");
	mpc_parser_t* Expr = mpc_new("expr");
	mpc_parser_t* Lispy = mpc_new("lispy");


	/* define the parsers above with the following language */
	mpca_lang(MPCA_LANG_DEFAULT,
		"														\
			number    : /-?[0-9]+/ ;							\
			operator  :	'+' | '-' | '*' | '/' ;					\
			expr 	  : <number> | '(' <operator> <expr>+ ')' ; \
			lispy     : /^/ <operator> <expr>+ /$/ ;			\
		",
		Number, Operator, Expr, Lispy);

	/* Print Version and Exit Information */
	puts("Lispy version 0.0.0.1");
	puts("Press Ctrl+c to exit\n");

	while(1){
		/* Prompt output */
		fputs("lispy> ", stdout); /* unlike puts(), fputs() does not append the newline character */

		/* Read the user input */
		fgets(input, 2048, stdin); /* maximum size of in put is 2048 */

		/* attemp to parse the user input */
		mpc_result_t r;
		/* mpc_parse() copies the result of parsing the input using the parser Lispy to r 
		   and returns 1 on sucess and 0 on failure */
		if (mpc_parse("<stdin>", input, Lispy, &r)){
			/* on success, print the AST */
			/* on success the internal structure is copied into r, into the field output */
			lval result = eval(r.output); /* evaluate user intput and store the result in 'result' */
			lval_println(result);
			mpc_ast_delete(r.output); /* delete structure r */
		}
		else{
			/* otherwise, print an error */
			/* the error is copied into the field error of r */
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
	}

	/* undefine or delete parsers */
	mpc_cleanup(4, Number, Operator, Expr, Lispy);

	return 0;
}

lval eval(mpc_ast_t* t){
	/* If tagged as a number */
	if (strstr(t->tag, "number")){
		/* Check if there is some error in conversion */
		errno = 0; /* special variable, used to ensure that the conversion to long goes correctly */
		long x = strtol(t->contents, NULL, 10);
		return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
	}
	/* the operator is always the 2nd child ( the first child is always '(' ) */
	char* op = t->children[1]->contents;
	/* the third child is stored in 'x' */
	lval x = eval(t->children[2]);
	/* iterate over the remaining children using the operator op */
	int i = 3;
	while (strstr(t->children[i]->tag, "expr")){
		/* while the child is an expression */
		/* first operand is 'x', second operand is 't->children[i]', the operator is 'op' */
		x = eval_op(x, op, eval(t->children[i]));
		i++;
	}

	return x;
}

/* use the operator string to see which operation to perform */
lval eval_op(lval x, char* op, lval y){
	/* If either type is an error, return it straight away */
	if(x.type == LVAL_ERR) {return x; }
	if(y.type == LVAL_ERR) {return y; }

	/* If the type is not error, perform the calculations on the number values */
	if (strcmp(op, "+") == 0)
		return lval_num(x.num + y.num);
	if (strcmp(op, "-") == 0)
		return lval_num(x.num - y.num);
	if (strcmp(op, "*") == 0)
		return lval_num(x.num * y.num);
	if (strcmp(op, "/") == 0){
			/* If the 2nd opearand is zero, return an error instead of the result */
			return y.num == 0 ? lval_err(LERR_DIV_ZERO) : lval_num(x.num / y.num);
	}
	return lval_err(LERR_BAD_OP);
}

/* Create a new nymber type lval */
lval lval_num(long x){
	lval v;
	v.type = LVAL_NUM;
	v.num = x;
	return v;
}

/* Create a new error type lval */
lval lval_err(int x){
	lval v;
	v.type = LVAL_ERR;
	v.err = x;
	return v;
}

/* Since an lval can now be one of two things(number or error),
using just printf is not the best option  */
/* Print an lval */
void lval_print(lval v){
	switch(v.type){
		/* if the type is a number */
		case LVAL_NUM:
			printf("%li", v.num);
			break;
		/* In case the type is an error */
			case LVAL_ERR:
			/* Check what type of error it is and print an appropriate error message */
			if(v.err == LERR_DIV_ZERO) {printf("Error: Division By Zero.");}
			if(v.err == LERR_BAD_OP)   {printf("Error: Invalid Operator.");}
			if(v.err == LERR_BAD_NUM)  {printf("Error: Invalid Number.");}
			break;

	}
}
/* Print an lval followed by a newline */
void lval_println(lval v){lval_print(v); putchar('\n');}

/**********************************************************************************************
-- NOTES --
	* One way to evaluate errors is to make them a possible result of an expression evaluation.
	That said, in Lispy, an expression will evaluate either a number or an error.
**********************************************************************************************/