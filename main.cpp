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
	/*7、编写字符串拷贝函数，不允许使用strcpy或类似功能函数。
		8、编写子串查找函数，查找子串在源串中第一次出现的位置。
		9、编写子串插入函数，根据输入的待插入的索引值和子串，将该子串插入并返回插入后的字符串。*/
	friend void StringCopyStr(String&Str1,const String&Str2);
	int FindStr(const String& Str) const { // 子串查找函数，查找子串在源串中第一次出现的位置
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
	int FindStr(const char* str) const { // 子串查找函数，查找子串在源串中第一次出现的位置
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
	cout << "默认构造函数" << endl;
	cout << "Str= ";
	Str.show();
	cout << "传入字符串类型进行构造" << endl;
	String Str1("hello world");
	cout << "Str1= ";
	Str1.show(); 
	cout << "拷贝构造函数进行初始化" << endl;
	cout << "Str2= ";
	String Str2(Str1);
	Str2.show();
	cout << "用重载的赋值运算符对Str进行赋值" << endl;
	cout << "Str= ";
	Str = Str2;
	Str.show();
	cout << "用Copy函数进行赋值操作" << endl;
	String Str3;
	StringCopyStr(Str3,Str);
	cout << "Str3= ";
	Str3.show();
	system("pause");
	system("cls");
	cout << "进行查找操作" << endl;
	char num[10];
	cout << "请输入你要在Str中查找的字符" << endl;
	cin >> num;
	int checknum = Str.FindStr(num);
	if (checknum == -1)cout << "查询失败" << endl;
	else cout << "字符出现的位置为: "<<checknum << endl;
	cout << "请输入你要在Str中插入的字符" << endl;
	cin >> num;
	int selectnum;
	cout << "请输入你要在Str中插入字符串的位置" << endl;
	cin >> selectnum;
	Str.InsertStr(num,selectnum);
	Str.show();
	system("pause");
	return 0;
}
