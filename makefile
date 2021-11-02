compiler = gcc -std=c17 -Wall -Wextra -Werror -pedantic -O2
cutest = lib/CuTest-AAU/CuTest.c
name = program
function_files = function.c
test_runner_name = tests

ifeq ($(OS),Windows_NT)
	extension := exe
else
	extension := out
endif

$(name).$(extension): $(name).c $(cutest) $(function_files) $(test_runner_name).c
	$(compiler) -o $(name).$(extension) $(name).c $(cutest) $(function_files) $(test_runner_name).c -lm

$(test_runner_name).c: $(name).c $(cutest) $(function_files)
	./make-tests.sh > tests.c
