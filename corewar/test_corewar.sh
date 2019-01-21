for filename in $(find .. -name "*cor");do
	echo $filename
	./corewar $filename -v 6 > ttown;
	./../z42_sources/corewar $filename -v 6 > ttorg
	res=$(diff ttown ttorg && echo "true")
	if [ $res=="true" ]; then
		echo "good" $filename
	else
		echo "ERROR" $filename
	fi 
done 
