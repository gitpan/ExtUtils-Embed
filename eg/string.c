#include <stdio.h>
#include <EXTERN.h>
#include <perl.h>
static PerlInterpreter *my_perl;
int perl_eval(char *string)
{
  char *argv[2];
  argv[0] = string;
  argv[1] = NULL;
  perl_call_argv("_eval_", 0, argv);
}
main (int argc, char **argv, char **env)
{
  char *embedding[] = { "", "-e", "sub _eval_ { eval $_[0] }" };
  STRLEN length;
  my_perl = perl_alloc();
  perl_construct( my_perl );
  perl_parse(my_perl, NULL, 3, embedding, NULL);
                                       /** Treat $a as an integer **/
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

