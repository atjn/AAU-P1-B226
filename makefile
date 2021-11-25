compiler = gcc -std=c17 -Wall -Wextra -Werror -pedantic -O2
cutest = lib/CuTest-AAU/CuTest.c
name = foodForChange
function_files = func/fileHandle.c func/ui.c func/algorithm.c func/utilities.c lib/GNU-Func/strtok_gnu.c
test_runner_name = tests

ifeq ($(OS),Windows_NT)
	extension := exe
else
	extension := out
	ubsan := -fsanitize=undefined -fno-sanitize-recover
endif

$(name).$(extension): $(name).c $(cutest) $(function_files) $(test_runner_name).c
	$(compiler) $(ubsan) -o $(name).$(extension) $(name).c $(cutest) $(function_files) $(test_runner_name).c -lm

$(test_runner_name).c: $(name).c $(cutest) $(function_files)
	./make-tests.sh > tests.c
