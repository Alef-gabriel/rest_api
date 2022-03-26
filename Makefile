NAME = api.out
CLI = cli.out
CC = gcc
CFLAGS = -fsanitize=address -g3

RM = rm -rf

INCLUDE = -I /usr/include/mysql -I ./include/
LIBS = -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -ldl -lz -lssl -lcrypto -lresolv -lm -lrt -ljson-c
PATH_SRC = ./src/
PATH_OBJS = ./objs/
PATH_CLI = ./cli/
PATH_CLI_OBJS = ./cli_objs/

SRCS = $(PATH_SRC)main.c $(PATH_SRC)utils.c $(PATH_SRC)mongoose.c\
	$(PATH_SRC)mjson.c $(PATH_SRC)parser.c $(PATH_SRC)routes.c\
	$(PATH_SRC)sql_requests.c $(PATH_SRC)structs_init_func.c

CLI_SRCS = $(PATH_CLI)get_next_line_utils.c $(PATH_CLI)get_next_line.c\
	$(PATH_CLI)main.c $(PATH_CLI)utils.c

OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(SRCS))

CLI_OBJS = $(patsubst $(PATH_CLI)%.c, $(PATH_CLI_OBJS)%.o, $(CLI_SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) ./objs/*.o -o $(NAME) $(LIBS)

$(PATH_OBJS)%.o: $(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -I. -c $< -o $@ $(LIBS)

cli: $(CLI)

$(CLI): $(CLI_OBJS)
	$(CC) -I ./include/ ./cli_objs/*.o -o $(CLI)

$(PATH_CLI_OBJS)%.o: $(PATH_CLI)%.c
	@mkdir -p $(PATH_CLI_OBJS)
	$(CC) -I ./include/ -I. -c $< -o $@

clean:
	@echo "\033[1;33mCleaning objects\033[0m"
	@$(RM) $(PATH_OBJS)
	@echo "\033[1;32mDone!\033[0m"

cliclean:
	@echo "\033[1;33mCleaning objects\033[0m"
	@$(RM) $(PATH_CLI_OBJS)
	@echo "\033[1;32mDone!\033[0m"

db:
	@gcc -I /usr/include/mysql init_database.c $(LIBS) && ./a.out
	@$(RM) a.out

fclean: clean
	@$(RM) http
	@$(RM) api.out
	@echo  "\033[1;33mCleaning all\033[0m"

clifclean: cliclean
	@$(RM) cli.out
	@echo  "\033[1;33mCleaning all\033[0m"

apitest:
	@gcc ./test/test.c -lcurl

re: fclean all

.PHONY: all clean fclean re