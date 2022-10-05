/* main.c */
#include "../include/database.h"
#include "../include/choicemenu.h"

#define __MAIN__
#ifdef __MAIN__
char _server[56] = "localhost";
char _user[56] = "pipo";
char _password[56] = "theclown";
char _database[56] = "f1";
#else
extern char _server[56];
extern char _user[56];
extern char _password[56];
extern char _database[56];
#endif


void main() {
  init_mysql();
  choice_menu();
}