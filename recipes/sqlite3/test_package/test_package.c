#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int main() {
    sqlite3* db_instance = NULL;
    char* errmsg = NULL;
    int result = 0;

    printf("Expected SQLite Version %s, found version: %s\n", EXPECTED_SQLITE3_VERSION, sqlite3_libversion());
    if(strcmp(sqlite3_libversion(), EXPECTED_SQLITE3_VERSION) != 0) {
        return EXIT_FAILURE;
    }

    printf("Creating new data base ...\n");
    result = sqlite3_open("bincrafters.db", &db_instance);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db_instance));
        sqlite3_close(db_instance);
        return EXIT_FAILURE;
    }
    printf("Done!\n");

    printf("Creating new table...\n");
    result = sqlite3_exec(db_instance, "CREATE TABLE package(ID INT PRIMARY KEY NOT NULL);", NULL, 0, &errmsg);
    if(result != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        return EXIT_FAILURE;
    }
    printf("Done!\n");

    printf("Closing connection ...\n");
    sqlite3_close(db_instance);
    if(result != SQLITE_OK) {
        fprintf(stderr, "Connection error: %s\n", errmsg);
        sqlite3_free(errmsg);
        return EXIT_FAILURE;
    }
    printf("Done!\n");

    return EXIT_SUCCESS;
}
