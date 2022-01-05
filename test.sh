#!/bin/bash

alright=1
for i in {1..32} ; do
	if ! cmp --quiet tests/$i <(./life -s tests/$((i - 1)) -f 1 -w -) ; then
		echo "$((i - 1)) --> $i failed."
		alright=0
	fi
done
(( $alright == 1 )) && echo "Test Pass :D"
