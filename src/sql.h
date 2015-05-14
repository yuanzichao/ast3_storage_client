#include <mysql/mysql.h>
#include "type_def.h"

MYSQL *g_conn; // mysql 连接
MYSQL_RES *g_res; // mysql 记录集
MYSQL_ROW g_row; // 字符串数组，mysql 记录行

#define MAX_BUF_SIZE 1024 // 缓冲区最大字节数

int init_mysql();
void print_mysql_error(const char *msg);
int query();
int query_disks();
int query_disks_info(char *diskName);
char* get_directory_id(char *dirName, char *diskName);
int query_directory_info(char *dirName, char *diskName);
int get_rows();
int get_fields();
void print_result();
Directory_Info get_directory_info(MYSQL_ROW g_row);
Disk_Info get_disk_info(MYSQL_ROW g_row);
File_Info get_file_info(MYSQL_ROW g_row);
int insert_directory(Directory_Info directory_info);
int insert_disk(Disk_Info disk_info);
int insert_file(File_Info file_info);
void update_directory(Directory_Info directory_info);
void update_disk(Disk_Info disk_info);
void update_file(File_Info file_info);
void delete();


void free_result();
void close_db();
