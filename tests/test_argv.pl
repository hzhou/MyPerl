if(!@ARGV){
    die "Usage: $0 [args]\n";
}

foreach my $a (@ARGV){
    print "arg: $a\n";
}
