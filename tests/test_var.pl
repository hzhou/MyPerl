my $a = "scope 0";
print "a: $a\n";

for(my $i=0;$i<2;$i++){
    my $a = "scope for";
    print "a: $a\n";
}

{
    my $a = "scope 1 ";
    my $a0 = $a;
    print "a: $a\n";
    $a .= $a0 x 3; # copy on write
    print "a: $a\n";
    my $a = "($a)";  # assignment, copy->1
    print "a: $a\n";
    my $a = $a0;
    print "a: $a\n";
} # dealloc

print "a: $a\n";

my $a=1;
print "a=1; b=a++ + ++a\n";
my $b = $a+++++$a;
print "a:$a, b:$b\n";

my $a=1;
print "a=1; b=++a + ++a\n";
my $b = ++$a + ++$a;
print "a:$a, b:$b\n";
