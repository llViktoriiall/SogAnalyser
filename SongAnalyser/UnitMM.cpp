//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitMM.h"
#include "UnitCR.h"
#include "UnitON.h"
#include "UnitHelp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Label3Click(TObject *Sender)
{
	Form3->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label4Click(TObject *Sender)
{
	Form2->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label5Click(TObject *Sender)
{
	Form4->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label6Click(TObject *Sender)
{
	Form1->Close();
	Form2->Close();
	Form3->Close();
	Form4->Close();
}
//---------------------------------------------------------------------------

