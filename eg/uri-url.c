
#include <stdio.h>
#include <EXTERN.h>
#include <perl.h>

static PerlInterpreter *my_perl;

SV *
new_uri_url(char *url, char *base)
{
  char code[200];

  /* code to construct a new URI::URL object */
  sprintf(code, "$url = new URI::URL qw(%s %s);", 
	  url, base);

  /* eval the code */
  perl_eval_sv(newSVpv(code,0), G_DISCARD | G_SCALAR);

  /* fetch the $url object */
  return perl_get_sv("url", FALSE);
}

char * 
url_method(SV *obj, char *method, char *arg)
{
  char *ret;
  int count;

  dSP;                            /* initialize stack pointer      */
  ENTER;                          /* everything created after here */
  SAVETMPS;                       /* ...is a temporary variable.   */
  PUSHMARK(sp);                   /* remember the stack pointer    */
  XPUSHs(sv_2mortal(newSVsv(obj)));   /* push the url object onto the stack */
  XPUSHs(sv_2mortal(newSVpv(arg,0))); /* push an optional arg onto the stack */
  PUTBACK;                        /* make local stack pointer global */
  count = perl_call_method(method, G_SCALAR); /* call the method */
  SPAGAIN;                        /* refresh stack pointer         */
                                    
  ret = POPp;                     /* pop the return value from stack */

  PUTBACK;
  
  FREETMPS;                       /* free that return value        */
  LEAVE;                       /* ...and the XPUSHed "mortal" args.*/
  
  return ret;
}

int main (int argc, char **argv, char **env)
{
  char *embedding[] = {"", "-MURI::URL", "-e", "0"};
  SV *url;
  char *ret;

  if(argc < 3) {
    fprintf(stderr, "usage: uri-url <url> <method> [<base>]\n");
    exit(1);
  }

  url = sv_newmortal();

  my_perl = perl_alloc();
  perl_construct( my_perl );

  perl_parse(my_perl, NULL, 4, embedding, NULL); 

  /* argv[1] is the fully qualified or relative url */
  /* argv[2] is the URI::URL method to call */
  /* argv[3] is the url base if needed to resolve relative url's */

  url = new_uri_url(argv[1], (argc==4) ? argv[3] : NULL);
  ret = url_method(url, argv[2], NULL); 
  printf ("%s = '%s'\n", argv[2], ret);

  perl_destruct(my_perl);
  perl_free(my_perl);
}








