#include <EXTERN.h>
#include <perl.h>

static PerlInterpreter *my_perl;

/** regex(string, operation)
**
** Used for =~ operations 
**
** Returns the number of successful matches, and
** modifies the input string if there were any.
**/
void xs_init(void);
static int regex(char *string[], char *operation)
{
  int n;

  dSP;                            /* initialize stack pointer      */
  ENTER;                          /* everything created after here */
  SAVETMPS;                       /* ...is a temporary variable.   */
  PUSHMARK(sp);                   /* remember the stack pointer    */
  XPUSHs(sv_2mortal(newSVpv(*string,0))); /* push the string onto the stack  */
  XPUSHs(sv_2mortal(newSVpv(operation,0))); /* push the operation onto stack  */
  PUTBACK;                      /* make local stack pointer global */
  perl_call_pv("regex", G_ARRAY); /* call the function */
  SPAGAIN;                        /* refresh stack pointer         */

  *string = POPp; /* fetch the perhaps modified string */
  n = POPi;       /* fetch the number of substiutions made */

  PUTBACK;
  FREETMPS;                       /* free that return value        */
  LEAVE;                         /* ...and the XPUSHed "mortal" args.*/

  return n;                     /* the number of substitutions made */
}

main (int argc, char **argv, char **env)
{
  char *embedding[] = { "", "regex.pl" };
  char *text;
  int num_matches;

  if(argc < 2) {
    fprintf(stderr, "usage: regex <string>\n");
    exit(1);
  }

  text = argv[1];
  my_perl = perl_alloc();
  perl_construct( my_perl );
  perl_parse(my_perl, xs_init, 2, embedding, NULL);
  perl_run(my_perl);
  
  if(num_matches = regex(&text, "m/([a-z]{4,6})/gi")) {
    AV *array;
    SV *match;
    STRLEN len;
    int i;

    /* get a pointer to the @Matches array */
    array = perl_get_av("Matches", FALSE);

    /* take a look at each element of the @Matches array */
    for(i=0; i < num_matches; i++) {
      match = av_shift(array); /* just like '$match = shift @Matches;' */
      printf("%s ", SvPV(match, len));
    }
    printf("\n\n");
  }
  
  /** Remove all vowels from text **/
  num_matches = regex(&text, "s/[aeiou]//gi");
  if (num_matches) {
    printf("regex: s/[aeiou]//gi...%d substitutions made.\n",
	   num_matches);
    printf("Now text is: %s\n\n", text);
  }

  /** Can we replace Perl with C?? **/
  
  if (!regex(&text, "s/Perl/C/")) {
    printf("Sorry, can't replace Perl with C\n\n");
  } 

  perl_destruct_level = 0;
  perl_destruct(my_perl);
  perl_free(my_perl);
}







