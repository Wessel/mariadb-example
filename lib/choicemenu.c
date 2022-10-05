#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Local imports */
#include "./utils.h"
#include "./database.h"

/* Hashed constants for choice menu */
#define SA 5863801
#define SF 5863806
#define AR 5863224
#define DR 5863323
#define MR 5863620
#define KL 5863548

/* variables */
unsigned long choiceHash;
char confirmation[3],
  table[56], field[56],
  identifier[2048], data[2048];

/**
 * @brief Shows `field` from `table`
 *
 * Used to list all rows that have a value
 * assigned to `field` in `table`. Determined
 * by user input.
 *
 * @returns Void.
 */
void table_show() {
  printf("\n\t[SHOW TABLE FIELD]\n");
  printf("Insert table to show:\t");
  scanf("%s", table);
  printf("Insert field to show:\t");
  scanf("%s", field);

  printf("Selected:\t\t%s[%s]\n", table, field);
  printf("Correct? (y/n):\t");
  scanf("%s", confirmation);

  if (strcmp(confirmation, "n") == 0 || strcmp(confirmation, "no") == 0)
    table_show();

  print_field(table, field);
}

/** @brief Puts `req` into `table`
 *
 * Used to let the end user add rows to
 * the desired table, asks for `req` and
 * `fieldData` to assign `req` to.
 *
 * @returns Void.
 */
void row_input() {
  char fieldData[2048];
  char req[2048];

  printf("\n\t[INSERT ROW INTO TABLE]\n");
  printf("Insert table to use:\t");
  scanf("%s", table);
  printf("Insert fields to use:\t");
  scanf("%s", fieldData);
  printf("Insert data for fields:\t");
  scanf("%s", req);

  printf("Selected:\t\t%s(%s): %s\n", table, fieldData, req);
  printf("Correct? (y/n):\t");
  scanf("%s", confirmation);

  if (strcmp(confirmation, "n") == 0 || strcmp(confirmation, "no") == 0)
    row_input();

  insert_row(table, fieldData, req);
}

/** @brief Removes `identifier` from `table`
 *
 * Deletes rows that match `identifier`
 * determined by the user from `table`.
 *
 * @returns Void.
 */
void row_delete() {
  printf("\n\t[DELETE ROW FROM TABLE]\n");
  printf("Insert table to use:\t");
  scanf("%s", table);
  printf("Insert identifier(s) to use:\t");
  scanf("%s", identifier);

  printf("Selected:\t\t%s: %s\n", table, identifier);
  printf("Correct? (y/n):\t");
  scanf("%s", confirmation);

  if (strcmp(confirmation, "n") == 0 || strcmp(confirmation, "no") == 0)
    row_delete();

  delete_row(table, identifier);
}

/** @brief Modifies `identifier` to `data` from `table`
 *
 * Searches for `identifier` in `table` and modifies it
 * to `data` all determined by the user.
 *
 * @returns Void.
 */
void row_modify() {
  printf("\n\t[MODIFY ROW]\n");
  printf("Insert table to use:\t");
  scanf("%s", table);
  printf("Insert identifier(s) to use:\t");
  scanf("%s", identifier);
  printf("Insert data to override:\t");
  scanf("%s", data);

  printf("Selected:\t\t%s(%s): %s\n", table, identifier, data);
  printf("Correct? (y/n):\t");
  scanf("%s", confirmation);

  if (strcmp(confirmation, "n") == 0 || strcmp(confirmation, "no") == 0)
    row_modify();

  modify_row(table, identifier, data);
}

/** @brief Activates the choice menu loop
 *
 * Used to give the user an interfcae to
 * interact with all the commands defined above.
 *
 * @returns Void.
 */
void choice_menu() {
  printf("Choose one of the following:\n");
  printf("\t[sa] Show all tables\n");
  printf("\t[sf] Show `field` from `table`\n");
  printf("\t[ar] Add `row` from `table`\n");
  printf("\t[dr] Delete `row` from `table`\n");
  printf("\t[dr] Modify `row` from `table`\n");
  printf("\t[kl] End database connection`\n");

  char input[2];

  printf("Choice:\t");
  scanf("%s", input);
  choiceHash = hash(input);

  switch (choiceHash)
  {
  case KL:
    printf("\t[Kill database connection]\n");
    kill(0);
    break;
  case SA:
    printf("\n\t[SHOW ALL TABLES]\n");
    print_tables();
    choice_menu();
    break;
  case SF:
    table_show();
    choice_menu();
    break;
  case AR:
    row_input();
    choice_menu();
    break;
  case DR:
    row_delete();
    choice_menu();
    break;
  case MR:
    row_modify();
    choice_menu();
    break;
  default:
    printf("\t[INVALID CHOOCE, PLEASE PICK AGAIN]\n");
    choice_menu();
  }
}