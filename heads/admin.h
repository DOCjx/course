//����Ա����


void admin(){
    char *menuArr[]={
                    "����",
                    "ѧ��֮��",//��ɾ�Ĳ�
                    "��ʦ֮��",//��ɾ�Ĳ飬TODO:����Ϣ
                    "����",
                    "��ǰλ�ã���ҳ"
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
        //���ȫ��Ϊע�����˳���ǰ�˵�ֱ����ҳ
        if( isLogout ) loop=0;
    }
}

