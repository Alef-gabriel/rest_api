#include "../include/api.h"

t_json	*creat_t_json(char *key)
{
	t_json	*res;

	res = (t_json *)malloc(sizeof(t_json) * 1);
	res->key = key;
	res->value = NULL;
	return (res);
}

t_json	**init_json_keys(void)
{
	t_json	**res;

	res = (t_json **)malloc(sizeof(t_json *) * 4);
	res[ARRAY_ID] = creat_t_json(ft_strdup("id"));
	res[ARRAY_AUTHOR] = creat_t_json(ft_strdup("author"));
	res[ARRAY_JOB] = creat_t_json(ft_strdup("job"));
	res[ARRAY_CITATION] = creat_t_json(ft_strdup("citation"));
	return (res);
}

t_keys	*creat_t_keys(char	*key, char *value)
{
	t_keys	*res;

	res = (t_keys *)malloc(sizeof(t_keys));
	res->key = ft_strdup(key);
	res->value = ft_strdup(value);
	res->next = NULL;
	return (res);
}

t_table	*creat_t_table(t_keys *value)
{
	t_table	*res;

	res = (t_table *)malloc(sizeof(t_table));
	res->value = value;
	res->next = NULL;
	return (res);
}
