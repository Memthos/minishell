*This project has been created as part of the 42 curriculum by mperrine and juperrin.*

## Description

Minishell is a project that consist in recreating a small portion of the [bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)).

The main features to make were the parsing part, with the tokenizer and the lexer. The execution part, that contains the pipes, files redirection, environment variables and signals handling.

We also had to recreate some build-in commands like :

- echo with option -n

- cd with only a relative or absolute path

- pwd with no options

- export with no options

- unset with no options

- env with no options or arguments

- exit with no options

But that's not all, we took this project further with its bonuses !

We recreated commands lists functionalities with the `&&` and `||` operations, in addition to parenthesis `()` for priorities and wildcards `*` (only in the current directory).

We used the [readline](https://bashcookbook.com/bashinfo/source/readline-8.3/doc/readline.pdf) function to mimic the bash input line behavior.

To have a working architecture and to merge the parsing and execution part in a good way, we used an [AST (Abstract syntax tree)](https://en.wikipedia.org/wiki/Abstract_syntax_tree), which can handle priorities in a very good way.

## Instructions

To use this beautiful minishell, you should first compile it like this :

`make` or `make all`.

Then you can execute the program like this :

`./minishell`.

You can alternatively use `make re` to recompile it.

## Resources

To make this project, we used the following resources :

The [bash manual](
https://www.gnu.org/software/bash/manual/bash.html).

The [AST (Abstract syntax tree)](https://en.wikipedia.org/wiki/Abstract_syntax_tree) data structure wiki page.

