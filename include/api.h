#ifndef API_H
# define API_H
# include "mongoose.h"
# include "mjson.h"
#include <time.h>
#include </usr/include/mysql/mysql.h>
# include <json-c/json.h>
# include <stdio.h>
# include <unistd.h>

# define ARRAY_ID 0
# define ARRAY_AUTHOR 1
# define ARRAY_JOB 2
# define ARRAY_CITATION 3

typedef struct t_json_values
{
	char				*key;
	struct json_object	*value;
}	t_json;

typedef struct t_keys_values
{
	char					*key;
	char					*value;
	struct t_keys_values	*next;
}	t_keys;

typedef struct t_table_values
{
	t_keys					*value;
	struct t_table_values	*next;
}	t_table;

typedef struct t_request_data
{
	struct json_object		*json;
	struct mg_http_message	*http;
	t_json					**json_values;
	char					*error;
	int						status;
	t_table					*table;
}	t_req;

extern t_req	g_request;

/* ULTILS */
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t destsize);
void	add_log(char *log);
/* STRUCTS_INIT_FUNC */
t_json	*creat_t_json(char *key);
t_json	**init_json_keys(void);
t_keys	*creat_t_keys(char	*key, char *value);
t_table	*creat_t_table(t_keys *value);
/* ROUTES */
void	post_route(struct mg_connection *c, struct mg_http_message *hm);
void	delete_route(struct mg_connection *c);
void	get_route(struct mg_connection *c);
void	put_rote(struct mg_connection *c);
/* SQL_REQUESTS */
MYSQL	*ft_mysql_execut(char	*cmd);
int		get_data(char *author);
int		append_in_db(void);
int		delete_in_db(char *id);
void	*finish_with_error(MYSQL *con);
int		put_in_db(char *id);
/* PARCER */
void	apend_data_in_struct(MYSQL_ROW	row, MYSQL_RES *result);
t_json	**append_json_values(struct json_object *rq_json);
char	*parse_id(char *body);
char	*put_to_json(t_table *table);
char	*parse_in_get(char *head);
void	parse_log(char *time);
#endif