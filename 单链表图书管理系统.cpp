//图书管理系统（单链表版）
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct book //图书
{
	char title[100];  //书名
	char isbn[100];  //书号
	char author[100];  //作者
	char publisher[100];  //出版社
	int cnt; //书籍数量
	struct book* next;  //下一本书籍
}Book;
Book* book_head;  //图书头指针
int book_amount;  //图书总数量

struct node //用户所借书籍
{
	int borrow_amount, max_amount; //所借书籍数量， 最大借书数
	double tax;  //超出时限收费比率
	time_t borrow_time[10], return_time[10];  //借、还时间
	Book borrow_book[10];  //每位最多借10本书籍
};

typedef struct user //用户
{
	char user_name[30];  //用户名
	char password[30];  //密码
	char ID[30]; //有效证件号码
	int admin;  //是否管理员
	struct node user_book;  //用户所借书籍
	struct user* next;  //下一位用户
}User;
User* user_head;  //用户头指针
User* gz007;  //超级管理员账号
int user_amount;  //用户总数量

//程序功能区
void welcome_page();  //欢迎页面
void producer_infor();  //制作人员信息
void manual();  //使用手册
void main_menu();  //主菜单

//主菜单功能区
void user_register();  //用户注册
void user_login();  //用户登录
void admin_login();  //管理员登陆

//核心功能区
void creat_user_list(char*, char*, char*);  //创建用户链表
void creat_book_list(char*, char*, char*, char*, int);  //创建图书链表
void user_initi(User*);  //用户图书管理初始化
void load();  //从文件中加载数据
void save();  //保存数据到文件

//用户功能区
void user_menu(User*);  //用户菜单
void user_change(User*);  //更改用户信息
int delete_user(User*);  //删除账号
void borrow_book(User*);  //借阅管理
void return_book(User*);  //还书管理
void history(User*);  //历史借阅浏览

//管理员功能区
void admin_initi();  //超级管理员账号初始化
User* serch_username(char*);  //查找用户名
void admin_menu(User*);  //管理员菜单
void query_user();  //用户信息查询
void admin_user();  //管理用户信息
void all_history(); //查看用户图书借阅归还情况
User* serch_user();  //按序号搜索用户
void set_admin(User*);  //设置管理员

//图书管理功能区
void add_book();  //增加图书信息
void delete_book();  //删除图书信息
void browse_book();  //图书浏览

int main()
{
	welcome_page();
	printf("退出系统成功，祝您生活愉快！\n");
	system("pause"); system("cls");
	return 0;
}

/********程序功能区***********/
void welcome_page()  //欢迎页面
{
	load();
	while (1)
	{
		system("color 30");
		printf("+---------------------------------------------+\n");
		printf("欢迎使用本图书管理系统!\n");
		printf("使用过程中如遇技术问题请及时联系制作人员!\n");
		printf("请输入选项前的数字以确认操作！\n");
		printf("1、进入系统\n");
		printf("2、查看制作人员信息\n");
		printf("3、查看本系统使用手册\n");
		printf("0、退出系统\n");
		printf("+---------------------------------------------+\n");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: main_menu(); break;
		case 2: producer_infor(); break;
		case 3: manual(); break;
		case 0: return;
		default: printf("错误的指令，请重新输入！\n"); system("pause"); system("cls"); break;
		}
	}
}

void producer_infor()  //制作人员信息
{
	printf("****************************************\n");
	printf("*   制作者信息如下：                   *\n");
	printf("*       姓名：LGC                   *\n");
	printf("*       班级：计算机科学与技术18-1班   *\n");
	printf("*       学号：5418********             *\n");
	printf("*       电话：187********              *\n");
	printf("*       QQ：26********                 *\n");
	printf("****************************************\n");
	system("pause"); system("cls");
}

void manual() //使用手册
{
	printf("*******************************************************************************\n");
	printf("用户须知:\n初始管理员账户：gz007\t密码：20000308\n证件号：5418\n\n");
	printf("鉴于制作人员水平有限。\n请严格按照系统提示进行操作，以免引起程序奔溃！！！\n");
	printf("*******************************************************************************\n");
	system("pause"); system("cls");
}

void main_menu()  //主菜单
{
	while (1)
	{
		system("color 1A");
		printf("+---------------------------------------------+\n");
		printf("欢迎进入本图书管理系统!\n");
		printf("请输入选项前的数字以确认操作！\n");
		printf("1、用户注册\n");
		printf("2、用户登陆\n");
		printf("3、管理员登陆\n");
		printf("0、返回欢迎页面\n");
		printf("+---------------------------------------------+\n");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: user_register(); break;
		case 2: user_login();  break;
		case 3: admin_login();  break;
		case 0: return;
		default: printf("错误的指令，请重新输入！\n"); system("pause"); system("cls"); break;
		}
	}
}


/********主菜单功能区***********/
void user_register()  //用户注册
{
	char name[30];
	printf("请输入您需要注册的用户名(不超过25个字母)：\n");
	scanf("%s", name);
	User* account;
	if (account = serch_username(name), account != NULL)
	{
		printf("该用户名已存在，请重新输入！\n");
		system("pause"); system("cls"); return;
	}
	printf("请输入您的账号密码(不超过25个字母)：\n");
	char password[30];
	scanf("%s", password);
	printf("请输入您的有效证件号码(不超过25个数字)：\n");
	char ID[30];
	scanf("%s", ID);
	creat_user_list(name, password, ID);
	printf("恭喜您注册成功！\n");
	++user_amount;
	system("pause"); system("cls");
}

void user_login()  //用户登录
{
	char name[30];
	printf("请输入您的用户名(不超过25个字母)：\n");
	scanf("%s", name);
	User* account;
	if (account = serch_username(name), account == NULL)
	{
		printf("该用户名不存在，请注册或重新登陆账号！\n");
		system("pause"); system("cls"); return;
	}
	printf("请输入您的账号密码(不超过25个字母)：\n");
	scanf("%s", name);
	if (strcmp(account->password, name))
	{
		printf("密码错误，请确认后重新登陆！\n");
		system("pause"); system("cls"); return;
	}
	printf("恭喜您登录成功,即将跳转用户界面...\n");
	system("pause"); system("cls");
	user_menu(account);
}

void admin_login()  //管理员登陆
{
	char name[30];
	printf("尊敬的管理员：\n");
	printf("请输入您的管理账号(不超过25个字母)：\n");
	scanf("%s", name);
	User* account;
	if (account = serch_username(name), account == NULL)
	{
		printf("该账号不存在，请重新输入！\n");
		system("pause"); system("cls"); return;
	}
	if (!account->admin)
	{
		printf("该账号暂无管理权限，请联系相关管理人员！\n");
		system("pause"); system("cls"); return;
	}
	printf("请输入该管理账号的密码(不超过25个字母)：\n");
	scanf("%s", name);
	if (strcmp(account->password, name))
	{
		printf("密码错误，请确认后重新登陆！\n");
		system("pause"); system("cls"); return;
	}
	printf("恭喜您登录成功,即将跳转管理界面...\n");
	system("pause"); system("cls");
	admin_menu(account);
}

/********核心功能区***********/
void creat_user_list(char* name, char* password, char* ID)  //创建用户链表
{
	User* np = (User*)malloc(sizeof(User));
	np = user_head;
	while (np->next) np = np->next;
	User* tp = (User*)malloc(sizeof(User));
	strcpy(tp->user_name, name);
	strcpy(tp->password, password);
	strcpy(tp->ID, ID);
	tp->admin = 0;
	tp->next = NULL;
	user_initi(tp);
	np->next = tp;
	save();
}

void creat_book_list(char* title, char* isbn, char* author, char* publisher, int cnt)  //创建图书链表
{
	Book* np = (Book*)malloc(sizeof(Book));
	np = book_head;
	while (np->next) np = np->next;
	Book* tb = (Book*)malloc(sizeof(Book));
	strcpy(tb->title, title);
	strcpy(tb->isbn, isbn);
	strcpy(tb->author, author);
	strcpy(tb->publisher, publisher);
	tb->cnt = cnt;
	tb->next = NULL;
	np->next = tb;
	save();
}

void user_initi(User* account)  //用户图书管理初始化
{
	account->user_book.borrow_amount = 0;
	account->user_book.max_amount = 10;
	account->user_book.tax = 1.0;
	memset(account->user_book.borrow_time, 0, sizeof(account->user_book.borrow_time));
	memset(account->user_book.return_time, 0, sizeof(account->user_book.return_time));
	memset(account->user_book.borrow_book, 0, sizeof(account->user_book.borrow_book));
}

void load()  //从文件中加载数据
{
	book_head = (Book*)malloc(sizeof(Book));
	book_head->next = NULL;
	book_amount = 0;

	FILE* fp2;
	fp2 = fopen("book.bin", "rb");
	if (fp2 == NULL)
	{
		fp2 = fopen("book.bin", "wb");
		if (fp2 == NULL)
		{
			printf("图书存储失败！\n"); exit(0);
		}
		fclose(fp2);
	}
	else
	{
		Book* bp = (Book*)malloc(sizeof(Book));
		bp = book_head;
		Book* tp = (Book*)malloc(sizeof(Book));
		while (fread(tp, sizeof(Book), 1, fp2))
		{
			bp->next = tp;
			++book_amount;
			tp = tp->next;
			tp = (Book*)malloc(sizeof(Book));
			bp = bp->next;
		}
		fclose(fp2);
	}

	user_head = (User*)malloc(sizeof(User));
	user_head->next = NULL;
	user_amount = 0;

	FILE* fp1;
	fp1 = fopen("user.bin", "rb");
	if (fp1 == NULL)
	{
		admin_initi(); return;
	}
	User* np = (User*)malloc(sizeof(User));
	np = user_head;
	User* temp = (User*)malloc(sizeof(User));
	while (fread(temp, sizeof(User), 1, fp1))
	{
		np->next = temp;
		++user_amount;
		temp = temp->next;
		temp = (User*)malloc(sizeof(User));
		np = np->next;
	}
	gz007 = user_head->next;
	fclose(fp1);
}

void save()  //保存数据到文件
{
	FILE* fp = fopen("user.bin", "wb");
	User* temp = user_head->next;
	while (temp)
	{
		fwrite(temp, sizeof(User), 1, fp);
		temp = temp->next;
	}
	fclose(fp);

	fp = fopen("book.bin", "wb");
	Book* tb = book_head->next;
	while (tb)
	{
		fwrite(tb, sizeof(Book), 1, fp);
		tb = tb->next;
	}
	fclose(fp);
}


/********用户功能区***********/
void user_menu(User* account)  //用户菜单
{
	while (1)
	{
		system("color 30");
		printf("+---------------------------------------------+\n");
		printf("用户：%s\n 欢迎您!\n", account->user_name);
		printf("请输入选项前的数字以确认操作！\n");
		printf("1、借阅管理\n");
		printf("2、还书管理\n");
		printf("3、历史借阅浏览\n");
		printf("4、图书浏览\n");
		printf("5、修改账号信息\n");
		printf("6、删除账号\n");
		printf("0、退出登陆\n");
		printf("+---------------------------------------------+\n");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: borrow_book(account); break;
		case 2: return_book(account); break;
		case 3: history(account); system("pause"); system("cls"); break;
		case 4: browse_book(); system("pause"); system("cls"); break;
		case 5: user_change(account);  break;
		case 6: if (delete_user(account))
		{
			printf("该账号已被删除，请重新登陆！\n");
			system("pause"); system("cls");
			return;
		}
				else break;
		case 0: printf("账号登出成功!\n"); system("pause"); system("cls"); return;
		default: printf("错误的指令，请重新输入！\n"); system("pause"); system("cls"); break;
		}
	}
}

void user_change(User* account)  //更改用户信息
{
	printf("待修改用户：%s\t 您现在可以更改您的个人信息!\n", account->user_name);
	printf("请重新输入您的密码(不超过25个字母)：\n");
	char password[30];
	scanf("%s", password);
	strcpy(account->password, password);
	printf("用户%s\t账号密码已修改！\n", account->user_name);
	printf("请重新输入您的有效证件号码(不超过25个字母)：\n");
	char ID[30];
	scanf("%s", ID);
	strcpy(account->ID, ID);
	printf("用户%s\t有效证件号码已修改！\n", account->user_name);
	save();
	printf("用户%s\t个人信息修改成功，正在返回上一界面...\n", account->user_name);
	system("pause"); system("cls");
}

int delete_user(User* account)  //删除账号
{
	printf("********************************************\n");
	if (!strcmp(account->user_name, gz007->user_name))
	{
		printf("用户%s拥有最高权限，不可被删除！！！正在返回上一层...\n", gz007->user_name);
		system("pause"); system("cls"); return 0;
	}
	printf("是否需要删除账号%s？\n", account->user_name);
	printf("请输入相应数字以继续操作！\n");
	printf("1、是\t0、否\n");
	int op;  scanf("%d", &op);
	if (op == 1)
	{
		if (account->user_book.borrow_amount)
		{
			printf("删除失败！该用户有%d本图书未归还！请先归还所借阅图书！\n", account->user_book.borrow_amount);
		}
		else
		{
			User* tp = (User*)malloc(sizeof(User));
			tp = user_head;
			User* np = (User*)malloc(sizeof(User));
			np = user_head->next;
			while (np)
			{
				if (!strcmp(np->user_name, account->user_name))
				{
					tp->next = np->next;
					free(np); --user_amount;
					save();
					printf("账号已删除成功！\n");
					system("pause"); system("cls");
					return 1;
				}
				tp = np;
				np = np->next;
			}
		}
	}
	else if (!op) printf("已取消本次操作！\n");
	else printf("输入选项错误，请重新输入！正在返回上一层...\n");
	system("pause"); system("cls"); return 0;
}

void borrow_book(User* account)  //借阅管理
{
	printf("用户%s：请输入您的有效身份证件号码(不超过25位)以继续！\n", account->user_name);
	char ID[30]; scanf("%s", ID); system("cls");
	if (strcmp(account->ID, ID))
	{
		printf("身份证件号码与账号不匹配，请检查后重新输入！\n");
		system("pause"); system("cls"); return;
	}
	while (1)
	{
		int ans = account->user_book.borrow_amount, Max = account->user_book.max_amount;
		if (ans == Max)
		{
			printf("用户%s：借阅图书数量 %d 本，已达上限 %d 本，请先归还部分图书！\n", account->user_name, ans, Max);
			system("pause"); system("cls"); return;
		}
		browse_book();
		printf("请输入您需要借阅的书籍序号(输入 -1 退出删除操作)：\n");
		int cnt; scanf("%d", &cnt);
		if (cnt == -1)
		{
			printf("已成功退出借阅系统！\n"); system("pause"); system("cls");
			return;
		}
		else if (cnt > book_amount || cnt <= 0)
		{
			printf("请正确输入上图中已有的图书序号！\n");
		}
		else
		{
			printf("请设置您需要借阅的时间(不超过90天)：\n");
			int day; scanf("%d", &day);
			if (day > 90 || day <= 0)
				printf("输入借阅时间不被允许，请重新输入！\n");
			else
			{
				Book* tb = (Book*)malloc(sizeof(Book));
				tb = book_head->next;
				for (int i = 1; i < cnt; ++i)
					tb = tb->next;
				account->user_book.borrow_book[ans] = *tb;
				account->user_book.borrow_time[ans] = time(NULL);
				account->user_book.return_time[ans] = time(NULL) + day * 3600 * 24;
				++account->user_book.borrow_amount;
				save();
				printf("用户%s：借阅图书《%s》成功！\n", account->user_name, tb->title);
			}
		}
		system("pause"); system("cls");
	}
}

void return_book(User * account)  //还书管理
{

	while (1)
	{
		history(account);
		if (!account->user_book.borrow_amount)
		{
			system("pause"); system("cls"); return;
		}
		printf("请输入您需要归还的书籍序号（输入-1以退出还书系统）！\n");
		int cnt = 0; scanf("%d", &cnt); system("cls");
		if (cnt == -1)
		{
			printf("正在退出还阅系统，请稍后...\n");
			system("pause"); system("cls"); return;
		}
		if (cnt > account->user_book.borrow_amount || cnt < 0)
		{
			printf("请正确输入上述书籍序号！\n");
		}
		else
		{
			int i = 0;
			for (--cnt; i < cnt; ++i);

			char title[100];
			strcpy(title, account->user_book.borrow_book[i].title);
			time_t t = time(NULL);
			printf("*************************************************\n");
			printf("规定还书时间：%s", ctime(&account->user_book.return_time[i]));
			printf("当前时间：%s", ctime(&t));
			t -= account->user_book.return_time[i];
			if (t > 0)
			{
				double cost = t / 3600.0 / 24 * account->user_book.tax;
				printf("由于您未在指定日期内归还《%s》,您需要支付违约金%.2lf元\n", title, cost);
			}
			else printf("书籍《%s》借阅未超出时间，无需支付违约金！\n", title);
			for (; i < account->user_book.borrow_amount; ++i)
			{
				account->user_book.borrow_book[i] = account->user_book.borrow_book[i + 1];
				account->user_book.borrow_time[i] = account->user_book.borrow_time[i + 1];
				account->user_book.return_time[i] = account->user_book.return_time[i + 1];
			}
			--account->user_book.borrow_amount;
			save();
			printf("书籍《%s》归还成功！\n", title);
		}
		system("pause"); system("cls");
	}
}

void history(User * account)  //历史借阅浏览
{
	int n = account->user_book.borrow_amount;
	printf("*************************************************************\n");
	printf("用户%s：\n", account->user_name);
	if (!n)
	{
		printf("暂无书籍在借阅记录！\n"); return;
	}
	printf("借阅书籍序号：\n");
	for (int i = 0; i < n; ++i)
	{
		struct node t = account->user_book;
		time_t nt = time(NULL) - t.return_time[i];
		double cost = 0.0;
		if (nt > 0) cost = t.tax * (nt / 3600.0 / 24);
		printf("%d：\n", i + 1);
		printf("  书名：《%s》\n", t.borrow_book[i].title);
		printf("  借阅日期：%s", ctime(&t.borrow_time[i]));
		printf("  规定还书日期：%s", ctime(&t.return_time[i]));
		if (nt > 0) printf("  是否超时：是\n");
		else printf("  是否超时：否\n");
		printf("  借阅费用：%.2lf\n", cost);
	}
}


/********管理员功能区***********/
void admin_initi()  //超级管理员账号初始化
{
	FILE* fp = fopen("user.bin", "wb");
	if (fp == NULL)
	{
		printf("管理员权限初始化失败！\n"); exit(0);
	}
	gz007 = (User*)malloc(sizeof(User));
	strcpy(gz007->user_name, "gz007");
	strcpy(gz007->password, "20000308");
	strcpy(gz007->ID, "5418");
	gz007->admin = 1;
	gz007->next = NULL;
	user_initi(gz007);
	user_head->next = gz007;
	user_amount = 1;
	save();
	fclose(fp);
}

User* serch_username(char* name)  //查找用户名
{
	User* np = user_head->next;
	while (np)
	{
		if (!strcmp(np->user_name, name)) return np;
		np = np->next;
	}
	return NULL;
}

void admin_menu(User * account)  //管理员菜单
{
	while (1)
	{
		system("color 9F");
		printf("*************************************************\n");
		printf("管理员：%s\n 欢迎您!\n", account->user_name);
		printf("请输入选项前的数字以确认操作！\n");
		printf("1、增加图书信息\n");
		printf("2、删除图书信息\n");
		printf("3、图书浏览\n");
		printf("4、管理用户信息\n");
		printf("0、退出登陆\n");
		printf("*************************************************\n");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: add_book(); break;
		case 2: delete_book(); break;
		case 3: browse_book(); system("pause"); system("cls"); break;
		case 4: admin_user(); break;
		case 0: printf("退出管理账号成功!\n"); system("pause"); system("cls"); return;
		default: printf("错误的指令，请重新输入！\n"); system("pause"); system("cls"); break;
		}
	}
}

void query_user()  //用户信息查询
{
	int cnt = 1;
	User* np = (User*)malloc(sizeof(User));
	np = user_head->next;
	printf("序号  用户名\t\t密码\t\t证件号码\t\t是否管理员\n");
	while (np)
	{
		printf("%d、 %-20s %-20s %-20s", cnt, np->user_name, np->password, np->ID);
		if (np->admin) printf(" 是\n");
		else printf(" 否\n");
		np = np->next;
		++cnt;
	}
}

void admin_user()  //管理用户信息
{
	while (1)
	{
		system("color 9F");
		printf("*************************************************\n");
		printf("欢迎进入用户管理界面！\n");
		printf("在此界面您可以自由查看、更改各用户信息！\n");
		printf("请输入选项前的数字以确认操作！\n");
		printf("1、查看用户个人信息\n");
		printf("2、修改用户个人信息\n");
		printf("3、查看用户图书借阅归还情况\n");
		printf("4、设置管理员权限\n");
		printf("5、删除用户账号\n");
		printf("0、返回总管理界面\n");
		printf("*************************************************\n");
		User* np = (User*)malloc(sizeof(User));
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: query_user(); system("pause"); system("cls"); break;
		case 2: if (np = serch_user(), np != NULL) user_change(np);
				else
		{
			system("pause"); system("cls");
		}
				break;
		case 3: all_history(); break;
		case 4: if (np = serch_user(), np != NULL) set_admin(np);
				else
		{
			system("pause"); system("cls");
		}
				break;
		case 5:if (np = serch_user(), np != NULL)
		{
			int admin = np->admin;
			if (delete_user(np) && admin)
				printf("该账号已被删除，请重新登陆！\n");
			system("pause"); system("cls");
			return;
		}
			   else
		{
			system("pause"); system("cls");
		}
			   break;
		case 0: printf("退出用户管理界面成功!\n"); system("pause"); system("cls"); return;
		default: printf("错误的指令，请重新输入！\n"); system("pause"); system("cls"); break;
		}
	}
}

void all_history() //查看用户图书借阅归还情况
{
	while (1)
	{
		printf("###########################################################\n");
		printf("欢迎使用用户图书借阅归还查询系统！\n");
		User* account = (User*)malloc(sizeof(User));
		account = serch_user();
		if (account)
		{
			history(account);
			printf("查阅成功！正在返回上一层...\n");
			system("pause"); system("cls"); return;
		}
		system("pause"); system("cls");
	}
}

User* serch_user()  //按序号搜索用户
{
	query_user();
	printf("请输入待操作的用户序号：\n");
	int cnt; scanf("%d", &cnt); system("cls");
	if (cnt > user_amount || cnt <= 0)
		printf("请正确输入上图中待操作的用户序号！\n");
	else
	{
		User* tb = (User*)malloc(sizeof(User));
		tb = user_head->next;
		for (int i = 1; i < cnt; ++i)
			tb = tb->next;
		return tb;
	}
	return NULL;
}

void set_admin(User * account)  //设置管理员
{
	printf("*******************************************************************\n");
	if (!strcmp(account->user_name, gz007->user_name))
	{
		printf("用户%s拥有最高管理权限，不可被修改！！！正在返回上一层...\n", gz007->user_name);
		system("pause"); system("cls"); return;
	}
	printf("是否确认将用户%s设置为管理员？\n", account->user_name);
	printf("请输入相应数字以继续操作！\n");
	printf("1、设置为管理员\t0、取消管理员权限\n");
	int op; scanf("%d", &op);
	if (op == 1)
	{
		account->admin = op;
		printf("用户%s\t管理员权限设置成功！\n", account->user_name);
	}
	else if (op == 0)
	{
		account->admin = op;
		printf("用户%s\t管理员权限已被取消！\n", account->user_name);
	}
	else
	{
		printf("设置管理员权限失败，请按要求输入！\n");
	}
	printf("*******************************************************************\n");
	save();
	system("pause"); system("cls");
}

/********图书功能区***********/
void add_book()  //增加图书信息
{
	char title[100], isbn[100], author[100], publisher[100];
	int cnt;
	printf("请输入需要添加的书籍名称：\n");
	scanf("%s", title);
	printf("请输入需要添加的书籍书号：\n");
	scanf("%s", isbn);
	printf("请输入需要添加的书籍作者：\n");
	scanf("%s", author);
	printf("请输入需要添加的书出版社：\n");
	scanf("%s", publisher);
	printf("请输入需要添加的书籍数量：\n");
	scanf("%d", &cnt);
	++book_amount;
	creat_book_list(title, isbn, author, publisher, cnt);
	printf("添加书籍《%s》成功！\n", title);
	system("pause"); system("cls");
}

void delete_book()  //删除图书信息
{
	while (1)
	{
		browse_book();
		printf("请输入待删除的书籍序号(输入 -1 退出删除操作)：\n");
		int cnt; scanf("%d", &cnt);
		if (cnt == -1)
		{
			printf("已成功退出删除系统！\n"); system("pause"); system("cls");
			return;
		}
		else if (cnt > book_amount || cnt <= 0)
		{
			printf("请正确输入上图中待删除的图书序号！\n");
		}
		else
		{
			Book* tb = (Book*)malloc(sizeof(Book));
			Book* np = (Book*)malloc(sizeof(Book));
			np = book_head;
			tb = book_head->next;
			for (int i = 1; i < cnt; ++i)
			{
				np = tb;
				tb = tb->next;
			}
			np->next = tb->next;
			free(tb); --book_amount;
			save();
			printf("该图书已从馆内删除成功！\n");
		}
		system("pause"); system("cls");
	}
}

void browse_book()  //图书浏览
{
	int cnt = 1;
	if (!book_amount)
	{
		printf("馆内暂无图书资料，请联系管理员添加书籍！\n");
		return;
	}
	Book* tb = (Book*)malloc(sizeof(Book));
	tb = book_head->next;
	printf("馆内图书详情如下：\n");
	printf("序号\t书名\t书号\t作者\t出版社\t总库存量\n");
	while (tb)
	{
		printf("%-4d、《%s》 %-20s %-20s %-20s %d\n", cnt, tb->title, tb->isbn,
			tb->author, tb->publisher, tb->cnt);
		tb = tb->next; ++cnt;
	}
}

