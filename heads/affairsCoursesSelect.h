//教务处操作

/*
	管理员信息函数
*/
//firstChild print
//功能,对用户的增加,删除,修改
//对课程的安排(增删改查),开课事件的安排
void addUser(userLink start);//添加用户
void deleteUser(userLink start);//删除用户
void replaceUserInfo(userLink start);//修改用户信息
void replaceInfo(userLink preInfo, userLink newInfo);//将原来用户信息用新用户信息替代
void copyLinkNode(userLink newInfo, userLink preInfo);//将之前节点拷贝到新节点上
void userManager();//增删改查用户，TODO:发消息
void coursesManager();//课程管理
void sysManager();//系统设置
void importCourse(int type);//导入课程、专业和学院信息
void printCourse(instituteList head);//不带头结点单链表，测试打印课程信息
void coursesDetail();//进入学院专业和课程的详情页进行相应操作
void updateCourse(int type);//对学院、专业和课程进行查看、删除和更新
int listToFile(instituteList head, int type);//将学院课程专业链存入到数据库
void setPageLength(int* defaultLength);//设置用户显示页面长度
void showAlluser();//显示全部用户
void importUser();//导入用户调用
void addUserByFile(userLink start,char* filename);//通过文件名批量添加用户
void addUserFunc();//添加用户调用函数

void searchByIdFunc();//按id查询调用
void searchUserFunc();
void searchUserByNameFunc(int ii);//按名字精确查询调用
void searchUserByNameFunc2(int ii);//按名字模糊查询调用
void deleteUserFunc();//删除用户调用函数
void replaceInfoFunc();//修改用户信息调用函数
void deleteOneUserById(int d);//通过id删除一个用户
void deleteMultiAmountUser(int startId,int endId);
void deleteMultiAmountUserByLength(int startId,int length);
void deleteMultiAmountUserManage();
void deleteMultiAmountUserFunc(int flag);

void addUsrCourse(userNode* us);//添加用户课程信息

void printNode(userLink up){//显示一个节点信息
        if (up->info) {
			printf("学号: %d", up->info->id);
			printf("\t角色号: %d", up->info->roleId);
			printf("\t姓名: %s", up->info->name);
			printf("\t密码: %s", up->info->passwd);
			printf("\t学院: %s\n", up->info->institute);
			printf("电话号码: %s ", up->info->phoneNum);
			printf("简介: %s  ", up->info->synopsis);
			coursePoint p;
			p = up->info->firstChild->next;
			if (p) {
				printf("当前课程有: \n");
				printf("课程号:");
				while(p){
                    printf(" %d ",p->courseId);
                    p = p->next;
				}
			}
			else {
				printf("当前无课程\n");
			}
		}
}

void deleteMultiAmountUserFunc(int flag){
    system("cls");
    clearInputBufer();
    int startId;
    char a;
    quickSortById(globalHead);
    if(flag == 1){//按起始id和截至id显示用户
            int endId;
            while(1){
                printf("请输入起始id:");
                scanf("%d",&startId);
                printf("请输入截至id:");
                scanf("%d",&endId);
                deleteMultiAmountUser(startId,endId);
                clearInputBufer();
                printf("输入(Y|y)继续修改,否则按任意键返回\n");
                a = getchar();
                if(a != 'Y' && a!='y'){
                    tip("正在返回");
                    break;
                }
            }

    }
    else if(flag == 2){//按起始id和长度显示用户
        while(1){
                int length;
                printf("请输入起始id:");
                scanf("%d",&startId);
                printf("请输入长度:");
                scanf("%d",&length);
                deleteMultiAmountUserByLength(startId,length);
                clearInputBufer();
                 //print(globalHead);
                printf("输入(Y|y)继续修改,否则按任意键返回\n");
                a = getchar();
                if(a != 'Y' && a!='y'){
                    tip("正在返回");
                    break;
                }
            }
    }
    else{
        printf("标记flag输入错误\n");
    }
}

void deleteMultiAmountUserManage(){
    char *menuArr[]={
                    "删除大量用户",
                    "通过起始id和截至id删除",
                    "通过起始id和长度删除",
                    "返回"
                };
    int loop=1;
    while( loop ){
        switch( showMenu(menuArr, 4) ){
            case 1: deleteMultiAmountUserFunc(1); break;
            case 2: deleteMultiAmountUserFunc(2); break;
            case -1: isLogout = 1; break;
            default: loop=0;
        }
        //如果全局为注销则退出当前菜单直到首页
        if( isLogout ) loop=0;
    }
}

void deleteMultiAmountUserByLength(int startId,int length){
    int i=0;
    if(startId>0){
        while(i<length){
            deleteOneUserById(startId+i);
            i++;
        }
    }
    else
        printf("id导入错误,请检查id号是否大于0\n");

}

void deleteMultiAmountUser(int startId,int endId){
    int i;
    if(startId<endId&&startId>0){
        for(i = startId;i<=endId;i++)
            deleteOneUserById(i);
    }
    else
        printf("id导入错误,请检查id号是否大于0或截至id是否大于起始id\n");

}


void deleteOneUserById(int d){
	userLink user;
	userLink pre = globalHead;
	user = searchById(globalHead, pre, d);
	if (!user)
		printf("id为%d的用户不存在\n",d);
	else {
        int i;
        userLink head;
        userLink p,pp;
        head = (userLink)malloc(sizeof(userList));
        head->info = NULL;
        head->next = NULL;
        pre->next = user->next;
        //找到user对应的文件
        i = getCorrectInsertIndex(user->info->name);
        readUserData(fileArr[i],head);
        pp = head;
        p = head->next;
        while(p&&strcmp(p->info->name,user->info->name)!=0){
                pp = p;
                p = p->next;
        }
        pp->next = p->next;
        free(p);
        writeInfoToFile(fileArr[i],head->next);
        freeUser(head);
        free(user);
        printf("删除成功\n");
	}
}

void replaceInfoFunc(){
    system("cls");
    quickSortById(globalHead);
    char a;
    while(1){
        replaceUserInfo(globalHead);
        printf("输入(Y|y)继续修改,否则按任意键返回\n");
        a = getchar();
        //printf("%c",a);
        if(a != 'Y'&&a != 'y'){
            tip("正在返回");
            break;
        }
        clearInputBufer();
    }

}

void deleteUserFunc(){
    system("cls");
    quickSortById(globalHead);
    char a;
    while(1){
        deleteUser(globalHead);
        printf("输入(Y|y)继续删除,否则按任意键返回\n");
        a = getchar();
        //printf("%c",a);
        if(a != 'Y'&&a != 'y'){
            tip("正在返回");
            break;
        }
        clearInputBufer();
    }

}

void searchByIdFunc(){//id要已经有序,若无序则在其中按id快排
    system("cls");
    userLink pre = NULL;
    userLink p;
    int id;
    clearInputBufer();
    quickSortById(globalHead);
    printf("请输入要查找的id号:");
    while(scanf("%d",&id)!=EOF){
        char a;
        if((p = searchById(globalHead,pre,id))){
            printNode(p);
        }
        else
            printf("id:%d不存在",id);
        printf("是否要继续查询(Y)或按任意键返回\n");
        clearInputBufer();
        a = getchar();
        if( a == 'Y'||a == 'y')
            printf("请输入要查找的id号:");
        else{
            tip("正在返回");
            break;
        }

    }

}

void searchUserByNameFunc(int ii){
    system("cls");
    char name[20];
    int i;
    userLink head,p;
    head = (userLink)malloc(sizeof(userList));
    head->next = NULL;
    head->info = NULL;
    printf("请输入要查找的名字:");
    clearInputBufer();
    while(1){
        int counter = 0;
        char a;
        gets(name);
        i = getCorrectInsertIndex(name);//找到名字对应的文件
        readUserData(fileArr[i],head);
        //printf("name = %s,i = %d",name,i);
        p = head->next;
        //print(head);
        while(p&&strcmp(p->info->name,name)>=0){
            if(strcmp(p->info->name,name)==0){
                if(ii==3){
                    printf("姓名%s ", p->info->name);
                    printf("学号%d ", p->info->id);
                    printf("角色号%d ", p->info->roleId);
                    //printf("密码%s ", user->info->passwd);
                    printf("学院%s ", p->info->institute);
                    printf("电话号码%s ", p->info->phoneNum);
                    printf("简介%s \n", p->info->synopsis);
                    counter++;
                }
                else{
                    if(p->info->roleId == (ii-1)){
                        printf("姓名%s ", p->info->name);
                        printf("学号%d ", p->info->id);
                        printf("角色号%d ", p->info->roleId);
                        //printf("密码%s ", user->info->passwd);
                        printf("学院%s ", p->info->institute);
                        printf("电话号码%s ", p->info->phoneNum);
                        printf("简介%s \n", p->info->synopsis);
                        counter++;
                    }
                }
            }
            p = p->next;
        }
        if(counter == 0)
            printf("未找到%s",name);
        printf("是否要继续查询:(Y|y),按否则按任意键退出\n");
        a = getchar();
        if(a != 'Y'&&a != 'y'){
            tip("正在返回");
            break;
        }
        printf("请输入要查找的名字:");

    }


}

void searchUserByNameFunc2(int ii){
    system("cls");
    char name[20];
    userLink head;
    printf("请输入要查找的关键字:");
    clearInputBufer();
    while(1){
        char a;
        int counter = 0;
        userLink p;
        gets(name);
         head = searchByStr(globalHead,name);
         p = head->next;
         while(p){
            if(ii==3){
                    printf("姓名%s ", p->info->name);
                    printf("学号%d ", p->info->id);
                    printf("角色号%d ", p->info->roleId);
                    //printf("密码%s ", user->info->passwd);
                    printf("学院%s ", p->info->institute);
                    printf("电话号码%s ", p->info->phoneNum);
                    printf("简介%s \n", p->info->synopsis);
                    counter++;
                }
                else{
                    if(p->info->roleId == (ii-1)){
                        printf("姓名%s ", p->info->name);
                        printf("学号%d ", p->info->id);
                        printf("角色号%d ", p->info->roleId);
                        //printf("密码%s ", user->info->passwd);
                        printf("学院%s ", p->info->institute);
                        printf("电话号码%s ", p->info->phoneNum);
                        printf("简介%s \n", p->info->synopsis);
                        counter++;
                    }
                }
                p = p->next;
         }

         if(counter == 0)
            printf("未找到关键字%s对应的用户\n",name);
        printf("是否要继续查询:(Y|y),按否则按任意键退出\n");
        a = getchar();
        if(a != 'Y'&&a != 'y'){
            tip("正在返回");
            break;
        }
        printf("请输入要查找的关键字:");
    }
}

void searchManage(int i){
    char *menuArr[]={
                    "查找用户",
                    "按id查找",
                    "按姓名查找",
                    "按姓名模糊查询",
                    "返回"
                };
    int loop=1;
    while( loop ){
        switch( showMenu(menuArr, 5) ){
            case 1: searchByIdFunc(); break;
            case 2: searchUserByNameFunc( i); break;
            case 3: searchUserByNameFunc2( i); break;
            case -1: isLogout = 1; break;
            default: loop=0;
        }
        //如果全局为注销则退出当前菜单直到首页
        if( isLogout ) loop=0;
    }
}

void affairsCoursesSelect(){
    char *menuArr[]={
                    "教务处",
                    "课程管理",//增删改查
                    "用户管理",
                    "系统设置",
                    "教师之家",
                    "当前位置：首页"
                };
    int loop=1;
    while( loop ){
        switch( showMenu(menuArr, 6) ){
            case 1: coursesManager(); break;
            case 2: userManager(); break;
            case 3: sysManager(); break;
            case 4: teaCoursesSelect(); break;
            case -1: isLogout = 1; break;
            default: loop=0;
        }
        //如果全局为注销则退出当前菜单直到首页
        if( isLogout ) loop=0;
    }
}
void nowsystemStatus(){
    int Status;
    printf("当前的系统状态是：%d\n",systemStatus);
    printf("请输入需要修改成的系统状态（0：为正常状态；1：为选课状态；）：\n");
    scanf("%d",&Status);
    systemStatus=Status;
    if(systemStatus==0){
        tip("当前系统状态已经修改为正常状态！");
    }else if(systemStatus==1){
        tip("当前系统状态已经修改成选课状态！");
    }else{
        tip("输入的系统状态不正确！");
    }

}
void changechance(){
    printf("当前用户密码可尝试次数为：%d\n",loginTimes);
    printf("请输入需要修改成的次数：");
    int newloginTimes;
    scanf("%d",&newloginTimes);
    loginTimes=newloginTimes;
    printf("当前用户密码可尝试次数已经被修改成：%d\n",loginTimes);
    tip(">>>>");


}
void changekeylength(){
    printf("当前用户密码长度为：%d\n",passLength);
    printf("请输入需要修改成的长度：");
    int newpassLength;
    scanf("%d",&newpassLength);
    passLength=newpassLength;
    printf("当前用户密码长度已经被修改成：%d\n",passLength);
    tip(">>>>");

}
void changeAdmin(){
    printf("当前管理员用户名：%d 密码：%s\n", Admin, AdminPass);
    printf("请输入修改的用户名：");
    int newpassLength;
    scanf("%d",&newpassLength);
    Admin=newpassLength;
    printf("请输入修改的密码：");
    scanf("%s", AdminPass);
    printf("当前管理员用户名、密码已经被修改成：%d 密码：%s\n", Admin, AdminPass);
    tip(">>>>");

}
void changePageMax(){
    printf("当前每页显示数据条数为：%d\n",pageMax);
    printf("请输入需要修改成的长度：");
    int newpassLength;
    scanf("%d",&newpassLength);
    pageMax=newpassLength;
    printf("每页显示数据条数已经被修改成：%d\n",pageMax);
    tip(">>>>");

}
void sysManager(){
    char *menuArr[]={
                    "系统设置",
                    "当前系统状态",//正常或者选课状态
                    "用户可尝试输入密码次数",
                    "用户密码长度",
                    "修改超级管理员用户名和密码",
                    "修改每页显示数据条数",
                    "当前位置：首页->教务处->系统设置"
                };
    int loop=1;
    while( loop ){
        switch( showMenu(menuArr, 7) ){
            case 1: nowsystemStatus();break;
            case 2: changechance();break;
            case 3: changekeylength();break;
            case 4: changeAdmin();break;
            case 5: changePageMax();break;
            case -1: isLogout = 1; break;
            default: loop=0;
        }
        //如果全局为注销则退出当前菜单直到首页
        if( isLogout ) loop=0;
    }
}
void printCourse(instituteList head){
    while(head){
        if( strcmp("", head->synopsis)==0 ){
            printf("\t\t\tId:%d Name:%s\n",head->instituteId, head->instituteName);
        }else{
            printf("\t\t\tId:%d Name:%s Synopsis:%s\n",head->instituteId, head->instituteName, head->synopsis);
        }

        head = head->next;
    }
}




//删除数据操作
void delCourse(instituteList head, int arr[]){
    instituteList pre,p,q,s;
    pre = head;
    p = q = head->next;
    int counter=0;
    if( arr[1]==-1 ) arr[1]=1;
    //查找要删除节点
    while( p&&p->instituteId!=arr[0] ){
        pre = p;
        p = p->next;
    }
    if( p ){
        q = p;
        while( (arr[1]--)&&q ){
            q = q->next;
        }
        pre->next = q;
        s = p;
        while( s!=q ){
            p = s->next;
            free(s);
            counter++;
            s = p;
        }
        printf("\t\t\t%d条数据",counter);
        tip("删除成功");
    }else{
        printf("\n\t\t\t");
        tip("输入id未找到");
    }
    //返回删除数据的条数
    arr[2] = counter;
}
//对学院、专业和课程排序,传入带头结点链，第二个参数是按什么排序，第三个参数是降序还是升序。
void sortCourses(instituteList head,int way,int flag){
    instituteList s, q, p, pre;
    int tag;//标记是否当前状态下有序

    tag = 1;
    if( !head->next ) return;
    //检测是不是已经当前状态下有序
    pre = head->next;
    if( pre->next ) p = pre->next;
    else tag = 0;
    if( !way ){
        while( p&&pre->instituteId<p->instituteId ){
            pre = p;
            p = p->next;
        }
    }else{
        while( p&&strcmp( pre->instituteName, p->instituteName )==-1 ){
            pre = p;
            p = p->next;
        }
    }
    if( !p ) tag = 0;
    //分解成两条链
    if( tag ){
        s = head->next;
        head->next = NULL;
    }
    while( s&&tag ){

        //指向头结点
        pre = head;
        p = head->next;
        //摘下一个节点
        q = s;
        s = s->next;
        q->next = NULL;
        //如果是第一次则直接放在head链后
        if( !p ){
            head->next = q;
            p = q;
        }else{
            if( !way ){
                //按学号从小到大
                while( p&&p->instituteId<q->instituteId ){
                    pre = p;
                    p = p->next;
                }
            }else{
                //按名称从小到大
                while( p&&strcmp(p->instituteName,q->instituteName)==-1 ){
                    pre = p;
                    p = p->next;
                }
            }
            q->next = p;
            pre->next = q;
        }
    }
    if( flag ){
        instituteList p=head->next,s=head;
        head->next = NULL;
        while( p ){
            s = p;
            p = p->next;
            s->next = head->next;
            head->next = s;
        }
    }
}


//对学院、专业和课程进行查看、删除和更新
void updateCourse(int type){
    FILE *fp;
    int dateTotal;
    if( type==1 ){
        fp = fopen("Data\\courses\\institutes.txt", "r");
    }else if( type==2 ){
        fp = fopen("Data\\courses\\majors.txt", "r");
    }else{
        fp = fopen("Data\\courses\\courses.txt", "r");
    }
    if( fp==NULL ) tip("打开数据失败");
    else{
        instituteList head;
        head = (instituteList)malloc(sizeof(instituteNode));
        head->next = NULL;
        dateTotal = fileToList(fp, head, type);
        sortCourses(head, 0, 0);
        courseShowByPage(head, dateTotal, type);
        listToFile(head, type);//修改后的数据存盘
        freeCourse(head);
    }
}
//选择对学院、专业和课程进行操作
void coursesDetail(){
    char *menuArr[]={
                    "选择操作",
                    "学院",
                    "专业",
                    "课程",
                    "当前位置：首页->教务处->课程管理"
                };
    int loop=1;
    while( loop ){
        int c;
        switch( c = showMenu(menuArr, 5) ){
            case 1:
            case 2:
            case 3: updateCourse(c);break;
            case -1: isLogout = 1; break;
            default: loop=0;
        }
        //如果全局为注销则退出当前菜单直到首页
        if( isLogout ) loop=0;
    }
}
//将学院课程专业链存入到数据库
int listToFile(instituteList head, int type){
    int counter=0;
    FILE* fw;
    instituteList s;
    s = head->next;
    if( type==1 ){
        fw = fopen("Data\\courses\\institutes.txt", "w");
    }else if( type==2 ){
        fw = fopen("Data\\courses\\majors.txt", "w");
    }else{
        fw = fopen("Data\\courses\\courses.txt", "w");
    }

    if( fw==NULL ){
        tip("文件打开失败");
    }else{
        while( s ){
            if( type!=3 ){
                fprintf(fw, "%d  %s\n", s->instituteId, s->instituteName);
            }else{
                //如果是导入课程则添加课程简介
                fprintf(fw, "%d  %s  %s\n", s->instituteId, s->instituteName, s->synopsis);
            }
            s = s->next;
            counter++;
        }
    }
    fprintf(fw, "-1");
    fclose(fw);
    return counter;
}
//导入课程相关
void importCourse(int type){
    char path[40];
    FILE *fp,*fw;
    //检测教务处输入的路径是否合法
    do{

        //清楚上次菜单输入时缓冲区里面的回车
        clearInputBufer();
        showTitle("请输入需要导入文件的完整路径（默认为软件根目录data.txt）：\n\t\t\t如：C:\\Users\\稻壳er\\Desktop\\data.txt\t\t0  退出\n",25);
        printf("\t\t\t路径：[                                              ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
        gets(path);
        //用户输入0是退出导入操作
        if( path[0]=='0' ) return;
        if( !path[0] ) {
            //用户没有输入路径时
            fp = fopen("data.txt", "r");
            if( fp==NULL ) tip("请检查软件根目录data.txt是否存在！");
        }else{
            //用户输入了路径时
            fp = fopen(path, "r");
            if( fp==NULL ) {
                printf("请检查路径：");
                tip(path);
            }
        }
	}while(  fp==NULL );
	if( type!=5 ){
        //进行除导入培养方案的其它，因为学院、专业和课程结构相同
	    //TODO:检测管理员路径的文件内容是不是对应类型的文件
        instituteList head;
        head = (instituteList)malloc(sizeof(instituteNode));
        head->next = NULL;
        head->instituteId = -1;
        fileToList(fp, head, type);
        listToFile(head, type);//将学院课程专业链存入到数据库
        tip("导入成功");
        freeCourse(head);
	}else{
	    //导入培养方案并按专业分类保存
	    //TODO:检测管理员路径的文件内容是不是对应类型的文件
	    int majorId;//专业id
	    char *planPath;//保存由majorId生成的保存路径
	    int n,e;//课程aov网络的节点数和边数
	    int courseId1,courseId2;
	    while (!feof(fp)) {
            fscanf(fp, "%d", &majorId);
            if( majorId!=-1 ){
                char s1[20] = "Data\\courses\\plans\\";//文件前面的路径
                planPath = outMajorPlans(s1, majorId);
                fw = fopen(planPath, "w");
                printf("\t\t\t");
                tip(planPath);
                printf("\n");
                if( fw==NULL ){
                    tip("新建培养计划文件失败");
                }else{
                    fscanf(fp, "%d %d", &n, &e);
                    fprintf(fw, "%d %d %d\n", majorId, n, e);
                    while(n--){
                        fscanf(fp, "%d", &courseId1);
                        fprintf(fw, "%d\n", courseId1);
                    }
                    while(e--){
                        fscanf(fp, "%d%d", &courseId1, &courseId2);
                        fprintf(fw, "%d %d\n", courseId1, courseId2);
                    }
                    fprintf(fw, "-1");
                    fclose(fw);
                    printf("\t\t\t");
                    tip("导入成功");
                    printf("\n");
                }
            }else{
                break;
            }
	    }
	}
	fclose(fp);
}
//课程管理
void coursesManager(){
    char *menuArr[]={
                    "课程管理",
                    "导入学院",
                    "导入专业",
                    "导入课程",
                    "排课",//系统状态是选课状态是才能排课，排时间排容量排老师
                    "导入培养方案",//分学院分专业导入培养方案
                    "学院、专业及课程详情",
                    "培养方案详情",
                    "当前位置：首页->教务处"
                };
    int loop=1;
    while( loop ){
        int c;
        switch( c = showMenu(menuArr, 9) ){
            case 1: case 2: case 3: case 5: importCourse(c);break;
            case 4: findPlan(1);break;
            case 6: coursesDetail();break;
            case 7: findPlan(0);break;
            case -1: isLogout = 1; break;
            default: loop=0;
        }
        //如果全局为注销则退出当前菜单直到首页
        if( isLogout ) loop=0;
    }
}
void userManager(){
    char *menuArr[]={
                    "用户管理",
                    "查看所有用户",
                    "查找用户",
                    "导入用户",
                    "添加用户",
                    "修改用户信息",
                    "删除用户",
                    "批量删除",
                    "当前位置：首页->教务处"
                };
    int loop=1;
    while( loop ){
        switch( showMenu(menuArr, 9) ){
            case -1: isLogout = 1; break;
            case 1:  showAlluser();break;
            case 2: searchManage(3);break;
            case 3: importUser();break;
            case 4: addUserFunc();break;
            case 5: replaceInfoFunc(); break;
            case 6: deleteUserFunc(); break;
            case 7: deleteMultiAmountUserManage();break;
            default: loop=0;
        }
        //如果全局为注销则退出当前菜单直到首页
        if( isLogout ) loop=0;
    }
}

void importUser(){
    char fileName[50];
    system("cls");
    clearInputBufer();
    printf("请输入要导入的用户信息文件:(完整路径)\n");
    gets(fileName);
    addUserByFile(globalHead,fileName);
    printf("输入任意键返回\n");
    system("pause");

}
void addUserFunc(){
    system("cls");
    clearInputBufer();
    addUser(globalHead);
}

void setPageLength(int* defaultLength){//设置用户显示页面长度
    int i;
    system("cls");
    printf("请输入页面显示信息长度:");
    while(scanf("%d",&i)!=EOF){
        clearInputBufer();
        if(i<=0)
            printf("请输入大于0的整数\n");
        else{
            *defaultLength = i;
            printf("设置的长度为:%d\n",i);
            tip("设置已更改");
            break;
        }
    }

}

void showAlluser(){//显示全部用户
    char *menuArr[]={
                    "显示设置",
                    "页表长度设置",
                    "未修改则按默认设置显示",
                    "返回",
                };
    int loop=1;
    int s = 1;
    int defaultLength = 5;
    while( loop ){
            switch( showMenu(menuArr, 4) ){
            case -1: isLogout = 1; break;
            case 1:
                 setPageLength(&defaultLength);
                break;
            case 2:
                infoListControl(globalHead,s,defaultLength);
                break;
            default: loop=0;
            }
        if( isLogout ) loop=0;
    }

}



//批量添加用户
void addUserByFile(userLink start,char* filename){
    userLink head,usInfo,p,q,newUserInfo,newUser;
    userLink uhead,pre;
    newUser = q  = NULL;
    int i;
    head = (userLink)malloc(sizeof(userList));
    head->info =  NULL;
    head->next = NULL;
    pre = start;
    readUserData(filename,head);
    usInfo = head->next;
    while(usInfo){
        p = usInfo->next;
        if(!(q = searchById(start, pre, usInfo->info->id))){//若id号不存在,直接添加,否则覆盖信息
            i = getCorrectInsertIndex(usInfo->info->name);
            uhead = (userLink)malloc(sizeof(userList));
            uhead->info =  NULL;
            uhead->next = NULL;
            newUserInfo = (userLink)malloc(sizeof(userList));
            newUserInfo->info = (userNode*)malloc(sizeof(userNode));
            newUserInfo->info->firstChild = (coursePoint)malloc(sizeof(courseList));;
            newUserInfo->info->firstChild->next = NULL;
            uhead->next = NULL;
            //usInfo->info->firstChild = NULL;
            usInfo->next = NULL;
            usInfo->flag = 0;
            copyLinkNode(newUserInfo,usInfo);//复制节点信息
            //创建用户信息链
            readUserData(fileArr[i], uhead);
            //插入信息
            insertToUserListByName(uhead, newUserInfo);
            writeInfoToFile(fileArr[i], uhead->next);
            //将信息插入到读出的按学号排序的用户信息链中
            insertToUserLinkById(start, usInfo);
            //写入信息
            freeUser(uhead);
        }
        else{//覆盖信息
            newUser = (userLink)malloc(sizeof(userList));
            newUser->info = (userNode*)malloc(sizeof(userNode));
            newUser->info->firstChild = (coursePoint)malloc(sizeof(courseList));
            newUserInfo->info->firstChild->next = NULL;
            usInfo->next = q->next;
            pre->next = usInfo;
            copyLinkNode(newUser,usInfo);
            replaceInfo(q,newUser);
        }
        usInfo = p;
    }

}

//添加单个用户
void addUser(userLink start) {//传入学号信息排好序的链,用于验证学号是否重复
	int i;
	int iid;
    userLink pre = NULL;
    userLink newUserInfo;
    printf("请按如下提示添加用户\n");
	printf("学号:");
	while (scanf("%d", &iid) != EOF) {
		clearInputBufer();
		if (!searchById(start, pre, iid)) {//判断学号是否重复
            newUserInfo = (userLink)malloc(sizeof(userList));
            newUserInfo->info = (userNode*)malloc(sizeof(userNode));
            newUserInfo->info->firstChild = (coursePoint)malloc(sizeof(courseList));
            newUserInfo->info->firstChild->next = NULL;
            userLink head = (userLink)malloc(sizeof(userList));
            head->info = NULL;
            head->next = NULL;
            userLink usInfo = (userLink)malloc(sizeof(userList));
            userNode* info = (userNode*)malloc(sizeof(userNode));
            info->firstChild = (coursePoint)malloc(sizeof(courseList));
            info->firstChild->next = NULL;
            usInfo->info = info;
            usInfo->info->id = iid;
			printf("角色号:");
			scanf("%d", &usInfo->info->roleId);
			clearInputBufer();
			printf("姓名:");
			gets(usInfo->info->name);
			printf("密码:");
			gets(usInfo->info->passwd);
			printf("学院:");
			gets(usInfo->info->institute);
			printf("电话号码:");
			gets(usInfo->info->phoneNum);
			printf("简介:");
			gets(usInfo->info->synopsis);

			//找到姓名对应的文件
			i = getCorrectInsertIndex(usInfo->info->name);
			//usInfo->info->firstChild = NULL;
			usInfo->next = NULL;
			usInfo->flag = 0;
			copyLinkNode(newUserInfo,usInfo);
			//创建用户信息链
			readUserData(fileArr[i], head);
			//print(head);
			//printf("i = %d\n",i);
			//插入信息
			//print(head);
			insertToUserListByName(head, newUserInfo);
			//写入信息
			writeInfoToFile(fileArr[i], head->next);

			//将信息插入到读出的按学号排序的用户信息链中
			insertToUserLinkById(start, usInfo);

			freeUser(head);
            printf("添加成功\n");
            printf("按任意键返回:");
            getch();
			tip("正在返回");
			break;
		}
		else {
			printf("该学号已存在,请重新输入\n");
		}
	}

}


//删除用户
void deleteUser(userLink start) {
	//在用户链中查找是否有对应的学号或名字
	//若有则删除用户
	//若输入的是名字,则找到其对应的学号，再进行删除
	int d;
	userLink user;
	userLink pre = start;
	printf("请输入要删除的学生学号:\n");
	scanf("%d", &d);
	user = searchById(start, pre, d);
	clearInputBufer();
	if (!user)
		printf("用户不存在\n");
	else {
		//显示用户信息
		printf("学号: %d\t", user->info->id);
		printf("角色号: %d\t", user->info->roleId);
		printf("姓名: %s\t", user->info->name);
		printf("密码: %s\t", user->info->passwd);
		printf("学院: %s\t", user->info->institute);
		printf("电话号码: %s\n", user->info->phoneNum);
		printf("简介: %s \n", user->info->synopsis);
		printf("是否要删除该记录?(Y,N)\n");
		char c;
		userLink head = (userLink)malloc(sizeof(userList));
		head->info = NULL;
		head->next = NULL;
		while ((c = getchar()) != EOF) {
            clearInputBufer();
			if (c == 'Y' || c == 'y') {
				//删除记录
				int i;
				userLink p,pp;

                pre->next = user->next;

				//找到user对应的文件
				i = getCorrectInsertIndex(user->info->name);
				readUserData(fileArr[i],head);
				pp = head;
				p = head->next;
				while(p&&strcmp(p->info->name,user->info->name)!=0){
                    pp = p;
                    p = p->next;
				}
				if(p)
                    pp->next = p->next;
                free(p);
                writeInfoToFile(fileArr[i],head->next);
                freeUser(head);
				free(user);
				printf("删除成功\n");
				break;
			}
			else if (c == 'N' || c == 'n') {
				printf("已取消删除\n");
				break;
			}
			else {
				printf("输入错误,请重新输入\n");
				printf("是否要删除该记录?(Y,N)\n");
			}
		}
		clearInputBufer();
	}
}

//修改用户信息
void copyLinkNode(userLink newInfo, userLink preInfo) {//将之前节点拷贝到新节点上
	newInfo->flag = preInfo->flag;
	newInfo->flag1 = preInfo->flag1;
	newInfo->info->id = preInfo->info->id;
	newInfo->info->roleId = preInfo->info->roleId;
	newInfo->info->counter = preInfo->info->counter;
	strcpy(newInfo->info->institute, preInfo->info->institute);
	strcpy(newInfo->info->name, preInfo->info->name);
	strcpy(newInfo->info->passwd, preInfo->info->passwd);
	strcpy(newInfo->info->phoneNum, preInfo->info->phoneNum);
	strcpy(newInfo->info->synopsis, preInfo->info->synopsis);
	newInfo->next = NULL;
	if(preInfo->info->firstChild->next){
        coursePoint p,q,r;
        q = preInfo->info->firstChild->next;
        r = newInfo->info->firstChild;
        while(q){
            p = (coursePoint)malloc(sizeof(courseList));
           // p->counter = q->counter;
            p->courseId = q->courseId;
            strcpy(p->time,q->time);
            r->next = p;
            r = p;
            q = q->next;
        }
        r->next = NULL;
	}


}
void addUsrCourse(userNode* us){
    int num;
    while(1){
        printf("请输入课程数目:");
        scanf("%d",&num);
        clearInputBufer();
        if(num>=0){
            int i = 0;
            int id;
            coursePoint p,q;
            us->counter = num;
            p = us->firstChild;
            while(i<num){
                q = (coursePoint)malloc(sizeof(courseList));
                printf("课程%d的id号:",i+1);
                scanf("%d",&id);
                clearInputBufer();
                q->courseId = id;
                printf("课程%d的开课时间:",i+1);
                gets(q->time);
                p->next = q;
                p = q;
                i++;
            }
            p->next = NULL;
            break;

        }
        else{
            printf("课程数目应该为大于等于0的整数,请重新输入\n");
        }
    }
}

void replaceUserInfo(userLink start) {
	//先查找用户
	//按姓名,关键字,或者学号
	//通过关键字找到对应的id号,再对其对应的信息进行修改
	int id;
	userLink user;
	userLink pre;
	pre = start;
	printf("请输入所要进行修改的信息对应的id号:\n");
	scanf("%d", &id);
	//查找id是否存在,并将信息显示
	user = searchById(start, pre, id);
	clearInputBufer();
	if (user) {
		userLink preLink = (userLink)malloc(sizeof(userList));
		preLink->info = (userNode*)malloc(sizeof(userNode));
		preLink->info->firstChild = (coursePoint)malloc(sizeof(courseList));
		preLink->info->firstChild ->next = NULL;
		copyLinkNode(preLink, user);
		preLink->next = NULL;
		userLink newInfoNode = (userLink)malloc(sizeof(userList));
		newInfoNode->info = (userNode*)malloc(sizeof(userNode));
		newInfoNode->info->firstChild = (coursePoint)malloc(sizeof(courseList));
		newInfoNode->info->firstChild->next = NULL;
		//对信息进行替换
		//printf("请输入要进行修改的信息的序号:\n");
		//printf("学号(0),角色号(1),姓名(2),密码(3),学院(4),电话号码(5),简介(6),-1表示退出\n");
		char *menuArr[]={
                    "信息修改",
                    "学号修改",
                    "角色号修改",
                    "姓名修改",
                    "密码修改",
                    "学院修改",
                    "电话号码修改",
                    "简介修改",
                    "课程修改",
                    "用户管理"
                };
                int loop=1;
    while( loop ){
        tip("修改信息\n");
        switch( showMenu(menuArr, 10) ){
            clearInputBufer();
            case 1: {
                int iid;
                printNode(user);
                printf("        学号:");//判断学号是否存在
					scanf("%d", &iid);
					if (!searchById(start, NULL, iid)) {
						//取下当前节点插入到用户链中
						pre->next = user->next;
						user->info->id = iid;
						user->next = NULL;
						insertToUserLinkById(start,user);
						//print(    start);
						tip("       修改成功\n");
					}
					else
						tip("       学号已存在,无法修改\n");
					break;
                }
            case 2: {
                int roleId;
                    printNode(user);
					printf("        请输入要修改的信息:\n");
					printf("        角色号:");//判断学号是否存在
					while (scanf("%d", &roleId) != EOF) {
						clearInputBufer();
						printf("0 学生 1 教职工 2管理员\n");
						if (roleId >= 0 && roleId <= 3) {
							user->info->roleId = roleId;
							tip("       修改成功\n");
							break;
						}
						else {
							printf("        角色号要在0~3之间\n");
							printf("        0 学生 1 老师 2教务处 3管理员\n");
							printf("        角色号:");
						}
					}
					break;
                }
            case 3:{
                    char name[20];
                    printNode(user);
					printf("        请输入要修改的信息:\n");
					printf("        姓名:");//判断学号是否存在
					gets(name);
					strcpy(user->info->name, name);
					tip("       修改成功\n");
					break;

            }
            case 4:  {
					char passwd[20];
                    printNode(user);
					printf("        请输入要修改的信息:\n");
					printf("        密码:");//判断学号是否存在
					gets(passwd);
					strcpy(user->info->passwd, passwd);
					tip("       修改成功\n");
					break;
                }
            case 5: {
					char institute[30];
					 printNode(user);
					printf("        请输入要修改的信息:\n");
					printf("        学院:");//判断学号是否存在
					gets(institute);
					strcpy(user->info->institute, institute);
					tip("       修改成功");
					break;
                }
            case 6:{
					char phoneNum[20];
					 printNode(user);
					printf("        请输入要修改的信息:\n");
					printf("        电话号码:");//判断学号是否存在
					gets(phoneNum);
					strcpy(user->info->phoneNum, phoneNum);
                    tip("       修改成功\n");
					break;
                }
            case 7:{
                char synopsis[100];
                   printNode(user);
					printf("        请输入要修改的信息:\n");
					printf("        简介:");//判断学号是否存在
					gets(synopsis);
					strcpy(user->info->synopsis, synopsis);
                    tip("       修改成功\n");
					break;
            }
            case 8:{
                printNode(user);
                addUsrCourse(user->info);
                 tip("       修改成功\n");
                break;
            }

            case -1: isLogout = 1; break;
            default: loop=0;
        }
        //如果全局为注销则退出当前菜单直到首页
        if( isLogout ) loop=0;
    }

		//将修改后的信息写入到文件中
		//如果修改了name,则将原先name对应的id删除,然后写入新文件
		//否则直接将信息写入
		//print(globalHead);
        copyLinkNode(newInfoNode,user);
        //newInfoNode->next = NULL;
        //print(globalHead);
        //system("pause");
       // printNode(newInfoNode);
		replaceInfo(preLink,newInfoNode);
	}
	else
		printf("该id号不存在\n");

}

void replaceInfo(userLink preInfo, userLink newInfo) {
	int i;
	userLink head = (userLink)malloc(sizeof(userList));
	head->info = NULL;
	head->next = NULL;
	//print(globalHead);
	if (strcmp(preInfo->info->name, newInfo->info->name) == 0) {//名字未修改
		i = getCorrectInsertIndex(preInfo->info->name);
		//newInfo->info->firstChild = NULL;
		newInfo->next = NULL;
		newInfo->flag = 0;
		//创建用户信息链
		readUserData(fileArr[i], head);
		userLink q = head->next;
		userLink pre = head;
		while (q&&preInfo->info->id != q->info->id) {//id修改了,找到文件中存的之前的id
				pre = q;
				q = q->next;
		}
        newInfo->next = q->next;
		pre->next = newInfo;
		free(q);
		//写入信息
		//printf("sdfdd");
		//print(head);
		system("pause");
		writeInfoToFile(fileArr[i], head->next);
		freeUser(head);

	}
	else {
		//找到之前信息进行删除
		i = getCorrectInsertIndex(preInfo->info->name);
		//创建用户信息链
		readUserData(fileArr[i], head);
		userLink q = head->next;
		userLink pre = head;
		while (q&&preInfo->info->id != q->info->id) {
			pre = q;
			q = q->next;
		}
        pre->next = q->next;
		free(q);
		//写入信息
		writeInfoToFile(fileArr[i], head->next);
		freeUser(head);
		head->next = NULL;
		//找到对应文件写入信息
		i = getCorrectInsertIndex(newInfo->info->name);
		//创建用户信息链
		//newInfo->info->firstChild = NULL;
		newInfo->next = NULL;
		newInfo->flag = 0;
		//创建用户信息链
		readUserData(fileArr[i], head);
		//插入信息
		insertToUserListByName(head, newInfo);
		//print(head);
		//写入信息
		writeInfoToFile(fileArr[i], head->next);
		freeUser(head);
	}

}
