#include <mysql/mysql.h>
#include "orm/db.h"

#define MAX_BUF_SIZE 1024 // 缓冲区最大字节数

MYSQL *g_conn; // mysql 连接
MYSQL_RES *g_res; // mysql 记录集
MYSQL_ROW g_row; // 字符串数组，mysql 记录行

//函数区
int init_mysql();
void print_mysql_error(const char *msg);
int query();
int query_disks();
int query_disk(char *diskName);
int query_disks_info(char *diskName);
char* get_directory_id(char *dirName, char *diskName);
int query_directory_info(char *dirName, char *diskName);
int query_file_info(char *fileName, char *dirName, char *diskName);
int get_rows();
int get_fields();
void print_result();
db_directory_info get_directory_info(MYSQL_ROW g_row);
db_disk_info get_disk_info(MYSQL_ROW g_row);
db_file_info get_file_info(MYSQL_ROW g_row);
int insert_directory(db_directory_info directory_info);
int insert_disk(db_disk_info disk_info);
int insert_file(db_file_info file_info);
void update_directory(db_directory_info directory_info);
void update_disk(db_disk_info disk_info);
void update_file(db_file_info file_info);
void delete();


void free_result();
void close_db();
