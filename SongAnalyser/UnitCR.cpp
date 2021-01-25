//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitCR.h"
#include "Song.h"
#include <iostream>
#include <fstream>
#include <string>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Label4Click(TObject *Sender)
{
	try
	{
		if(Edit1->Text.IsEmpty()||Edit2->Text.IsEmpty()||MemoWr->Lines->Text.IsEmpty())
		{
			throw 2;
		}
	}
	catch(int err)
	{
		ShowMessage("Ви не ввели потрібні дані.");
		return;
	}
	if( SaveTextFileDialog1->Execute())
	 {
		MemoWr->Lines->SaveToFile(SaveTextFileDialog1->FileName);
		std::ofstream file;
		wstring filepath = SaveTextFileDialog1->FileName.c_str();
		file.open(filepath.c_str(), ios::app);
		string t;
		AnsiString n;
		n=Edit2->Text;
		t=n.c_str();
		file<<t<<std::endl;
		n=Edit1->Text;
		t=n.c_str();
		file<<t<<std::endl;
		file.close();
		Memo2->Lines->Add("Файл збережено.");
	 }
}
//---------------------------------------------------------------------------

