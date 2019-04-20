input=$1
x=$2
y=$3
c=$4
echo "$input"
echo "start!"
./paintBucket $input $x $y $c sample.out
./paintBucket-ref $input $x $y $c sample-ref.out
diff sample.out sample-ref.out
echo "finish!"
