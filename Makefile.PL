# -*- perl -*-
use ExtUtils::MakeMaker;
use Config;

$VERSION = "1.03";

print "Writing Makefile for ExtUtils::embed tests...\n";

system "$Config{perlpath} t/writetest.pl";
    
WriteMakefile(
	      VERSION   => $VERSION,
	      DISTNAME  => 'ExtUtils-embed',
	      SKIP      => [qw(static dynamic)],
	      'dist'    => {COMPRESS=> 'gzip -9f', SUFFIX=>'gz', 
			     },
	      'linkext' => {LINKTYPE => '' }, 
	      'clean'   => {FILES => "*% *~"},
             );
