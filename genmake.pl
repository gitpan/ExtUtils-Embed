use Config;

#$makefile = "t/Makefile";
$cfile = shift;
$makefile = shift || "Makefile";

open(MAKEFILE, "> $makefile") || die "can't open '$makfile' $!";

print MAKEFILE <<"HEAD";
#ExtUtils::Embed test Makefile

RM = $Config{rm} -f
CC = $Config{cc}
PERL = $Config{perlpath}
CFILE = $cfile

HEAD

print MAKEFILE <<'EOM';

STATIC_EXTS = -std 
EXTUTILS_EMBED = $(PERL)  -I../blib -I../lib -MExtUtils::Embed
XS_INIT =  `$(EXTUTILS_EMBED) -e xsinit -- -o xsinit.c $(STATIC_EXTS)`
LD_OPTS =  `$(EXTUTILS_EMBED) -e ldopts -- $(STATIC_EXTS)`
CCFLAGS =  `$(EXTUTILS_EMBED) -e ccflags`
CCDLFLAGS = `$(EXTUTILS_EMBED) -e ccdlflags`
PERL_INC = `$(EXTUTILS_EMBED) -e perl_inc`

OBJS = xsinit.o $(CFILE).o

all : $(CFILE)

xsinit.c :
	$(XS_INIT)
 
xsinit.o :
	$(CC) $(CCFLAGS) -c xsinit.c $(PERL_INC)

$(CFILE).o : 
	$(CC) $(CCFLAGS) -c $(CFILE).c $(PERL_INC)

$(CFILE) : xsinit.c $(OBJS)
	$(CC) $(CCFLAGS) $(CCDLFLAGS) -o $@ $(OBJS) $(LD_OPTS)

clean : 
	$(RM) *.o *~ *.bak xsinit.c embed

EOM

close MAKEFILE;
