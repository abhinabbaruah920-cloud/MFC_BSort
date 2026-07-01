
// BSortDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BSort.h"
#include "BSortDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <sstream>
#include <string>
#include <atlconv.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBSortDlg dialog




CBSortDlg::CBSortDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBSortDlg::IDD, pParent)
{

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBSortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBSortDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CBSortDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_IMPORT, &CBSortDlg::OnBnClickedImport)
END_MESSAGE_MAP()


// CBSortDlg message handlers

BOOL CBSortDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.
	c1=c2=s1=s2=-1;
	size=0;
	D.Create(IDD_DIALOG1,this);
	D.ShowWindow(SW_SHOW);
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBSortDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBSortDlg::OnPaint()
{
	CPaintDC dc(this);
	int x=20;
	for(int i=0;i<size;i++){
		CBrush brush;
		if(i==s1 || i==s2){
			brush.CreateSolidBrush(RGB(255,155,0));}
		else if(i==c1 || i==c2){
			brush.CreateSolidBrush(RGB(0,255,0));
		}else{
			brush.CreateSolidBrush(RGB(0,0,255));	
		}
		dc.SelectObject(&brush);
		int h = arr[i]*2;
		dc.Rectangle(x,300-h,x+30,300);
		x+=40;
	}



	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


void CBSortDlg::Processmsg(){
	MSG msg;
	while(PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
	DispatchMessage(&msg);
	}
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBSortDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBSortDlg::OnBnClickedButton1()
{
	D.AddNo(arr,size);
	for(int i=0;i<size-1;i++){
		for(int j=0;j<size-i-1;j++){
			c1=j;
			c2=j+1;
			s1=s2=-1;
			Invalidate();
			UpdateWindow();
			Processmsg();
			Sleep(100);

			if(arr[j]>arr[j+1]){
				s1=j;
				s2=j+1;
				Invalidate();
				UpdateWindow();
				Processmsg();
				Sleep(100);
				int temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
				s1=j;
				s2=j+1;
				D.AddNo(arr,size);
				Invalidate();
				UpdateWindow();
				Processmsg();
				Sleep(100);
			}
		}
	}
	s1=s2=c1=c2=-1;
	Invalidate();
	UpdateWindow();
	Processmsg();
	Sleep(100);
}


void CBSortDlg::OnBnClickedImport()
{
    CFileDialog dlg(TRUE,_T("csv"),NULL,OFN_FILEMUSTEXIST,_T("CSV Files (*.csv)|*.csv||"));
    if(dlg.DoModal()==IDOK){
        CString filename= dlg.GetPathName();
        CStdioFile file;
    if(!file.Open(filename,CFile::modeRead)){
        AfxMessageBox(_T("Cannot open file."));
            return;
        }
	CString line;
	size = 0;
		while(file.ReadString(line)){
			line.Trim();
		    int pos=0;
		    CString token;
	    while(!(token=line.Tokenize(_T(","),pos)).IsEmpty()){
        token.Trim();
        if(!token.IsEmpty()&&size <100){
            arr[size++] = _ttoi(token);
        }
    }
}
        file.Close();
    Invalidate();
    UpdateWindow();
    }
}



