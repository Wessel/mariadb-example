#ifndef DATABASE_H
#define DATABASE_H

extern char _server[56];
extern char _user[56];
extern char _password[56];
extern char _database[56];

void init_mysql();
void kill(int code);
char *get_tables(void);
char *print_tables(void);
char *print_field(char *table, char *field);
int insert_row(char table[56], char fieldData[2048], char req[2048]);
int delete_row(char table[56], char identifier[2048]);
int modify_row(char table[56], char identifier[2048], char data[2048]);

#endif