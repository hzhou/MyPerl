package pkg;

our $g_a = "g_a";

my $m_a = "m_a";

sub test{
    printf "g_a=%s, m_a=%s\n", $g_a, $m_a;
}

my $m_a = "m_a 2";

sub test_2{
    printf "g_a=%s, m_a=%s\n", $g_a, $m_a;
}

1;
