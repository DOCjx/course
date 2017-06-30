//管理员操作


void admin(){
    char *menuArr[]={
                    "超管",
                    "学生之家",//增删改查
                    "教师之家",//增删改查，TODO:发消息
                    "教务处",
                    "当前位置：首页"
                };
    int loop=1;
    while( loop ){
        switch( showMenu(menuArr, 5) ){
            case 1: stuCoursesSelect();break;
            case 2: teaCoursesSelect();break;
            case 3: affairsCoursesSelect();break;
            case -1: isLogout = 1; break;
            default: loop=0;
        }
        //如果全局为注销则退出当前菜单直到首页
        if( isLogout ) loop=0;
    }
}

