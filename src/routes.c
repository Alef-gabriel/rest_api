#include "../include/api.h"

void	post_route(struct mg_connection *c, struct mg_http_message *hm)
{
	char	*json = NULL;

	g_request.status = 200;
	if (strstr(g_request.http->method.ptr, "POST") != NULL)
	{
		g_request.status = 400;
		g_request.json = json_tokener_parse(g_request.http->body.ptr);
		g_request.json_values = append_json_values(g_request.json);
		if (g_request.json_values != NULL)
		{
			if (g_request.status = append_in_db() == 201)
				json = mjson_aprintf("{%Q:%Q}", "Result", "success");
			else
				json = mjson_aprintf("{%Q:%Q}", "Result", "failed");
		}
		else
			json = mjson_aprintf("{%Q:%Q}", "Result", "Invalid Json");
	}
	else
		json = mjson_aprintf("{%Q:%Q}", "Result", "USE POST METHOD");
	mg_http_reply(c, g_request.status, "Content-Type: application/json\r\n", "%s", json);
	free(json);
}

void	delete_route(struct mg_connection *c)
{
	char	*json = NULL;

	g_request.status = 200;
	if (strstr(g_request.http->method.ptr, "DELETE") != NULL)
	{
		g_request.status = 400;
		if (g_request.status = delete_in_db((char *)g_request.http->body.ptr) == 201)
			json = mjson_aprintf("{%Q:%Q}", "Result", "success");
		else
			json = mjson_aprintf("{%Q:%Q}", "Result", "failed");
	}
	else
		json = mjson_aprintf("{%Q:%Q}", "Result", "USE DELETE METHOD");
	mg_http_reply(c, g_request.status, "Content-Type: application/json\r\n", "%s", json);
	free(json);
}

void	get_route(struct mg_connection *c)
{
	char	*json;
	char	*author;

	g_request.json_values = init_json_keys();
	if (author = parse_in_get((char *)g_request.http->head.ptr))
	{
		get_data(author);
		if (g_request.status == 200)
			json = put_to_json(g_request.table);
		else
			json = mjson_aprintf("{\n\t%Q: %Q\n}", "Result", "NOT FOUND");
	}
	else
		json = mjson_aprintf("{\n\t%Q: %Q\n}", "Manual", "Insert author name later '/' and press enter");
	mg_http_reply(c, g_request.status, "Content-Type: application/json\r\n", "%s", json);
	free(author);
	free(json);
}

void	put_rote(struct mg_connection *c)
{
	char	*json = NULL;
	char	*id;
	g_request.status = 200;
	if (strstr(g_request.http->method.ptr, "PUT") != NULL)
	{
		g_request.status = 400;
		id = parse_id((char *)g_request.http->body.ptr);
		g_request.json = json_tokener_parse(g_request.http->body.ptr);
		g_request.json_values = append_json_values(g_request.json);
		if (g_request.json_values != NULL)
		{
			if (g_request.status = put_in_db(id) == 201)
				json = mjson_aprintf("{%Q:%Q}", "Result", "success");
			else
				json = mjson_aprintf("{%Q:%Q}", "Result", "Failed");
		}
		else
			json = mjson_aprintf("{%Q:%Q}", "Result", "Invalid Json");
	}
	else
		json = mjson_aprintf("{%Q:%Q}", "Result", "USE PUT METHOD");
	mg_http_reply(c, g_request.status, "Content-Type: application/json\r\n", "%s", json);
	free(json);
}
