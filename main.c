#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h>

void insert_use_prestmt(sqlite3 *db, int count);
void insert_use_batch(sqlite3 *db, int count);

int main(int argc, char const *argv[])
{
    sqlite3 *db;
    sqlite3_open("testdb.db" ,&db);
    sqlite3_exec(db,"drop table if exists t1",0,0,0);  
    sqlite3_exec(db,"create table t1(id integer,x integer,y integer ,weight real)",0,0,0);
    int count = 10000;

    clock_t start_t, end_t, total_t;
    start_t = clock();
    insert_use_prestmt(db, count);
    end_t = clock();
    total_t = end_t - start_t;

    printf("CLOCKS_PER_SEC = %d\n", CLOCKS_PER_SEC);
    printf("insert rows: %d\n", count);
    printf("total_t = %ld\n", total_t);
    printf("spend time: %lf\n", (total_t*0.1*10)/CLOCKS_PER_SEC);

    sqlite3_close(db); 
    return 0;
}

void insert_use_prestmt(sqlite3 *db, int count) {
    sqlite3_exec(db,"begin;",0,0,0);  
    sqlite3_stmt *stmt;  
    const char* sql = "INSERT INTO t1(id,x,y,weight) VALUES (?,?,?,?)";  
    sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,0);  
      
    for(int i=0;i<count;++i)  
    {         
        sqlite3_bind_int(stmt,1,2);  
        sqlite3_bind_int(stmt,2,2);  
        sqlite3_bind_int(stmt,3,2);  
        sqlite3_bind_double(stmt,4,1.2);
        sqlite3_step(stmt);
        sqlite3_reset(stmt);
        // printf("a");
    }  
    sqlite3_finalize(stmt);  
    sqlite3_exec(db,"commit;",0,0,0);
}

void insert_use_batch(sqlite3 *db, int count) {
    int i;
    char *values = "INSERT INTO t1(id,x,y,weight) VALUES ";
    values = (char *)malloc(strlen(values)+12*count+1);
    values[0] = '\0';
    strcat(values, "INSERT INTO t1(id,x,y,weight) VALUES ");
    for (i = 0; i < count; i ++) {
        strcat(values, "(1,2,3,1.2),");
    }
    int len = strlen(values);
    values[len-1] = '\0';
}
