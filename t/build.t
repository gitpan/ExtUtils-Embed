
use Cwd;

$cwd = fastcwd;
chdir "t";
system("make clean");

print "1..1\n";

$res = system("make") == 0 ? "ok" : "not ok";

print "$res 1\n";

chdir $cwd;