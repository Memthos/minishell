/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juperrin <juperrin@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 10:47:57 by mperrine          #+#    #+#             */
/*   Updated: 2026/04/28 13:00:12 by juperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Libft header
# include "../libs/libft_tools/includes/main.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <bits/sigaction.h>
# include <bits/types/siginfo_t.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include <limits.h>

//Local headers
# include "shell.h"
# include "init.h"
# include "parser.h"
# include "execute.h"
# include "pipe.h"
# include "redirection.h"
# include "commands.h"
# include "sighandle.h"
# include "outputs.h"
# include "lists.h"
# include "dictionary.h"
# include "types.h"
# include "utils.h"

#endif
