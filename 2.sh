# Title : Write a program to implement an address book with options given below: a) Create address book. b) View address book. c) Insert a record. d) Delete a record. e) Modify a record. f) Exit 
# Code:

ch=1
while [ $ch -ne 7 ]
do
	echo -e "\nEnter the choise to perform operation on Address Book "
	echo -e "1.Create Address Book \n2.Insert a Record \n3.Modify a record \n4.View Address Book \n5.Search Record in Address Book  \n6.Delete a Record  \n7.Exit"
	read ch
	case $ch in
	1)
		echo "Enter the file name"
		read filename
		touch $filename
		echo "Address Book Name $filename Created"
	;;
	
	2)
		if [ -f $filename ]
		then
			echo "Enter the Name of Person"
			read pname
			echo "Enter the Person ID"
			read pid
			echo "Enter the City Name"
			read pcity
			while [ True ]
			do
				echo "Enter the Mobile No."
				read pmob
				if [ ${#pmob} -eq 10 ]
				then
					break
				else
					echo "Enter The valid 10 Digit Mobile No."
				fi
			done

			echo -e "$pname\t$pid\t$pcity\t$pmob" >> $filename
		fi
	;;
	
	3)
		if [ -f $filename ]
		then
			echo -e "\n1.Modify the specific Record \n2.Modify all the Record"
			read ch1
			case $ch1 in
			1)
				echo -e "Enter the Person Id to get Record Line Number"
				read pidrecord
				lineno=$(grep -n $pidrecord $filename | cut -d ":" -f1)
				echo -e "Which field You Want to modify \n1.Person Name \n2.Person ID \n3.City \n4.Mobile No."
				read ch2
				case $ch2 in
				1)
					echo -e "\nEnter name of person"
					read pname
					echo -e "\nEnter Name to Modify"
					read pnamepatt
					sed -i "${lineno} s/$pname/$pnamepatt/" $filename
				;;
				
				2)
					echo -e "\nEnter ID of person"
					read pid
					echo -e "\nEnter ID to Modify"
					read pidpatt
					sed -i "${lineno} s/$pid/$pidpatt/" $filename
				;;
				
				3)
					echo -e "\nEnter city of person"
					read pcity
					echo -e "\nEnter City to Modify"
					read pcitypatt
					sed -i "${lineno} s/$pcity/$pcitypatt/" $filename
				;;
				
				4)
					echo -e "\nEnter mobile no. of person"
					read pmob
					echo -e "\nEnter Mobile No. to Modify"
					read pmobpatt
					sed -i "${lineno} s/$pmob/$pmobpatt/" $filename
				;;
				
				esac
			;;
			
			2)
				echo -e "\nEnter the Old String"
				read patternold
				echo -e "\nEnter the New String"
				read patternnew
				sed -i 's/'$patternold'/'$patternnew'/' $filename			
			;;

			esac

		else
			echo "File Does not Exist"
		fi	
	;;
	
	4)
		if [ -f $filename ]
		then
			cat $filename
		else
			echo "File Does not Exist"
		fi
	;;
	
	5)
		if [ -f $filename ]
		then
			echo -e "Enter the Person ID to search record"
			read pidpatt
			grep $pidpatt $filename
		else
			echo "File Does not Exist"
		fi
	;;
	
	6)
		if [ -f $filename ]
		then
			echo -e "Enter the Person ID to delete record"
			read pidpatt
			echo "Record deleted sucessfully"
			grep $pidpatt $filename
			sed -i '/'$pidpatt'/d' $filename
		else
			echo "File Does not Exist"
		fi
	;;
	
	7)
		echo -e "\nProgram Ended" 
	;;
	esac
done
