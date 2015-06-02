//头文件区域
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"virtualdirectory.h"
#include"sql.h"

//int key;
//char* currentDisk;
//char* currentDirectory;

//主函数
int main()
{

	init_mysql();//初始化数据库

	//声明命令

/*	char command[100];
	char parameter1[100];
	char parameter2[100];
*/
	char* input;
	//char input[100];
    printf("您可通过help获取帮助\n");

	while(1){

        input=NULL;
		fgets(input,100,stdin);   //获取用户输入指令，以回车结束

		key=format(input);//命令解析：主要对input进行格式化处理
		//scanf("%s",&input);
		//if(strcmp(input,"show")==0)
			//key=0;

		//执行响应的动作，key为命令解析后结果，决定调用哪个函数
		switch (key) {

			case 0:
				excute_show();    //执行show操作
				break;
			case 1:
				//excute_use(currentDisk);    //执行use操作
				printf("Disk changed\n");
				break;
			case 2:
				excute_list(currentDisk);
				break;
			case 3:
				//excute_cd(currentDirectory);
				printf("Directory changed\n");
				break;
			case 4:
				excute_ls();
				break;
			case 5:
				//excute_pwd();
				printf("%s\n",currentDirectory);
				break;
			//case 6:
				//excute_query();
				//break;
			case 7:
				excute_help();
				break;
		}//指令执行结束，重新循环

	}


}













