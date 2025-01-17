#include "Song.h"
#include "UnitON.h"
#include <fstream.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
//--------------------------------SONG---------------------------------------

Song::Song()
{
}

Song::~Song()
{
}

Song:: set_author(wstring filepath)
{
	string aut;
	ifstream file;
	file.open(filepath.c_str());
	getline (file, aut);
	this->author=aut;
}

string Song:: get_author()
{
	return (this->author);
}

Song:: set_name(wstring filepath)
{
	string n;
	ifstream file;
	string no_need;
	file.open(filepath.c_str());
	getline (file, no_need);
	getline (file,n);
	this->name=n;
}

string Song:: get_name()
{
	return (this->name);
}

Song:: set_num_couplet(wstring filepath)
{
	num_couplet=0;
	string line;
	ifstream file;
	file.open(filepath.c_str());
	while(!(file.eof()))//���� �� ����� �����
	{
		char t='a';
		while(t)//���� �� ������ �� ������� �����, ����� ���� �������
		{
			getline (file, line);
			t=line[0];
		}
		num_couplet++;
	}
}

int Song:: get_num_couplet()
{
	return (this->num_couplet);
}

void Song:: read(Couplet song[],wstring filepath )
{
	string line;
	ifstream file;
	file.open(filepath.c_str());
	getline (file, line);
	getline (file, line);
	for(int i=0;i<num_couplet;++i)//���� �� ������ �� ������� �����, ����� ���� �������
	{
		int count=0;
		char t='a';
		vector<string> couplet;
		while(t)
		{
			getline (file, line);
			count++;
			couplet.push_back(line);//�������� ������
			t=line[0];
		}
		song[i].set_text(couplet);
		song[i].set_size(count);
	}
	line=this->author;//�������� ������
	UnicodeString str = line.c_str();
	Form2->MemoWr->Lines->Add(str);
	line=this->name;//�������� �����
	str = line.c_str();
	Form2->MemoWr->Lines->Add(str+"\n");
}

//--------------------------------COUPLET------------------------------------

Couplet::Couplet()
{
}

Couplet::~Couplet()
{
}

Couplet::set_text(vector <string> lines)
{
	this->text=lines;
}

Couplet::set_pos(int num)
{
	this->pos=num;
}

Couplet::set_size(int num)
{
	this->size=num;
}

vector <string> Couplet:: get_text()
{
	return text;
}

int Couplet:: get_pos()
{
	return this->pos;
}

int Couplet:: get_size()
{
	return size;
}

void Couplet:: print()
{
	string line;
	for(int i=0;i<text.size();++i)
	{
		line=text[i];
		UnicodeString str = line.c_str();
		Form2->MemoWr->Lines->Add(str);
	}
}

void Couplet::print_labeled()
{
	string line;
	for(int i=0;i<text.size();++i)
	{
		line=text[i];
		UnicodeString str = line.c_str();
		if(i==(text.size()-1))//���� �� ����� ������ �� ���������, �� �� �� ��������
		{
			Form2->MemoWr->Lines->Add(str);
		}
		else
		{
			Form2->MemoWr->Lines->Add(IntToStr(this->pos)+"."+IntToStr(i+1)+"|"+str);
		}
	}
}

void Couplet:: find_char(char sym)
{
	bool find = false;
	string line;
	for(int i=0;i<text.size();++i)
	{
		line=text[i];
		UnicodeString str = line.c_str();
		for(int j=0;j<strlen(line.c_str());++j)
		{
			if(sym==line[j])
			{
				Form2->Memo1->Lines->Add("������ �������� � ������ �"+IntToStr(this->pos)+
				" � ���� �" +IntToStr(i+1)+" ������� �"+IntToStr(j+1));
				find=true;
			}
		}
	}
	if(!find)
	{
		Form2->Memo1->Lines->Add("�������� � ������ �"+IntToStr(this->pos)+
				" �� ���� ��������.");
	}
}

void Couplet::find_word(int word_len, char *word)
{
	bool find = false;
	string line;
	int line_len;
	for(int k=0;k<text.size();++k)
	{
		line=text[k];
		UnicodeString str = line.c_str();
		line_len=strlen(line.c_str());
		int i,j;
		i=-1;
		do{
			j=1;
			++i;
			while((j<word_len)&&(line[i+j]==word[j]))j++;
		}while(j<word_len&&i<(line_len-word_len));
		if(j==word_len)
		{
			Form2->Memo1->Lines->Add("����� �������� � ������ �"+IntToStr(this->pos)+
				" � ���� �" +IntToStr(k+1)+" ������� �"+IntToStr(i));
				find=true;
		}
	}
	if(!find)
	{
		Form2->Memo1->Lines->Add("�������� � ������ �"+IntToStr(this->pos)+
				" �� ���� ��������.");
	}
}

void Couplet::find_string(string line)
{
	bool find = false;
	string cmp;
	for(int k=0;k<text.size();++k)
	{
		cmp=text[k];
		if(cmp==line)
		{
			Form2->Memo1->Lines->Add("������ �������� � ������ �"+IntToStr(this->pos)+
				" � ���� �" +IntToStr(k+1));
			find=true;
		}
	}
	if(!find)
	{
			Form2->Memo1->Lines->Add("�������� � ������ �"+IntToStr(this->pos)+
				" �� ���� ��������.");
	}
}

void Couplet::show_first_lines()
{
	string line;
	line=text[0];
	UnicodeString str = line.c_str();
	Form2->MemoWr->Lines->Add(str);
}


void Couplet::show_last_lines()
{
	string line;
	int pos;
	pos=text.size();
	line=text[pos-2];
	UnicodeString str = line.c_str();
	Form2->MemoWr->Lines->Add(str);
}

void Couplet::del_line(int posit)
{
	text.erase(text.begin()+posit-1);
}

void Couplet::change_places(int pos1,int pos2)
{
	std::swap(text[pos1],text[pos2]);
}

string Couplet::return_line(int l_pos)
{
	string line;
	line=text[l_pos];
    return line;
}

//�������� �������� ���������, ����������� ����� �������� ���(����, ���, �.�.)
//� ��� � ��� ������� ��������, ���� ����������, �� � ����( a_check ������� �� ����, ���������)
//�������� ���� �������� ����� ��������� �������� ���� ���� �����( ��� a_check �� ����� ���� (�� ����) � ��� ( �� ����� � ���: ����))
//���� � ���� � �� � � �� �(���������), �� ����� ��������� ��������� � ������� ������� true

//��������� � ����� ��� � ���. �� ����� � � ����� � ����������� � ����� ��������(��� ������� � � ������ ������� ����� �� ������)
//���� � ��� � �����, ������ ������� ������ ������� �� ��������. � ����� ����� �� ������� �������� ��� � ���� ������
//� ������� � �������, � ��� ��� ��� ���������. �� ���� ������ �����, ��� ��������� ������������
bool Couplet:: find_rhyme_abab()
{
	bool a_check=false;
	bool b_check=false;
	char check1,check2;
	int leng1,leng2;
	string line1,line2;

	line1=text[0];
	leng1=line1.size()-1;
	check1=line1[leng1];
	line2=text[2];
	leng2=line2.size()-1;
	check2=line2[leng2];
	if(check1==check2)
	{
		a_check=true;
	}

	line1=text[1];
	leng1=line1.size()-1;
	check1=line1[leng1];
	line2=text[3];
	leng2=line2.size()-1;
	check2=line2[leng2];
	if(check1==check2)
	{
		b_check=true;
	}

	if(a_check&&b_check)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Couplet:: find_rhyme_vhv(char h)
{
	bool v_check=false;
	bool h_check=false;
	char check1,check2;
	int leng1,leng2;
	string line1,line2;

	line1=text[0];
	leng1=line1.size()-1;
	check1=line1[leng1];
	line2=text[2];
	leng2=line2.size()-1;
	check2=line2[leng2];
	if(check1==check2)
	{
		v_check=true;
	}

	line1=text[1];
	leng1=line1.size()-1;
	check1=line1[leng1];
	check2=h;
	if(check1==check2)
	{
		h_check=true;
	}

	if(v_check&&h_check)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Couplet::find_rhyme_hdd(char h)
{
	bool h_check=false;
	bool d_check=false;
	char check1,check2;
	int leng1,leng2;
	string line1,line2;

	line1=text[0];
	leng1=line1.size()-1;
	check1=line1[leng1];
	check2=h;
	if(check1==check2)
	{
		h_check=true;
	}

	line1=text[1];
	leng1=line1.size()-1;
	check1=line1[leng1];
	line2=text[2];
	leng2=line2.size()-1;
	check2=line2[leng2];
	if(check1==check2)
	{
		d_check=true;
	}

	if(h_check&&d_check)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Couplet::find_rhyme_zez(char e)
{
	bool z_check=false;
	bool e_check=false;
	char check1,check2;
	int leng1,leng2;
	string line1,line2;

	line1=text[0];
	leng1=line1.size()-1;
	check1=line1[leng1];
	line2=text[2];
	leng2=line2.size()-1;
	check2=line2[leng2];
	if(check1==check2)
	{
		z_check=true;
	}

	line1=text[1];
	leng1=line1.size()-1;
	check1=line1[leng1];
	check2=e;
	if(check1==check2)
	{
		e_check=true;
	}

	if(z_check&&e_check)
	{
		return true;
	}
	else
	{
		return false;
	}
}


std::ostream& operator<< (std::ostream &out,const Couplet &C)
{
	string line;
	for(int i=0;i<C.text.size();++i)
	{
		line=C.text[i];
		UnicodeString str = line.c_str();
		Form2->MemoWr->Lines->Add(str);
	}
}

std::istream& operator >> (std::istream &in,Couplet &C)
{
	vector <string> temp;
	temp=C.get_text();
	C.set_text(temp);
	return in;
}
