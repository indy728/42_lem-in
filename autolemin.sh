header()
{
	clear;
	echo "\x1B[31m    .    _    _ _______ ____  _      ______ __  __ _____ _   _";
	echo "\x1B[32m    /\  | |  | |__   __/ __ \| |    |  ____|  \/  |_   _| \ | |";
	echo "\x1B[33m   /  \ | |  | |  | | | |  | | |    | |__  | \  / | | | |  \| |";
	echo "\x1B[34m  / /\ \| |  | |  | | | |  | | |    |  __| | |\/| | | | | . \` |";
	echo "\x1B[35m / ____ \ |__| |  | | | |__| | |____| |____| |  | |_| |_| |\  |";
	echo "\x1B[36m/_/    \_\____/   |_|  \____/|______|______|_|  |_|_____|_| \_|\x1B[0m";

	echo "\x1B[31m         ___      \x1B[32m  _  __  ___   _   _   __ ___  ___   ___";
	echo "\x1B[31m        / o.)_ __ \x1B[32m / |/ /,' _/ .' \ / \,' // o |/ o | / _/";
	echo "\x1B[31m       / o \ \V / \x1B[32m/ || /_\ \`. / o // \,' // _,'/  ,' / _/";
	echo "\x1B[31m      /___,'  )/ \x1B[32m/_/|_//___,'/_n_//_/ /_//_/  /_/\`_\/___/";
	echo "\x1B[31m             //\x1B[0m";
	echo; echo; echo;
}

maps()
{
	for map in $1/* 
	do
	header;
	echo "\x1B[35m***********INPUT FILE************\x1B[0m";
	echo $map;
	echo "\x1B[35m*********************************\x1B[0m";

	echo "\x1B[32m***********CAT INPUT************\x1B[0m";
	cat -e $map;
	echo "\x1B[32m********************************\x1B[0m";

	echo "\x1B[36m*********LEM-IN RESULT**********\x1B[0m";
	./lem-in < $map;
	echo "\x1B[36m********************************\x1B[0m";

	read;
done;
}

clear;
header;
printf "\x1B[32mSelect farms: [s]mall | [m]edium | [l]arge | [e]rror: \x1B[0m";
read response;

if [ $response = "s" ]
	then	maps ./maps/small
elif [ $response = "m" ]
	then	maps ./maps/medium
elif [ $response = "l" ]
	then	maps ./maps/large
elif [ $response = "e" ]
	then	maps ./maps/error
else
	exit
fi
clear;
exit;
