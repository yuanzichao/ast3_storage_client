/*
 * virtualdirectory.c
 *
 *  Created on: 2015年5月28日
 *      Author: jermaine
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"sql.h"
#include"virtualdirectory.h"

/*
 * format()：命令预处理
 * 参数：char* command
 * 返回值：基本上需要两个：命令本身及所带参数（ls -l 或者 cd 目录名）或者定义全局变量在函数中赋值
 *
 */
int format(char* input){

	char* newInput;
	newInput=strtok(input,"\n");

	char* command;
	char* parameter1;
	char* parameter2;
	char* parameter3;
	char* parameter4;

	command=strtok(newInput," ");
	parameter1=strtok(NULL," ");
	parameter2=strtok(NULL," ");
	parameter3=strtok(NULL," ");
	parameter4=strtok(NULL," ");
	//printf("%s\n",command);


	if((strcmp(command,"ls")==0)&&(parameter1==NULL))
	{
		key=0;
	}
	else if((strcmp(command,"ls")==0)&&(strcmp(parameter1,"-l")==0)&&(parameter2==NULL))
	{
		key=1;
	}
	else if((strcmp(command,"cd")==0)&&(strcmp(parameter1,"/")==0)&&(parameter2==NULL))
	{
		key=2;
		currentDisk=parameter1;
	}
	else if((strcmp(command,"cd")==0)&&(strcmp(parameter1,"..")==0)&&(parameter2==NULL))
	{
		key=3;
		//currentDirectory=parameter1;
	}
	else if((strcmp(command,"cd")==0)&&(parameter1!=NULL)&&(strcmp(parameter1,"..")!=0)&&(strcmp(parameter1,"/")!=0)&&(parameter2==NULL))
	{
		key=4;
		currentDirectory=parameter1;
	}
	else if((strcmp(command,"open")==0)&&(parameter1!=NULL)&&(parameter2==NULL))
	{
		key=5;
		currentDisk=parameter1;
	}
	else if((strcmp(command,"ls")==0)&&(strcmp(parameter1,"-l")==0)&&(parameter2!=NULL)&&(parameter3==NULL))
	{
		key=6;
		fileName = parameter2;
	}
	else if((strcmp(command,"pwd")==0)&&(parameter1==NULL))
	{
		key=7;
	}
	else if((strcmp(command,"query")==0)&&(parameter1!=NULL)&&(parameter2!=NULL)&&(parameter3==NULL))
	{
		key=8;
		startTime = parameter1;
		endTime = parameter2;
	}
	else if(strcmp(command,"location")==0)
	{
		key=9;
		start_ra = parameter1;
		end_ra = parameter2;
		start_dec = parameter3;
		end_dec  = parameter4;
	}

	else
	{
		key=10;
	}
	return key;

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
	//printf("%d",print_result());
	/*if((print_result())!=13)
	{
		printf("%s\n","There is no disk information");
	}*/
	free_result();     //释放结果集

}


/*
 * execute_show_all():执行show操作
 * 参数：无
 * 返回值：无
 * 功能描述：列出所有磁盘详细信息
 */
void excute_show_all(){

	query_all_disks();     //查询所有磁盘信息
	print_result();    //打印结果
	//printf("%d",print_result());
	/*if((print_result())!=13)
	{
		printf("%s\n","There is no disk information");
	}*/
	free_result();     //释放结果集

}


/*
 * execute_use(char* diskName):执行use操作
 * 参数：char* diskName
 * 返回值：无
 * 功能描述：进入指定磁盘"

void excute_use(char* diskName){

	currentDisk=diskName;

} */


/*
 * execute_list(char* diskName):执行list操作
 * 参数：char* diskName
 * 返回值：无
 * 功能描述：列出指定磁盘下的目录信息
 */
void excute_list(char* diskName){

	query_disks_info(diskName);  //查询目录信息
	print_result();              //打印结果
	//printf("%d",print_result());
	/*if((print_result())!=11)
	{
		printf("%s\n","There are no directories in the disk");
	}*/
	free_result();               //释放结果集

}


/*
 * execute_list(char* diskName):执行list操作
 * 参数：char* diskName
 * 返回值：无
 * 功能描述：列出指定磁盘下的目录信息
 */
void excute_list_all(char* diskName){

	query_disks_all_info(diskName);  //查询目录信息
	print_result();              //打印结果
	//printf("%d",print_result());
	/*if((print_result())!=11)
	{
		printf("%s\n","There are no directories in the disk");
	}*/
	free_result();               //释放结果集

}


/*
 * execute_ls(char* parameter):执行ls
 * 参数：char* parameter
 * 返回值：无
 * 功能描述：在终端显示当前目录结构
 */
void excute_ls(char* dirName, char* diskName){

	query_directory_info(dirName, diskName);//查询当前目录内文件和目录信息
	print_result();       //打印结果
	//printf("%d",print_result());
	/*if((print_result())!=13)
	{
		printf("%s\n","There are no files in the directory");
	}*/
	free_result();        //释放结果集

}


/*
 * execute_ls(char* parameter):执行ls
 * 参数：char* parameter
 * 返回值：无
 * 功能描述：在终端显示当前目录详细信息
 */
void excute_ls_all(char* dirName, char* diskName){

	query_directory_all_info(dirName, diskName);//查询当前目录内文件和目录详细信息
	print_result();       //打印结果
	//printf("%d",print_result());
	/*if((print_result())!=13)
	{
		printf("%s\n","There are no files in the directory");
	}*/
	free_result();        //释放结果集

}


/*
 * execute_pwd():执行pwd操作
 * 参数：无
 * 返回值：无
 * 功能描述：显示当前工作目录

void excute_pwd(){

	printf(currentDisk, " ",currentDirectory,"\n");

}*/


/*
 * execute_time(char *start_time, char *end_time):执行query操作
 * 参数：无
 * 返回值：无
 * 功能描述：显示当前工作目录
 */
void query_time(char *start_time,  char *end_time){

	query_file_by_time(start_time, end_time);//根据时间查询文件信息
	print_result();		  //打印结果
	//printf("%d",print_result());
	/*if((print_result())!=13)
	{
		printf("%s\n","No file was retrieved");
	}*/
	free_result();        //释放结果集

}


/**
 * query_location(char *start_ra, char *end_ra, char *start_dec, char *end_dec)
 * 参数：起止位置坐标
 * 返回值：无
 * 功能描述：根据位置查询文件信息
 */
void
query_location(char *start_ra, char *end_ra, char *start_dec, char *end_dec){

	query_file_by_location(start_ra, end_ra, start_dec, end_dec);	//根据位置查询文件信息
	print_result();		  //打印结果
	free_result();        //释放结果集
}


void excute_return_parent_directory(char* dirName,char* diskName){

	char* dirID;
	memset(dirID, 0, sizeof(char)*100);
	memcpy(dirID,get_parent_id(dirName,diskName),strlen(get_parent_id(dirName,diskName)));
	memset(currentDirectory, 0, sizeof(char)*100);
	memcpy(currentDirectory,return_directory(dirID,diskName),strlen(return_directory(dirID,diskName)));
	//char* dirID=get_parent_id(dirName,diskName);
	//currentDirectory=return_directory(dirID,diskName);
	print_result();
	free_result();

}


void excute_ls_file(char* fileName,char* dirName,char* diskName){

	get_file_info(fileName,dirName, diskName);
}

/*
 * execute_help():执行query操作
 * 参数：无
 * 返回值：无
 * 功能描述：显示帮助信息
 */
void excute_help(){
	printf("本软件为虚拟目录，您可通过以下指令进行操作\n");
	printf("ls\t\t\t\t列出所有磁盘及目录信息\n");
	printf("ls -l\t\t\t\t列出磁盘及目录详细信息\n");
	printf("open 磁盘名\t\t\t进入指定磁盘\n");
	printf("cd 目录名\t\t\t\t切换到指定目录\n");
	printf("cd ..\t\t\t\t返回父目录\n");
	printf("cd /\t\t\t\t返回根目录\n");
	printf("ls \t\t\t\t列出当前目录下的文件信息\n");
	printf("pwd\t\t\t\t显示当前工作目录\n");
	printf("query 开始日期 终止日期\t\t检索日期范围内的文件\n");
	printf("location 起始赤经 终止赤经 起始赤纬 终止赤纬\t\t检索指定位置范围内的文件\n");

}

