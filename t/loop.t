if($] < 5.00393) {
    print "1..0\n";
    warn "skipping loops tests for Perl version $]\n";
    exit();
}

print "1..18\n";

$p = "t/loop";

sub test {
    my($num, $code) = @_;
    $pat = "ok $num.*" x 10;
    $s = `$p -e '$code; print "ok $num"'`;
    print "ok $num\n" if $s =~ /$pat/;
}

@n = split //, `$p -e 'print "."'`;
$n = 10;
for (1..scalar @n) {
    print "ok $_\n";
}

test ++$n, 'use FileHandle (); FileHandle->new;'; 

test ++$n, <<'EOF';
package Scotch;
@ISA = qw(Drink);
package Drink;
sub drink {1}

package main;
drink Scotch or die;

EOF

#syntax error, currently leaks
test ++$n, 'eval q($oops =;)';

for (qw{strict English}) {
    test ++$n, "use $_";
}

#reset rs ok?
test ++$n, 'die unless $/ eq "\\n"; $/="";';

test ++$n, 'die if ' . 
    join(' || ', 
    'defined $scalar',
    'defined @array',
    'defined %hash')    .
    ';$scalar++; @array = (1..3); %hash = (a=>1);';

printf "ok %d\n", ++$n if(`$p t/eval.test` =~ /ok 16\n1\.\.16/);

