// DataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BSort.h"
#include "DataDlg.h"
#include "afxdialogex.h"


// DataDlg dialog

IMPLEMENT_DYNAMIC(DataDlg, CDialogEx)

DataDlg::DataDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(DataDlg::IDD, pParent)
{

}

DataDlg::~DataDlg()
{
}

void DataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST1,list);
}


BEGIN_MESSAGE_MAP(DataDlg, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &DataDlg::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// DataDlg message handlers


void DataDlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
}

void DataDlg::AddNo(int arr[],int size){
	CString str;
	for(int i=0;i<7;i++){
		CString temp;
		temp.Format(_T("%d"),arr[i]);
		str+=temp+(_T(" "));
	}
	list.AddString(str);
	list.SetCurSel(list.GetCount()-1);
}
