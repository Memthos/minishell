*This project has been created as part of the 42 curriculum by juperrin and mperrine.*

## Description

Minishell is a project that consist of recreating a small portion of [bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)).

There are two main features inside Minishell, the parsing and the execution.
Inside the parsing, the main steps are the **tokenization**, and the creation of an [**AST**](https://en.wikipedia.org/wiki/Abstract_syntax_tree) (Abstract syntax tree).

Using an AST allowed us to be able to structure the command being parsed in an effective way to handle the bonuses with a simpler approach.

On the side of the execution, the AST is read recursively and different actions are made depending of the token of the node being looked at. We can cite the **files redirection**, **update of environment variables** and the **signals handling**.

We also had to recreate some built-in commands like :

- **echo** with option **-n**

- **cd** with only a relative or absolute path

- **pwd** with no options

- **export** with no options

- **unset** with no options

- **env** with no options or arguments

- **exit** with no options

But that's not all, we took this project further with its bonuses!

We recreated commands lists functionality with `&&` and `||` operations. In addition to these, parenthesis `()` are also implemented and are used to simulate priorities. There is also an implementation of wildcards `*` (only in the current directory).

We used the [readline](https://bashcookbook.com/bashinfo/source/readline-8.3/doc/readline.pdf) function to mimic the bash input line behavior.

## Instructions

To use this beautiful minishell, you should first compile it with one of those commands :

```bash
make
make bonus
```

Then you can execute the program like this :
```bash
./minishell
```

You can also clean the object files and the executable with these commands :
```bash
make clean
make fclean
```

Or rebuild the project with this command :
```bash
make re
```

## Resources

To make this project, we used the following resources :

The [bash](https://www.gnu.org/software/bash/manual/bash.html) manual.

This Open Group [guide](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html) for the AST structure.

The [AST](https://en.wikipedia.org/wiki/Abstract_syntax_tree) (Abstract syntax tree) data structure wiki page.

AI was used to check how some special cases are parsed inside bash and to fix spelling errors in this readme.

