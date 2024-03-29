#include <mysql/mysql.h>
#include <stdio.h>

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

char *_server = "localhost";
char *_user = "pipo";
char *_password = "theclown"; /* set me first */
char *_database = "mysql";

void init(char *server, char *user, char *password, char *database) {
  _server = server;
  _user = user;
  _password = password; /* set me first */
  _database = database;

  conn = mysql_init(NULL);

  /* Connect to database */
  if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }

  /* send SQL query */
  if (mysql_query(conn, "show tables")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }

  res = mysql_use_result(conn);

  /* output table name */
  printf("MySQL Tables in mysql database:\n");

  while ((row = mysql_fetch_row(res)) != NULL)
    printf("%s \n", row[0]);
}

void kill(int code) {
  mysql_free_result(res);
  mysql_close(conn);
}