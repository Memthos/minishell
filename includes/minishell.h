/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:47:57 by mperrine          #+#    #+#             */
/*   Updated: 2026/02/08 12:38:22 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <term.h>
# include <curses.h>

//Libft header
# include "../libs/libft_tools/includes/libft.h"

//Typedef and enums headers
# include "definitions.h"
# include "enums.h"

//Chained lists header
# include "lists.h"
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

//Utils header
# include "utils.h"

#endif
