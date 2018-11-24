#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h>


int main(int argc, char const *argv[])
{
    sqlite3 *db;
    sqlite3_open("testdb.db" ,&db);
    sqlite3_exec(db,"drop table if exists t1",0,0,0);  
    sqlite3_exec(db,"create table t1(id integer,x integer,y integer ,weight real)",0,0,0);

    int i;
    char *values = "INSERT INTO t1(id,x,y,weight) VALUES ";
    int s = 1000000;
    values = (char *)malloc(strlen(values)+12*s+1);
    values[0] = '\0';
    strcat(values, "INSERT INTO t1(id,x,y,weight) VALUES ");
    for (i = 0; i < s; i ++) {
        strcat(values, "(1,2,3,1.2),");
    }
    int len = strlen(values);
    values[len-1] = '\0';
    // printf("%s", values);

    clock_t start_t, end_t, total_t;

    start_t = clock();
    sqlite3_exec(db, values, 0, 0, 0);
    end_t = clock();
    total_t = end_t - start_t;
    printf("CLOCKS_PER_SEC = %d\n", CLOCKS_PER_SEC);
    printf("insert rows: %d\n", s);
    printf("total_t = %ld\n", total_t);
    printf("spend time: %lf\n", (total_t*0.1*10)/CLOCKS_PER_SEC);

    sqlite3_close(db); 
    return 0;
}
