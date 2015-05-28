/*
 * function.c
 *
 *  Created on: 2015年5月28日
 *      Author: jermaine
 */

#include"test_sql.h"
#include"sql.h"
#include<stdio.h>

/*
 * format()：命令预处理
 * 参数：char* command
 * 返回值：基本上需要两个：命令本身及所带参数（ls -l 或者 cd 目录名）或者定义全局变量在函数中赋值
 *
 */
void format(char* command){

	if(strcmp(command,"show")==0)
		key=0;
	else if(strcmp(command,"use")==0)
		key=1;
	else if(strcmp(command,"list")==0)
		key=2;
	else if(strcmp(command,"ast3cd")==0)
		key=3;
	else if(strcmp(command,"ast3ls")==0)
	    key=4;
	else if(strcmp(command,"ast3pwd")==0)
		key=5;
	else if(strcmp(command,"query")==0)
		key=6;
	else
		key=7;
}//定义好之后反向修改主函数调用



/*
 * execute_show():执行show操作
 * 参数：无
 * 返回值：无
 * 功能描述：列出所有磁盘信息
 */
void excute_show(){

	query_disks();     //查询所有磁盘信息
	print_result();    //打印结果
	free_result();     //释放结果集

}


/*
 * execute_use(char* diskName):执行use操作
 * 参数：char* diskName
 * 返回值：无
 * 功能描述：进入指定磁盘
 */
void excute_use(char* diskName){

	currentDisk=diskName;

}


/*
 * execute_list(char* diskName):执行list操作
 * 参数：char* diskName
 * 返回值：无
 * 功能描述：列出指定磁盘下的目录信息
 */
void excute_list(){

//	query_disks_info(diskName);  //查询目录信息
	print_result();              //打印结果
	free_result();               //释放结果集

}


/*
 * execute_cd(char* dirName):执行cd操作
 * 参数：char* dirName
 * 返回值：无
 * 功能描述：切换当前工作目录
 */
void excute_cd(char* dirName){

	currentDirectory=dirName;

}


/*
 * execute_ls(char* parameter):执行ls
 * 参数：char* parameter
 * 返回值：无
 * 功能描述：在终端显示当前目录结构
 */
void execute_ls(char* directory){

	query_directory_info(currentDirectory,currentDisk);//查询当前目录内文件和目录信息
	print_result();       //打印结果
	free_result();        //释放结果集

}


/*
 * execute_pwd():执行pwd操作
 * 参数：无
 * 返回值：无
 * 功能描述：显示当前工作目录
 */
void excute_pwd(){

	printf(currentDisk, " ",currentDirectory,"\n");

}


/*
 * execute_query(date date1,date date2):执行query操作
 * 参数：无
 * 返回值：无
 * 功能描述：显示当前工作目录

void excute_query(date date1,date date2){


}
 */


/*
 * execute_help():执行query操作
 * 参数：无
 * 返回值：无
 * 功能描述：显示当前工作目录
 */
void excute_help(){
	printf("本软件为虚拟目录，您可通过以下指令进行操作\n");
	printf("show       列出所有磁盘信息\n");
	printf("use 磁盘名       进入指定磁盘\n");
	printf("list    列出所在磁盘下的目录信息\n");
	printf("ast3cd 目录名    切换到指定目录\n");
	printf("ast3ls 目录名    列出当前目录下的文件信息\n");
	printf("ast3pwd      显示当前工作目录\n");
	printf("query 日期 日期    检索日期范围内的文件\n");

}



