#!/bin/bash

clear
row=5
col=50
flag=1
input=1
indicator="d"
s=13
t=0;
r_no=$s
c_no=$s
r=(5 5 5 5 5 5 5 5 5 5 5 5 5)
c=(50 51 52 53 54 55 56 57 58 59 60 61 62)
tput cup 30 0
for(( i=1;i<=142;i++ ))
do
	echo -n "="
done
tput cup 1 0
for(( i=1;i<=28;i++ ))
do
	echo  "||"
done
tput cup 1 142
for(( i=1;i<=28;i++ ))
do
	tput cup $i 140
	echo  "||"
done

tput cup 30 65
echo "WELCOME TO THE SNAKE WORLD"
while test $flag -ne 2
	do

		read -s -t .05 -n 1 input
		if [ -z "$input"  ]; then
			tput cup ${r[0]} ${c[0]}
			echo " "
			for(( i=0;i<r_no;i++ ))
			do
				r[i]=$((${r[$i+1]}))
				c[i]=$((${c[$i+1]}))
			done
			if [ "$indicator" = "w" ]; then
				r[r_no]=$((${r[r_no-1]}-1))
				c[r_no]=$((${c[r_no-1]}))
			elif [ "$indicator" = "d" ]; then
				r[r_no]=$((${r[r_no-1]}))
				c[r_no]=$((${c[r_no-1]}+1))
			elif [ "$indicator" = "s" ]; then
				r[r_no]=$((${r[r_no-1]}+1))
				c[r_no]=$((${c[r_no-1]}))
			else
				r[r_no]=$((${r[r_no-1]}))
				c[r_no]=$((${c[r_no-1]}-1))

			fi
			for(( i=0;i<=r_no;i++ ))
			do
				tput cup ${r[$i]} ${c[$i]}
				echo "*"
			done

		elif [ "$input" = "s" ]; then
			indicator="s"
			tput cup ${r[0]} ${c[0]}
			echo " "
			for(( i=0;i<r_no;i++ ))
			do
				r[i]=$((${r[$i+1]}))
				c[i]=$((${c[$i+1]}))
			done
			r[r_no]=$((${r[r_no-1]}+1))
			c[r_no]=$((${c[r_no-1]}))
			for(( i=0;i<=r_no;i++ ))
			do
				tput cup ${r[$i]} ${c[$i]}
				echo "*"
			done
		elif [ "$input" = "d" ]; then
			indicator="d"
			tput cup ${r[0]} ${c[0]}
			echo " "
			for(( i=0;i<r_no;i++ ))
			do
				r[i]=$((${r[$i+1]}))
				c[i]=$((${c[$i+1]}))
			done
			r[r_no]=$((${r[r_no-1]}))
			c[r_no]=$((${c[r_no-1]}+1))
			for(( i=0;i<=r_no;i++ ))
			do
				tput cup ${r[$i]} ${c[$i]}
				echo "*"
			done
		elif [ "$input" = "a" ]; then
			indicator="a"
			tput cup ${r[0]} ${c[0]}
			echo " "
			for(( i=0;i<r_no;i++ ))
			do
				r[i]=$((${r[$i+1]}))
				c[i]=$((${c[$i+1]}))
			done
			r[r_no]=$((${r[r_no-1]}))
			c[r_no]=$((${c[r_no-1]}-1))
			for(( i=0;i<=r_no;i++ ))
			do
				tput cup ${r[$i]} ${c[$i]}
				echo "*"
			done
		elif [ "$input" = "w" ]; then
			indicator="w"
			tput cup ${r[0]} ${c[0]}
			echo " "
			for(( i=0;i<r_no;i++ ))
			do
				r[i]=$((${r[$i+1]}))
				c[i]=$((${c[$i+1]}))
			done
			r[r_no]=$((${r[r_no-1]}-1))
			c[r_no]=$((${c[r_no-1]}))
			for(( i=0;i<=r_no;i++ ))
			do
				tput cup ${r[$i]} ${c[$i]}
				echo "*"
			done

		fi
		for(( i=0;i<=142;i++ ))
		do
			if [ ${r[$r_no-1]} -eq 29 ] && [ ${c[$r_no-1]} -eq $i ]; then
				#flag=2
				#clear
				#tput cup 25 65
				#echo "TUMSE NA HO PAEGA"
				#break
				r_no=13
				c_no=13
				r=(5 5 5 5 5 5 5 5 5 5 5 5 5)
				c=(50 51 52 53 54 55 56 57 58 59 60 61 62)
				tput cup 30 0
				indicator="d"
			fi
		done

		for(( i=1;i<=30;i++ ))
		do
			if [ ${r[$r_no-1]} -eq $i ] && [ ${c[$r_no-1]} -eq 3 ]; then
				#flag=2
				#clear
				#tput cup 25 65
				#echo "REHENDO YAR TUM"
				#break
				indicator="d"
				r_no=13
	c_no=13
r=(5 5 5 5 5 5 5 5 5 5 5 5 5)
c=(50 51 52 53 54 55 56 57 58 59 60 61 62)
tput cup 30 0

			fi
		done
		for(( i=1;i<=30;i++ ))
		do
			if [ ${r[$r_no-1]} -eq $i ] && [ ${c[$r_no-1]} -eq 139 ]; then
				#flag=2
				#clear
				#tput cup 25 65
				#echo "JAAOO YAR.. TUMHARI BAS KI NAHI HAI"
				#break
				indicator="d"
				r_no=13
c_no=13
r=(5 5 5 5 5 5 5 5 5 5 5 5 5)
c=(50 51 52 53 54 55 56 57 58 59 60 61 62)
tput cup 30 0

			fi
		done
		i=$(($i+1))
		if [ $(($i%20)) -eq 0 ]; then
		s=$(($s+1))
		r_no=$s
		c_no=$s
		if [ "$indicator" = "w" ]; then
				r[r_no]=$((${r[r_no-1]}-1))
				c[r_no]=$((${c[r_no-1]}))
			elif [ "$indicator" = "d" ]; then
				r[r_no]=$((${r[r_no-1]}))
				c[r_no]=$((${c[r_no-1]}+1))
			elif [ "$indicator" = "s" ]; then
				r[r_no]=$((${r[r_no-1]}+1))
				c[r_no]=$((${c[r_no-1]}))
			else
				r[r_no]=$((${r[r_no-1]}))
				c[r_no]=$((${c[r_no-1]}-1))

			fi
	done
done
