# P1 Exam Program for B226
![GitHub Workflow Status (event)](https://img.shields.io/github/workflow/status/atjn/AAU-P1-B226/Compile)

## Developer zone

The program can be build from source by opening this folder in a terminal and running:
```sh
make
```

For this to work, you need to have `make` and `gcc` installed on your system. If you have an incompatible compiler setup, you can make a copy of the `makefile` and call it something like `makefile-local`. This file will not be uploaded to GitHub, so you can freely modify it to work with your system. When you are done, you can run it with:
```sh
make -f makefile-local
```

Now you can run the program from the command line by writing:
```sh
./program.out
```
Or on Windows:
```sh
./program.exe
```

You can also run all unit tests with:
```sh
./program.out --test
```
