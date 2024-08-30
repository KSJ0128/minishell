/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungbel <seungbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:37:11 by seungbel          #+#    #+#             */
/*   Updated: 2024/08/29 12:21:21 by seungbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 환경변수 목록 출력 = 이후는  ""를 붙여서 출력하도록 구현
static void	print_envp(char *str)
{
	int		idx;
	int		idx2;
	char	**strlst;

	idx = 0;
	while (str[idx])
	{
		if (str[idx++] == '=')
		{
			strlst = ft_split(str, '=');
			if (!strlst)
				handle_error(-1);
			printf("declare -x %s=", strlst[0]); // 이부분에서 null이 나오면 어떻게 하나? -> input을 받을 때 처리해줘야 함, `=abx': not a valid identifier 이런식으로
			idx2 = 1;
			while (strlst[idx2])
			{
				printf("\"%s", strlst[idx2]);
				free(strlst[idx2++]);
			}
			free(strlst);
			printf("\"\n");
			return ;
		}
	}
	printf("declare -x %s\n", str);	
}

// envp 뒤에 하나를 더 추가해서 새로운 envp를 만드는 부분
static char	**add_envp(char **envp, char *str)
{
	int		idx;
	char	**new_envp;

	new_envp = (char **)malloc(sizeof(char *) * (ft_lstlen(envp) + 2));
	if (!new_envp)
		handle_error(-1);
	idx = 0;
	while (idx < ft_lstlen(envp))
	{
		new_envp[idx] = ft_strdup(envp[idx]);
		if (!new_envp[idx])
			handle_error(-1);
		idx++;
	}
	new_envp[idx++] = ft_strdup(str);
	if (!new_envp)
		handle_error(-1);
	new_envp[idx] = 0;
	return (new_envp);
}

// 이름이 같은게 이미 envp에 등록되었는지 판단
int	find_str(char *en, char *str)
{
	int	len;

	len = (int)ft_strlen(str);
	if (ft_strncmp(en, str, len) == 0
		&& (en[len] == '\0' || en[len] == '='))
		return (1);
	else
		return (0);
}

// 이미 등록된 게 존재하면 덧붙이고 return 1, 없으면 그냥 return 0
int	join_envp(char ***envp, char *str)
{
	char	**strlst;
	int		len;
	int		idx;

	strlst = ft_split(str, '=');
	if (!strlst)
		handle_error(-1);
	len = ft_lstlen(*envp);
	idx = 0;
	while (idx < len)
	{
		if (find_str((*envp)[idx], strlst[0]) && strlst[1])
		{
			free((*envp)[idx]);
			(*envp)[idx] = ft_strdup(str);
			if (!(*envp)[idx])
				handle_error(-1);
			break ;
		}
		idx++;
	}
	free_lst(strlst);
	return (idx < len);
}

void	ft_export(t_file *file, char ***envp)
{
	char	*str;
	char	**new_envp;
	int		idx;

	idx = 0;
	str = 0;
	if (!file)
	{
		while ((*envp)[idx])
			print_envp((*envp)[idx++]);
		return ;
	}
	str = file->data;
	if (*str == '=')
		printf("\'%s\' : not a valid identifier\n", str);
	else
	{
		if (join_envp(envp, str))
			return ;
		new_envp = add_envp(*envp, str);
		free_lst(*envp);
		*envp = new_envp;
	}
}
