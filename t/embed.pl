
use Config '%Config';

sub test {
    my($num,$true,$msg) = @_;
    print($true ? "ok $num $msg\n" : "not ok $num $msg\n");
}

@exts = ('DynaLoader', split(' ', $Config{static_ext}));

printf "1..%d\n", scalar @exts;

foreach $module (@exts) {
    eval { require "$module.pm"; };

    test ++$i, ! $@, $@;
}
