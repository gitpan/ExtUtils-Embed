# -*- perl -*-
use ExtUtils::MakeMaker;
use Config;

$VERSION = "1.06";

print "Writing Makefile for ExtUtils::embed tests...\n";

system "$Config{perlpath} genmake.pl embed t/Makefile";
    
WriteMakefile(
	      VERSION   => $VERSION,
	      DISTNAME  => 'ExtUtils-embed',
	      SKIP      => [qw(static dynamic)],
	      'dist'    => {COMPRESS=> 'gzip -9f', SUFFIX=>'gz', 
			     },
	      'linkext' => {LINKTYPE => '' }, 
	      'clean'   => {FILES => "*% *~"},
             );
