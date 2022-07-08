/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yacis@student.42istanbul.com.tr <yacis>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:35:22 by yacis@stude       #+#    #+#             */
/*   Updated: 2022/07/08 14:43:10 by yacis@stude      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char *str)
{
	int		i;
	char	*dizi;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	dizi = malloc(sizeof(char) * (i + 2));
	if (!dizi)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != '\n')
		dizi[i] = str[i];
	if (str[i] == '\n')
	{
		dizi[i] = str[i];
		i++;
	}
	dizi[i] = '\0';
	return (dizi);
}

char	*ft_create(char *str)
{
	int		i;
	int		j;
	char	*dizi;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (ft_free(str));
	dizi = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!dizi)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		dizi[j++] = str[i++];
	dizi[j] = '\0';
	free(str);
	return (dizi);
}

char	*ft_read_and_create(int fd, char *str)
{
	char	*buff;
	int		rc;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rc = 1;
	while (!ft_strchr(str, '\n') && rc != 0)
	{
		rc = read(fd, buff, BUFFER_SIZE);
		if (rc == -1)
			return (ft_free(buff));
		buff[rc] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[256];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str[fd] = ft_read_and_create(fd, str[fd]);
	if (!str[fd])
		return (0);
	line = ft_get_line(str[fd]);
	str[fd] = ft_create(str[fd]);
	return (line);
}
