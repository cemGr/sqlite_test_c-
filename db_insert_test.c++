#include <iostream>
#include <sqlite3.h>
#include <string>
  
using namespace std;
  //test for insert and delet
static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
  
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
  
    printf("\n");
    return 0;
}
  
int main(int argc, char** argv)
{
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("example.db", &DB);
    string query = "SELECT * FROM TEAM;";
  
    cout << "STATE OF TABLE BEFORE INSERT" << endl;
  
    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
  
    string sql("INSERT INTO TEAM VALUES(1, 'CEM', 'GRAF', 24);"
               "INSERT INTO TEAM VALUES(2, 'THOMAS', 'ZETH', 21);"
               "INSERT INTO TEAM VALUES(3, 'LUCAS', 'GRAF', 21);");
  
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Records created Successfully!" << std::endl;
  
    cout << "STATE OF TABLE AFTER INSERT" << endl;
  
    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
  
    sql = "DELETE FROM TEAM WHERE ID = 2;";
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error DELETE" << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Record deleted Successfully!" << std::endl;
  
    cout << "STATE OF TABLE AFTER DELETE OF ELEMENT" << endl;
    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
  
    sqlite3_close(DB);
    return (0);
}