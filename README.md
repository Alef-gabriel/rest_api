![API REST](./img/books_image.png)

## Ctations REST API
The citation Api provides access to general citations

## Tool kit
* [Mjson](https://github.com/cesanta/mjson)
* [Mongoose](https://mongoose.ws/)
* [json-c](https://json-c.github.io/json-c/json-c-current-release/doc/html/index.html)
* [Mysql](https://zetcode.com/db/mysqlc/)

## How to run
* Install [mysql](https://zetcode.com/mysql/)

* Install dev lib
> ```sudo apt install default-libmysqlclient-dev```
go to init_database.c and ./src/sql_requests.c in functio ```mysql_real_connect(con, "localhost", "root", "", NULL, 0, NULL, 0)```
put your mysql user in ```"root"``` and password in ```""```.
Creat db and table with ```make db``` and ```./a.out```.
### Api inicialize with ```make``` or ```make all``` and ```./api.out```
![image](https://user-images.githubusercontent.com/63974787/155889187-3c084e9b-d8e9-4ac9-8023-609c93fdfae8.png)

### Cli
For view api logs.
run cli ```make cli``` and ```./cli.out```
![image](https://user-images.githubusercontent.com/63974787/155890176-1df902d3-cfba-4589-89a4-c00b4712b02b.png)

### Api test ```make test``` and ```./a.out```

