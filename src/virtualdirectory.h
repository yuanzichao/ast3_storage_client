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
void excute_show_all();
//void excute_use(char* diskName);
void excute_list();
void excute_list_all();
void excute_cd(char* dirName);
void excute_ls(char* diskName, char* dirName);
void excute_ls_all(char* diskName, char* dirName);
void excute_ls_file(char* fileName,char* dirName, char* diskName);
void excute_pwd();
void query_time(char *start_time, char * end_time);
void query_location(char *start_ra, char *end_ra, char *start_dec, char *end_dec);
void excute_return_parent_directory(char* dirName,char* diskName);
void excute_help();
