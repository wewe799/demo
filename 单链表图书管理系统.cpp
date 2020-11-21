//ͼ�����ϵͳ��������棩
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct book //ͼ��
{
	char title[100];  //����
	char isbn[100];  //���
	char author[100];  //����
	char publisher[100];  //������
	int cnt; //�鼮����
	struct book* next;  //��һ���鼮
}Book;
Book* book_head;  //ͼ��ͷָ��
int book_amount;  //ͼ��������

struct node //�û������鼮
{
	int borrow_amount, max_amount; //�����鼮������ ��������
	double tax;  //����ʱ���շѱ���
	time_t borrow_time[10], return_time[10];  //�衢��ʱ��
	Book borrow_book[10];  //ÿλ����10���鼮
};

typedef struct user //�û�
{
	char user_name[30];  //�û���
	char password[30];  //����
	char ID[30]; //��Ч֤������
	int admin;  //�Ƿ����Ա
	struct node user_book;  //�û������鼮
	struct user* next;  //��һλ�û�
}User;
User* user_head;  //�û�ͷָ��
User* gz007;  //��������Ա�˺�
int user_amount;  //�û�������

//��������
void welcome_page();  //��ӭҳ��
void producer_infor();  //������Ա��Ϣ
void manual();  //ʹ���ֲ�
void main_menu();  //���˵�

//���˵�������
void user_register();  //�û�ע��
void user_login();  //�û���¼
void admin_login();  //����Ա��½

//���Ĺ�����
void creat_user_list(char*, char*, char*);  //�����û�����
void creat_book_list(char*, char*, char*, char*, int);  //����ͼ������
void user_initi(User*);  //�û�ͼ������ʼ��
void load();  //���ļ��м�������
void save();  //�������ݵ��ļ�

//�û�������
void user_menu(User*);  //�û��˵�
void user_change(User*);  //�����û���Ϣ
int delete_user(User*);  //ɾ���˺�
void borrow_book(User*);  //���Ĺ���
void return_book(User*);  //�������
void history(User*);  //��ʷ�������

//����Ա������
void admin_initi();  //��������Ա�˺ų�ʼ��
User* serch_username(char*);  //�����û���
void admin_menu(User*);  //����Ա�˵�
void query_user();  //�û���Ϣ��ѯ
void admin_user();  //�����û���Ϣ
void all_history(); //�鿴�û�ͼ����Ĺ黹���
User* serch_user();  //����������û�
void set_admin(User*);  //���ù���Ա

//ͼ���������
void add_book();  //����ͼ����Ϣ
void delete_book();  //ɾ��ͼ����Ϣ
void browse_book();  //ͼ�����

int main()
{
	welcome_page();
	printf("�˳�ϵͳ�ɹ���ף��������죡\n");
	system("pause"); system("cls");
	return 0;
}

/********��������***********/
void welcome_page()  //��ӭҳ��
{
	load();
	while (1)
	{
		system("color 30");
		printf("+---------------------------------------------+\n");
		printf("��ӭʹ�ñ�ͼ�����ϵͳ!\n");
		printf("ʹ�ù������������������뼰ʱ��ϵ������Ա!\n");
		printf("������ѡ��ǰ��������ȷ�ϲ�����\n");
		printf("1������ϵͳ\n");
		printf("2���鿴������Ա��Ϣ\n");
		printf("3���鿴��ϵͳʹ���ֲ�\n");
		printf("0���˳�ϵͳ\n");
		printf("+---------------------------------------------+\n");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: main_menu(); break;
		case 2: producer_infor(); break;
		case 3: manual(); break;
		case 0: return;
		default: printf("�����ָ����������룡\n"); system("pause"); system("cls"); break;
		}
	}
}

void producer_infor()  //������Ա��Ϣ
{
	printf("****************************************\n");
	printf("*   ��������Ϣ���£�                   *\n");
	printf("*       ������LGC                   *\n");
	printf("*       �༶���������ѧ�뼼��18-1��   *\n");
	printf("*       ѧ�ţ�5418********             *\n");
	printf("*       �绰��187********              *\n");
	printf("*       QQ��26********                 *\n");
	printf("****************************************\n");
	system("pause"); system("cls");
}

void manual() //ʹ���ֲ�
{
	printf("*******************************************************************************\n");
	printf("�û���֪:\n��ʼ����Ա�˻���gz007\t���룺20000308\n֤���ţ�5418\n\n");
	printf("����������Աˮƽ���ޡ�\n���ϸ���ϵͳ��ʾ���в������������������������\n");
	printf("*******************************************************************************\n");
	system("pause"); system("cls");
}

void main_menu()  //���˵�
{
	while (1)
	{
		system("color 1A");
		printf("+---------------------------------------------+\n");
		printf("��ӭ���뱾ͼ�����ϵͳ!\n");
		printf("������ѡ��ǰ��������ȷ�ϲ�����\n");
		printf("1���û�ע��\n");
		printf("2���û���½\n");
		printf("3������Ա��½\n");
		printf("0�����ػ�ӭҳ��\n");
		printf("+---------------------------------------------+\n");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: user_register(); break;
		case 2: user_login();  break;
		case 3: admin_login();  break;
		case 0: return;
		default: printf("�����ָ����������룡\n"); system("pause"); system("cls"); break;
		}
	}
}


/********���˵�������***********/
void user_register()  //�û�ע��
{
	char name[30];
	printf("����������Ҫע����û���(������25����ĸ)��\n");
	scanf("%s", name);
	User* account;
	if (account = serch_username(name), account != NULL)
	{
		printf("���û����Ѵ��ڣ����������룡\n");
		system("pause"); system("cls"); return;
	}
	printf("�����������˺�����(������25����ĸ)��\n");
	char password[30];
	scanf("%s", password);
	printf("������������Ч֤������(������25������)��\n");
	char ID[30];
	scanf("%s", ID);
	creat_user_list(name, password, ID);
	printf("��ϲ��ע��ɹ���\n");
	++user_amount;
	system("pause"); system("cls");
}

void user_login()  //�û���¼
{
	char name[30];
	printf("�����������û���(������25����ĸ)��\n");
	scanf("%s", name);
	User* account;
	if (account = serch_username(name), account == NULL)
	{
		printf("���û��������ڣ���ע������µ�½�˺ţ�\n");
		system("pause"); system("cls"); return;
	}
	printf("�����������˺�����(������25����ĸ)��\n");
	scanf("%s", name);
	if (strcmp(account->password, name))
	{
		printf("���������ȷ�Ϻ����µ�½��\n");
		system("pause"); system("cls"); return;
	}
	printf("��ϲ����¼�ɹ�,������ת�û�����...\n");
	system("pause"); system("cls");
	user_menu(account);
}

void admin_login()  //����Ա��½
{
	char name[30];
	printf("�𾴵Ĺ���Ա��\n");
	printf("���������Ĺ����˺�(������25����ĸ)��\n");
	scanf("%s", name);
	User* account;
	if (account = serch_username(name), account == NULL)
	{
		printf("���˺Ų����ڣ����������룡\n");
		system("pause"); system("cls"); return;
	}
	if (!account->admin)
	{
		printf("���˺����޹���Ȩ�ޣ�����ϵ��ع�����Ա��\n");
		system("pause"); system("cls"); return;
	}
	printf("������ù����˺ŵ�����(������25����ĸ)��\n");
	scanf("%s", name);
	if (strcmp(account->password, name))
	{
		printf("���������ȷ�Ϻ����µ�½��\n");
		system("pause"); system("cls"); return;
	}
	printf("��ϲ����¼�ɹ�,������ת�������...\n");
	system("pause"); system("cls");
	admin_menu(account);
}

/********���Ĺ�����***********/
void creat_user_list(char* name, char* password, char* ID)  //�����û�����
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

void creat_book_list(char* title, char* isbn, char* author, char* publisher, int cnt)  //����ͼ������
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

void user_initi(User* account)  //�û�ͼ������ʼ��
{
	account->user_book.borrow_amount = 0;
	account->user_book.max_amount = 10;
	account->user_book.tax = 1.0;
	memset(account->user_book.borrow_time, 0, sizeof(account->user_book.borrow_time));
	memset(account->user_book.return_time, 0, sizeof(account->user_book.return_time));
	memset(account->user_book.borrow_book, 0, sizeof(account->user_book.borrow_book));
}

void load()  //���ļ��м�������
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
			printf("ͼ��洢ʧ�ܣ�\n"); exit(0);
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

void save()  //�������ݵ��ļ�
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


/********�û�������***********/
void user_menu(User* account)  //�û��˵�
{
	while (1)
	{
		system("color 30");
		printf("+---------------------------------------------+\n");
		printf("�û���%s\n ��ӭ��!\n", account->user_name);
		printf("������ѡ��ǰ��������ȷ�ϲ�����\n");
		printf("1�����Ĺ���\n");
		printf("2���������\n");
		printf("3����ʷ�������\n");
		printf("4��ͼ�����\n");
		printf("5���޸��˺���Ϣ\n");
		printf("6��ɾ���˺�\n");
		printf("0���˳���½\n");
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
			printf("���˺��ѱ�ɾ���������µ�½��\n");
			system("pause"); system("cls");
			return;
		}
				else break;
		case 0: printf("�˺ŵǳ��ɹ�!\n"); system("pause"); system("cls"); return;
		default: printf("�����ָ����������룡\n"); system("pause"); system("cls"); break;
		}
	}
}

void user_change(User* account)  //�����û���Ϣ
{
	printf("���޸��û���%s\t �����ڿ��Ը������ĸ�����Ϣ!\n", account->user_name);
	printf("������������������(������25����ĸ)��\n");
	char password[30];
	scanf("%s", password);
	strcpy(account->password, password);
	printf("�û�%s\t�˺��������޸ģ�\n", account->user_name);
	printf("����������������Ч֤������(������25����ĸ)��\n");
	char ID[30];
	scanf("%s", ID);
	strcpy(account->ID, ID);
	printf("�û�%s\t��Ч֤���������޸ģ�\n", account->user_name);
	save();
	printf("�û�%s\t������Ϣ�޸ĳɹ������ڷ�����һ����...\n", account->user_name);
	system("pause"); system("cls");
}

int delete_user(User* account)  //ɾ���˺�
{
	printf("********************************************\n");
	if (!strcmp(account->user_name, gz007->user_name))
	{
		printf("�û�%sӵ�����Ȩ�ޣ����ɱ�ɾ�����������ڷ�����һ��...\n", gz007->user_name);
		system("pause"); system("cls"); return 0;
	}
	printf("�Ƿ���Ҫɾ���˺�%s��\n", account->user_name);
	printf("��������Ӧ�����Լ���������\n");
	printf("1����\t0����\n");
	int op;  scanf("%d", &op);
	if (op == 1)
	{
		if (account->user_book.borrow_amount)
		{
			printf("ɾ��ʧ�ܣ����û���%d��ͼ��δ�黹�����ȹ黹������ͼ�飡\n", account->user_book.borrow_amount);
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
					printf("�˺���ɾ���ɹ���\n");
					system("pause"); system("cls");
					return 1;
				}
				tp = np;
				np = np->next;
			}
		}
	}
	else if (!op) printf("��ȡ�����β�����\n");
	else printf("����ѡ��������������룡���ڷ�����һ��...\n");
	system("pause"); system("cls"); return 0;
}

void borrow_book(User* account)  //���Ĺ���
{
	printf("�û�%s��������������Ч���֤������(������25λ)�Լ�����\n", account->user_name);
	char ID[30]; scanf("%s", ID); system("cls");
	if (strcmp(account->ID, ID))
	{
		printf("���֤���������˺Ų�ƥ�䣬������������룡\n");
		system("pause"); system("cls"); return;
	}
	while (1)
	{
		int ans = account->user_book.borrow_amount, Max = account->user_book.max_amount;
		if (ans == Max)
		{
			printf("�û�%s������ͼ������ %d �����Ѵ����� %d �������ȹ黹����ͼ�飡\n", account->user_name, ans, Max);
			system("pause"); system("cls"); return;
		}
		browse_book();
		printf("����������Ҫ���ĵ��鼮���(���� -1 �˳�ɾ������)��\n");
		int cnt; scanf("%d", &cnt);
		if (cnt == -1)
		{
			printf("�ѳɹ��˳�����ϵͳ��\n"); system("pause"); system("cls");
			return;
		}
		else if (cnt > book_amount || cnt <= 0)
		{
			printf("����ȷ������ͼ�����е�ͼ����ţ�\n");
		}
		else
		{
			printf("����������Ҫ���ĵ�ʱ��(������90��)��\n");
			int day; scanf("%d", &day);
			if (day > 90 || day <= 0)
				printf("�������ʱ�䲻���������������룡\n");
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
				printf("�û�%s������ͼ�顶%s���ɹ���\n", account->user_name, tb->title);
			}
		}
		system("pause"); system("cls");
	}
}

void return_book(User * account)  //�������
{

	while (1)
	{
		history(account);
		if (!account->user_book.borrow_amount)
		{
			system("pause"); system("cls"); return;
		}
		printf("����������Ҫ�黹���鼮��ţ�����-1���˳�����ϵͳ����\n");
		int cnt = 0; scanf("%d", &cnt); system("cls");
		if (cnt == -1)
		{
			printf("�����˳�����ϵͳ�����Ժ�...\n");
			system("pause"); system("cls"); return;
		}
		if (cnt > account->user_book.borrow_amount || cnt < 0)
		{
			printf("����ȷ���������鼮��ţ�\n");
		}
		else
		{
			int i = 0;
			for (--cnt; i < cnt; ++i);

			char title[100];
			strcpy(title, account->user_book.borrow_book[i].title);
			time_t t = time(NULL);
			printf("*************************************************\n");
			printf("�涨����ʱ�䣺%s", ctime(&account->user_book.return_time[i]));
			printf("��ǰʱ�䣺%s", ctime(&t));
			t -= account->user_book.return_time[i];
			if (t > 0)
			{
				double cost = t / 3600.0 / 24 * account->user_book.tax;
				printf("������δ��ָ�������ڹ黹��%s��,����Ҫ֧��ΥԼ��%.2lfԪ\n", title, cost);
			}
			else printf("�鼮��%s������δ����ʱ�䣬����֧��ΥԼ��\n", title);
			for (; i < account->user_book.borrow_amount; ++i)
			{
				account->user_book.borrow_book[i] = account->user_book.borrow_book[i + 1];
				account->user_book.borrow_time[i] = account->user_book.borrow_time[i + 1];
				account->user_book.return_time[i] = account->user_book.return_time[i + 1];
			}
			--account->user_book.borrow_amount;
			save();
			printf("�鼮��%s���黹�ɹ���\n", title);
		}
		system("pause"); system("cls");
	}
}

void history(User * account)  //��ʷ�������
{
	int n = account->user_book.borrow_amount;
	printf("*************************************************************\n");
	printf("�û�%s��\n", account->user_name);
	if (!n)
	{
		printf("�����鼮�ڽ��ļ�¼��\n"); return;
	}
	printf("�����鼮��ţ�\n");
	for (int i = 0; i < n; ++i)
	{
		struct node t = account->user_book;
		time_t nt = time(NULL) - t.return_time[i];
		double cost = 0.0;
		if (nt > 0) cost = t.tax * (nt / 3600.0 / 24);
		printf("%d��\n", i + 1);
		printf("  ��������%s��\n", t.borrow_book[i].title);
		printf("  �������ڣ�%s", ctime(&t.borrow_time[i]));
		printf("  �涨�������ڣ�%s", ctime(&t.return_time[i]));
		if (nt > 0) printf("  �Ƿ�ʱ����\n");
		else printf("  �Ƿ�ʱ����\n");
		printf("  ���ķ��ã�%.2lf\n", cost);
	}
}


/********����Ա������***********/
void admin_initi()  //��������Ա�˺ų�ʼ��
{
	FILE* fp = fopen("user.bin", "wb");
	if (fp == NULL)
	{
		printf("����ԱȨ�޳�ʼ��ʧ�ܣ�\n"); exit(0);
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

User* serch_username(char* name)  //�����û���
{
	User* np = user_head->next;
	while (np)
	{
		if (!strcmp(np->user_name, name)) return np;
		np = np->next;
	}
	return NULL;
}

void admin_menu(User * account)  //����Ա�˵�
{
	while (1)
	{
		system("color 9F");
		printf("*************************************************\n");
		printf("����Ա��%s\n ��ӭ��!\n", account->user_name);
		printf("������ѡ��ǰ��������ȷ�ϲ�����\n");
		printf("1������ͼ����Ϣ\n");
		printf("2��ɾ��ͼ����Ϣ\n");
		printf("3��ͼ�����\n");
		printf("4�������û���Ϣ\n");
		printf("0���˳���½\n");
		printf("*************************************************\n");
		int op; scanf("%d", &op); system("cls");
		switch (op)
		{
		case 1: add_book(); break;
		case 2: delete_book(); break;
		case 3: browse_book(); system("pause"); system("cls"); break;
		case 4: admin_user(); break;
		case 0: printf("�˳������˺ųɹ�!\n"); system("pause"); system("cls"); return;
		default: printf("�����ָ����������룡\n"); system("pause"); system("cls"); break;
		}
	}
}

void query_user()  //�û���Ϣ��ѯ
{
	int cnt = 1;
	User* np = (User*)malloc(sizeof(User));
	np = user_head->next;
	printf("���  �û���\t\t����\t\t֤������\t\t�Ƿ����Ա\n");
	while (np)
	{
		printf("%d�� %-20s %-20s %-20s", cnt, np->user_name, np->password, np->ID);
		if (np->admin) printf(" ��\n");
		else printf(" ��\n");
		np = np->next;
		++cnt;
	}
}

void admin_user()  //�����û���Ϣ
{
	while (1)
	{
		system("color 9F");
		printf("*************************************************\n");
		printf("��ӭ�����û�������棡\n");
		printf("�ڴ˽������������ɲ鿴�����ĸ��û���Ϣ��\n");
		printf("������ѡ��ǰ��������ȷ�ϲ�����\n");
		printf("1���鿴�û�������Ϣ\n");
		printf("2���޸��û�������Ϣ\n");
		printf("3���鿴�û�ͼ����Ĺ黹���\n");
		printf("4�����ù���ԱȨ��\n");
		printf("5��ɾ���û��˺�\n");
		printf("0�������ܹ������\n");
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
				printf("���˺��ѱ�ɾ���������µ�½��\n");
			system("pause"); system("cls");
			return;
		}
			   else
		{
			system("pause"); system("cls");
		}
			   break;
		case 0: printf("�˳��û��������ɹ�!\n"); system("pause"); system("cls"); return;
		default: printf("�����ָ����������룡\n"); system("pause"); system("cls"); break;
		}
	}
}

void all_history() //�鿴�û�ͼ����Ĺ黹���
{
	while (1)
	{
		printf("###########################################################\n");
		printf("��ӭʹ���û�ͼ����Ĺ黹��ѯϵͳ��\n");
		User* account = (User*)malloc(sizeof(User));
		account = serch_user();
		if (account)
		{
			history(account);
			printf("���ĳɹ������ڷ�����һ��...\n");
			system("pause"); system("cls"); return;
		}
		system("pause"); system("cls");
	}
}

User* serch_user()  //����������û�
{
	query_user();
	printf("��������������û���ţ�\n");
	int cnt; scanf("%d", &cnt); system("cls");
	if (cnt > user_amount || cnt <= 0)
		printf("����ȷ������ͼ�д��������û���ţ�\n");
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

void set_admin(User * account)  //���ù���Ա
{
	printf("*******************************************************************\n");
	if (!strcmp(account->user_name, gz007->user_name))
	{
		printf("�û�%sӵ����߹���Ȩ�ޣ����ɱ��޸ģ��������ڷ�����һ��...\n", gz007->user_name);
		system("pause"); system("cls"); return;
	}
	printf("�Ƿ�ȷ�Ͻ��û�%s����Ϊ����Ա��\n", account->user_name);
	printf("��������Ӧ�����Լ���������\n");
	printf("1������Ϊ����Ա\t0��ȡ������ԱȨ��\n");
	int op; scanf("%d", &op);
	if (op == 1)
	{
		account->admin = op;
		printf("�û�%s\t����ԱȨ�����óɹ���\n", account->user_name);
	}
	else if (op == 0)
	{
		account->admin = op;
		printf("�û�%s\t����ԱȨ���ѱ�ȡ����\n", account->user_name);
	}
	else
	{
		printf("���ù���ԱȨ��ʧ�ܣ��밴Ҫ�����룡\n");
	}
	printf("*******************************************************************\n");
	save();
	system("pause"); system("cls");
}

/********ͼ�鹦����***********/
void add_book()  //����ͼ����Ϣ
{
	char title[100], isbn[100], author[100], publisher[100];
	int cnt;
	printf("��������Ҫ��ӵ��鼮���ƣ�\n");
	scanf("%s", title);
	printf("��������Ҫ��ӵ��鼮��ţ�\n");
	scanf("%s", isbn);
	printf("��������Ҫ��ӵ��鼮���ߣ�\n");
	scanf("%s", author);
	printf("��������Ҫ��ӵ�������磺\n");
	scanf("%s", publisher);
	printf("��������Ҫ��ӵ��鼮������\n");
	scanf("%d", &cnt);
	++book_amount;
	creat_book_list(title, isbn, author, publisher, cnt);
	printf("����鼮��%s���ɹ���\n", title);
	system("pause"); system("cls");
}

void delete_book()  //ɾ��ͼ����Ϣ
{
	while (1)
	{
		browse_book();
		printf("�������ɾ�����鼮���(���� -1 �˳�ɾ������)��\n");
		int cnt; scanf("%d", &cnt);
		if (cnt == -1)
		{
			printf("�ѳɹ��˳�ɾ��ϵͳ��\n"); system("pause"); system("cls");
			return;
		}
		else if (cnt > book_amount || cnt <= 0)
		{
			printf("����ȷ������ͼ�д�ɾ����ͼ����ţ�\n");
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
			printf("��ͼ���Ѵӹ���ɾ���ɹ���\n");
		}
		system("pause"); system("cls");
	}
}

void browse_book()  //ͼ�����
{
	int cnt = 1;
	if (!book_amount)
	{
		printf("��������ͼ�����ϣ�����ϵ����Ա����鼮��\n");
		return;
	}
	Book* tb = (Book*)malloc(sizeof(Book));
	tb = book_head->next;
	printf("����ͼ���������£�\n");
	printf("���\t����\t���\t����\t������\t�ܿ����\n");
	while (tb)
	{
		printf("%-4d����%s�� %-20s %-20s %-20s %d\n", cnt, tb->title, tb->isbn,
			tb->author, tb->publisher, tb->cnt);
		tb = tb->next; ++cnt;
	}
}

