echo "===" >> $1

awk ' 
{
	if($0 == "===") {
		exit 1
	} else if(NF < "'"$3"'" || NF < "'"$2"'") {
		print >> "'"$1"'";
	} else {
		temp = $"'"$3"'";
		$"'"$3"'" = $"'"$2"'";
		$"'"$2"'" = temp;
		print >> "'"$1"'";
	}
}
' $1