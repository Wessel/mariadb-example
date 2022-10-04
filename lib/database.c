#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

/* Sets global variables if not set */
#ifdef __MAIN__
char _server[56] = "localhost";
char _user[56] = "pipo";
char _password[56] = "theclown";
char _database[56] = "mysql";
#else
extern char _server[56];
extern char _user[56];
extern char _password[56];
extern char _database[56];
#endif

/* Variables */
MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

MYSQL_RES *query(char *command) {
  if (mysql_query(conn, "SHOW TABLES")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }

  return mysql_use_result(conn);
}

/** @brief Starts the connection to the database
 *
 * Initializes a conncection to `_user@_serve r`
 * That will be used by the rest of this lib.
 *
 * @returns Void.
 */
void init_mysql() {
  conn = mysql_init(NULL);
  if (!mysql_real_connect(conn, _server, _user, _password, _database, 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
}

/** @brief Ends the connection to `_server`
 *
 * This function is used to cleanly exit the
 * database when operations are finished.
 *
 * @returns Void.
 */
void kill() {
  mysql_free_result(res);
  mysql_close(conn);
}

/* Functions that return to stdout */
/** @brief Prints all tables available in `_database`
 *
 * Loops through all tables in `_database` accsessible
 * by `_user` and prints them to stdout.
 *
 * @returns Void.
 */
void print_tables() {
  res = query("SHOW TABLES");

  while ((row = mysql_fetch_row(res)) != NULL)
    printf("%s\n", row[0]);
}

/** @brief Prints all values of `field` from `table`
 *
 * Loops through `field` in `table` and prints them out
 * to stdout.
 *
 * @param table The table to view
 * @param field The field to view from `table`
 *
 * @returns Void.
 */
void print_field(char* table, char* field) {
  char command[2048];
  sprintf(command, "SELECT %s FROM %s", field, table);

  res = query(command);

  while ((row = mysql_fetch_row(res)) != NULL)
    printf("%s\n", row[0]);
}

/* Functions that return a usable variable */
/** @brief Returns all tables in `_database`
 *
 * Returns all tables in `_database` to a string,
 * seperated with new lines (\n).
 *
 * @returns str The string of tables in `_database`
 */
char *get_tables() {
  res = query("SHOW TABLES");

  char *str = malloc(sizeof(char) * 2048);
  sprintf(str, "");

  while ((row = mysql_fetch_row(res)) != NULL)
    sprintf(str, "%s %s\n", str, row[0]);

  return str;
}

/** @brief Inserts `req` into `table` using `fieldData`
 *
 * Used to create an entry into `table` with `req`
 * as data that is put into `fieldData`.
 *
 * @param table The table to insert the row into
 * @param fieldData The fields to assign `req` to
 * @param req The data to assign to the new row
 *
 * @returns Void
 */
void insert_row(char table[56], char fieldData[2048], char req[2048]) {
  char command[2048];
  sprintf(command, "INSERT INTO %s (%s) VALUES (%s)", table, fieldData, req);

  res = query(command);

  while ((row = mysql_fetch_row(res)) != NULL)
    printf("%s\n", row[0]);
}

/** @brief Deletes row matching `identifier` from `table`
 *
 * This function is used to delete unwanted rows
 * from `table` that match the conditions mentioned
 * in `identifier`.
 *
 * @param table The table to match the identifier to
 * @param identifier The conditions to use when searching
 *
 * @returns Void.
 */
void delete_row(char table[56], char identifier[2048]) {
  char command[2048];
  sprintf(command, "DELETE FROM %s WHERE %s", table, identifier);

  res = query(command);

  while ((row = mysql_fetch_row(res)) != NULL)
    printf("%s\n", row[0]);
}

/** @brief Modify a row in `table` that match `identifier` using `data`
 *
 * Changes the values of rows found in `table` matching the
 * `identifier` to the desired values passed into `data`.
 *
 * @param table The table to modify the row from
 * @param identifier The identifier for the row to modify
 * @param data The data to overwrite the row
 * found with `identifier` with
 *
 * @returns Void.
 */
void modify_row(char table[56], char identifier[2048], char data[2048]) {
  char command[2048];
  sprintf(command, "UPDATE %s SET %s WHERE %s", table, data, identifier);

  res = query(command);

  while ((row = mysql_fetch_row(res)) != NULL)
    printf("%s\n", row[0]);
}