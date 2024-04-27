/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atudor <atudor@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:03:21 by atudor            #+#    #+#             */
/*   Updated: 2024/04/17 17:03:24 by atudor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
# include "../exec/exec.h"

void export_unset_var(t_data *data, char *name) {
    t_export *prev;
    t_export *unset;

    prev = get_existing_node_position(data, name);
    if (!prev || !prev->next)
        return;

    unset = prev->next; // Get the node to remove
    prev->next = unset->next; // Unlink the node from the list

    // Safely free the node
    if (unset->name) {
        free(unset->name);
        unset->name = NULL;
    }
    if (unset->value) {
        free(unset->value);
        unset->value = NULL;
    }
    if (unset->str) {
        //free(unset->str);
        unset->str = NULL;
    }
    //free(unset); // Finally, free the node itself
}



// void	export_unset_var(t_data *data, char *name)
// {
// 	t_export	*prev;
// 	t_export	*unset;

// 	prev = get_existing_node_position(data, name);
// 	if (!prev || !prev->next)
// 		return ;
// 	unset = prev->next;
// 	if (unset->next)
// 		prev->next = unset->next;
// 	else
// 		prev->next = NULL;

// 	// free(unset->name);
// 	// unset->name = NULL;
// 	// free(unset->value);
// 	// unset->value = NULL;
// 	// free(unset->str);
// 	// unset->str = NULL;
// 	// //free(unset);
// }

// void export_unset_var(t_data *data, char *name) {
//     t_export *prev;
//     //t_export *unset;

//     // Find the node just before the one to remove
//     prev = get_existing_node_position(data, name);
//     if (!prev || !prev->next)
//         return;

//     // 'unset' is the node to remove
//     //unset = prev->next;

//     // Relink the list before freeing the node
//    // prev->next = unset->next;

//     // Properly free the content of the node and the node itself
//     //free(prev->next->name);
// 	prev->next->name = "?";
//     //free(unset->value);
//     //free(unset->str);
//     //free(unset);
// }


void	ft_unset(t_xcmd *xcmd, t_data *data)
{
	int		i;

	i = 1;
	while (xcmd->cmd[i])
	{
		printf("unset: %s\n", xcmd->cmd[i]);
		env_unset_var(&data->env_list, xcmd->cmd[i]);
		export_unset_var(data, xcmd->cmd[i]);
		i++;
	}
	xcmd->exit_status = 0;
}
