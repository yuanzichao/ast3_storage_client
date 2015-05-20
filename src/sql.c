#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sql.h"
#include "utils/read_conf.h"

//数据库连接信息
char g_host_name[MAX_BUF_SIZE];
char g_user_name[MAX_BUF_SIZE];
char g_password[MAX_BUF_SIZE];
char g_db_name[MAX_BUF_SIZE];
char g_db_port[MAX_BUF_SIZE];

/**
 * 初始化数据库连接
 */
int
init_mysql() {

	//获取数据库连接信息
	GetProfileString("./etc/ast3_db_info.conf", "DB_INFO", "HostName", g_host_name);
	GetProfileString("./etc/ast3_db_info.conf", "DB_INFO", "UserName", g_user_name);
	GetProfileString("./etc/ast3_db_info.conf", "DB_INFO", "Password", g_password);
	GetProfileString("./etc/ast3_db_info.conf", "DB_INFO", "DBName", g_db_name);
	GetProfileString("./etc/ast3_db_info.conf", "DB_INFO", "DBPort", g_db_port);

	//初始化
    g_conn = mysql_init(NULL);

    //连接数据库
    if(!mysql_real_connect(g_conn, g_host_name, g_user_name, g_password, g_db_name, atoi(g_db_port), NULL, 0)) // 如果失败
        return EXIT_FAILURE;

    return EXIT_SUCCESS; // 返回成功
}


/**
 * 打印最后一次错误
 */
void
print_mysql_error(const char *msg) {
    if (msg)
        printf("%s: %s\n", msg, mysql_error(g_conn));
    else
        puts(mysql_error(g_conn));
}


/**
 * 查询
 */
int
query() {

    char sql[MAX_BUF_SIZE];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "SELECT * FROM `disk_info`");

    if (mysql_query(g_conn, sql)){
    	 print_mysql_error(NULL);
    }

    g_res = mysql_store_result(g_conn); // 从服务器传送结果集至本地，mysql_use_result直接使用服务器上的记录集

    return EXIT_SUCCESS;
}


/**
 * 查询所有硬盘信息
 */
int
query_disks(){

    char sql[MAX_BUF_SIZE];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "SELECT * FROM `disk_info`");

    if (mysql_query(g_conn, sql)){
    	 print_mysql_error(NULL);
    }

    g_res = mysql_store_result(g_conn); // 从服务器传送结果集至本地，mysql_use_result直接使用服务器上的记录集

    return EXIT_SUCCESS;
}


/**
 * 查询指定硬盘信息
 */
int
query_disk(char *diskName){

    char sql[MAX_BUF_SIZE];
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "SELECT * FROM `disk_info` Where disk_name = '%s'", diskName);

    if (mysql_query(g_conn, sql)){
    	 print_mysql_error(NULL);
    }

    g_res = mysql_store_result(g_conn); // 从服务器传送结果集至本地，mysql_use_result直接使用服务器上的记录集

    return EXIT_SUCCESS;
}


/**
 * 查询硬盘内目录信息
 */
int
query_disks_info(char *diskName){

	char sql[MAX_BUF_SIZE];
	memset(sql, 0, sizeof(sql));
	sprintf(sql, "SELECT * FROM `directory_info` Where disk_name = '%s' AND parent_id = 0", diskName);

	if (mysql_query(g_conn, sql)){
		 print_mysql_error(NULL);
	}

	g_res = mysql_store_result(g_conn); // 从服务器传送结果集至本地，mysql_use_result直接使用服务器上的记录集

	return EXIT_SUCCESS;
}


/**
 * 获取目录ID
 */
char*
get_directory_id(char *dirName, char *diskName){

	char sql[MAX_BUF_SIZE];
	memset(sql, 0, sizeof(sql));
	sprintf(sql, "SELECT directory_id FROM `directory_info` Where directory_name = '%s' AND disk_name = '%s'", dirName, diskName);

	if (mysql_query(g_conn, sql)){
		 print_mysql_error(NULL);
	}

	g_res = mysql_store_result(g_conn); // 从服务器传送结果集至本地，mysql_use_result直接使用服务器上的记录集

	char *dirId = (char *) malloc(MAX_BUF_SIZE);
	int i;
	while ((g_row = mysql_fetch_row(g_res))) {
		for(i=0; i<get_fields(); i++){
			sprintf(dirId, "%s", g_row[i]);   //获取目录ID
		}
	}

	return dirId;

}



/**
 * 查询目录内文件和目录信息
 */
int
query_directory_info(char *dirName, char *diskName){

	char *dirId = (char *) malloc(MAX_BUF_SIZE);
	dirId = get_directory_id(dirName, diskName);
	free_result();


	char sql[MAX_BUF_SIZE];
	memset(sql, 0, sizeof(sql));
	sprintf(sql, "SELECT * FROM `file_info` Where directory_id = '%s' AND disk_name = '%s'", dirId, diskName);

	if (mysql_query(g_conn, sql)){
		 print_mysql_error(NULL);
	}

	g_res = mysql_store_result(g_conn); // 从服务器传送结果集至本地，mysql_use_result直接使用服务器上的记录集

	return EXIT_SUCCESS;
}


/**
 * 查询文件信息
 */
int
query_file_info(char *fileName, char *dirName, char *diskName){

	char *dirId = (char *) malloc(MAX_BUF_SIZE);
	dirId = get_directory_id(dirName, diskName);
	free_result();


	char sql[MAX_BUF_SIZE];
	memset(sql, 0, sizeof(sql));
	sprintf(sql, "SELECT * FROM `file_info` Where file_name = '%s' AND directory_id = '%s' AND disk_name = '%s'", fileName, dirId, diskName);

	if (mysql_query(g_conn, sql)){
		 print_mysql_error(NULL);
	}

	g_res = mysql_store_result(g_conn); // 从服务器传送结果集至本地，mysql_use_result直接使用服务器上的记录集

	return EXIT_SUCCESS;
}



/**
 * 获取数据集行数
 */
int
get_rows(){
	return mysql_num_rows(g_res);
}


/**
 * 获取数据集列数
 */
int
get_fields(){
	return mysql_num_fields(g_res);
}


/**
 * 打印结果
 */
void
print_result(){
	int i;
	while ((g_row = mysql_fetch_row(g_res))) {
		for(i=0; i<get_fields(); i++){
			printf("%s\t", g_row[i]);
		}
		printf("\n");

	}

}


/**
 * 获取Directory_Info
 */
Directory_Info
get_directory_info(MYSQL_ROW g_row){
	Directory_Info directory_info;
	memcpy(&directory_info, *g_row, sizeof(directory_info));
    return directory_info;
}

/**
 * 获取Disk_Info
 */
Disk_Info
get_disk_info(MYSQL_ROW g_row){
	Disk_Info disk_info = {};
	memcpy(&disk_info, *g_row, sizeof(disk_info));
    return disk_info;
}

/**
 * 获取File_Info
 */
File_Info
get_file_info(MYSQL_ROW g_row){
	File_Info file_info;
	memcpy(&file_info, *g_row, sizeof(file_info));
    return file_info;
}



/**
 * 插入目录信息
 */
int
insert_directory(Directory_Info directory_info)
 {
      char sql[MAX_BUF_SIZE];
      memset(sql, 0, sizeof(sql));
      sprintf(sql, "INSERT INTO directory_info(directory_name, disk_uuid, disk_name, parent_id, directory_size, time, recent_use_time, permission, accessed_time, file_number) VALUES \ ('%s', '%s', '%s', %d, %f, '%s', '%s', %d, %d, %d)", directory_info.directory_name, directory_info.disk_uuid, directory_info.disk_name, directory_info.parent_id, directory_info.directory_size, directory_info.time, directory_info.recent_use_time, directory_info.permission, directory_info.accessed_time, directory_info.file_number);

      if (mysql_query(g_conn, sql) != 0){
    	  print_mysql_error(NULL);
          return EXIT_FAILURE;
       }

      printf("insert data into directory_info successfully\n");
      return EXIT_SUCCESS;
  }


/**
 * 插入磁盘信息
 */
int
insert_disk(Disk_Info disk_info)
 {
      char sql[MAX_BUF_SIZE];
      memset(sql, 0, sizeof(sql));

      sprintf(sql, "INSERT INTO disk_info(disk_name, disk_uuid, disk_type, disk_capacity, disk_used, recent_use_time, permisssion, disk_status) VALUES \ ('%s', '%s', '%s', %f, %f, '%s', %d, %d)", disk_info.disk_name, disk_info.disk_uuid, disk_info.disk_type, disk_info.disk_capacity, disk_info.disk_used, disk_info.recent_use_time, disk_info.permission, disk_info.disk_status);

      if (mysql_query(g_conn, sql) != 0){
    	  print_mysql_error(NULL);
          return EXIT_FAILURE;
       }

      printf("insert data into disk_info successfully\n");
      return EXIT_SUCCESS;
  }


/**
 * 插入文件信息
 */
int
insert_file(File_Info file_info)
 {
      char sql[MAX_BUF_SIZE];
      memset(sql, 0, sizeof(sql));

      sprintf(sql, "INSERT INTO file_info(file_name, disk_uuid, directory_id, disk_name, md5, file_size, location, time, recent_use_time, permission, file_type, accessed_time) VALUES \ ('%s', '%s', %d, '%s', '%s', %f, '%s', '%s', '%s', %d, %d, %d)", file_info.file_name, file_info.disk_uuid, file_info.directory_id, file_info.disk_name, file_info.md5, file_info.file_size, file_info.location, file_info.time, file_info.recent_use_time, file_info.permission, file_info.file_type, file_info.accessed_time);

      if (mysql_query(g_conn, sql) != 0){
    	  print_mysql_error(NULL);
          return EXIT_FAILURE;
       }

      printf("insert data into file_info successfully\n");
      return EXIT_SUCCESS;
  }


/**
 * 更新目录信息
 * 包括 `directory_size`, `recent_use_time`, `accessed_time`, `file_number`
 */
void
update_directory(Directory_Info directory_info) {
	char sql[MAX_BUF_SIZE];
	memset(sql, 0, sizeof(sql));

    sprintf(sql, "UPDATE directory_info SET '%s'=%f, '%s'='%s', '%s'=%d, '%s'=%d WHERE  '%s'='%s' AND '%s'='%s'",
    		"directory_size", directory_info.directory_size, "recent_use_time", directory_info.recent_use_time,
			"accessed_time", directory_info.accessed_time, "file_number", directory_info.file_number,
			"directory_name", directory_info.directory_name, "disk_uuid", directory_info.disk_uuid);


	int res = mysql_query(g_conn, sql);
	if (!res) {
		printf("Update %lu rows\n", (unsigned long)mysql_affected_rows(g_conn));
	} else {
		print_mysql_error(NULL);
	}
}


/**
 * 更新磁盘信息
 * 包括 `disk_used`, `recent_use_time`, `disk_status`
 */
void
update_disk(Disk_Info disk_info) {
	char sql[MAX_BUF_SIZE];
	memset(sql, 0, sizeof(sql));

    sprintf(sql, "UPDATE disk_info SET '%s'=%f, '%s'='%s', '%s'=%d WHERE  '%s'='%s' AND '%s'='%s'",
    		"disk_used", disk_info.disk_used, "recent_use_time", disk_info.recent_use_time, "disk_status", disk_info.disk_status,
			"disk_name", disk_info.disk_name, "disk_uuid", disk_info.disk_uuid);


	int res = mysql_query(g_conn, sql);
	if (!res) {
		printf("Update %lu rows\n", (unsigned long)mysql_affected_rows(g_conn));
	} else {
		print_mysql_error(NULL);
	}
}


/**
 * 更新文件信息
 * 包括 `recent_use_time`, `accessed_time`
 */
void
update_file(File_Info file_info) {
	char sql[MAX_BUF_SIZE];
	memset(sql, 0, sizeof(sql));

    sprintf(sql, "UPDATE file_info SET '%s'='%s', '%s'=%d WHERE  '%s'='%s' AND '%s'='%s'",
    		"recent_use_time", file_info.recent_use_time, "accessed_time", file_info.accessed_time,
			"file_name", file_info.file_name, "md5", file_info.md5);


	int res = mysql_query(g_conn, sql);
	if (!res) {
		printf("Update %lu rows\n", (unsigned long)mysql_affected_rows(g_conn));
	} else {
		print_mysql_error(NULL);
	}
}


/**
 * 删除记录（不提供）
 */
void
delete() {
}



/**
 * 释放结果集
 */
void
free_result(){
	mysql_free_result(g_res);
}

/**
 * 关闭数据库
 */
void
close_db(){
	mysql_close(g_conn); // 关闭链接
}



