/*
Calling a Perl subroutine from your C program 

To call individual Perl subroutines, you'll need to remove the call to perl_run() and replace it with a call to
perl_call_argv(). 

That's shown below, in a program I'll call showtime.c. 
*/

#include <stdio.h>
#include <EXTERN.h>
#include <perl.h>
static PerlInterpreter *my_perl;
int main(int argc, char **argv, char **env)
{
  my_perl = perl_alloc();
  perl_construct(my_perl);
  perl_parse(my_perl, NULL, argc, argv, NULL);
  /*** This replaces perl_run() ***/
  perl_call_argv("showtime", G_DISCARD | G_NOARGS, argv);
  perl_destruct(my_perl);
  perl_free(my_perl);
}
