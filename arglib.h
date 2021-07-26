
/*

Description


*/


#ifndef ARGLIB_H
#define ARGLIB_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFS_IMPLEMENTATION
#include "defs.h"

/* MAX string length of multi-char label */
#define ARG_MAX_SLABEL_LEN 12

enum arglib__dtype{
	ARG_FLAG,
	ARG_INT,
	ARG_FLOAT,
	ARG_STR
};

enum arglib__req{
	ARG_REQ,
	ARG_OPT
};

struct arglib__struct{
	char c_label;
	char s_label[ARG_MAX_SLABEL_LEN];
	char *descr;
	int dtype;
	int flag_req;
	void *pval;
};
typedef struct arglib__struct _ARGS;

/* --- Function declarations --- */

/*
Returns the current number of predefined arguments
*/
int arglib_argnum();


/*
Adds a new argument to the argument list with the input parameters.
If the parameter values are out of bounds, NULL is returned.
*/
_ARGS *arglib_add_option(const char c_label,
						 const char *s_label, 
						 const char *descr,
						 int type, int req);

/*
Initialises argument list and adds the help argument
*/
_ARGS *arglib_init();


/*
Frees option argument list
*/
void arglib_free();

/*
Interprets the command line arguments
and reads options and parameters.
*/
_ARGS *arglib_parse(const int argc, const char *argv[]);

/*
Retrieves the value of an option read from the input arguments.
The value must be cast to the appropriate data type.
Undefined options will return NULL.
Flags will return (int)0 if defined, and NULL otherwise. 
*/
void *arglib_get_value(const char *arg_label);

#endif


/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/

#ifdef ARGLIB_IMPLEMENTATION

/* Data type string names corresponding to data type macro values */
static char* _dtypes[] = {"flag", "int", "double", "string"};

/* String representation for required/optional flags */
static char* _reqflag[] = {"required", "optional"};

/* Length of argument list, global */
size_t ARG_NUM = 0;

/* Global pointer to args */
static _ARGS *ARGLIB_ARG_STRUCT = NULL;


/*
Returns the current number of predefined arguments
*/
int arglib_argnum() {
	return ARG_NUM;
}

/*
Adds a new argument to the argument list with the input parameters.
If the parameter values are out of bounds, NULL is returned.
*/
_ARGS *arglib_add_option(const char c_label,
						 const char *s_label, 
						 const char *descr,
						 int type, int req) {
	
	/* Check if input parameters are out of bounds*/
	if(s_label && ULIB_STRLEN(s_label)+1 > (size_t)ARG_MAX_SLABEL_LEN)
		return NULL;

	if(type < ARG_FLAG || type > ARG_STR)
		return NULL;

	if(req != ARG_REQ && req != ARG_OPT)
		return NULL;
	
	/*Check that labels are unique*/
	size_t i;
	for(i=0; i<ARG_NUM; i++)
	{
		if(s_label && ULIB_STRCMP(s_label,ARGLIB_ARG_STRUCT[i].s_label)==0){
			return NULL;
		}
		if(c_label==ARGLIB_ARG_STRUCT[i].c_label){
			return NULL;
		}
	}

	/* Increase list size*/
	ARG_NUM++;
	ARGLIB_ARG_STRUCT = ULIB_REALLOC(ARGLIB_ARG_STRUCT, sizeof(_ARGS) * ARG_NUM );

	/* Construct new argument element*/
	_ARGS new_arg = {.c_label = c_label, .dtype = type, .flag_req = req};
	
	/* Store string label*/
	if(s_label){
		ULIB_STRCPY(new_arg.s_label, s_label);
	}
	else{
		ULIB_STRCPY(new_arg.s_label, "\0");
	}

	/* Store description*/
	if(descr){
		new_arg.descr = ULIB_MALLOC(ULIB_STRLEN(descr)+1);
		ULIB_STRCPY(new_arg.descr, descr);
	}
	else{
		new_arg.descr = ULIB_MALLOC(2);
		ULIB_STRCPY(new_arg.descr, "\0");
	}

	/* Insert into argument list*/
	ULIB_MEMCPY(&ARGLIB_ARG_STRUCT[ARG_NUM-1], &new_arg, sizeof(_ARGS));

	return ARGLIB_ARG_STRUCT;
}

/*
Initialises option list and adds the help flag
*/
_ARGS *arglib_init() {
	ARG_NUM = 0;

	/*Initialise with first command: help*/
	ARGLIB_ARG_STRUCT = arglib_add_option(0, "help", "Displays valid arguments and exits the program", ARG_FLAG, ARG_OPT);

	return ARGLIB_ARG_STRUCT;
}

/*
Frees option argument list
*/
void arglib_free() {
	size_t i;
	for(i=0; i<ARG_NUM; i++){
		free(ARGLIB_ARG_STRUCT[i].descr);
		free(ARGLIB_ARG_STRUCT[i].pval);
	}
	free(ARGLIB_ARG_STRUCT);
	ARGLIB_ARG_STRUCT = NULL;
	ARG_NUM = 0;
}

/*
Displays information of all predefined options.
*/
static void arglib_help(const char *argv[]) {
	ULIB_PRINTF(" USAGE: %s --[LABEL] [VALUE] --[FLAG]\n", argv[0]);
	ULIB_PRINTF("        %s -[LABEL] [VALUE] -[FLAG]\n", argv[0]);

	size_t i;
	for(i=0; i<ARG_NUM; i++)
	{
		char  c_label = ARGLIB_ARG_STRUCT[i].c_label;
		char* s_label = ARGLIB_ARG_STRUCT[i].s_label;

		/* Char Label*/
		if(c_label != '\0') ULIB_PRINTF(" %5s-%c,", "", c_label);
		else ULIB_PRINTF(" %8s,", "");
		/* Multi-char label*/
		if(*s_label != '\0') ULIB_PRINTF(" --%-12s :", s_label);
		else ULIB_PRINTF(" %14s :", "");

		/* Param type & Req*/
		int padding = ULIB_STRLEN("required")+ULIB_STRLEN("double")+10;
		char paddedStr[padding];
		ULIB_STRCPY(paddedStr, "(");
		ULIB_STRCAT(paddedStr, _dtypes[ARGLIB_ARG_STRUCT[i].dtype]);
		ULIB_STRCAT(paddedStr, ", ");
		ULIB_STRCAT(paddedStr, _reqflag[ARGLIB_ARG_STRUCT[i].flag_req]);
		ULIB_STRCAT(paddedStr, ")");
		ULIB_PRINTF("%-*s",padding, paddedStr);

		/* Description*/
		ULIB_PRINTF("%s\n", ARGLIB_ARG_STRUCT[i].descr);

		/*
		|     -c, --compiler 		:(double, required)      Description
		|     -v, --verbose			:(flag, optional)		 Description
		...
		*/

		/*
		Note: %10s ->  |      text|
			  %-10s -> |text      |

		%5s-%c, --%-16s :(%s, %s)


		*/


	}
}


/*
Displays usage of an input option argument
*/
static void arglib_usage_info(_ARGS *arg) {
	ULIB_PRINTF(" Usage: ");
	/* Char Label*/
	ULIB_PRINTF(" %5s-%c,", "", arg->c_label);
	/* Multi-char label*/
	ULIB_PRINTF(" %2s--%s ", "", arg->s_label);
	/* Parameter data type*/
	if(arg->dtype != ARG_FLAG){
		ULIB_PRINTF(" [%s]", _dtypes[arg->dtype]);
	}
	/* Description*/
	ULIB_PRINTF(" %s\n", arg->descr);
}




/*
Converts a input string 'str' into an integer.
The result is stored at the input pointer 'dest'.
On fail, NULL is returned.
*/
static int *arglib_strtoint(int *dest, const char *str) {
	char *endptr;
	int val;

	/*Convert string to integer.*/
	val = (int) strtol(str, &endptr, 10);
	/*Checks if conversion worked*/
	if(endptr == str){
		return (NULL);
	}
	*dest = val;
	return dest;
}


/*
Convert string to double.
*/
static double *arglib_strtoflt(double *dest, const char *str) {
	char *endptr;
	double val;
	/* Converts string to double*/
	val = (double) strtod(str, &endptr);
	/* Checks if conversion worked*/
	if(endptr == str){
		return (NULL);
	}
	*dest = val;
	return dest;
}


/*
Compares input argument with a predefined option label.

*/
static _ARGS *arglib_cmp_arg(_ARGS *arg, const char *argv) {
	/* Single-char argument*/
	if(ULIB_STRLEN(argv)==2 && argv[0] == '-' && argv[1] != '-')
	{
		if(arg->c_label == argv[1]){
			return arg;
		}
		return NULL;
	}
	/* Multi-char argument*/
	if(ULIB_STRLEN(argv)>2 && argv[0] == '-' && argv[1] == '-')
	{
		if( ULIB_STRCMP(argv+2, arg->s_label) == 0 ){
			return arg;
		}
	}
	return NULL;
}


/*
Casts an input string parameter into a predefined argument's data type,
and stores it in memory.
*/
static _ARGS *arglib_cast_arg(_ARGS *arg, const char *argv) {
	/* Integer type*/
	if(arg->dtype == ARG_INT){
		int idata;
		if(arglib_strtoint(&idata, argv) == NULL){
			return NULL;
		}
		arg->pval = ULIB_MALLOC(sizeof(int));
		*((int*)arg->pval) = idata;
		return arg;
	}
	/* Float type*/
	if(arg->dtype == ARG_FLOAT){
		double fdata;
		if(arglib_strtoflt(&fdata, argv) == NULL){
			return NULL;
		}
		arg->pval = ULIB_MALLOC(sizeof(double));
		*((double*)arg->pval) = fdata;
		return arg;
	}
	/* String type*/
	if(arg->dtype == ARG_STR){
		arg->pval = ULIB_MALLOC(ULIB_STRLEN(argv)+1);
		ULIB_STRCPY(arg->pval, argv);
		return arg;
	}
	return NULL;
}


/*
Compares input arguments with defined argument list
and extracts values. 
*/
_ARGS *arglib_parse(const int argc, const char *argv[]) {

	/* Look for HELP command*/
	size_t i;
	for(i=1; i<(size_t)argc; i++)
	{
		if( ULIB_STRCMP(argv[i], "--help") == 0 || ULIB_STRCMP(argv[i], "-h") == 0 ){
			arglib_help(argv);
			return NULL;
		}
	}
	/* NOTE: consider looping by (1st) defined options
	 * and then input args.
	 * That way, help comnand is read first automatically
	 */

	/*
	Loop over input arguments.
	Ignore the first argument (program call name)
	by beginning the loop at i=1
	*/
	for(i=1; i<(size_t)argc; i++)
	{
		/*Find corresponding defined arg*/
		short found = 0;
		size_t j;
		for(j=1; j<ARG_NUM; j++)
		{
			if(arglib_cmp_arg(&ARGLIB_ARG_STRUCT[j], argv[i])){
				found = 1;
				/*Check if value already read*/
				if(ARGLIB_ARG_STRUCT[j].pval){
					ULIB_FPRINTF(stderr, " [ARGLIB] Error: argument '%s' already defined\n", argv[i]);
					return NULL;
				}
				/*Seek parameter for non-flag arg*/
				if(ARGLIB_ARG_STRUCT[j].dtype != ARG_FLAG){
					/*Catch parameter following label*/
					if(i == (size_t)argc-1 || arglib_cast_arg(&ARGLIB_ARG_STRUCT[j],argv[i+1]) == NULL){	
						ULIB_FPRINTF(stderr, " [ARGLIB] Error: argument '%s' requires %s parameter\n", argv[i], _dtypes[ARGLIB_ARG_STRUCT[j].dtype]);
						arglib_usage_info(&ARGLIB_ARG_STRUCT[j]);
						return NULL;
					}
					i++;
				}
				/*Set defined flag value as '0'*/
				else{
					ARGLIB_ARG_STRUCT[j].pval = ULIB_MALLOC(sizeof(int));
					*((int*)ARGLIB_ARG_STRUCT[j].pval) = 0;
				}
				break;
			}
		}
		if(found == 0){
			ULIB_FPRINTF(stderr, " [ARGLIB] Error: unknown argument '%s'\n", argv[i]);
			exit(-1);
		}
	}

	/*Check that all required arguments are filled*/
	for(i=0; i<ARG_NUM; i++)
	{
		if(ARGLIB_ARG_STRUCT[i].flag_req == ARG_REQ && !ARGLIB_ARG_STRUCT[i].pval){
			ULIB_FPRINTF(stderr, " [ARGLIB] Error: required argument '%s' not defined\n", ARGLIB_ARG_STRUCT[i].s_label);
			return NULL;
		}
	}


	return ARGLIB_ARG_STRUCT;
}



/*
Retrieves the input argument value read from the parser.
The value must be cast to te appropriate data type.
A NULL value means no value was read.
*/
void *arglib_get_value(const char *arg_label) {
	size_t i;
	for(i=0; i<ARG_NUM; i++)
	{
		if( ULIB_STRLEN(arg_label) > 1 && ULIB_STRCMP(ARGLIB_ARG_STRUCT[i].s_label, arg_label) == 0)
			return (ARGLIB_ARG_STRUCT[i].pval);
		if( ULIB_STRLEN(arg_label) == 1 && ARGLIB_ARG_STRUCT[i].c_label == arg_label[0])
			return (ARGLIB_ARG_STRUCT[i].pval);
	}
	return NULL;
}

#endif /* ARGLIB_IMPLEMENTATION */