# -*- perl -*-
use ExtUtils::MakeMaker;
use Config;

$VERSION = "1.08";

print "Writing Makefile for ExtUtils::Embed tests...\n";

system "$^X genmake embed t/Makefile";
    
WriteMakefile(
	      VERSION   => $VERSION,
	      NAME  => 'ExtUtils-Embed',
	      'dist'    => {COMPRESS=> 'gzip -9f', SUFFIX=>'gz', 
			     },
	      'linkext' => {LINKTYPE => '' }, 
	      'clean'   => {FILES => "*% *~"},
             );

sub MY::clean {
    my($self) = shift;
    my $string = $self->MM::clean;
    $string .= "\t-cd t/ && \$(MAKE) clean";
    return $string;
}



