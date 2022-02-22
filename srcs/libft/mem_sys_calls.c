/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_sys_calls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabidal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:38:13 by maabidal          #+#    #+#             */
/*   Updated: 2022/02/22 19:47:26 by jmaia            ###   ########.fr       */
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
		ft_exit(1, NULL);
	}
	node = malloc(sizeof(t_list));
	if (node == NULL)
	{
		free(tmp);
		write_error(NULL);
		ft_exit(1, NULL);
	}
	node->content = tmp;
	ft_lstadd_front(&g_ptrs_lst, node);
	return (tmp);
}

//pas besoin de verifier que le premier node n'est pas NULL
//car l'address est censee etre presente dans la grace a ft_malloc
void	ft_free(void *add)
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
	free(add);
}

void	ft_exit(int status, char *append_msg)
{
	t_list	*next;

	while (g_ptrs_lst)
	{
		next = g_ptrs_lst->next;
		free(g_ptrs_lst->content);
		free(g_ptrs_lst);
		g_ptrs_lst = next;
	}
	if (status)
		write_error(append_msg);
	exit(status);
}
