#include <stdio.h>

/* Declare a static buffer for user input of maximum size of 2048 characters */
static char input[2048]; /* "static" is used to make the variable local to the current file */

int main(int argc, char** argv){

	/* Print Version and Exit Information */
	puts("Lispy version 0.0.0.1");
	puts("Press Ctrl+c to exit\n");

	while(1){
		/* Prompt output */
		fputs("lispy> ", stdout); /* unlike puts(), fputs() does not append the newline character */

		/* Read the user input */
		fgets(input, 2048, stdin); /* maximum size of in put is 2048 */

		/* Echo the input back to the user */
		printf("No you're a %s", input);
	}

	return 0;
}