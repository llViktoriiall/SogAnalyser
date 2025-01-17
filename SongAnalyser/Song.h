#ifndef SONGH
#define SONGH

#include "Unit_Main.h"
#include <string>
#include <vector>
using namespace std;

class Couplet;

class Song {
	public:
	Song();
	~Song();
	set_author(wstring filepath);
	set_name(wstring filepath);
	set_num_couplet(wstring filepath);
	string get_author();
	string get_name();
	int get_num_couplet();
	void read(Couplet song[],wstring filepath ); //����� ����
	private:
	string author;
	string name;
	int num_couplet;
};

class Couplet {
	public:
	Couplet();
	~Couplet();
	set_text(vector <string> lines);
	set_pos(int num);
	set_size(int num);
	vector <string> get_text();
	void print();//����
	void print_labeled();//���� � ��������
	int get_pos();
	int get_size();
	friend void Song::read(Couplet song[],wstring filepath ); //����� ����
	void find_char(char sym);  //����� �������
	void find_word(int word_len, char *word); //����� �����
	void find_string(string line); //����� ������
	void show_first_lines();//���� ������ ������
	void show_last_lines();//���� �������� ������
	void del_line(int posit);//��������� ������
	void change_places(int pos1,int pos2);//������� ������
	string return_line(int l_pos);//�������� ������ �� ������� �������
	bool find_rhyme_abab();//���� ����
	bool find_rhyme_vhv(char h);//���� ���
	bool find_rhyme_hdd(char h);//���� ���
	bool find_rhyme_zez(char e);//���� ���
	friend std::ostream& operator << (std::ostream &out, const Couplet &C);//�������������� ����
	friend std::istream& operator >> (std::istream &in, Couplet &C);//�������������� ���
	private:
	vector <string> text;
	int pos;
	int size;
};

#endif
