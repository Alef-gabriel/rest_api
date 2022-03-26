#include "../include/api.h"

t_req	g_request;

static void hand(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	if (ev == MG_EV_HTTP_MSG)
	{
		time_t curtime;

		fn_data = (char *)fn_data;
		time(&curtime);
		g_request.http = (struct mg_http_message *) ev_data;
		if (mg_http_match_uri(g_request.http, "/post"))
			post_route(c, g_request.http);
		else if (mg_http_match_uri(g_request.http, "/delete"))
			delete_route(c);
		else if (mg_http_match_uri(g_request.http, "/put"))
			put_rote(c);
		else if (mg_http_match_uri(g_request.http, "/*"))
			get_route(c);
		else
			mg_http_reply(c, 404, "Content-Type: application/json\r\n","NOT FOUND");
		parse_log(ctime(&curtime));
	}
}

int main()
{
	struct mg_mgr mgr;

	mg_mgr_init(&mgr);
	mg_http_listen(&mgr, "http://localhost:8000", hand, &mgr);
	for (;;) mg_mgr_poll(&mgr, 1000);
	mg_mgr_free(&mgr);
	return 0;
}