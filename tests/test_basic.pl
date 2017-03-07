print 'Hello World, once!'; print "\n";
print "Hello World, ", "twice!\n";
# -- printf --
printf "1/3 = %f\n", 1/3;
# -- scalar --
our $a = 1+1;
printf "1+1 = %d\n", $a;
# -- scalar and string 
my ($a, $b) = (1, 2);
print "a is $a, b is $b\n";
# -- array --
my @a = (3, 2, 1);
print "array a: @a - ", @a, "\n";
# -- hash --
my %a = (a=>10, b=>11, c=>12);
printf "hash a{a} = %d\n", $a{a};
# -- switch --
print "if-else: ";
my $x = 'test';
if ($x eq $x) { print "ok\n";} else {print "not ok\n";}
# -- while --
print "while 1 to 10:";
my $i=1;
while($i<=10){print " ", $i; $i=$i+1;}
print "\n";
# -- for --
print "  for 1 to 10:";
for(my $i=1;$i<=10;$i++){print " ",$i;} 
print "\n";
# -- bare block --
{ # DEBUG
1
}
