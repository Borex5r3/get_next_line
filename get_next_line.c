/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbaich <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:09:33 by adbaich           #+#    #+#             */
/*   Updated: 2021/12/01 13:29:48 by adbaich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **s)
{
	free(*s);
	*s = NULL;
}

size_t	ft_strlen(char	*s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int	c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (0);
}

static int	joinup(int i, char *s2, char *p, int j)
{
	while (s2[j])
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	size_t	s;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	s = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = (char *)malloc(sizeof(char) * s);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	i = joinup(i, s2, p, j);
	p[i] = '\0';
	ft_free(&s1);
	return (p);
}

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
		if (rd_bytes == -1 )
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
	while (d_main[i] != '\n' &&  d_main[i])
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
	{
		str[j] = d_main[i];
		i++;
		j++;
	}
	str[j] = '\0';
	ft_free(&d_main);
	return (str);
}

char	*get_next_line(int	fd)
{
	static char	*d_main;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	d_main = ft_reading(fd, d_main);
	if (!d_main)
	{
		ft_free(&d_main);
		return (NULL);
	}
	if (!d_main[0])
	{
		ft_free(&d_main);
		return (NULL);
	}
	line = ft_returning(d_main);
	d_main = ft_modifying(d_main);
	return (line);
}

/*int	main()
{
	int	fd;
	
	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}*/
