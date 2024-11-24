opt=1
while [ "$opt" -lt 6 ]
do

 echo -e "Choose one of following options:\n 1. Create address book\n 2. View address book\n 3. Insert a recored\n 4. Delete a record\n 5. Modify a record\n 6. Exit"
  read opt
  case $opt in
  1) 
  echo "Enter the name of the address book"
     read filename
     if [ -e $filename ] ; then
        rm $filename
      fi
      cont=1
      echo -e "Name \t Number \t Address \t " | cat >> $filename
      while [ "$cont" -gt 0 ]
      do 
        echo -e "\nEnter the name"
        read name
        echo "Enter number $name"
        read number
        echo "Enter address of $name"
        read address
        echo -e "$name \t $number \t\t $address" | cat >> $filename
        echo "Enter 0 to stop and 1 to continue"
        read cont
      done
      ;;
  2) cat $filename
     ;;
  3) echo "Enter the name of the person"
     read name
     echo "Enter number of $name"
     read number
     echo "Enter address of $name"
     read address
     echo -e "$name \t $number \t $address" | cat >> $filename
     ;;
  4)  echo "Enter name or number of recored to be deleted"
      read pattern
      temp="temp"
      grep -v $pattern $filename | cat >> $temp
      rm $filename
      cat $temp | cat >> $filename
      rm $temp
      ;;
  5) echo "Enter name or number of recored to be modified"
      read pattern
      temp="temp"
      grep -v $pattern $filename | cat >> $temp
      rm $filename
      cat $temp | cat >> $filename
      rm $temp
      echo "Enter name of person"
      read name
      echo "Enter number of $name"
      read number
      echo "Enter address of $name"
      read address
      echo -e "$name \t $number \t $address" | cat >> $filename
      ;;
  esac
done

    
      
      
     