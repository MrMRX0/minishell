/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:20:44 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/03 11:03:52 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_stdin_stdout(int *std_in, int *std_out)
{
	*std_in = dup(0);
	*std_out = dup(1);
}

void	restore_stdin_stdout(int std_in, int std_out)
{
	dup2(std_in, 0);
	dup2(std_out, 1);
	close(std_in);
	close(std_out);
}

void	prompt(t_data *data)
{
	data->input = readline(COLOR_BOLD_RED "➜  minishell " COLOR_RESET);
	if (!data->input)
	{
		printf("exit_main\n");
		ft_free(data);
		exit(0);
	}
	data->prompt_call_times++;
}

int	minishell(t_data *data, char **env)
{
	billed_env_list(env, data);
	data->prompt_call_times = 0;
	while (1)
	{
		free_linked_list(&data->token);
		main_signal_handler();
		prompt(data);
		add_history(data->input);
		data->flag = 0;
		data->env = transform_env(data->env_list);
		if (parsing(data->input, data) == 0)
		{
			if (parser(data) == 1)
				return (free(data->input), 0);
			save_stdin_stdout(&data->std_in, &data->std_out);
			execution(data);
			restore_stdin_stdout(data->std_in, data->std_out);
		}
		free(data->input);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	if (ac != 1)
		return (1);
	memset(&data, 0, sizeof(t_data));
	minishell(&data, env);
	return (0);
}
