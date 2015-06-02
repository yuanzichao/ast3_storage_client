/*
 * virtualdirectory.h
 *
 *  Created on: 2015年5月28日
 *      Author: jermaine
 */

#ifndef SRC_VIRTUALDIRECTORY_H_
#define SRC_VIRTUALDIRECTORY_H_



#endif /* SRC_VIRTUALDIRECTORY_H_ */

int key;
char* currentDisk;
char* currentDirectory;




//函数声明区



int format(char* parameter);

void excute_show();
void excute_use(char* diskName);
void excute_list();
void excute_cd(char* dirName);
void excute_ls();
void excute_pwd();
void excute_query();
void excute_help();
