#include "../include/api.h"

void	apend_data_in_struct(MYSQL_ROW	row, MYSQL_RES *result)
{
	t_table	*tb;
	t_keys	*ky;
	int		num_fields;

	g_request.status = 404;
	num_fields = mysql_num_fields(result);
	g_request.table = NULL;
	tb = creat_t_table(creat_t_keys(NULL, NULL));
	while ((row = mysql_fetch_row(result)))
	{
		g_request.status = 200;
		ky = tb->value;
		for(int i = 0; i < num_fields; i++)
		{
			tb->value->key = g_request.json_values[i]->key;
			tb->value->value = ft_strdup(row[i]);
			tb->value->next = creat_t_keys(NULL, NULL);
			tb->value = tb->value->next;
		}
		tb->value = ky;
		if (g_request.table == NULL)
			g_request.table = tb;
		tb->next = creat_t_table(creat_t_keys(NULL, NULL));
		tb = tb->next;
	}
}

t_json	**append_json_values(struct json_object *rq_json)
{
	int		i;
	t_json	**json_s;

	i = 1;
	json_s = init_json_keys();
	while (i < 4)
	{
		if (!(json_object_object_get_ex(rq_json, json_s[i]->key, &json_s[i]->value)))
			return (NULL);
		i++;
	}
	return (json_s);
}

char	*parse_id(char *body)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (body[i] != '}')
		i++;
	i++;
	if (body[i] >= '0' && body[i] <= '9')
	{
		j = 1;
		while (body[i + j] >= '0' && body[i+ j] <= '9')
			j++;
		g_request.http->body.ptr = (const char*)ft_substr(body, 0, i);
		return (ft_substr(body, i, j));
	}
	return (NULL);
}

char	*put_to_json(t_table *table)
{
	char	*json;
	char	*obj;

	json = "[\n";
	while (table && table->value->key)
	{
		obj = "\t{\n";
		while (table->value->key)
		{
			obj = ft_strjoin(obj , mjson_aprintf("\t\t%Q:%Q", table->value->key, table->value->value));
			if(table->value->next->key != NULL)
				obj = ft_strjoin(obj ,",\n");
			table->value = table->value->next;
		}
		if (table->next->value->key)
			obj = ft_strjoin(obj, "\n},\n");
		json = ft_strjoin(json, obj);
		table = table->next;
	}
	json = ft_strjoin(json, "\n\t}\n]\n");
	return (json);
}

char	*parse_in_get(char *head)
{
	int		i;

	i = 0;
	while (*head && *head != '/')
		head++;
	head++;
	while (head[i] && head[i] != ' ')
		i++;
	if (i == 0)
		return (NULL);
	return (ft_substr(head, 0, i));
}

void	parse_log(char *time)
{
	char	*log;
	char	*aux;
	int		i;
	int		j;

	i = 0;
	aux = (char *)g_request.http->head.ptr;
	while (aux[i] != '/')
		i++;
	j = i;
	log = ft_strjoin(ft_substr(aux, 0, i - 1), "   |   ");
	while (aux[i] != ' ')
		i++;
	log = ft_strjoin(log ,ft_substr(aux, j, i - j));
	log = ft_strjoin(log, "   |   ");
	log = ft_strjoin(log, time);
	add_log(log);
	free(log);
}
