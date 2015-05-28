//头文件区域
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"test_sql.h"
#include"sql.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//主函数
int main(void)
{

	init_mysql();//初始化数据库

	//声明命令
	char command[100];

    printf("您可通过help获取帮助\n");

	while(1){
		//gets(command);   //获取指令，以回车结束
		scanf("%s",command);

		//命令解析：主要对command进行格式化处理，指令格式有限，所以可以一一对应
		//format(command);  //命令处理，可以先不实现
		format(command);

		//执行响应的动作，key为命令解析后结果，决定调用哪个函数
		switch (key) {

			case 0:
				//新开一个线程执行相应操作
				execute_show();    //执行show操作
				break;
			case 1:
				//新开一个线程执行相应操作
				execute_use(currentDisk);    //执行use操作
				break;
			case 2:
				excute_list();
				break;
			case 3:
				excute_cd(currentDirectory);
				break;
			case 4:
				excute_ls();
				break;
			case 5:
				excute_pwd();
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













