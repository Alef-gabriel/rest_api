#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	CURL		*curl;
	CURLcode	res;
	int			i;
	int			j;
	struct curl_slist	*heder = NULL;
	char	*method[] = {"POST", "GET", "GET", NULL};
	char	*routes[] = {"http://localhost:8000/post","http://localhost:8000/Olavo","http://localhost:8000/Hans-Hermann", NULL};
	char	*json[] = {"{\"author\": \"Olavo\",\"job\": \"O Imbecil Coletivo\",\"citation\" : \"Jamais critiquei ninguém por ser de esquerda, e sim por não saber sê-lo com alguma dignidade. Falo contra a impostura daqueles que, no fundo, só estão na esquerda porque aí podem proteger-se de toda a crítica da solidariedade ideológica\"}",
	"{\"author\": \"Olavo\",\"job\": \"O Futuro do Pensamento Brasileiro\",\"crimeia\" : \"O importante é não estudar por estudar, para \"adquirir cultura\" ou seguir carreira universitária, mas para encontrar respostas a questões determinadas, que tenham importância existencial para você, para sua formação de ser humano e não só de estudioso.\"}",
	"{\"author\": \"Hans-Hermann\",\"job\": \"Democracia - O Deus que falhou\",\"citation\" : \"O estado monárquico não possui fronteiras naturais. Aumentar a propriedade da sua família é o ideal do príncipe; ele se esforça para legar ao seu sucessor um território maior do que aquele que herdou do seu pai.\"}", NULL};

	j = 1;
	i = 0;
	while (json[i])
	{
		curl = curl_easy_init();
		if(curl)
		{
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method[0]);
			curl_easy_setopt(curl, CURLOPT_URL, routes[0]);
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "http");
			heder = curl_slist_append(heder, "Content-Type: application/json");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, heder);
			curl_easy_setopt(curl, CURLOPT_POST, 1);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json[i]);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(json[i]));
			res = curl_easy_perform(curl);
		}
		curl_easy_cleanup(curl);
		sleep(1);
		i++;
	}
	//result sucess
	//result invalid json
	//result sucess
	while (routes[j])
	{
		curl = curl_easy_init();
		if(curl)
		{
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method[j]);
			curl_easy_setopt(curl, CURLOPT_URL, routes[j]);
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "http");
			heder = curl_slist_append(heder, "Content-Type: application/json");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, heder);
			res = curl_easy_perform(curl);
		}
		curl_easy_cleanup(curl);
		sleep(1);
		j++;
	}
	return (0);
}