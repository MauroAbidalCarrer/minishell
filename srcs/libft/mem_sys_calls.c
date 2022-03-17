/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_sys_calls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:38:13 by maabidal          #+#    #+#             */
/*   Updated: 2022/03/16 21:27:21 by maabidal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//on ne peut pas utiliser lst_new puisaue lstnew utilise ft_malloc
void	*ft_malloc(size_t size)
{
	void	*tmp;
	t_list	*node;

	tmp = malloc(size);
	if (tmp == NULL)
	{
		write_error(NULL);
		ft_exit(1);
	}
	node = malloc(sizeof(t_list));
	if (node == NULL)
	{
		free(tmp);
		write_error(NULL);
		ft_exit(1);
	}
	node->content = tmp;
	ft_lstadd_front(&g_ptrs_lst, node);
	return (tmp);
}

//pas besoin de verifier que le premier node n'est pas NULL
//car l'address est censee etre presente dans la grace a ft_malloc
void	ft_remove(void *add)
{
	t_list	*node;
	t_list	*prev;

	prev = NULL;
	node = g_ptrs_lst;
	while (node->content != add)
	{
		prev = node;
		node = node->next;
	}
	if (prev)
		prev->next = node->next;
	else
		g_ptrs_lst = node->next;
	free(node);
}

void	ft_free(void *add)
{
	ft_remove(add);
	free(add);
}

void	free_all(void)
{
	t_list	*next;

	while (g_ptrs_lst)
	{
		next = g_ptrs_lst->next;
		free(g_ptrs_lst->content);
		free(g_ptrs_lst);
		g_ptrs_lst = next;
	}
}

void	ft_exit(int status)
{
	free_all();
	//rl_clear_history();
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
