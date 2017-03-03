use lib "tests";

our $it = "world";
my $it = "my it";
printf "Hello %s!\n", $it;
printf "Hello %s!\n", pkg::test(1, 2);
printf "Hello %s!\n", test(1, 2);
printf "Hello %s!\n", $it;

sub test{
    my ($a, $b) = @_;
    our $it = "test";
    return "world".$a.$b;
}

use pkg;
pkg::test_2();
