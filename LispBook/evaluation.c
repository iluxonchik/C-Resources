#include <stdio.h>
#include "mpc.h"

/* Function Prototypes */
long eval_op(long, char*, long);
long eval(mpc_ast_t*);

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
			long result = eval(r.output); /* evaluate user intput and store the result in 'result' */
			printf("%li\n", result); 
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

long eval(mpc_ast_t* t){
	/* if tagged as a number, return it directly, otherwise it's an expression */
	if (strstr(t->tag, "number"))
		return atoi(t->contents);
	/* the operator is always the 2nd child ( the first child is always '(' ) */
	char* op = t->children[1]->contents;
	/* the third child is stored in 'x' */
	long x = eval(t->children[2]);
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
long eval_op(long x, char* op, long y){
	if (strcmp(op, "+") == 0)
		return x + y;
	if (strcmp(op, "-") == 0)
		return x - y;
	if (strcmp(op, "*") == 0)
		return x * y;
	if (strcmp(op, "/") == 0)
		return x / y;
	return 0;
}