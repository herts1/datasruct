#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max 81
void modification(){
	printf("1.学号\n"); 
	printf("2.性别\n"); 
	printf("3.名字\n"); 
	printf("4.联系电话\n"); 
	printf("5.家庭住址\n"); 
	printf("6.成绩\n"); 
	printf("0.退出\n");
}
//修改名单 
void menu() {
	printf("\n-------学生管理系统--------\n");
	printf("1.添加\n");
	printf("2.删除\n");
	printf("3.修改\n"); 
	printf("4.查找\n"); 
	printf("5.成绩统计\n"); 
	printf("6.成绩排序\n");
	printf("7.保存文件信息\n");  
	printf("0.退出\n");
}   //建立菜单     
//建立菜单 
typedef struct Student{
	int id; //学号 
	char gender[10];  //性别 
	char name[20];  //名字 
	int score[10];   //分数
	int sum=0;  //总分 
	long long num=0;  //联系电话 
	char home[20];   //家庭住址 
	Student *next;   
}Student;
//定义 
Student *initlist(){
	Student *head =(Student *)malloc(sizeof(Student));
	head->next=NULL;
	return head;
}  //初始化初链表 
//初始化初链表 
void add_student(Student *head){
    Student* p = head;
    while(p->next!=NULL)p=p->next;
    Student* newinf =(Student *)malloc(sizeof(Student));
    printf("自选（跳过请输入‘0’）\n"); 
    printf("请输入学号："); 
    scanf("%d",&newinf->id);
    printf("请输入性别：");
    scanf("%s",newinf->gender);
    printf("请输入名字：");
    scanf("%s",newinf->name);
    printf("请输入联系电话：");
    scanf("%lld",&newinf->num);
	printf("请输入家庭住址：");
	scanf("%s",newinf->home); 
	printf("请输入待输入成绩个数：");
	int n;
	scanf("%d",&n);
	if(n<3){
		printf("低于最小个数！"); 
	} else{
		printf("请按顺序输入成绩：\n"); 
		for(int i=0;i<n;i++){
			scanf("%d",&newinf->score[i]);
			newinf->sum+=newinf->score[i];
		}
	}
	
	newinf->next=NULL;
    p->next=newinf;
    printf("添加over\n");
}    //模块：添加学生信息 
//模块：添加学生信息 
void del_student(Student *head){
	int id;
	Student *p=head,*q;
	printf("请输入删除学生的学号："); 
	scanf("%d",&id);
	while(p->next!=NULL){
		if(p->next->id==id){
			q=p->next;
			p->next=q->next;
			free(q);
			printf("删除成功\n");
			return; 
		}
		p=p->next;
	} 
	printf("未找到该学生\n");
} 
//模块：删除学生信息 
void modify_student(Student *head){
	Student *p=head;
	int id;
	
	printf("请输入要修改学生的学号：");
	scanf("%d",&id);
	while(p->next!=NULL){
		if(p->next->id==id){
			while(1){
				modification();
				int n;
				scanf("%d",&n);
				switch (n) {
					case 1:
						printf("请输入待更改的学号："); 
						scanf("%d",&p->next->id);
						break;
					case 2:
						printf("请输入待更改的性别："); 
						scanf("%s",p->next->gender);
						break;
					case 3:
						printf("请输入待更改的名字："); 
						scanf("%s",p->next->name);
						break;
					case 4:
						printf("请输入待更改的电话号码：");
						scanf("%lld",&p->next->num);
						break;
					case 5:
						printf("请输入待更改的家庭住址：");
						scanf("%s",p->next->home);
						break;
					case 6:
						printf("请输入本次课程个数：");
						int m;
						scanf("%d", &m);
						printf("请输入待更改的科目：");
						int n;
						scanf("%d",&n);
						printf("请输入待更改的分数：");
						scanf("%d",&p->next->score[n]); 
						p->next->sum=0;
						for(int i=0;i<m;i++){
							p->next->sum+=p->next->score[i];
						}
					
					
					case 0:
						printf("修改over\n");
						return; 
				}
				
			}
		}
	}
	printf("未找到该学生！\n"); 
} 
//模块：修改学生信息 
void search_student(Student *head){
	Student *p=head;
	int id;
	printf("请输入查找学生的学号：");
	scanf("%d",&id);
	while(p->next!=NULL){
		if(p->next->id==id){
			printf("以下是该学生的信息：\n");
			printf("学号：%d\n",p->next->id);
			printf("性别：%s\n",p->next->gender);
			printf("名字：%s\n",p->next->name);
			printf("电话号码：%lld\n",p->next->num);
			printf("家庭住址：%s\n",p->next->home);
			return;
		}
		p=p->next; 
	}
	printf("未找到该学生！");
}
//模块：查找学生信息
void statiscore_average(Student *head){
	Student *p=head;
	int average=0;
	
	int count=0;
	while(p->next!=NULL){
		count++;
		average+=p->next->sum;
		p=p->next;
	} 
	printf("平均成绩：%d\n",average/count) ;
}
//模块：计算学生平均成绩
void statiscore_fail(Student *head){
	Student *p=head;
	int n; 
	printf("请输入本次课程个数：");
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		printf("%d.统计科目%d不合格学生个数\n",i,i-1);
		}
	int goal;
	printf("请输入科目：");
	scanf("%d",&goal);
	int count=0;
	while(p->next!=NULL){
		if(p->next->score[goal]<60){
			count++;
		}
		p=p->next;
	} 
	printf("科目%d不合格个数：%d",goal-1,count);
}
//模块：计算学生不合格个数 
void sort_score(Student *head) {
    
    
    printf("请输入本次课程个数：");
    int n;
    scanf("%d", &n);
    
    
    int length = 0;
    Student *count_ptr = head->next;  
    while (count_ptr != NULL) {
        length++;
        count_ptr = count_ptr->next;
    }
    
    // 冒泡排序
    for (int i = 0; i < length - 1; i++) {
        Student *p = head->next;  
        int swapped = 0;
        
        for (int j = 0; j < length - i - 1 && p != NULL && p->next != NULL; j++) {
            if (p->sum < p->next->sum) {
                
                int temp_id = p->id;
                p->id = p->next->id;
                p->next->id = temp_id;
                char temp_name[20];
                strcpy(temp_name, p->name);
                strcpy(p->name, p->next->name);
                strcpy(p->next->name, temp_name);
                char temp_gender[10];
                strcpy(temp_gender, p->gender);
                strcpy(p->gender, p->next->gender);
                strcpy(p->next->gender, temp_gender);
                long long temp_num=p->num;
                p->num=p->next->num;
                p->next->num=temp_num;
				char temp_home[20];
				strcpy(temp_home, p->home);
				strcpy(p->home, p->next->home);
				strcpy(p->next->home, temp_home);
                
                int temp_sum = p->sum;
                p->sum = p->next->sum;
                p->next->sum = temp_sum;
                
                
                for (int k = 0; k < n; k++) {
                    int temp_score = p->score[k];
                    p->score[k] = p->next->score[k];
                    p->next->score[k] = temp_score;
                }
                
                swapped = 1;
            }
            p = p->next;
        }
        
        
        if (!swapped) {
            break;
        }
    }
    
    
    printf("\n======= 成绩排序结果 =======\n");
    Student *current = head->next;  
    
	while (current != NULL) {
        printf("学号：%d 姓名：%s 总分：%d\n", 
               current->id, current->name, current->sum);
        current = current->next;
    }
}
//模块：排序学生总成绩
void sort_only (Student *head){
	printf("请输入本次课程个数：");
	int n;
	scanf("%d", &n);
	int length = 0;
	    Student *count_ptr = head->next;  
	    while (count_ptr != NULL) {
	        length++;
	        count_ptr = count_ptr->next;
	    }
	    while(1){
			printf("请输入要排序的科目：");
			int m;
			scanf("%d",&m);
			 
		
		
		
		// 冒泡排序
		    for (int i = 0; i < length - 1; i++) {
		        Student *p = head->next;  
		        int swapped = 0;
		        
		        for (int j = 0; j < length - i - 1 && p != NULL && p->next != NULL; j++) {
		            if (p->score[m] < p->next->score[m]) {
		                
		                int temp_id = p->id;
		                p->id = p->next->id;
		                p->next->id = temp_id;
		                char temp_name[20];
		                strcpy(temp_name, p->name);
		                strcpy(p->name, p->next->name);
		                strcpy(p->next->name, temp_name);
		                char temp_gender[10];
		                strcpy(temp_gender, p->gender);
		                strcpy(p->gender, p->next->gender);
		                strcpy(p->next->gender, temp_gender);
		                long long temp_num=p->num;
						p->num=p->next->num;
		                p->next->num=temp_num;
						char temp_home[20];
						strcpy(temp_home, p->home);
						strcpy(p->home, p->next->home);
						strcpy(p->next->home, temp_home);
		                
		                int temp_sum = p->sum;
		                p->sum = p->next->sum;
		                p->next->sum = temp_sum;
		                
		                
		                for (int k = 0; k < n; k++) {
		                    int temp_score = p->score[k];
		                    p->score[k] = p->next->score[k];
		                    p->next->score[k] = temp_score;
		                }
		                
		                swapped = 1;
		            }
		            p = p->next;
		        }
		        
		        
		        if (!swapped) {
		            break;
		        }
		    }
		    
		    
		    printf("\n======= 成绩排序结果 =======\n");
		    Student *current = head->next;  
		    
			while (current != NULL) {
		        printf("学号：%d 姓名：%s 科目%d：%d\n", 
		               current->id, current->name,m, current->score[m]);
		        current = current->next;
		    }
	    }
}
void save_file(Student *head){
	FILE *fp=fopen("student.dat","wb");
	if(fp==NULL){
		printf("文件打开失败！\n");
		return; 
	}
	Student *p=head->next;
	while(p!=NULL){
		fwrite(p,sizeof(Student),1,fp);
		p=p->next;
	}
	fclose(fp);
}
//模块：保存到文件 
void load_file(Student *head){
	FILE *fp=fopen("student.dat","rb");  //打开文件 
		if(fp==NULL){
			printf("无历史数据，新建文件！\n");
			return; 
		}
		Student *p=head;
		Student *newd;
		while(fread(newd=(Student *)malloc(sizeof(Student)),sizeof(Student),1,fp)){
			newd->next=NULL;
			p->next=newd;
			p=p->next;
			
		} 
		fclose(fp);
	
}
//模块：从文件读取 
int main () {
	Student *head=initlist();
	load_file(head); //检查是否存在文件 
	while(1){
		menu(); //菜单 
		int n;
		scanf("%d",&n);
		switch (n) {
			case 1:
				add_student(head);  //添加 
				break;
			case 2:     
				del_student(head);  //删除 
				break;
			case 3:
				modify_student(head);  //修改 
				break;
			case 4:
				search_student(head);  //查找 
				break;			
			case 5:
				statiscore_average(head);  //计算平均分 //计算不及格个数 
				statiscore_fail(head);
				break;	 
			case 6:
				sort_score(head);      //总分排序 
				sort_only(head);       //单科排序 
				break; 
			case 7:
				save_file(head);
				printf("保存成功！");
				break; 
			
			case 0:
				printf("成功退出！欢迎下次使用！");
				return 0;
			default:
				printf("请重新输入：");
				break;
		
		}
		
		
	}
	
}
