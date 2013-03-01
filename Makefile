det.exe: det.c
	gcc -g -pedantic -Wall -Wextra -Werror=return-type $< -o $@