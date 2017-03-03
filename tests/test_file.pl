open(In, "tests/test_basic.pl") or die "can't open tests/test_basic.pl\n";
while (<In>){
    if( /printf?\s+(.*)/){
        print STDOUT "    $1\n";
    }
}
close In;
