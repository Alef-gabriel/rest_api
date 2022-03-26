#include </usr/include/mysql/mysql.h>
#include <stdio.h>

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

int main(int argc, char **argv)
{
	 MYSQL *con;

	/*START THE CONECTION */
	con = mysql_init(NULL);
	if (con == NULL)
		finish_with_error(con);
	if (mysql_real_connect(con, "localhost", "root", "", NULL, 0, NULL, 0) == NULL)
		finish_with_error(con);
	/*CREAT DATABASE*/
	if (mysql_query(con, "CREATE DATABASE api42"))
		finish_with_error(con);
	mysql_close(con);
	/*START TABLE*/
	con = mysql_init(NULL);
	if (con == NULL)
		finish_with_error(con);
	if (mysql_real_connect(con, "localhost", "root", "", "api42", 0, NULL, 0) == NULL)
		finish_with_error(con);
	if (mysql_query(con, "DROP TABLE IF EXISTS citation"))
		finish_with_error(con);
	if (mysql_query(con, "CREATE TABLE citation(id INT PRIMARY KEY AUTO_INCREMENT, author VARCHAR(255), job VARCHAR(255), citation VARCHAR(255))"))
		finish_with_error(con);
	mysql_close(con);
	exit(0);
}