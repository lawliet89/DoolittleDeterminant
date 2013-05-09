det: det.c
	gcc -g -pedantic -Wall -Wextra -Werror=return-type $< -o $@
