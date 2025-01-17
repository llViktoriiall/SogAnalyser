//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitON.h"
#include "Song.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
Song S;
Couplet *Coups;
int c_num=0;//������� �������
int l_num=0;//������� �����

//����� ��� ������ ������ � �����������
bool sym =false;
bool word=false;
bool line=false;
bool coup=false;
bool ch_coup=false;
bool ch_line=false;
bool change=false;
bool labeled=false;

//����� ��� ������ ����
bool song=false;
bool sonet=false;

wstring filepath;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::N3Click(TObject *Sender)
{
	if(OpenTextFileDialog1->Execute())
	{
		MemoWr->Lines->LoadFromFile( OpenTextFileDialog1->FileName );
	}
	filepath = OpenTextFileDialog1->FileName.c_str();//����������� ����� �� �����, ��� �������� ���� �������
	S.set_num_couplet(filepath);
	c_num=S.get_num_couplet();
	Coups = new Couplet [c_num];//��������� ����� �������
	MemoWr->Lines->Clear();
	S.set_author(filepath);
	S.set_name(filepath);
	S.read(Coups,filepath);//���������� � ����� ����
	vector <string> test;
	test=Coups[0].get_text();
	try//�������� �� � ����� ������ �������
	{
		if(c_num==1)
		{
			throw 0;
		}
	}
	catch(int err)
	{
		ShowMessage("����� ���� �� ������� �� ������� ��� �� ��������.");
		return;
	}
	for(int i =0;i<c_num;++i)
	{
		Coups[i].set_pos(i+1);
		//����������� �������������� ���������, ��� ��������, �� ���� ��������
		std::cin>>Coups[i];
		std::cout<<Coups[i];
	}
	Shape1->Visible=true;
	Label29->Visible=true;
	MemoWr->Visible=true;
	Label30->Visible=false;
	song = true;//���� ��� ����������, ������ �������� ������ �� ���������

	//�������� �� ����� ��������� � ����� ���������
	//��������� - 4 ������� 14 ����� �� �������(������������ ����) � ��� �� �������(��������� ����), ����: ���� ���� ��� ���
	//!!!��� �� ��� ���� ϲ���� ���� �� �� �������, �� � ���� �������� ���� �� ������² ��ʲ������,�� ������ �������� �����
	//��������� - 4 ������� 14 ����� �� ������� � ��� �� �������, ����: ���� ���� ��� ���
	if(c_num==4)//�������
	{
		l_num=0;
		for(int i =0;i<4;++i)
		{
				l_num+=Coups[i].get_size();
        }
		l_num-=4;
		if(l_num==14)//�����
		{
			int n1,n2,n3,n4;
			n1=Coups[0].get_size();
			n2=Coups[1].get_size();
			n3=Coups[2].get_size();
			n4=Coups[3].get_size();
			if(n1==5&&n2==5&&n3==4&&n4==4)//������� � �������
			{
				if(Coups[0].find_rhyme_abab()&&Coups[1].find_rhyme_abab())//����
				{
					string temp_line;
					temp_line=Coups[3].return_line(0);
					int temp_length=temp_line.size()-1;
					char h=temp_line[temp_length];
					if(Coups[2].find_rhyme_vhv(h))
					{
						string temp_line;
						temp_line=Coups[2].return_line(1);
						int temp_length=temp_line.size()-1;
						char h=temp_line[temp_length];
						if(Coups[3].find_rhyme_hdd(h))
						{
							ShowMessage("�� ��������� �����.");
							sonet = true;
						}
					}
					temp_line=Coups[3].return_line(1);
					temp_length=temp_line.size()-1;
					char e=temp_line[temp_length];
					if(Coups[2].find_rhyme_zez(e)&&Coups[3].find_rhyme_zez(e))//����
					{
						ShowMessage("�� ��������� �����.");
						sonet = true;
					}
				}

			}
		}
	}

	//����� � ����� 5 ������� 15 ����� �� ������� � ��� �� ������� � � ���� ������ �� ���� ����� ����� ��������, ����: ���� ���� ��� ��� + ���� �����
	if(c_num==5)
	{
		l_num=0;
		for(int i =0;i<5;++i)
		{
				l_num+=Coups[i].get_size();
		}
		l_num-=5;
		if(l_num==15)
		{
			int n1,n2,n3,n4,n5;
			n1=Coups[0].get_size();
			n2=Coups[1].get_size();
			n3=Coups[2].get_size();
			n4=Coups[3].get_size();
			n5=Coups[4].get_size();
			if(n1==5&&n2==5&&n3==4&&n4==4&&n5==2)
			{
				if(Coups[0].find_rhyme_abab())
				{
					string temp_line;
					temp_line=Coups[3].return_line(0);
					int temp_length=temp_line.size()-1;
					char h=temp_line[temp_length];
					if(Coups[2].find_rhyme_vhv(h))
					{
						string temp_line;
						temp_line=Coups[2].return_line(1);
						int temp_length=temp_line.size()-1;
						char h=temp_line[temp_length];
						if(Coups[3].find_rhyme_hdd(h))
						{
							ShowMessage("�� ����� � �����.");
							sonet = true;
						}
					}
				}

			}
		}
	}

	//���������� ����� - ����� ��� ����� �������, ����� ��� �� ����
	if(c_num==3)
	{
		l_num=0;
		for(int i =0;i<3;++i)
		{
				l_num+=Coups[i].get_size();
		}
		l_num-=3;
		if(l_num==10)
		{
			int n1,n2,n3;
			n1=Coups[0].get_size();
			n2=Coups[1].get_size();
			n3=Coups[2].get_size();
			if(n1==5&&n2==4&&n3==4)
			{
				if(Coups[0].find_rhyme_abab())
				{
					string temp_line;
					temp_line=Coups[2].return_line(0);
					int temp_length=temp_line.size();
					char h=temp_line[temp_length];
					if(Coups[1].find_rhyme_vhv(h))
					{
						string temp_line;
						temp_line=Coups[2].return_line(1);
						int temp_length=temp_line.size()-1;
						char h=temp_line[temp_length];
						if(Coups[2].find_rhyme_hdd(h))
						{
							ShowMessage("�� ���������� �����.");
							sonet = true;
						}
					}
				}

			}
		}
	}

	//������������ - �������� �������, ���� �������
	if(c_num==4)
	{
		l_num=0;
		for(int i =0;i<4;++i)
		{
				l_num+=Coups[i].get_size();
		}
		l_num-=4;
		if(l_num==14)
		{
			int n1,n2,n3,n4;
			n1=Coups[0].get_size();
			n2=Coups[1].get_size();
			n3=Coups[2].get_size();
			n4=Coups[3].get_size();
			if(n1==4&&n2==4&&n3==5&&n4==5)
			{
                string temp_line;
				temp_line=Coups[1].return_line(1);
				int temp_length=temp_line.size()-1;
				char h=temp_line[temp_length];
				if(Coups[0].find_rhyme_vhv(h))
				{
					string temp_line;
					temp_line=Coups[0].return_line(1);
					int temp_length=temp_line.size()-1;
					char h=temp_line[temp_length];
					if(Coups[1].find_rhyme_hdd(h))
					{
						 if(Coups[2].find_rhyme_abab()&&Coups[3].find_rhyme_abab())
						{
							ShowMessage("�� ������������ �����.");
							sonet = true;
						}
					}
				}
			}
		}
	}
	if(!sonet)
	{
		ShowMessage("�� �� �����.");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label6Click(TObject *Sender)
{
	Label24->Visible=true;
	Label23->Visible=true;
	Label26->Visible=false;
	Label27->Visible=false;
	Edit1->Visible=true;
	Edit2->Visible=true;
	Label28->Visible=true;
	sym =true;
	word=false;
	line=false;
	coup=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label5Click(TObject *Sender)
{
	//������ ���������
	Label24->Visible=true;
	Label23->Visible=false;
	Label26->Visible=false;
	Label27->Visible=false;
	Edit1->Visible=true;
	Edit2->Visible=false;
	Label28->Visible=true;
	sym = true;
	word=false;
	line=false;
	coup=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label2Click(TObject *Sender)
{
	//������ ���������
  	Label7->Visible=false;
	Label8->Visible=false;
	Label9->Visible=false;
	Label10->Visible=false;
	Label5->Visible=true;
	Label5->Top=110;
	Label5->Left=20;
	Label6->Visible=true;
	Label6->Top=140;
	Label6->Left=20;
	Label3->Top=180;
	Label3->Left=20;
	Label4->Top=220;
	Label4->Left=20;
	Label24->Visible=false;
	Label23->Visible=false;
	Label26->Visible=false;
	Label27->Visible=false;
	Edit1->Visible=false;
	Edit2->Visible=false;
	Label28->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::N11Click(TObject *Sender)
{
	//������ ���������
	try
	{
		if(!song)
		{
			throw 0;
		}
	}
	catch(int err)
	{
		ShowMessage("�������� �������� �����.");
		return;
	}
//search
	Label1->Visible=true;
	Label2->Visible=true;
	Label3->Visible=true;
	Label4->Visible=true;
	Label11->Visible=true;
	Label12->Visible=true;
	Label13->Visible=true;
	Label16->Visible=true;
	Memo1->Visible=true;
	Label31->Visible=true;
//change
	Label14->Visible=false;
	Label15->Visible=false;
    Label17->Visible=false;
	Label19->Visible=false;
	Label20->Visible=false;
	Label18->Visible=false;
	Memo2->Visible=false;
	Label32->Visible=false;
	Label21->Visible=false;
	Edit3->Visible=false;
	Label22->Visible=false;
	Edit4->Visible=false;
	Label25->Visible=false;
	Edit5->Visible=false;
	Edit6->Visible=false;
	Label22->Visible=false;

	Memo1->Lines->Clear();
	Memo1->Lines->Add("����� ������ ��������");
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Label3Click(TObject *Sender)
{
	//������ ���������
	Label5->Visible=false;
	Label6->Visible=false;
	Label9->Visible=false;
	Label10->Visible=false;
	Label7->Visible=true;
	Label7->Top=150;
	Label7->Left=20;
	Label8->Visible=true;
	Label8->Top=180;
	Label8->Left=20;
	Label3->Top=110;
	Label3->Left=20;
	Label4->Top=220;
	Label4->Left=20;
	Label24->Visible=false;
	Label23->Visible=false;
	Label26->Visible=false;
	Label27->Visible=false;
	Edit1->Visible=false;
	Edit2->Visible=false;
	Label28->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label4Click(TObject *Sender)
{
	//������ ���������
	Label5->Visible=false;
	Label6->Visible=false;
	Label7->Visible=false;
	Label8->Visible=false;
	Label9->Visible=true;
	Label9->Top=190;
	Label9->Left=20;
	Label10->Visible=true;
	Label10->Top=220;
	Label10->Left=20;
	Label4->Top=150;
	Label4->Left=20;
	Label3->Top=110;
	Label3->Left=20;
	Label24->Visible=false;
	Label23->Visible=false;
	Label26->Visible=false;
	Label27->Visible=false;
	Edit1->Visible=false;
	Edit2->Visible=false;
	Label28->Visible=false;

}
//---------------------------------------------------------------------------
void __fastcall TForm2::Label7Click(TObject *Sender)
{
	//������ ���������
	Label24->Visible=false;
	Label23->Visible=false;
	Label26->Visible=false;
	Label27->Visible=true;
	Edit1->Visible=true;
	Edit2->Visible=false;
	Label28->Visible=true;
	sym =false;
	word=true;
	line=false;
	coup=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label8Click(TObject *Sender)
{
	//������ ���������
	Label24->Visible=false;
	Label23->Visible=true;
	Label26->Visible=false;
	Label27->Visible=true;
	Edit1->Visible=true;
	Edit2->Visible=true;
	Label28->Visible=true;
    sym =false;
	word=true;
	line=false;
	coup=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label9Click(TObject *Sender)
{
	//������ ���������
	Label24->Visible=false;
	Label23->Visible=false;
	Label26->Visible=true;
	Label27->Visible=false;
	Label28->Visible=true;
	Edit1->Visible=true;
	Edit2->Visible=false;
    sym =false;
	word=false;
	line=true;
	coup=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label10Click(TObject *Sender)
{
	//������ ���������
	Label24->Visible=false;
	Label23->Visible=true;
	Label26->Visible=true;
	Label27->Visible=false;
	Edit1->Visible=true;
	Edit2->Visible=true;
	Label28->Visible=true;
    sym =false;
	word=false;
	line=true;
	coup=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Label29Click(TObject *Sender)
{
	//������� ����
	if(!labeled)
	{
		Shape1->Pen->Color=clSkyBlue;
		labeled=true;
        MemoWr->Lines->Text="";
		for(int i =0;i<c_num;++i)
		{
			Coups[i].print_labeled();
		}
	}
	else
	{
		Shape1->Pen->Color=clBtnShadow;
		labeled=false;
        MemoWr->Lines->Text="";
		for(int i =0;i<c_num;++i)
		{
			Coups[i].print();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label28Click(TObject *Sender)
{
	try
	{
		if(Edit1->Text.IsEmpty())
		{
			throw 1;
		}
	}
	catch(int err)
	{
		ShowMessage("�� �� ����� ������� ����.");
		return;
	}
	if(sym)//����� �������
	{
		char finder;
		finder=Edit1->Text[1];
		if(coup)//� ������
		{
			try
			{
				if(Edit2->Text.IsEmpty())
				{
					throw 1;
				}
			}
			catch(int err)
			{
				ShowMessage("�� �� ����� ������� ����.");
				return;
			}
			char test1;
			test1=Edit2->Text[1];
			try
			{
				if(!isdigit(test1))
				{
					throw 2;
				}
			}
			catch(int err)
			{
				ShowMessage("�� ����� ������ ����.");
				return;
			}
			int test_1,test_2;
			test_1=StrToInt(Edit2->Text);
			int test_size;
			int pos;
			pos=StrToInt(Edit2->Text);
			test_size=Coups[pos].get_size();
			try
			{
				if(test_1>test_size||test_1<1)
				{
					throw 2;
				}
			}
			catch(int err)
			{
				ShowMessage("�� ������ �� ��� ������� �� ����.");
				return;
			}
			Coups[pos-1].find_char(finder);
		}
		else//� ����
		{
			for(int i =0;i<c_num;++i)
			{
				Coups[i].find_char(finder);
			}
		}
	}
	if(word)//����� �����
	{
		char *finder;
		char test1;
		test1==Edit1->Text[1];
		try
		{
			if(isdigit(test1)||test1==' ')
			{
				throw 2;
			}
		}
		catch(int err)
		{
			ShowMessage("�� ����� ������ ����.");
			return;
		}
		int leng = Edit1->GetTextLen();
		AnsiString ed_txt = Edit1->Text;
		finder=ed_txt.c_str();
		if(coup)//� ������
		{
			try
			{
				if(Edit2->Text.IsEmpty())
				{
					throw 1;
				}
			}
			catch(int err)
			{
				ShowMessage("�� �� ����� ������� ����.");
				return;
			}
			char test1;
			test1=Edit2->Text[1];
			try
			{
				if(!isdigit(test1))
				{
					throw 2;
				}
			}
			catch(int err)
			{
				ShowMessage("�� ����� ������ ����.");
				return;
			}
			int test_1,test_2;
			test_1=StrToInt(Edit2->Text);
			int test_size;
			int pos;
			pos=StrToInt(Edit2->Text);
			test_size=Coups[pos].get_size();
			try
			{
				if(test_1>test_size||test_1<1)
				{
					throw 2;
				}
			}
			catch(int err)
			{
				ShowMessage("�� ������ �� ��� ������� �� ����.");
				return;
			}

			Coups[pos-1].find_word(leng,finder);
		}
		else //� ����
		{
			for(int i =0;i<c_num;++i)
			{
				Coups[i].find_word(leng,finder);
			}
		}
	}
	if(line)//����� ������
	{
		string finder;
        char test1;
		test1==Edit1->Text[1];
		try
		{
			if(isdigit(test1)||test1==' ')
			{
				throw 2;
			}
		}
		catch(int err)
		{
			ShowMessage("�� ����� ������ ����.");
			return;
		}
		AnsiString str;
		str=Edit1->Text;
		finder=str.c_str();
		if(coup)//� ������
		{
            try
			{
				if(Edit2->Text.IsEmpty())
				{
					throw 1;
				}
			}
			catch(int err)
			{
				ShowMessage("�� �� ����� ������� ����.");
				return;
			}
			char test1;
			test1=Edit2->Text[1];
			try
			{
				if(!isdigit(test1))
				{
					throw 2;
				}
			}
			catch(int err)
			{
				ShowMessage("�� ����� ������ ����.");
				return;
			}
			int test_1,test_2;
			test_1=StrToInt(Edit2->Text);
			int test_size;
			int pos;
			pos=StrToInt(Edit2->Text);
			test_size=Coups[pos].get_size();
			try
			{
				if(test_1>test_size||test_1<1)
				{
					throw 2;
				}
			}
			catch(int err)
			{
				ShowMessage("�� ������ �� ��� ������� �� ����.");
				return;
			}
			Coups[pos-1].find_string(finder);
		}
		else//� ����
		{
			for(int i =0;i<c_num;++i)
			{
				Coups[i].find_string(finder);
			}
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Label12Click(TObject *Sender)
{
    Shape1->Pen->Color=clBtnShadow;
	labeled=false;
	MemoWr->Lines->Text="";
	for(int i =0;i<c_num;++i)
	{
		Coups[i].show_first_lines();
	}
	Memo1->Lines->Add("����� ����� ��������");
	Shape1->Pen->Color=clBtnShadow;
	labeled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label13Click(TObject *Sender)
{
    Shape1->Pen->Color=clBtnShadow;
	labeled=false;
	MemoWr->Lines->Text="";
	for(int i =0;i<c_num;++i)
	{
		Coups[i].show_last_lines();
	}
	Memo1->Lines->Add("������� ����� ��������");
    Shape1->Pen->Color=clBtnShadow;
	labeled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label31Click(TObject *Sender)
{
	S.set_num_couplet(filepath);
	c_num=S.get_num_couplet();
    delete[] Coups;
	Coups = new Couplet [c_num];//��������� ����� �������
	MemoWr->Lines->Clear();
	S.set_author(filepath);
	S.set_name(filepath);
	S.read(Coups,filepath);//���������� � ����� ����
	MemoWr->Lines->Text="";
	for(int i =0;i<c_num;++i)
	{
		Coups[i].print();
	}
	Shape1->Pen->Color=clBtnShadow;
	labeled=false;
}
//---------------------------------------------------------------------------


void __fastcall TForm2::N10Click(TObject *Sender)
{
	//������ ���������
	try
	{
		if(!song)
		{
			throw 0;
		}
	}
	catch(int err)
	{
		ShowMessage("�������� �������� �����.");
		return;
	}
//search
	Label1->Visible=false;
	Label2->Visible=false;
	Label3->Visible=false;
	Label4->Visible=false;
	Label11->Visible=false;
	Label12->Visible=false;
	Label13->Visible=false;
	Label16->Visible=false;
	Memo1->Visible=false;
	Label31->Visible=false;
	Label24->Visible=false;
	Label23->Visible=false;
	Label26->Visible=false;
	Label27->Visible=false;
	Edit1->Visible=false;
	Edit2->Visible=false;
	Label28->Visible=false;
	Edit5->Visible=true;
	Edit6->Visible=true;
//change
	Label14->Visible=true;
	Label15->Visible=true;
	Label19->Visible=true;
	Label20->Visible=true;
	Label18->Visible=true;
	Memo2->Visible=true;
	Edit5->Visible=false;
	Edit6->Visible=false;

	Memo2->Lines->Clear();
	Memo2->Lines->Add("����� ����������� ��������");
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Label15Click(TObject *Sender)
{
	//������ ���������
	Label32->Visible=true;
	Label21->Visible=true;
	Edit3->Visible=true;
	Label22->Visible=true;
	Label17->Visible=true;
	Edit4->Visible=false;
	Edit5->Visible=true;
	Edit6->Visible=true;
	Label25->Visible=false;
	ch_coup=false;
	ch_line=true;
	Label21->Top=380;
	Label22->Top=310;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label19Click(TObject *Sender)
{
    //������ ���������
	Label25->Visible=true;
	Label21->Visible=true;
	Label22->Visible=true;
	Label25->Top=150;
	Label22->Top=225;
	Label21->Top=300;
	Edit3->Visible=true;
	Edit4->Visible=true;
	Edit6->Visible=false;
	Label32->Visible=false;
	Label17->Visible=false;
	ch_coup=true;
	ch_line=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label21Click(TObject *Sender)
{
	int c_pos;
	int l_pos;
	if(ch_line)
	{
		try
		{
			if(Edit5->Text.IsEmpty()||Edit3->Text.IsEmpty())
			{
				throw 2;
			}
		}
		catch(int err)
		{
			ShowMessage("�� �� ����� ������� ����.");
			return;
		}
		char test1, test2;
		test1=Edit3->Text[1];
		test2=Edit5->Text[1];
		try
		{
			if(!isdigit(test1)||!isdigit(test2))
			{
				throw 2;
			}
		}
		catch(int err)
		{
			ShowMessage("�� ����� ������ ����.");
			return;
		}
		int test_1,test_2;
		test_1=StrToInt(Edit3->Text);
		test_2=StrToInt(Edit5->Text);
		int test_size;
		c_pos=StrToInt(Edit5->Text);
		--c_pos;
		test_size=Coups[c_pos].get_size();
		try
		{
			if(test_1>test_size||test_2>c_num||test_1<1||test_2<1)
			{
				throw 2;
			}
		}
		catch(int err)
		{
			ShowMessage("�� ������ �� ��� ������� �� ����.");
			return;
		}
	   l_pos=StrToInt(Edit3->Text);
	   Coups[c_pos].del_line(l_pos);
	   MemoWr->Lines->Text="";
	   for(int i =0;i<c_num;++i)
	   {
			Coups[i].print();
	   }
	   Memo2->Lines->Add("������ ��������.");
	}
	if(ch_coup)
	{
		try
		{
			if(Edit3->Text.IsEmpty())
			{
				throw 3;
			}
		}
		catch(int err)
		{
			ShowMessage("�� �� ����� ������� ����.");
			return;
		}
		char test1;
		test1=Edit3->Text[1];
		try
		{
			if(!isdigit(test1))
			{
				throw 2;
			}
		}
		catch(int err)
		{
			ShowMessage("�� ����� ������ ����.");
			return;
		}
		int test_1;
		test_1=StrToInt(Edit3->Text);
		int test_size;
		try
		{
			if(test_1>c_num||test_1<1)
			{
				throw 2;
			}
		}
		catch(int err)
		{
			ShowMessage("�� ������ �� ��� ����.");
			return;
		}
		c_pos=StrToInt(Edit3->Text);
		Coups[c_pos-1].~Couplet();
		MemoWr->Lines->Text="";
		for(int i =0;i<c_num;++i)
		{
			Coups[i].print();
		}
		--c_num;
        Memo2->Lines->Add("������ ��������.");
	}
	Shape1->Pen->Color=clBtnShadow;
	labeled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label22Click(TObject *Sender)
{
	int c_pos;
	int l_pos;
	int l_new_pos;
	int c_new_pos;
	if(ch_line)
	{
		try
		{
			if(Edit5->Text.IsEmpty()||Edit3->Text.IsEmpty()||Edit6->Text.IsEmpty())
			{
				throw 2;
			}
		}
		catch(int err)
		{
			ShowMessage("�� �� ����� ������� ����.");
			return;
		}
		char test1, test2, test3;
		test1=Edit3->Text[1];
		test2=Edit5->Text[1];
		test3=Edit6->Text[1];
		try
		{
			if(!isdigit(test1)||!isdigit(test2)||!isdigit(test3))
			{
				throw 2;
			}
		}
		catch(int err)
		{
			ShowMessage("�� ����� ������ ����.");
			return;
		}
		int test_1,test_2,test_3;
		test_1=StrToInt(Edit3->Text);
		test_2=StrToInt(Edit5->Text);
		test_3=StrToInt(Edit6->Text);
		int test_size=4;
		c_pos=StrToInt(Edit5->Text);
		c_pos--;
		test_size=Coups[c_pos].get_size();
		try
		{
			if(test_1>test_size||test_2>c_num||test_1<1||test_2<1||test_3>test_size||test_3<1)
			{
				throw 2;
			}
		}
		catch(int err)
		{
			ShowMessage("�� ������ �� ��� ������� �� ����.");
			return;
		}
		l_pos=StrToInt(Edit3->Text)-1;
		l_new_pos=StrToInt(Edit6->Text)-1;
		Coups[c_pos].change_places(l_pos,l_new_pos);
		MemoWr->Lines->Text="";
		for(int i =0;i<c_num;++i)
		{
			Coups[i].print();
		}
		Memo2->Lines->Add("����� ������� ������.");
	}
	if(ch_coup)
	{
		try
		{
			if(Edit5->Text.IsEmpty()||Edit3->Text.IsEmpty())
			{
				throw 2;
			}
		}
		catch(int err)
		{
			ShowMessage("�� �� ����� ������� ����.");
			return;
		}
		char test1, test2;
		test1=Edit3->Text[1];
		test2=Edit5->Text[1];
        try
		{
			if(!isdigit(test1)||!isdigit(test2))
			{
				throw 2;
			}
		}
		catch(int err)
		{
			ShowMessage("�� ����� ������ ����.");
			return;
		}
        int test_1;
		test_1=StrToInt(Edit3->Text);
		int test_size;
		try
		{
			if(test_1>c_num||test_1<1)
			{
				throw 2;
			}
		}
		catch(int err)
		{
			ShowMessage("�� ������ �� ��� ����.");
			return;
		}
		c_pos=StrToInt(Edit3->Text)-1;
		c_new_pos=StrToInt(Edit5->Text)-1;
		vector <string> temp1;
		temp1=Coups[c_pos].get_text();
		vector <string> temp2;
		temp2=Coups[c_new_pos].get_text();
		Coups[c_pos].set_text(temp2);
		Coups[c_new_pos].set_text(temp1);
		MemoWr->Lines->Text="";
		for(int i =0;i<c_num;++i)
		{
			Coups[i].print();
		}
        Memo2->Lines->Add("������� ������� ������.");
	}
	Shape1->Pen->Color=clBtnShadow;
	labeled=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::N4Click(TObject *Sender)
{
	try
	{
		if(!song)
		{
			throw 0;
		}
	}
	catch(int err)
	{
		ShowMessage("�������� �������� �����.");
		return;
	}
	if( SaveTextFileDialog1->Execute() )
	 {
	  	MemoWr->Lines->SaveToFile( SaveTextFileDialog1->FileName );
	 }
}
//---------------------------------------------------------------------------



void __fastcall TForm2::N7Click(TObject *Sender)
{
	ShowMessage("������� ���������� RenRin.\n�������� ��������: LerellaSS@gmail.com");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::N6Click(TObject *Sender)
{
	ShowMessage("��������� �����: 4+4+3+3 ���� ���� ��� ���\n����� � �����: 4+4+3+3+1 ���� ���� ��� ��� �\n��������� �����: 4+4+3+3 ���� ���� ��� ���\n���������������: 4+3+3 ���� ��� ���\n������������ �����: 3+3+4+4 ��� ��� ���� ����");
}
//---------------------------------------------------------------------------


