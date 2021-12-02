/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbaich <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:18:40 by adbaich           #+#    #+#             */
/*   Updated: 2021/12/02 10:22:32 by adbaich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_reading(int fd, char *d_main)
{
	char	*buff;
	int		rd_bytes;

	rd_bytes = 1;
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!ft_strchr(d_main, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			ft_free(&buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		d_main = ft_strjoin(d_main, buff);
	}
	ft_free(&buff);
	return (d_main);
}

char	*ft_returning(char	*d_main)
{
	char	*str;
	int		i;

	i = 0;
	while (d_main[i] != '\n' && d_main[i])
		i++;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (d_main[i] && d_main[i] != '\n')
	{
		str[i] = d_main[i];
		i++;
	}
	if (d_main[i] == '\n')
	{
		str[i] = d_main[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_modifying(char *d_main)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (d_main[i] != '\n' && d_main[i])
		i++;
	if (d_main[i] == '\0')
	{
		ft_free(&d_main);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(d_main) - i +1));
	if (!str)
	{
		ft_free (&d_main);
		return (NULL);
	}
	i++;
	j = 0;
	while (d_main[i])
		str[j++] = d_main[i++];
	str[j] = '\0';
	ft_free(&d_main);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*d_main[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	d_main[fd] = ft_reading(fd, d_main[fd]);
	if (!d_main[fd])
	{
		ft_free(&d_main[fd]);
		return (NULL);
	}
	if (!d_main[fd][0])
	{
		ft_free(&d_main[fd]);
		return (NULL);
	}
	line = ft_returning(d_main[fd]);
	d_main[fd] = ft_modifying(d_main[fd]);
	return (line);
}
