/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:47:57 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/24 09:57:23 by juperrin         ###   ########.fr       */
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
# include "../libs/libft_tools/headers/libft.h"

//Typedef and enums headers
# include "definitions.h"
# include "enums.h"

//Chained list header
# include "list.h"
# include "commands.h"
# include "../libs/libft_tools/headers/libft.h"

//Signals headers
# include <signal.h>
# include <bits/sigaction.h>
# include <bits/types/siginfo_t.h>
# include "sighandle.h"

//Init header
# include "init.h"

//Parsing header
# include "parser.h"

#endif
