// MergeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "BSort.h"
#include "MergeDialog.h"
#include "afxdialogex.h"


// MergeDialog dialog

IMPLEMENT_DYNAMIC(MergeDialog, CDialogEx)

MergeDialog::MergeDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(MergeDialog::IDD, pParent)
{
	LSize= RSize= MSize=0;
    CLeft=CRight= -1;
}

MergeDialog::~MergeDialog()
{
}

void MergeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MergeDialog, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void MergeDialog::OnPaint()
{
    CPaintDC dc(this);
    int i,x,y;
    CString str;

    dc.TextOut(10,20, _T("Left Array: "));
    x = 140;
    y = 10;
    for(i=0;i<LSize;i++){
        CRect rect(x,y,x+40,y+40);
        if(i==CLeft){
            CBrush brush(RGB(255,255,0));
            dc.FillRect(&rect,&brush);
        }else{
            CBrush brush(RGB(100,180,255));
            dc.FillRect(&rect,&brush);
        }

        dc.Rectangle(&rect);
        str.Format(_T("%d"), LArr[i]);
        dc.DrawText(str,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
        x +=60;
    }

    dc.TextOut(10,150,_T("Right Array: "));
    x=y=140;
    for(i=0;i<RSize;i++){
        CRect rect(x,y,x+40,y+40);
        if(i==CRight){
            CBrush brush(RGB(255,255,0));
            dc.FillRect(&rect,&brush);
        }else{
            CBrush brush(RGB(255,150,150));
            dc.FillRect(&rect, &brush);
        }
        dc.Rectangle(&rect);
        str.Format(_T("%d"),RArr[i]);
        dc.DrawText(str,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
        x+= 60;
    }

    dc.TextOut(10,300,_T("Merged: "));
    x=140;	y=290;
    for(i=0;i<MSize;i++){
        CRect rect(x,y,x+40,y+40);
        CBrush brush(RGB(120,255,120));

        dc.FillRect(&rect,&brush);
        dc.Rectangle(&rect);
        str.Format(_T("%d"),MArr[i]);
        dc.DrawText(str,&rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
        x+=60;
    }
}

void MergeDialog::SetArr(int L[],int n1,int R[],int n2){
    int i;
    LSize =n1;
    RSize =n2;
    MSize =0;
    CLeft=CRight =-1;

    for(i=0;i< n1;i++){
        LArr[i]=L[i];
    }
    for(i=0;i<n2;i++)
    {
		RArr[i]=R[i];
    }
    Invalidate();
    UpdateWindow();
}

void MergeDialog::SetComp(int LIndex,int RIndex)
{
    CLeft=LIndex;
    CRight=RIndex;
    Invalidate();
    UpdateWindow();
}

void MergeDialog::AddMValue(int value){
    if(MSize <10)
    {
        MArr[MSize]=value;
        MSize++;
    }
    Invalidate();
    UpdateWindow();
}

void MergeDialog::RMerge(){
    LSize=RSize=MSize=0;
    CLeft=CRight=-1;
    Invalidate();
    UpdateWindow();
}