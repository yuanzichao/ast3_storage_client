/*
 * virtualdirectory.h
 *
 *  Created on: 2015年5月28日
 *      Author: jermaine
 */

#include <mysql/mysql.h>
#include "orm/db.h"

#ifndef SRC_VIRTUALDIRECTORY_H_
#define SRC_VIRTUALDIRECTORY_H_



#endif /* SRC_VIRTUALDIRECTORY_H_ */

int key;
char* currentDisk;
char* currentDirectory;
char* currentDirId;

char* fileName;

char* startTime;
char* endTime;

char *start_ra;
char *end_ra;
char *start_dec;
char *end_dec;

MYSQL_ROW g_row1; // 字符串数组，mysql 记录行


//函数声明区



int format(char* parameter);

void excute_show();
void excute_show_primary();
void excute_show_all();
//void excute_use(char* diskName);
void excute_list_directory(char* diskName,char* dirId);//列出当前磁盘/目录下的目录名
void excute_list_primary_directory(char* diskName,char* dirId);//列出当前磁盘/目录下的目录基本信息
void excute_list_all_directory(char* diskName,char* dirId);//列出当前磁盘/目录下的目录详细信息
void excute_cd(char* dirName);
void excute_list_file(char* diskName, char* dirId);//列出当前磁盘/目录下的文件名
void excute_list_primary_file(char* diskName, char* dirId);//列出当前磁盘/目录下的文件基本信息
void excute_list_all_file(char* diskName, char* dirId);//列出当前磁盘/目录下的文件详细信息
void excute_list_primary_oneFile(char* diskName,char* dirId, char* fileName);//列出指定文件的基本信息
void excute_ls_file_wildcard(char* fileName,char* dirName, char* diskName);
void excute_list_all_oneFile(char* diskName,char* dirId, char* fileName);//列出指定文件的详细信息
void excute_pwd();
void query_time_from_home(char *start_time, char * end_time);
void query_time_from_curr(char* diskName,char* dirId,char *start_time,  char *end_time);//在当前目录下搜索符合时间范围内的文件
void query_location(char *start_ra, char *end_ra, char *start_dec, char *end_dec);//从根目录下开始搜索符合空间范围内的文件
void query_location_curr(char* dirName,char* diskName,char *start_ra, char *end_ra, char *start_dec, char *end_dec);//在当前目录下搜索符合空间范围内的文件
//void excute_return_parent_directory(char* dirName,char* diskName);
void excute_copy_file();
void excute_help();
void excute_return_parent_directory(); //返回父目录
int excute_change_directory(char* diskName,char* dirName,char* parentId);//切换到指定目录
