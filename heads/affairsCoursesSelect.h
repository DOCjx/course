//���񴦲���

/*
	����Ա��Ϣ����
*/
//firstChild print
//����,���û�������,ɾ��,�޸�
//�Կγ̵İ���(��ɾ�Ĳ�),�����¼��İ���
void addUser(userLink start);//����û�
void deleteUser(userLink start);//ɾ���û�
void replaceUserInfo(userLink start);//�޸��û���Ϣ
void replaceInfo(userLink preInfo, userLink newInfo);//��ԭ���û���Ϣ�����û���Ϣ���
void copyLinkNode(userLink newInfo, userLink preInfo);//��֮ǰ�ڵ㿽�����½ڵ���
void userManager();//��ɾ�Ĳ��û���TODO:����Ϣ
void coursesManager();//�γ̹���
void sysManager();//ϵͳ����
void importCourse(int type);//����γ̡�רҵ��ѧԺ��Ϣ
void printCourse(instituteList head);//����ͷ��㵥�������Դ�ӡ�γ���Ϣ
void coursesDetail();//����ѧԺרҵ�Ϳγ̵�����ҳ������Ӧ����
void updateCourse(int type);//��ѧԺ��רҵ�Ϳγ̽��в鿴��ɾ���͸���
int listToFile(instituteList head, int type);//��ѧԺ�γ�רҵ�����뵽���ݿ�
void setPageLength(int* defaultLength);//�����û���ʾҳ�泤��
void showAlluser();//��ʾȫ���û�
void importUser();//�����û�����
void addUserByFile(userLink start,char* filename);//ͨ���ļ�����������û�
void addUserFunc();//����û����ú���

void searchByIdFunc();//��id��ѯ����
void searchUserFunc();
void searchUserByNameFunc(int ii);//�����־�ȷ��ѯ����
void searchUserByNameFunc2(int ii);//������ģ����ѯ����
void deleteUserFunc();//ɾ���û����ú���
void replaceInfoFunc();//�޸��û���Ϣ���ú���
void deleteOneUserById(int d);//ͨ��idɾ��һ���û�
void deleteMultiAmountUser(int startId,int endId);
void deleteMultiAmountUserByLength(int startId,int length);
void deleteMultiAmountUserManage();
void deleteMultiAmountUserFunc(int flag);

void addUsrCourse(userNode* us);//����û��γ���Ϣ

void printNode(userLink up){//��ʾһ���ڵ���Ϣ
        if (up->info) {
			printf("ѧ��: %d", up->info->id);
			printf("\t��ɫ��: %d", up->info->roleId);
			printf("\t����: %s", up->info->name);
			printf("\t����: %s", up->info->passwd);
			printf("\tѧԺ: %s\n", up->info->institute);
			printf("�绰����: %s ", up->info->phoneNum);
			printf("���: %s  ", up->info->synopsis);
			coursePoint p;
			p = up->info->firstChild->next;
			if (p) {
				printf("��ǰ�γ���: \n");
				printf("�γ̺�:");
				while(p){
                    printf(" %d ",p->courseId);
                    p = p->next;
				}
			}
			else {
				printf("��ǰ�޿γ�\n");
			}
		}
}

void deleteMultiAmountUserFunc(int flag){
    system("cls");
    clearInputBufer();
    int startId;
    char a;
    quickSortById(globalHead);
    if(flag == 1){//����ʼid�ͽ���id��ʾ�û�
            int endId;
            while(1){
                printf("��������ʼid:");
                scanf("%d",&startId);
                printf("���������id:");
                scanf("%d",&endId);
                deleteMultiAmountUser(startId,endId);
                clearInputBufer();
                printf("����(Y|y)�����޸�,�������������\n");
                a = getchar();
                if(a != 'Y' && a!='y'){
                    tip("���ڷ���");
                    break;
                }
            }

    }
    else if(flag == 2){//����ʼid�ͳ�����ʾ�û�
        while(1){
                int length;
                printf("��������ʼid:");
                scanf("%d",&startId);
                printf("�����볤��:");
                scanf("%d",&length);
                deleteMultiAmountUserByLength(startId,length);
                clearInputBufer();
                 //print(globalHead);
                printf("����(Y|y)�����޸�,�������������\n");
                a = getchar();
                if(a != 'Y' && a!='y'){
                    tip("���ڷ���");
                    break;
                }
            }
    }
    else{
        printf("���flag�������\n");
    }
}

void deleteMultiAmountUserManage(){
    char *menuArr[]={
                    "ɾ�������û�",
                    "ͨ����ʼid�ͽ���idɾ��",
                    "ͨ����ʼid�ͳ���ɾ��",
                    "����"
                };
    int loop=1;
    while( loop ){
        switch( showMenu(menuArr, 4) ){
            case 1: deleteMultiAmountUserFunc(1); break;
            case 2: deleteMultiAmountUserFunc(2); break;
            case -1: isLogout = 1; break;
            default: loop=0;
        }
        //���ȫ��Ϊע�����˳���ǰ�˵�ֱ����ҳ
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
        printf("id�������,����id���Ƿ����0\n");

}

void deleteMultiAmountUser(int startId,int endId){
    int i;
    if(startId<endId&&startId>0){
        for(i = startId;i<=endId;i++)
            deleteOneUserById(i);
    }
    else
        printf("id�������,����id���Ƿ����0�����id�Ƿ������ʼid\n");

}


void deleteOneUserById(int d){
	userLink user;
	userLink pre = globalHead;
	user = searchById(globalHead, pre, d);
	if (!user)
		printf("idΪ%d���û�������\n",d);
	else {
        int i;
        userLink head;
        userLink p,pp;
        head = (userLink)malloc(sizeof(userList));
        head->info = NULL;
        head->next = NULL;
        pre->next = user->next;
        //�ҵ�user��Ӧ���ļ�
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
        printf("ɾ���ɹ�\n");
	}
}

void replaceInfoFunc(){
    system("cls");
    quickSortById(globalHead);
    char a;
    while(1){
        replaceUserInfo(globalHead);
        printf("����(Y|y)�����޸�,�������������\n");
        a = getchar();
        //printf("%c",a);
        if(a != 'Y'&&a != 'y'){
            tip("���ڷ���");
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
        printf("����(Y|y)����ɾ��,�������������\n");
        a = getchar();
        //printf("%c",a);
        if(a != 'Y'&&a != 'y'){
            tip("���ڷ���");
            break;
        }
        clearInputBufer();
    }

}

void searchByIdFunc(){//idҪ�Ѿ�����,�������������а�id����
    system("cls");
    userLink pre = NULL;
    userLink p;
    int id;
    clearInputBufer();
    quickSortById(globalHead);
    printf("������Ҫ���ҵ�id��:");
    while(scanf("%d",&id)!=EOF){
        char a;
        if((p = searchById(globalHead,pre,id))){
            printNode(p);
        }
        else
            printf("id:%d������",id);
        printf("�Ƿ�Ҫ������ѯ(Y)�����������\n");
        clearInputBufer();
        a = getchar();
        if( a == 'Y'||a == 'y')
            printf("������Ҫ���ҵ�id��:");
        else{
            tip("���ڷ���");
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
    printf("������Ҫ���ҵ�����:");
    clearInputBufer();
    while(1){
        int counter = 0;
        char a;
        gets(name);
        i = getCorrectInsertIndex(name);//�ҵ����ֶ�Ӧ���ļ�
        readUserData(fileArr[i],head);
        //printf("name = %s,i = %d",name,i);
        p = head->next;
        //print(head);
        while(p&&strcmp(p->info->name,name)>=0){
            if(strcmp(p->info->name,name)==0){
                if(ii==3){
                    printf("����%s ", p->info->name);
                    printf("ѧ��%d ", p->info->id);
                    printf("��ɫ��%d ", p->info->roleId);
                    //printf("����%s ", user->info->passwd);
                    printf("ѧԺ%s ", p->info->institute);
                    printf("�绰����%s ", p->info->phoneNum);
                    printf("���%s \n", p->info->synopsis);
                    counter++;
                }
                else{
                    if(p->info->roleId == (ii-1)){
                        printf("����%s ", p->info->name);
                        printf("ѧ��%d ", p->info->id);
                        printf("��ɫ��%d ", p->info->roleId);
                        //printf("����%s ", user->info->passwd);
                        printf("ѧԺ%s ", p->info->institute);
                        printf("�绰����%s ", p->info->phoneNum);
                        printf("���%s \n", p->info->synopsis);
                        counter++;
                    }
                }
            }
            p = p->next;
        }
        if(counter == 0)
            printf("δ�ҵ�%s",name);
        printf("�Ƿ�Ҫ������ѯ:(Y|y),������������˳�\n");
        a = getchar();
        if(a != 'Y'&&a != 'y'){
            tip("���ڷ���");
            break;
        }
        printf("������Ҫ���ҵ�����:");

    }


}

void searchUserByNameFunc2(int ii){
    system("cls");
    char name[20];
    userLink head;
    printf("������Ҫ���ҵĹؼ���:");
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
                    printf("����%s ", p->info->name);
                    printf("ѧ��%d ", p->info->id);
                    printf("��ɫ��%d ", p->info->roleId);
                    //printf("����%s ", user->info->passwd);
                    printf("ѧԺ%s ", p->info->institute);
                    printf("�绰����%s ", p->info->phoneNum);
                    printf("���%s \n", p->info->synopsis);
                    counter++;
                }
                else{
                    if(p->info->roleId == (ii-1)){
                        printf("����%s ", p->info->name);
                        printf("ѧ��%d ", p->info->id);
                        printf("��ɫ��%d ", p->info->roleId);
                        //printf("����%s ", user->info->passwd);
                        printf("ѧԺ%s ", p->info->institute);
                        printf("�绰����%s ", p->info->phoneNum);
                        printf("���%s \n", p->info->synopsis);
                        counter++;
                    }
                }
                p = p->next;
         }

         if(counter == 0)
            printf("δ�ҵ��ؼ���%s��Ӧ���û�\n",name);
        printf("�Ƿ�Ҫ������ѯ:(Y|y),������������˳�\n");
        a = getchar();
        if(a != 'Y'&&a != 'y'){
            tip("���ڷ���");
            break;
        }
        printf("������Ҫ���ҵĹؼ���:");
    }
}

void searchManage(int i){
    char *menuArr[]={
                    "�����û�",
                    "��id����",
                    "����������",
                    "������ģ����ѯ",
                    "����"
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
        //���ȫ��Ϊע�����˳���ǰ�˵�ֱ����ҳ
        if( isLogout ) loop=0;
    }
}

void affairsCoursesSelect(){
    char *menuArr[]={
                    "����",
                    "�γ̹���",//��ɾ�Ĳ�
                    "�û�����",
                    "ϵͳ����",
                    "��ʦ֮��",
                    "��ǰλ�ã���ҳ"
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
        //���ȫ��Ϊע�����˳���ǰ�˵�ֱ����ҳ
        if( isLogout ) loop=0;
    }
}
void nowsystemStatus(){
    int Status;
    printf("��ǰ��ϵͳ״̬�ǣ�%d\n",systemStatus);
    printf("��������Ҫ�޸ĳɵ�ϵͳ״̬��0��Ϊ����״̬��1��Ϊѡ��״̬������\n");
    scanf("%d",&Status);
    systemStatus=Status;
    if(systemStatus==0){
        tip("��ǰϵͳ״̬�Ѿ��޸�Ϊ����״̬��");
    }else if(systemStatus==1){
        tip("��ǰϵͳ״̬�Ѿ��޸ĳ�ѡ��״̬��");
    }else{
        tip("�����ϵͳ״̬����ȷ��");
    }

}
void changechance(){
    printf("��ǰ�û�����ɳ��Դ���Ϊ��%d\n",loginTimes);
    printf("��������Ҫ�޸ĳɵĴ�����");
    int newloginTimes;
    scanf("%d",&newloginTimes);
    loginTimes=newloginTimes;
    printf("��ǰ�û�����ɳ��Դ����Ѿ����޸ĳɣ�%d\n",loginTimes);
    tip(">>>>");


}
void changekeylength(){
    printf("��ǰ�û����볤��Ϊ��%d\n",passLength);
    printf("��������Ҫ�޸ĳɵĳ��ȣ�");
    int newpassLength;
    scanf("%d",&newpassLength);
    passLength=newpassLength;
    printf("��ǰ�û����볤���Ѿ����޸ĳɣ�%d\n",passLength);
    tip(">>>>");

}
void changeAdmin(){
    printf("��ǰ����Ա�û�����%d ���룺%s\n", Admin, AdminPass);
    printf("�������޸ĵ��û�����");
    int newpassLength;
    scanf("%d",&newpassLength);
    Admin=newpassLength;
    printf("�������޸ĵ����룺");
    scanf("%s", AdminPass);
    printf("��ǰ����Ա�û����������Ѿ����޸ĳɣ�%d ���룺%s\n", Admin, AdminPass);
    tip(">>>>");

}
void changePageMax(){
    printf("��ǰÿҳ��ʾ��������Ϊ��%d\n",pageMax);
    printf("��������Ҫ�޸ĳɵĳ��ȣ�");
    int newpassLength;
    scanf("%d",&newpassLength);
    pageMax=newpassLength;
    printf("ÿҳ��ʾ���������Ѿ����޸ĳɣ�%d\n",pageMax);
    tip(">>>>");

}
void sysManager(){
    char *menuArr[]={
                    "ϵͳ����",
                    "��ǰϵͳ״̬",//��������ѡ��״̬
                    "�û��ɳ��������������",
                    "�û����볤��",
                    "�޸ĳ�������Ա�û���������",
                    "�޸�ÿҳ��ʾ��������",
                    "��ǰλ�ã���ҳ->����->ϵͳ����"
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
        //���ȫ��Ϊע�����˳���ǰ�˵�ֱ����ҳ
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




//ɾ�����ݲ���
void delCourse(instituteList head, int arr[]){
    instituteList pre,p,q,s;
    pre = head;
    p = q = head->next;
    int counter=0;
    if( arr[1]==-1 ) arr[1]=1;
    //����Ҫɾ���ڵ�
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
        printf("\t\t\t%d������",counter);
        tip("ɾ���ɹ�");
    }else{
        printf("\n\t\t\t");
        tip("����idδ�ҵ�");
    }
    //����ɾ�����ݵ�����
    arr[2] = counter;
}
//��ѧԺ��רҵ�Ϳγ�����,�����ͷ��������ڶ��������ǰ�ʲô���򣬵����������ǽ���������
void sortCourses(instituteList head,int way,int flag){
    instituteList s, q, p, pre;
    int tag;//����Ƿ�ǰ״̬������

    tag = 1;
    if( !head->next ) return;
    //����ǲ����Ѿ���ǰ״̬������
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
    //�ֽ��������
    if( tag ){
        s = head->next;
        head->next = NULL;
    }
    while( s&&tag ){

        //ָ��ͷ���
        pre = head;
        p = head->next;
        //ժ��һ���ڵ�
        q = s;
        s = s->next;
        q->next = NULL;
        //����ǵ�һ����ֱ�ӷ���head����
        if( !p ){
            head->next = q;
            p = q;
        }else{
            if( !way ){
                //��ѧ�Ŵ�С����
                while( p&&p->instituteId<q->instituteId ){
                    pre = p;
                    p = p->next;
                }
            }else{
                //�����ƴ�С����
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


//��ѧԺ��רҵ�Ϳγ̽��в鿴��ɾ���͸���
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
    if( fp==NULL ) tip("������ʧ��");
    else{
        instituteList head;
        head = (instituteList)malloc(sizeof(instituteNode));
        head->next = NULL;
        dateTotal = fileToList(fp, head, type);
        sortCourses(head, 0, 0);
        courseShowByPage(head, dateTotal, type);
        listToFile(head, type);//�޸ĺ�����ݴ���
        freeCourse(head);
    }
}
//ѡ���ѧԺ��רҵ�Ϳγ̽��в���
void coursesDetail(){
    char *menuArr[]={
                    "ѡ�����",
                    "ѧԺ",
                    "רҵ",
                    "�γ�",
                    "��ǰλ�ã���ҳ->����->�γ̹���"
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
        //���ȫ��Ϊע�����˳���ǰ�˵�ֱ����ҳ
        if( isLogout ) loop=0;
    }
}
//��ѧԺ�γ�רҵ�����뵽���ݿ�
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
        tip("�ļ���ʧ��");
    }else{
        while( s ){
            if( type!=3 ){
                fprintf(fw, "%d  %s\n", s->instituteId, s->instituteName);
            }else{
                //����ǵ���γ�����ӿγ̼��
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
//����γ����
void importCourse(int type){
    char path[40];
    FILE *fp,*fw;
    //�����������·���Ƿ�Ϸ�
    do{

        //����ϴβ˵�����ʱ����������Ļس�
        clearInputBufer();
        showTitle("��������Ҫ�����ļ�������·����Ĭ��Ϊ�����Ŀ¼data.txt����\n\t\t\t�磺C:\\Users\\����er\\Desktop\\data.txt\t\t0  �˳�\n",25);
        printf("\t\t\t·����[                                              ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
        gets(path);
        //�û�����0���˳��������
        if( path[0]=='0' ) return;
        if( !path[0] ) {
            //�û�û������·��ʱ
            fp = fopen("data.txt", "r");
            if( fp==NULL ) tip("���������Ŀ¼data.txt�Ƿ���ڣ�");
        }else{
            //�û�������·��ʱ
            fp = fopen(path, "r");
            if( fp==NULL ) {
                printf("����·����");
                tip(path);
            }
        }
	}while(  fp==NULL );
	if( type!=5 ){
        //���г�����������������������ΪѧԺ��רҵ�Ϳγ̽ṹ��ͬ
	    //TODO:������Ա·�����ļ������ǲ��Ƕ�Ӧ���͵��ļ�
        instituteList head;
        head = (instituteList)malloc(sizeof(instituteNode));
        head->next = NULL;
        head->instituteId = -1;
        fileToList(fp, head, type);
        listToFile(head, type);//��ѧԺ�γ�רҵ�����뵽���ݿ�
        tip("����ɹ�");
        freeCourse(head);
	}else{
	    //����������������רҵ���ౣ��
	    //TODO:������Ա·�����ļ������ǲ��Ƕ�Ӧ���͵��ļ�
	    int majorId;//רҵid
	    char *planPath;//������majorId���ɵı���·��
	    int n,e;//�γ�aov����Ľڵ����ͱ���
	    int courseId1,courseId2;
	    while (!feof(fp)) {
            fscanf(fp, "%d", &majorId);
            if( majorId!=-1 ){
                char s1[20] = "Data\\courses\\plans\\";//�ļ�ǰ���·��
                planPath = outMajorPlans(s1, majorId);
                fw = fopen(planPath, "w");
                printf("\t\t\t");
                tip(planPath);
                printf("\n");
                if( fw==NULL ){
                    tip("�½������ƻ��ļ�ʧ��");
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
                    tip("����ɹ�");
                    printf("\n");
                }
            }else{
                break;
            }
	    }
	}
	fclose(fp);
}
//�γ̹���
void coursesManager(){
    char *menuArr[]={
                    "�γ̹���",
                    "����ѧԺ",
                    "����רҵ",
                    "����γ�",
                    "�ſ�",//ϵͳ״̬��ѡ��״̬�ǲ����ſΣ���ʱ������������ʦ
                    "������������",//��ѧԺ��רҵ������������
                    "ѧԺ��רҵ���γ�����",
                    "������������",
                    "��ǰλ�ã���ҳ->����"
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
        //���ȫ��Ϊע�����˳���ǰ�˵�ֱ����ҳ
        if( isLogout ) loop=0;
    }
}
void userManager(){
    char *menuArr[]={
                    "�û�����",
                    "�鿴�����û�",
                    "�����û�",
                    "�����û�",
                    "����û�",
                    "�޸��û���Ϣ",
                    "ɾ���û�",
                    "����ɾ��",
                    "��ǰλ�ã���ҳ->����"
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
        //���ȫ��Ϊע�����˳���ǰ�˵�ֱ����ҳ
        if( isLogout ) loop=0;
    }
}

void importUser(){
    char fileName[50];
    system("cls");
    clearInputBufer();
    printf("������Ҫ������û���Ϣ�ļ�:(����·��)\n");
    gets(fileName);
    addUserByFile(globalHead,fileName);
    printf("�������������\n");
    system("pause");

}
void addUserFunc(){
    system("cls");
    clearInputBufer();
    addUser(globalHead);
}

void setPageLength(int* defaultLength){//�����û���ʾҳ�泤��
    int i;
    system("cls");
    printf("������ҳ����ʾ��Ϣ����:");
    while(scanf("%d",&i)!=EOF){
        clearInputBufer();
        if(i<=0)
            printf("���������0������\n");
        else{
            *defaultLength = i;
            printf("���õĳ���Ϊ:%d\n",i);
            tip("�����Ѹ���");
            break;
        }
    }

}

void showAlluser(){//��ʾȫ���û�
    char *menuArr[]={
                    "��ʾ����",
                    "ҳ��������",
                    "δ�޸���Ĭ��������ʾ",
                    "����",
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



//��������û�
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
        if(!(q = searchById(start, pre, usInfo->info->id))){//��id�Ų�����,ֱ�����,���򸲸���Ϣ
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
            copyLinkNode(newUserInfo,usInfo);//���ƽڵ���Ϣ
            //�����û���Ϣ��
            readUserData(fileArr[i], uhead);
            //������Ϣ
            insertToUserListByName(uhead, newUserInfo);
            writeInfoToFile(fileArr[i], uhead->next);
            //����Ϣ���뵽�����İ�ѧ��������û���Ϣ����
            insertToUserLinkById(start, usInfo);
            //д����Ϣ
            freeUser(uhead);
        }
        else{//������Ϣ
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

//��ӵ����û�
void addUser(userLink start) {//����ѧ����Ϣ�ź������,������֤ѧ���Ƿ��ظ�
	int i;
	int iid;
    userLink pre = NULL;
    userLink newUserInfo;
    printf("�밴������ʾ����û�\n");
	printf("ѧ��:");
	while (scanf("%d", &iid) != EOF) {
		clearInputBufer();
		if (!searchById(start, pre, iid)) {//�ж�ѧ���Ƿ��ظ�
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
			printf("��ɫ��:");
			scanf("%d", &usInfo->info->roleId);
			clearInputBufer();
			printf("����:");
			gets(usInfo->info->name);
			printf("����:");
			gets(usInfo->info->passwd);
			printf("ѧԺ:");
			gets(usInfo->info->institute);
			printf("�绰����:");
			gets(usInfo->info->phoneNum);
			printf("���:");
			gets(usInfo->info->synopsis);

			//�ҵ�������Ӧ���ļ�
			i = getCorrectInsertIndex(usInfo->info->name);
			//usInfo->info->firstChild = NULL;
			usInfo->next = NULL;
			usInfo->flag = 0;
			copyLinkNode(newUserInfo,usInfo);
			//�����û���Ϣ��
			readUserData(fileArr[i], head);
			//print(head);
			//printf("i = %d\n",i);
			//������Ϣ
			//print(head);
			insertToUserListByName(head, newUserInfo);
			//д����Ϣ
			writeInfoToFile(fileArr[i], head->next);

			//����Ϣ���뵽�����İ�ѧ��������û���Ϣ����
			insertToUserLinkById(start, usInfo);

			freeUser(head);
            printf("��ӳɹ�\n");
            printf("�����������:");
            getch();
			tip("���ڷ���");
			break;
		}
		else {
			printf("��ѧ���Ѵ���,����������\n");
		}
	}

}


//ɾ���û�
void deleteUser(userLink start) {
	//���û����в����Ƿ��ж�Ӧ��ѧ�Ż�����
	//������ɾ���û�
	//�������������,���ҵ����Ӧ��ѧ�ţ��ٽ���ɾ��
	int d;
	userLink user;
	userLink pre = start;
	printf("������Ҫɾ����ѧ��ѧ��:\n");
	scanf("%d", &d);
	user = searchById(start, pre, d);
	clearInputBufer();
	if (!user)
		printf("�û�������\n");
	else {
		//��ʾ�û���Ϣ
		printf("ѧ��: %d\t", user->info->id);
		printf("��ɫ��: %d\t", user->info->roleId);
		printf("����: %s\t", user->info->name);
		printf("����: %s\t", user->info->passwd);
		printf("ѧԺ: %s\t", user->info->institute);
		printf("�绰����: %s\n", user->info->phoneNum);
		printf("���: %s \n", user->info->synopsis);
		printf("�Ƿ�Ҫɾ���ü�¼?(Y,N)\n");
		char c;
		userLink head = (userLink)malloc(sizeof(userList));
		head->info = NULL;
		head->next = NULL;
		while ((c = getchar()) != EOF) {
            clearInputBufer();
			if (c == 'Y' || c == 'y') {
				//ɾ����¼
				int i;
				userLink p,pp;

                pre->next = user->next;

				//�ҵ�user��Ӧ���ļ�
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
				printf("ɾ���ɹ�\n");
				break;
			}
			else if (c == 'N' || c == 'n') {
				printf("��ȡ��ɾ��\n");
				break;
			}
			else {
				printf("�������,����������\n");
				printf("�Ƿ�Ҫɾ���ü�¼?(Y,N)\n");
			}
		}
		clearInputBufer();
	}
}

//�޸��û���Ϣ
void copyLinkNode(userLink newInfo, userLink preInfo) {//��֮ǰ�ڵ㿽�����½ڵ���
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
        printf("������γ���Ŀ:");
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
                printf("�γ�%d��id��:",i+1);
                scanf("%d",&id);
                clearInputBufer();
                q->courseId = id;
                printf("�γ�%d�Ŀ���ʱ��:",i+1);
                gets(q->time);
                p->next = q;
                p = q;
                i++;
            }
            p->next = NULL;
            break;

        }
        else{
            printf("�γ���ĿӦ��Ϊ���ڵ���0������,����������\n");
        }
    }
}

void replaceUserInfo(userLink start) {
	//�Ȳ����û�
	//������,�ؼ���,����ѧ��
	//ͨ���ؼ����ҵ���Ӧ��id��,�ٶ����Ӧ����Ϣ�����޸�
	int id;
	userLink user;
	userLink pre;
	pre = start;
	printf("��������Ҫ�����޸ĵ���Ϣ��Ӧ��id��:\n");
	scanf("%d", &id);
	//����id�Ƿ����,������Ϣ��ʾ
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
		//����Ϣ�����滻
		//printf("������Ҫ�����޸ĵ���Ϣ�����:\n");
		//printf("ѧ��(0),��ɫ��(1),����(2),����(3),ѧԺ(4),�绰����(5),���(6),-1��ʾ�˳�\n");
		char *menuArr[]={
                    "��Ϣ�޸�",
                    "ѧ���޸�",
                    "��ɫ���޸�",
                    "�����޸�",
                    "�����޸�",
                    "ѧԺ�޸�",
                    "�绰�����޸�",
                    "����޸�",
                    "�γ��޸�",
                    "�û�����"
                };
                int loop=1;
    while( loop ){
        tip("�޸���Ϣ\n");
        switch( showMenu(menuArr, 10) ){
            clearInputBufer();
            case 1: {
                int iid;
                printNode(user);
                printf("        ѧ��:");//�ж�ѧ���Ƿ����
					scanf("%d", &iid);
					if (!searchById(start, NULL, iid)) {
						//ȡ�µ�ǰ�ڵ���뵽�û�����
						pre->next = user->next;
						user->info->id = iid;
						user->next = NULL;
						insertToUserLinkById(start,user);
						//print(    start);
						tip("       �޸ĳɹ�\n");
					}
					else
						tip("       ѧ���Ѵ���,�޷��޸�\n");
					break;
                }
            case 2: {
                int roleId;
                    printNode(user);
					printf("        ������Ҫ�޸ĵ���Ϣ:\n");
					printf("        ��ɫ��:");//�ж�ѧ���Ƿ����
					while (scanf("%d", &roleId) != EOF) {
						clearInputBufer();
						printf("0 ѧ�� 1 ��ְ�� 2����Ա\n");
						if (roleId >= 0 && roleId <= 3) {
							user->info->roleId = roleId;
							tip("       �޸ĳɹ�\n");
							break;
						}
						else {
							printf("        ��ɫ��Ҫ��0~3֮��\n");
							printf("        0 ѧ�� 1 ��ʦ 2���� 3����Ա\n");
							printf("        ��ɫ��:");
						}
					}
					break;
                }
            case 3:{
                    char name[20];
                    printNode(user);
					printf("        ������Ҫ�޸ĵ���Ϣ:\n");
					printf("        ����:");//�ж�ѧ���Ƿ����
					gets(name);
					strcpy(user->info->name, name);
					tip("       �޸ĳɹ�\n");
					break;

            }
            case 4:  {
					char passwd[20];
                    printNode(user);
					printf("        ������Ҫ�޸ĵ���Ϣ:\n");
					printf("        ����:");//�ж�ѧ���Ƿ����
					gets(passwd);
					strcpy(user->info->passwd, passwd);
					tip("       �޸ĳɹ�\n");
					break;
                }
            case 5: {
					char institute[30];
					 printNode(user);
					printf("        ������Ҫ�޸ĵ���Ϣ:\n");
					printf("        ѧԺ:");//�ж�ѧ���Ƿ����
					gets(institute);
					strcpy(user->info->institute, institute);
					tip("       �޸ĳɹ�");
					break;
                }
            case 6:{
					char phoneNum[20];
					 printNode(user);
					printf("        ������Ҫ�޸ĵ���Ϣ:\n");
					printf("        �绰����:");//�ж�ѧ���Ƿ����
					gets(phoneNum);
					strcpy(user->info->phoneNum, phoneNum);
                    tip("       �޸ĳɹ�\n");
					break;
                }
            case 7:{
                char synopsis[100];
                   printNode(user);
					printf("        ������Ҫ�޸ĵ���Ϣ:\n");
					printf("        ���:");//�ж�ѧ���Ƿ����
					gets(synopsis);
					strcpy(user->info->synopsis, synopsis);
                    tip("       �޸ĳɹ�\n");
					break;
            }
            case 8:{
                printNode(user);
                addUsrCourse(user->info);
                 tip("       �޸ĳɹ�\n");
                break;
            }

            case -1: isLogout = 1; break;
            default: loop=0;
        }
        //���ȫ��Ϊע�����˳���ǰ�˵�ֱ����ҳ
        if( isLogout ) loop=0;
    }

		//���޸ĺ����Ϣд�뵽�ļ���
		//����޸���name,��ԭ��name��Ӧ��idɾ��,Ȼ��д�����ļ�
		//����ֱ�ӽ���Ϣд��
		//print(globalHead);
        copyLinkNode(newInfoNode,user);
        //newInfoNode->next = NULL;
        //print(globalHead);
        //system("pause");
       // printNode(newInfoNode);
		replaceInfo(preLink,newInfoNode);
	}
	else
		printf("��id�Ų�����\n");

}

void replaceInfo(userLink preInfo, userLink newInfo) {
	int i;
	userLink head = (userLink)malloc(sizeof(userList));
	head->info = NULL;
	head->next = NULL;
	//print(globalHead);
	if (strcmp(preInfo->info->name, newInfo->info->name) == 0) {//����δ�޸�
		i = getCorrectInsertIndex(preInfo->info->name);
		//newInfo->info->firstChild = NULL;
		newInfo->next = NULL;
		newInfo->flag = 0;
		//�����û���Ϣ��
		readUserData(fileArr[i], head);
		userLink q = head->next;
		userLink pre = head;
		while (q&&preInfo->info->id != q->info->id) {//id�޸���,�ҵ��ļ��д��֮ǰ��id
				pre = q;
				q = q->next;
		}
        newInfo->next = q->next;
		pre->next = newInfo;
		free(q);
		//д����Ϣ
		//printf("sdfdd");
		//print(head);
		system("pause");
		writeInfoToFile(fileArr[i], head->next);
		freeUser(head);

	}
	else {
		//�ҵ�֮ǰ��Ϣ����ɾ��
		i = getCorrectInsertIndex(preInfo->info->name);
		//�����û���Ϣ��
		readUserData(fileArr[i], head);
		userLink q = head->next;
		userLink pre = head;
		while (q&&preInfo->info->id != q->info->id) {
			pre = q;
			q = q->next;
		}
        pre->next = q->next;
		free(q);
		//д����Ϣ
		writeInfoToFile(fileArr[i], head->next);
		freeUser(head);
		head->next = NULL;
		//�ҵ���Ӧ�ļ�д����Ϣ
		i = getCorrectInsertIndex(newInfo->info->name);
		//�����û���Ϣ��
		//newInfo->info->firstChild = NULL;
		newInfo->next = NULL;
		newInfo->flag = 0;
		//�����û���Ϣ��
		readUserData(fileArr[i], head);
		//������Ϣ
		insertToUserListByName(head, newInfo);
		//print(head);
		//д����Ϣ
		writeInfoToFile(fileArr[i], head->next);
		freeUser(head);
	}

}
