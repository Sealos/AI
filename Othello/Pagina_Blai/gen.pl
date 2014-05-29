use Data::Dumper qw(Dumper);

for (my $i=0; $i <= 5; $i++)
{
	for (my $j=33; $j >= 18; $j--)
	{
		$result = `/usr/bin/time --format "%U" ./main $i $j | tac | egrep -m 1 .`;
		print "$result";
	}
	print "\n"
}