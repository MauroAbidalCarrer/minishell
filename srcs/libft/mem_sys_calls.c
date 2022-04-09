/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_sys_calls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:38:13 by maabidal          #+#    #+#             */
/*   Updated: 2022/04/09 20:15:41 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	**mem_man(void)
{
	static t_list	**ptrs;

	if (ptrs == NULL)
	{
		ptrs = malloc(sizeof(t_list *));
		if (ptrs == NULL)
			write_error(NULL, NULL, NULL);
		*ptrs = NULL;
	}
	return (ptrs);
}

//on ne peut pas utiliser lst_new puisaue lstnew utilise ft_malloc
void	*ft_malloc(size_t size)
{
	void	*tmp;
	t_list	*node;
	t_list	**ptrs;

	tmp = malloc(size);
	if (tmp == NULL)
	{
		write_error(NULL, NULL, NULL);
		ft_exit(1);
	}
	node = malloc(sizeof(t_list));
	if (node == NULL)
	{
		free(tmp);
		write_error(NULL, NULL, NULL);
		ft_exit(1);
	}
	node->content = tmp;
	ptrs = mem_man();
	if (ptrs == NULL)
		return (free(tmp), free(node), exit(1), NULL);
	ft_lstadd_front(ptrs, node);
	return (tmp);
}

//pas besoin de verifier que le premier node n'est pas NULL
//car l'address est censee etre presente dans la grace a ft_malloc
void	ft_free(void *add)
{
	t_list	*node;
	t_list	*prev;

	prev = NULL;
	node = *mem_man();
	while (node && node->content != add)
	{
		prev = node;
		node = node->next;
	}
	if (!node)
		return ;
	if (prev)
		prev->next = node->next;
	else
		*mem_man() = node->next;
	free(node);
	free(add);
}

void	ft_exit(int status)
{
	t_list	*next;

	if (mem_man() == NULL)
		exit(1);
	while (*mem_man())
	{
		next = (*mem_man())->next;
		free((*mem_man())->content);
		free(*mem_man());
		*mem_man() = next;
	}
	free(mem_man());
	exit(status);
}

/*
char		*g_exe_name;
t_list	*g_ptrs_lst;
int	main(int ac, char **av)
{
	char **my_av;

	if (ac < 5)
	{
		printf("input at least 4 arguments\n");
		ft_exit(1);
	}

	printf("alocating arguments\n");
	my_av = ft_malloc(sizeof(char *) * (ac + 1));
	printf("done\n\n");
	for (int i = 0; i < ac; i++)
	{
		my_av[i] = ft_malloc(sizeof(char) * (ft_strlen(av[i]) + 1));
		for (int j = 0; av[i][j]; j++)
			my_av[i][j] = av[i][j];
		my_av[i][ft_strlen(av[i])] = 0;
		printf("copied [%s], add = %p\n", my_av[i], my_av[i]);
	}
	my_av[ac] = NULL;
	printf("done\n\nRemoving av[%d] = [%s] add = %p,
 and av[0] = [%s] add = %p\n", ac - 2, av[ac - 2], av[ac - 2], av[0], av[0]);
	ft_remove(my_av[ac - 2]);
	ft_remove(my_av[0]);
	free(my_av[ac - 2]);
	free(my_av[0]);
	printf("done\n\nfreeing av[1]\n");
	ft_free(my_av[1]);
	printf("exiting\n");
	ft_exit(0);
}
*/
