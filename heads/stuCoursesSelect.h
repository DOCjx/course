
void seachMyPlan(){
    int temp;
    char* name;
    if( role==3 ){
        printf("\t\t\t");
        tip("管理员没有培养方案的哟");
        printf("\n");
        return;
    }
    system("cls");
    temp = (userNum  - (userNum / 100000000)*100000000) / 1000;
    char s1[20] = "Data\\courses\\plans\\";
    name = outMajorPlans(s1, temp);
    showPlan(name);//输出培养方案
}
void seachTea(){
    searchManage(2);
}
void seachStu(){
    searchManage(1);
}

//学生进行选课
void stuCoursesSelect(){
    char *menuArr[]={
                    "学生之家",
                    "我的培养方案",
                    "进行选课",
                    "查询老师信息",
                    "查询同学信息",
                    "课表查询",
                    "当前位置：首页"
                };
    int loop=1;
    while( loop ){
        switch( showMenu(menuArr, 7) ){
            case 1: seachMyPlan();break;
            case 2: findPlan(1);break;
            case 3: seachTea();break;
            case 4: seachStu();break;
            case -1: isLogout = 1; break;
            default: loop=0;
        }
        //如果全局为注销则退出当前菜单直到首页
        if( isLogout ) loop=0;
    }
}
