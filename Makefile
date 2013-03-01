det.exe: det.cpp
	g++ -g -pedantic -Wall -Wextra -Werror=return-type $< -o $@
