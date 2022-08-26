/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:53:32 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/16 10:59:16 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* -------------------------------------------------------------------------- */

int	main(int ac, char **av)
{
	t_cub	cub;
	char	*ext;

	if (ac != 2)
		return (EXIT_FAILURE);
	ext = ft_strrchr(av[1], '.');
	if (ext == NULL || ft_strcmp(ext, ".cub"))
		ft_perror(EXT_ERR, 1);
	process_file_data(av[1], &cub.input, &cub.player);
	init_display_params(&cub);
	return (EXIT_SUCCESS);
}
