# Minishell
![42](https://img.shields.io/badge/-42-black?style=for-the-badge&logo=42&logoColor=white) ![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

## Description
As beautiful as a shell, minishell is a smaller reproduction of bash
## Features
- Builtin
Command               | args / options | description |
----------------------|------|------------|
`echo`       | `-n ` | print args inside the stdout |
`cd`        | `~` | move beetween folder |
`pwd`     | none | print the complete path to your current folder | 
`export`    | `id=var` | print all env variable  |
`unset`     | `id` | remove a variable to the env |
`env`       | none |  print all assigned variable | 
`exit`     | `code` | exit the shell |


## Getting started
### Download the repository
```
git clone git@github.com:Ernst-Devan/42_Minishell.git Dernst_Minishell
```
### Access and compile
```
cd Dernst_fdf
make
```
### Launch the program
```
./minishell
```
## Acknowledgments
- Basic Shell (https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

