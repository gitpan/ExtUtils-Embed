#include <EXTERN.h>
#include <perl.h>

static PerlInterpreter *my_perl;

I32 perl_eval(char *string)
{
  return perl_eval_sv(newSVpv(string,0), G_DISCARD);
}

main (int argc, char **argv, char **env)
{
  char *embedding[] = { "", "-e", "0" };
  STRLEN length;
  my_perl = perl_alloc();
  perl_construct( my_perl );
  perl_parse(my_perl, NULL, 3, embedding, NULL);
                                       /** Treat $a as an integer **/
  perl_run(my_perl);
  perl_eval("$a = 3; $a **= 2");
  printf("a = %d\n", SvIV(perl_get_sv("a", FALSE)));
                                       /** Treat $a as a float **/
  perl_eval("$a = 3.14; $a **= 2");
  printf("a = %f\n", SvNV(perl_get_sv("a", FALSE)));
                                       /** Treat $a as a string **/
  perl_eval("$a = 'rekcaH lreP rehtonA tsuJ'; $a = reverse($a); ");
  printf("a = %s\n", SvPV(perl_get_sv("a", FALSE), length));
  perl_destruct(my_perl);
  perl_free(my_perl);
}

