use Config;

$makefile = "t/Makefile";

open(MAKEFILE, "> $makefile") || die "can't open '$makfile' $!";

print MAKEFILE <<"HEAD";
#ExtUtils::embed test Makefile

RM = $Config{rm} -f
LD = $Config{ld}
CC = $Config{cc}
CCFLAGS = $Config{ccflags}
CCDLFLAGS = $Config{ccdlflags}

PERL = $Config{perlpath}
PERL_CORE = $Config{archlib}/CORE

STATIC_EXTS = -std 

HEAD

print MAKEFILE <<'EOM';

XS_INIT =  $(PERL)  -I../blib -I../lib -MExtUtils::embed -e xsinit --
LD_OPTS =  $(PERL)  -I../blib -I../lib -MExtUtils::embed -e ldopts --

OBJS = xsinit.o embed.o

all : embed

xsinit.c :
	`$(XS_INIT) -o xsinit.c $(STATIC_EXTS)`
 
xsinit.o :
	$(CC) $(CCFLAGS) -c xsinit.c -I$(PERL_CORE) 

embed.o : 
	$(CC) $(CCFLAGS) -c embed.c -I$(PERL_CORE) 

embed : xsinit.c $(OBJS)
	$(CC) $(CCFLAGS) $(CCDLFLAGS) -o $@ $(OBJS) `$(LD_OPTS) $(STATIC_EXTS)` 

clean : 
	$(RM) *.o *~ *.bak xsinit.c embed

EOM

close MAKEFILE;
