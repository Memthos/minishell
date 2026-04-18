/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:47:57 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/17 11:10:27 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Libft header
# include "../libs/libft_tools/includes/main.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>

//Typedef and enums headers
# include "types.h"

# include "shell.h"

//Chained lists header
# include "lists.h"

//Dictionary header
# include "dictionary.h"

//Stack header
# include "stack_lst.h"

# include "execute.h"

//Commands header
# include "commands.h"

//Signals headers
# include <signal.h>
# include <bits/sigaction.h>
# include <bits/types/siginfo_t.h>
# include "sighandle.h"

//Init header
# include "init.h"

//Parsing header
# include "parser.h"

# include "pipe.h"

//Outputs header
# include "outputs.h"

//Utils header
# include "utils.h"

#endif
