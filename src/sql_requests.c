#include "../include/api.h"

void	*finish_with_error(MYSQL *con)
{
	g_request.error = ft_strdup(mysql_error(con));
	mysql_close(con);
	g_request.status = 500;
	return (NULL);
}

MYSQL	*ft_mysql_execut(char	*cmd)
{
	MYSQL	*con;

	con = mysql_init(NULL);
	if (con == NULL)
		finish_with_error(con);
	if (mysql_real_connect(con, "localhost", "root", "", "api42", 0, NULL, 0) == NULL)
		finish_with_error(con);
	if (mysql_query(con, cmd))
		finish_with_error(con);
	return (con);
}

int	get_data(char *author)
{
	MYSQL		*con;
	MYSQL_RES	*result;
	MYSQL_ROW	row;
	MYSQL_FIELD	*field;
	char		*sql_cmd;

	g_request.status = 200;
	sql_cmd = "select *from citation where author=\'";
	author = ft_strjoin(author, "\'");
	sql_cmd = ft_strjoin(sql_cmd, author);
	con = ft_mysql_execut(sql_cmd);
	result = mysql_store_result(con);
	if (result == NULL)
	{
		finish_with_error(con);
		return (g_request.status);
	}
	apend_data_in_struct(row, result);
	mysql_free_result(result);
	mysql_close(con);
	return (g_request.status);
}

int	append_in_db(void)
{
	MYSQL	*con;
	char	*sql_cmd;

	g_request.status = 201;
	sql_cmd = ft_strdup("INSERT INTO citation VALUES(0,");
	for (size_t i = 1; i < 4; i++)
	{
		sql_cmd = ft_strjoin(sql_cmd, "\'");
		sql_cmd = ft_strjoin(sql_cmd, json_object_get_string(g_request.json_values[i]->value));
		if (i != 3)
			sql_cmd = ft_strjoin(sql_cmd, "\',");
		else
			sql_cmd = ft_strjoin(sql_cmd, "\')");
	}
	con = ft_mysql_execut(sql_cmd);
	mysql_close(con);
	return (g_request.status);
}

int	delete_in_db(char *id)
{
	MYSQL	*con;
	char	*sql_cmd;

	g_request.status = 201;
	sql_cmd = ft_strjoin("DELETE FROM citation WHERE id =", id);
	con = ft_mysql_execut(sql_cmd);
	mysql_close(con);
	return (g_request.status);
}

int		put_in_db(char *id)
{
	MYSQL	*con;
	char	*sql_cmd;

	sql_cmd = ft_strdup("UPDATE citation SET ");
	for (size_t i = 1; i < 4; i++)
	{
		sql_cmd = ft_strjoin(sql_cmd, g_request.json_values[i]->key);
		sql_cmd = ft_strjoin(sql_cmd, "=\'");
		sql_cmd = ft_strjoin(sql_cmd, json_object_get_string(g_request.json_values[i]->value));
		if (i != 3)
			sql_cmd = ft_strjoin(sql_cmd, "\',");
		else
			sql_cmd = ft_strjoin(sql_cmd, "\' WHERE id =");
	}
	sql_cmd = ft_strjoin(sql_cmd, id);
	con = ft_mysql_execut(sql_cmd);
	mysql_close(con);
	return (201);
}
