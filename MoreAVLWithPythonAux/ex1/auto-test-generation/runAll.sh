        #!/bin/bash
		clear
		chmod 777 *
		
        for i in $( ls *.in | cut -d \. -f1 ); do
            ./main < $i.in > \out_$i.out
        done
		echo "Running Merge checks"
		echo "===================="
		echo ""
		for i in $( ls *.in | cut -d \. -f1 ); do
			echo "#" $i 			
			if [[ `diff $i.out out_$i.out` == "" ]]; then
				echo "Passed!"
			else
				echo "Something goes wrong.."
			fi
        done
		echo ""
		echo "Running VALGRIND checks"
		echo "======================="
		echo ""
		for i in $( ls *.in | cut -d \. -f1 ); do
			sleep 2
			echo "                              #" $i
			echo ""
			valgrind --leak-check=full -v -q ./main < $i.in  > tmp.out 2> log_$i.txt
			if [[ `tail -n-4 log_$i.txt | head -n+1 | cut -d " " -f2-` == "All heap blocks were freed -- no leaks are possible" && `tail -n-1 log_$i.txt | cut -d " " -f2-` == "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 6 from 6)" ]]; then
				tail -n-4 log_$i.txt
				echo ""
				echo "======================== PASSED ========================="
				echo ""
			else
				echo ""
				cat log_$i.txt
				echo ""
				echo "xxxxxxxxxxxxxxxxxxxxxxxx SOMETHING WRONG xxxxxxxxxxxxxxxxxxxxxxxx"
			fi
			rm tmp.out
        done
		if [[ $1 == "log" ]]; then
			for i in $( ls *.in | cut -d \. -f1 );do
				echo "                              #" $i
				echo ""
				cat log_$i.txt
				echo ""
				echo "END OF FILE\n"
				echo ""
			done
		else
			for i in $( ls *.in | cut -d \. -f1 );do
				rm log_$i.txt
			done
		fi
			sleep 2
		
		