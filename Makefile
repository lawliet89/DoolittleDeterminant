det.exe: det.c
	gcc -pedantic -Wall -Wextra -Werror=return-type -Wno-reorder $< -o $@