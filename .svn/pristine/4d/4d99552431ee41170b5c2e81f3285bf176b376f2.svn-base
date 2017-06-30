//任课老师操作
void selectCourse();//老师进行安排课

//老师进行安排课
void selectCourse(){
    classList head, s;
    head = (classList)malloc(sizeof(classNode));
    head->next = NULL;
    readCourseFromFile(head, userNum);
    s = head->next;
    while(s){
        printf("%d",s->classId);
        s = s->next;
    }
    freeCourseManager(head);
    system("pause");
}
void teaCoursesSelect(){
    char *menuArr[]={
                    "教师之家",
                    "培养方案查询",
                    "安排课程",
                    "查询学生信息",
                    "查询同事信息",
                    "课表查询",
                    "当前位置：首页"
                };
    int loop=1;
    while( loop ){
        switch( showMenu(menuArr, 6) ){
            case 1: findPlan(0);break;
            case 2: selectCourse();break;
            case 3: seachStu();break;
            case 4: seachTea();break;
            case -1: isLogout = 1; break;
            default: loop=0;
        }
        //如果全局为注销则退出当前菜单直到首页
        if( isLogout ) loop=0;
    }
}
