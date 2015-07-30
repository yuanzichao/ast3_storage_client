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


	if((strcmp(command,"ls")==0)&&(parameter1==NULL))   //ls
	{
		key=0;
	}
	else if((strcmp(command,"ls")==0)&&(strcmp(parameter1,"-l")==0)&&(parameter2==NULL))   //ls -l
	{
		key=1;
	}
	else if((strcmp(command,"ls")==0)&&(strcmp(parameter1,"-l")==0)&&(parameter2!=NULL)&&(strcmp(parameter2,"*.fits")!=0)&&(parameter3==NULL))   //ls -l fileName
	{
		key=2;
		fileName=parameter2;
	}
	else if((strcmp(command,"ls")==0)&&(strcmp(parameter1,"-***")==0)&&(parameter2==NULL))   //ls -***
	{
		key=3;
	}
	else if((strcmp(command,"ls")==0)&&(strcmp(parameter1,"-***")==0)&&(parameter2!=NULL)&&(parameter3==NULL))  //ls -*** fileName
	{
		key=4;
		fileName = parameter2;
	}
	else if((strcmp(command,"cd")==0)&&(strcmp(parameter1,"/")==0)&&(parameter2==NULL))  //cd /
	{
		key=5;
		currentDisk=parameter1;
	}
	else if((strcmp(command,"cd")==0)&&(strcmp(parameter1,"..")==0)&&(parameter2==NULL))   //cd ..
	{
		key=6;
		//currentDirectory=parameter1;
	}
	else if((strcmp(command,"cd")==0)&&(parameter1!=NULL)&&(strcmp(parameter1,"..")!=0)&&(strcmp(parameter1,"/")!=0)&&(parameter2==NULL)) //cd dir
	{
		key=7;
		currentDirectory=parameter1;
	}
	else if((strcmp(command,"open")==0)&&(parameter1!=NULL)&&(parameter2==NULL))  //open disk
	{
		key=8;
		currentDisk=parameter1;
	}

	else if((strcmp(command,"pwd")==0)&&(parameter1==NULL))  //pwd
	{
		key=9;
	}
	else if((strcmp(command,"find")==0)&&(strcmp(parameter1,"time")==0)&&(parameter2!=NULL)&&(parameter3!=NULL)&&(parameter4==NULL)) //find time
	{
		key=10;
		startTime = parameter2;
		endTime = parameter3;
	}
	else if((strcmp(command,"find")==0)&&(strcmp(parameter1,"/time")==0)&&(parameter2!=NULL)&&(parameter3!=NULL)&&(parameter4==NULL))  //find /time
	{
		key=11;
		startTime = parameter2;
		endTime = parameter3;
	}
	else if(strcmp(command,"/location")==0)  //  /location
	{
		key=12;
		start_ra = parameter1;
		end_ra = parameter2;
		start_dec = parameter3;
		end_dec  = parameter4;
	}
	else if(strcmp(command,"location")==0)  //  location
	{
		key=13;
		start_ra = parameter1;
		end_ra = parameter2;
		start_dec = parameter3;
		end_dec  = parameter4;
	}
	/*else if((strcmp(command,"ls")==0)&&(strcmp(parameter1,"-l")==0)&&(strcmp(parameter2,"*.fits")==0)&&(parameter3==NULL))
	{
		key=11;
		fileName = parameter2;
	}*/
	else if((strcmp(command,"cp")==0)&&(parameter1!=NULL))
	{
		key=14;
	}
	else
	{
		key=100;
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
 * execute_show_primary():执行show操作
 * 参数：无
 * 返回值：无
 * 功能描述：列出所有磁盘详细信息
 */
void excute_show_primary(){

	query_primary_disks();     //查询所有磁盘信息
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
void excute_list_directory(char* diskName,char* dirId){

	query_disks_info(diskName,dirId);  //查询目录信息
	print_result();              //打印结果
	//printf("%d",print_result());
	/*if((print_result())!=11)
	{
		printf("%s\n","There are no directories in the disk");
	}*/
	free_result();               //释放结果集

}


/*
 * execute_list_primary(char* diskName):执行list操作
 * 参数：char* diskName
 * 返回值：无
 * 功能描述：列出指定磁盘下的目录基本信息
 */
void excute_list_primary_directory(char* diskName,char* dirId){

	query_disks_primary_info(diskName,dirId);  //查询目录信息
	print_result();              //打印结果
	//printf("%d",print_result());
	/*if((print_result())!=11)
	{
		printf("%s\n","There are no directories in the disk");
	}*/
	free_result();               //释放结果集

}


/*
 * execute_list_all(char* diskName):执行list操作
 * 参数：char* diskName
 * 返回值：无
 * 功能描述：列出指定磁盘下的目录信息
 */
void excute_list_all_directory(char* diskName,char* dirId){

	query_disks_all_info(diskName,dirId);  //查询目录信息
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
void excute_list_file(char* diskName, char* dirId){

	query_directory_info(diskName, dirId);//查询当前目录内文件和目录信息
	print_result();       //打印结果
	//printf("%d",print_result());
	/*if((print_result())!=13)
	{
		printf("%s\n","There are no files in the directory");
	}*/
	free_result();        //释放结果集

}


/*
 * execute_ls_primary(char* parameter):执行ls
 * 参数：char* parameter
 * 返回值：无
 * 功能描述：在终端显示当前目录基本信息
 */
void excute_list_primary_file(char* dirName, char* dirId){

	query_directory_primary_info(dirName, dirId);//查询当前目录内文件和目录详细信息
	print_result();       //打印结果
	//printf("%d",print_result());
	/*if((print_result())!=13)
	{
		printf("%s\n","There are no files in the directory");
	}*/
	free_result();        //释放结果集

}


/*
 * execute_ls_all(char* dirName, char* diskName):执行ls
 * 参数：char* parameter
 * 返回值：无
 * 功能描述：在终端显示当前目录详细信息
 */
void excute_list_all_file(char* diskName, char* dirId){

	query_directory_all_info(diskName, dirId);//查询当前目录内文件和目录详细信息
	print_result();       //打印结果
	//printf("%d",print_result());
	/*if((print_result())!=13)
	{
		printf("%s\n","There are no files in the directory");
	}*/
	free_result();        //释放结果集

}


/*
 * execute_ls_file_wildcard(char* fileName,char* dirName, char* diskName):执行ls
 * 参数：char* parameter
 * 返回值：无
 * 功能描述：在终端显示当前目录详细信息
 */
void excute_ls_file_wildcard(char* fileName,char* dirName, char* diskName){

	query_directory_wildcard_info(fileName,dirName,diskName);

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
void query_time_from_home(char *start_time,  char *end_time){

	query_file_by_time(start_time, end_time);//根据时间查询文件信息
	print_result();		  //打印结果
	//printf("%d",print_result());
	/*if((print_result())!=13)
	{
		printf("%s\n","No file was retrieved");
	}*/
	free_result();        //释放结果集

}


/*
 * execute_time(char *start_time, char *end_time):执行query操作
 * 参数：无
 * 返回值：无
 * 功能描述：显示当前工作目录
 */
void query_time_from_curr(char* diskName,char* dirId,char *start_time,  char *end_time){

	query_file_by_time_curr(diskName,dirId,start_time, end_time);//根据时间查询文件信息
	//print_result();		  //打印结果

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


/**
 * query_location(char *start_ra, char *end_ra, char *start_dec, char *end_dec)
 * 参数：起止位置坐标
 * 返回值：无
 * 功能描述：根据位置查询文件信息
 */
void
query_location_curr(char* diskName,char* dirId,char *start_ra, char *end_ra, char *start_dec, char *end_dec){

	query_file_by_curr_location(diskName,dirId,start_ra, end_ra, start_dec, end_dec);	//根据位置查询文件信息
	//print_result();		  //打印结果
	free_result();        //释放结果集
}



/*void excute_return_parent_directory(char* dirName,char* diskName){

	char* dirID;
	memset(dirID, 0, sizeof(char)*100);
	memcpy(dirID,get_parent_id(dirName,diskName),strlen(get_parent_id(dirName,diskName)));
	memset(currentDirectory, 0, sizeof(char)*100);
	memcpy(currentDirectory,return_directory(dirID,diskName),strlen(return_directory(dirID,diskName)));
	//char* dirID=get_parent_id(dirName,diskName);
	//currentDirectory=return_directory(dirID,diskName);
	print_result();
	free_result();

}*/
/*
 * 返回父目录
 */
void excute_return_parent_directory(){

	if(strcmp(currentDisk,"home")==0)
	{

	}
	else if(strcmp(currentDirectory,"unknown")==0)
	{
		memset(currentDisk, 0, sizeof(char)*MAX_BUF_SIZE);
		memcpy(currentDisk, "home",sizeof(char)*4);
	}
	else
	{
		currentDirId = get_parent_id(currentDirId);
		if(strcmp(currentDirId,"0")==0)
		{
			memset(currentDirectory, 0, sizeof(char)*MAX_BUF_SIZE);
			memcpy(currentDirectory, "unknown", sizeof(char)*7);
			//当前ID？
		}
		else
		{
			currentDirectory = get_directory_name(currentDirId);
		}
	}

}

int excute_change_directory(char* diskName,char* dirName,char* parentId){

    char* dirId = (char*)malloc(MAX_BUF_SIZE);
	dirId = get_directory_id(diskName,dirName,parentId);
	if(strcmp(dirId,"false")==0)
	{
		printf("%s","The directory not exist.\n");
		return 1;
	}
	else
	{
		currentDirId = dirId;
		return 0;
	}
}

/*
 * 显示指定文件的基本信息
 */
void excute_list_primary_oneFile(char* diskName,char* dirId, char* fileName){

	get_file_primary_info(diskName,dirId,fileName);
	print_result();
	free_result();
}


void excute_list_all_oneFile(char* diskName,char* dirId, char* fileName){

	get_file_all_info(diskName,dirId, fileName);
	print_result();
	free_result();
}

void excute_copy_file(){

	printf("The file has been copied to cache directory\n");
}


/*
 * execute_help():执行query操作
 * 参数：无
 * 返回值：无
 * 功能描述：显示帮助信息
 */
void excute_help(){
	printf("本软件为虚拟目录，您可通过以下指令进行操作\n");
	printf("ls\t\t\t\t\t\t列出所有磁盘名、目录名和文件名\n");
	printf("ls -l\t\t\t\t\t\t列出所有磁盘、目录及文件的基本信息\n");
	printf("ls -l 文件名\t\t\t\t\t列出指定文件的基本信息\n");
	printf("ls -***\t\t\t\t\t\t列出所有磁盘、目录及文件的详细信息\n");
	printf("ls -*** 文件名\t\t\t\t\t列出指定文件的详细信息\n");
	printf("open 磁盘名\t\t\t\t\t进入指定磁盘\n");
	printf("cd 目录名\t\t\t\t\t\t切换到指定目录\n");
	printf("cd ..\t\t\t\t\t\t返回父目录\n");
	printf("cd /\t\t\t\t\t\t返回根目录\n");
	printf("pwd\t\t\t\t\t\t显示当前工作目录\n");
	printf("find time 开始日期 终止日期\t\t\t在当前目录下检索日期范围内的文件\n");
	printf("find /time 开始日期 终止日期\t\t\t从根目录开始检索日期范围内的文件\n");
	printf("location 起始赤经 终止赤经 起始赤纬 终止赤纬\t\t在当前目录下检索指定位置范围内的文件\n");
	printf("/location 起始赤经 终止赤经 起始赤纬 终止赤纬\t\t从根目录开始检索指定位置范围内的文件\n");
	printf("cp 文件名\t\t\t\t\t\t复制指定目录下的文件到特定路径下\n");
	printf("cp 目录名\t\t\t\t\t\t复制指定文件到特定路径下\n");

}

