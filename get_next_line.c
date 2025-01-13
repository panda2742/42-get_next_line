/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehosta <ehosta@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:14:50 by ehosta            #+#    #+#             */
/*   Updated: 2025/01/13 18:58:51 by ehosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	get_nl_pos(const char *s, int len)
{
	ssize_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
		return ((-1 * (len == 0)) + (i * len));
	return (i);
}

char	*join_res_buffer(char *res, char *buffer, int *end, int is_nl)
{
	ssize_t	eof_buffer;
	size_t	res_len;
	size_t	out_len;
	size_t	i;
	ssize_t	j;
	char	*out;

	printf("\n\t1 * buffer: %s$", buffer);
	res_len = 0;
	eof_buffer = get_nl_pos(buffer, 1);
	printf("\n\t2 * buffer: %s$", buffer);
	if (!is_nl && !res && !eof_buffer)
		return (NULL);
	if (is_nl)
	{
		*end = 1;
		eof_buffer++;
	}
	if (res)
		res_len = ft_sstrlen(res);
	out_len = res_len + eof_buffer;
	out = malloc(out_len + 1);
	if (!out)
		return (NULL);
		
	i = 0;
	j = 0;
	while (res && res[j])
		out[i++] = res[j++];
	j = 0;
	printf("\n\t3 * buffer: %s$", buffer);
	while (j < eof_buffer)
		out[i++] = buffer[j++];
	out[i] = 0;
	printf("\n\t4 * buffer: %s$", buffer);
	printf("\n\t4 * out: %s$", out);
	ft_memmove(buffer, buffer + eof_buffer, ft_sstrlen(buffer + eof_buffer) + 1);
	printf("\n\t5 * buffer: %s$", buffer);
	res = out;
	return (out);
}

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char	*res;
	ssize_t	read_bytes;
	int		end;

	printf("\n========== DEBUG START ==========\n");
	printf("\nbuffer: %s$", buffer[fd]);
	end = 0;
	res = join_res_buffer(NULL, buffer[fd], &end, get_nl_pos(buffer[fd], 0) > -1);
	printf("\n========== first call\n");
	printf("\nend: %d$", end);
	read_bytes = 1;
	while (read_bytes > 0 && !end)
	{
		read_bytes = read(fd, buffer[fd], BUFFER_SIZE);
		if (read_bytes < 0)
			buffer[fd][0] = 0;
		if (read_bytes < 0)
			return (free(res), NULL);
		if (read_bytes == 0)
			return (res);
		buffer[fd][read_bytes] = 0;
		printf("\ndebug buffer: %s$", buffer[fd]);
		res = join_res_buffer(res, buffer[fd], &end, get_nl_pos(buffer[fd], 0) > -1);
	}
	printf("\nres: %s$", res);
	printf("\n==========  DEBUG END  ==========\n");
	return (res);
}
