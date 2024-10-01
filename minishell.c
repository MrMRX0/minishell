/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 04:20:44 by ibougajd          #+#    #+#             */
/*   Updated: 2024/10/01 06:52:32 by ibougajd         ###   ########.fr       */
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

int minishell(t_data	*data, char **env)
{
	char *input ;
				 
	input = NULL;
	billed_env_list(env, data); //free
	data->prompt_call_times = 0;
	while(1)
	{
		free_linked_list(&data->token);
		data->token = (t_token *){0};
		main_signal_handler();
		input = readline(COLOR_BOLD_RED "➜  minishell " COLOR_RESET);
		// input = "ls -la";
		data->prompt_call_times ++;
		if (!input)
			return(printf("exit_main\n"), ft_free(data),  exit(0), 0);
		add_history(input);
		data->flag = 0;
		data->env = transform_env(data->env_list); // free
		// data->env = env;
		if(parsing(input, data) == 0)
		{
			if(parser(data) == 1)
			{
				free(input);
				return 0;
			}
			save_stdin_stdout(&data->std_in, &data->std_out);
			execution(data);
			restore_stdin_stdout(data->std_in, data->std_out);
		}
		free(input);
	}
	return(0);
}
int main(int ac, char **av, char **env)
{
	(void)av;
	t_data	data;

	if (ac != 1)
		return 1;
	memset(&data, 0, sizeof(t_data));
	minishell(&data, env);
	return (0);
	
}