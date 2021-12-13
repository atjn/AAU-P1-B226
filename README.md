# Food For Change - P1 Exam Program for B226
[![GitHub Workflow Status (branch)](https://img.shields.io/github/workflow/status/atjn/AAU-P1-B226/Compile/main)](https://github.com/atjn/AAU-P1-B226/actions/workflows/compile.yml)
[![LGTM Grade](https://img.shields.io/lgtm/grade/cpp/github/atjn/AAU-P1-B226)](https://lgtm.com/projects/g/atjn/AAU-P1-B226)
[![Website](https://img.shields.io/website?label=documentation&url=https%3A%2F%2Fatjn.github.io%2FAAU-P1-B226%2FDoc%2Fhtml%2Findex.html)](https://atjn.github.io/AAU-P1-B226/Doc/html/index.html)

## What is this?

Food For Change helps you cook food that reduce your carbon footprint. Tell it what recipe you want to make, and it gives you three alternative recipes with varying levels of Co2-reductions. You don't need to follow the exact recipes, you can simply use them as inspiration to alter elements of your own recipe.

The program is written for a university exam. Do not expect to see further development of it, but feel free to use the code for your own project!

## How does it work?

The program has a list of recipes that all contain a set of ingredients. Each ingredient is also associated with a category. Every category contains a list of ingredients that should be interchangeable.

When you tell the program to show you a specific recipe, it finds some alternative ingredients from each category, and combines them to match a certain target of reduced Co2-emissions. It generates several of these recipes for different emission targets, to give the user more choice.

All of the data used by the program is located in the `data` folder. You can open the files in any spreadsheet editor and change the data to your liking. Just note that the files need to be saved as semicolon-separated csv files, which is not a standard format, but something we have been forced to use due to crappy Microsoft Excel practices :(

## How to build

The program can be built from source by opening this folder in a terminal and running:
```sh
make
```
For this to work, you need to have `make` and `gcc` installed on your system. If you have an incompatible compiler setup, you can make a copy of the `makefile` and call it something like `makefile-local`. This file will not be uploaded to GitHub, so you can freely modify it to work with your system. When you are done, you can run it with:
```sh
make -f makefile-local
```

Now you can run the program from the command line by writing:
```sh
./foodForChange.out
```
Or on Windows:
```sh
./foodForChange.exe
```

## Documentation

The program is documented with inline comments. Most editors should pick these up and run some form of IntelliSense for you. You can also browse the code through our [Doxygen documentation](https://atjn.github.io/AAU-P1-B226/Doc/html/index.html).

## Testing

The code is runtime-tested with a range of asserts and linked sanitizers. It also has some unit tests that can be run with:
```sh
./foodForChange.out --test
```

## Benchmarking

The algorithm that generates recipes is of an exponential complexity, so if any development is made on the program, it is a good idea to benchmark the changes to see if you just made the program completely unusable ;)

Benchmarks can be run with:
```sh
./foodForChange.out --bench <ingredients>
```

Where `<ingredients>` is an integer, telling the benchmarking utility how many ingredients should be in the recipes that the algorithm is tested on.

It is also possible to append `--accuracy` to the command, which will make the utility measure how close the output recipes are to the optimal recipe combinations for each target.

You can also change the values of the preprocessor directives in `bench/bench.c` to further alter the behavior of the benchmarking utility.
