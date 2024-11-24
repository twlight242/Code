opt=1
while["$opt" -lt 6]

do
	echo -e "Choose one of following options:\n 1. Create address book\n 2. View address book\n 3. Insert a recored\n 4. Delete a record\n 5. Modify a record\n 6. Exit"
	read opt
	case $opt in 
		1)
