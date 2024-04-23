#include<iostream>
#include<cstring>
using namespace std;
class String {
	char* Pstr;
	int Strlen;
	int Strlength(const char *Str) {
		int strlen = 0;
		while (Str[strlen] != '\0')
			strlen++;
		return strlen;
	}
public:
	String() {
		Pstr = new char[1];
		Pstr[0] = '\0';
		Strlen = 0;
	}
	String(const char*Str) {
		Strlen = Strlength(Str);
		Pstr = new char[Strlen + 1];
		for (int i = 0; i < Strlen;i++) {
			Pstr[i] = Str[i];
		}
		Pstr[Strlen] = '\0';
	}
	String(int n,char c) {
		Strlen = n;
		Pstr = new char[n + 1];
		for (int i = 0; i < Strlen;i++) {
			Pstr[i] = c;
		}
		Pstr[Strlen] = '\0';
	}
	String(const String&Str) {
		Strlen = Str.Strlen;
		Pstr = new char[Strlen + 1];
		for (int i = 0; i < Strlen; i++) {
			Pstr[i] = Str.Pstr[i];
		}
		Pstr[Strlen] = '\0';
	}
	String& operator = (const String&Str){
		if (Pstr != NULL) {
			delete[]Pstr;
			this->Pstr = NULL;
			this->Strlen = 0;
		}
		Strlen = Str.Strlen;
		Pstr = new char[Strlen + 1];
		for (int i = 0; i < Strlen; i++) {
			Pstr[i] = Str.Pstr[i];
		}
		Pstr[Strlen] = '\0';
		return *this;
	}
	~String()
	{
		if (Pstr!=NULL) {
			delete[]Pstr;
			Strlen = 0;
			Pstr = NULL;
		}
	}
	int StrLength()const { return this->Strlen; }
	/*7����д�ַ�������������������ʹ��strcpy�����ƹ��ܺ�����
		8����д�Ӵ����Һ����������Ӵ���Դ���е�һ�γ��ֵ�λ�á�
		9����д�Ӵ����뺯������������Ĵ����������ֵ���Ӵ��������Ӵ����벢���ز������ַ�����*/
	friend void StringCopyStr(String&Str1,const String&Str2);
	int FindStr(const String& Str) const { // �Ӵ����Һ����������Ӵ���Դ���е�һ�γ��ֵ�λ��
		int len1 = Strlen;
		int len2 = Str.Strlen;
		for (int i = 0; i <= len1 - len2; i++) {
			int j = 0;
			while (j < len2 && Pstr[i + j] == Str.Pstr[j]) {
				j++;
			}
			if (j == len2) {
				return i;
			}
		}
		return -1;
	}
	int FindStr(const char* str) const { // �Ӵ����Һ����������Ӵ���Դ���е�һ�γ��ֵ�λ��
		String Str(str);
		int len1 = Strlen;
		int len2 = Str.Strlen;
		for (int i = 0; i <= len1 - len2; i++) {
			int j = 0;
			while (j < len2 && Pstr[i + j] == Str.Pstr[j]) {
				j++;
			}
			if (j == len2) {
				return i;
			}
		}
		return -1;
	}
	void InsertStr(String&Str,int n) {
		Strlen = Strlen + Str.Strlen;
		char* NewSpace = new char[Strlen+1];
		int i = 0;
		while (Pstr[i]!='\0'&&i<n-1)
		{
			NewSpace[i] = Pstr[i];
			i++;
		}
		int j = i;
		int k = 0;
		while (Str.Pstr[k]!='\0'&&k<Str.Strlen)
		{
			NewSpace[i] = Str.Pstr[k];
			k++;
			i++;
		}
		while (Pstr[j] != '\0'&&i<Strlen+1) {
			NewSpace[i] = Pstr[j];
			j++;
			i++;
		}
		NewSpace[Strlen] = '\0';
		if (Pstr!=NULL) 
		{
			delete[]Pstr;
			Pstr = NULL;
		}
		Pstr = NewSpace;
	}
	void InsertStr(const char* str, int n) {
		String Str(str);
		this->InsertStr(Str,n);
	}
	void show()const {
		for (int i = 0; i < Strlen; i++) {
			cout << Pstr[i];
		}
		cout << endl;
	}
};

void StringCopyStr(String& Str1, const String& Str2)
{
	if (Str1.Pstr!=NULL) {
		delete[]Str1.Pstr;
		Str1.Strlen = 0;
		Str1.Pstr = NULL;
	}
	Str1.Strlen = Str2.Strlen;
	Str1.Pstr = new char[Str1.Strlen + 1];
	for (int i = 0; i < Str1.Strlen+1;i++)
	{
		Str1.Pstr[i] = Str2.Pstr[i];
	}
}
int main() {
	String Str;
	cout << "Ĭ�Ϲ��캯��" << endl;
	cout << "Str= ";
	Str.show();
	cout << "�����ַ������ͽ��й���" << endl;
	String Str1("hello world");
	cout << "Str1= ";
	Str1.show(); 
	cout << "�������캯�����г�ʼ��" << endl;
	cout << "Str2= ";
	String Str2(Str1);
	Str2.show();
	cout << "�����صĸ�ֵ�������Str���и�ֵ" << endl;
	cout << "Str= ";
	Str = Str2;
	Str.show();
	cout << "��Copy�������и�ֵ����" << endl;
	String Str3;
	StringCopyStr(Str3,Str);
	cout << "Str3= ";
	Str3.show();
	system("pause");
	system("cls");
	cout << "���в��Ҳ���" << endl;
	char num[10];
	cout << "��������Ҫ��Str�в��ҵ��ַ�" << endl;
	cin >> num;
	int checknum = Str.FindStr(num);
	if (checknum == -1)cout << "��ѯʧ��" << endl;
	else cout << "�ַ����ֵ�λ��Ϊ: "<<checknum << endl;
	cout << "��������Ҫ��Str�в�����ַ�" << endl;
	cin >> num;
	int selectnum;
	cout << "��������Ҫ��Str�в����ַ�����λ��" << endl;
	cin >> selectnum;
	Str.InsertStr(num,selectnum);
	Str.show();
	system("pause");
	return 0;
}
