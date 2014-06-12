
for (my $j=23; $j >= 14; $j--)
{
	$result = `/usr/bin/time --format "%U" ./main 1 $j | tac | egrep -m 1 .`;
	print "$result";
}
print "\n"
