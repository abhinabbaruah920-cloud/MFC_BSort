
// BSortDlg.cpp : implementation file
//
#include "stdafx.h"
#include "Resource.h"
#include "BSort.h"
#include "BSortDlg.h"
#include "afxdialogex.h"
#include <atlconv.h>
// Header Files for taking csv file as input
#include <fstream>
#include <sstream>
#include <string>
// Merge Dialog 
#include "MergeDialog.h"


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
	DDX_Control(pDX,IDC_COMBO1,comboAlgo); // DDX control for ComboBox
}

BEGIN_MESSAGE_MAP(CBSortDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CBSortDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_IMPORT, &CBSortDlg::OnBnClickedImport)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CBSortDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CBSortDlg message handlers

BOOL CBSortDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	c1=c2=s1=s2=-1; //Initialize CPaintDC variables
	size=0; // Initialize array size
	SetWindowPos(NULL,700,110,0,0,SWP_NOSIZE|SWP_NOZORDER);
	D.Create(IDD_DATADIALOG,this);				// Initialize Data Dialog box 
	D.SetWindowPos(NULL,100,110,0,0,SWP_NOSIZE|SWP_NOZORDER);
	D.ShowWindow(SW_SHOW);						// Show Data Dialog window function
	MD.Create(IDD_MERGEDIALOG,this);			// Creating the merge Dialog

	// Adding Strings to ComboBox
	comboAlgo.AddString(_T("SELECT ALGO"));			
	comboAlgo.AddString(_T("Bubble Sort"));
	comboAlgo.AddString(_T("Selection Sort"));
	comboAlgo.AddString(_T("Insertion Sort"));
	comboAlgo.AddString(_T("Quick Sort"));
	comboAlgo.AddString(_T("Merge Sort"));
	comboAlgo.SetCurSel(0);		// Setting "SELECT ALGO" as the first option


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

void CBSortDlg::OnPaint()			// OnPaint function
{
	CPaintDC dc(this);
	int x=30;
	for(int i=0;i<size;i++){
		CBrush brush;
		if(i==s1 || i==s2){
			brush.CreateSolidBrush(RGB(255,155,0));}		// ORANGE when Swapping
		else if(i==c1 || i==c2){
			brush.CreateSolidBrush(RGB(0,255,0));			// GREEN when Comparing
		}else{
			brush.CreateSolidBrush(RGB(0,0,255));			// Normal BLUE
		}
		dc.SelectObject(&brush);		// Selecting brush to Paint
		int h = arr[i]*2;

		// Defining the Bar Dimensions 
		dc.Rectangle(x,300-h,x+20,300);
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


void CBSortDlg::Processmsg(){		// Extending Processmsg Function to handle Window messages
	MSG msg;
	while(PeekMessage(&msg,NULL,0,0,PM_REMOVE)){		// Removing messages from Window Message Queue
	DispatchMessage(&msg);
	}
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBSortDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBSortDlg::OnBnClickedButton1()		// START BUTTON
{
	if(size==0){
		AfxMessageBox(_T("Import CSV file first !!"));
		return;
	}
int choice = comboAlgo.GetCurSel();

	if(size!=0 && choice ==0){
		AfxMessageBox(_T("Please select sorting algorithm"));
		return;
	}
		switch(choice){
			case 1:
				D.list.ResetContent();
				MD.ShowWindow(SW_HIDE);
				bubble();
				break;
			case 2:
				D.list.ResetContent();
				MD.ShowWindow(SW_HIDE);
				selection();
				break;
			case 3:
				D.list.ResetContent();
				MD.ShowWindow(SW_HIDE);
				insertion();
				break;
			case 4:
				D.list.ResetContent();
				MD.ShowWindow(SW_HIDE);
				quick();
				break;
			case 5:
				D.list.ResetContent();
				MD.SetWindowPos(NULL,300,600,0,0,SWP_NOSIZE|SWP_NOZORDER);
				MD.ShowWindow(SW_SHOW);		// Showing the merge window
				mergesort(0,size-1);
				break;
		}
}


void CBSortDlg::OnBnClickedImport()			// IMPORT button to import numerical CSV file
{		
	CString filename;
	CStdioFile file;
    CFileDialog dlg(TRUE,_T("csv"),NULL,OFN_FILEMUSTEXIST,_T("CSV Files (*.csv)|*.csv||"));
    if(dlg.DoModal()==IDOK){
        filename= dlg.GetPathName();
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


void CBSortDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}


void CBSortDlg:: bubble(){		//Extending Bubble Sort funtion and implementation
	
	D.AddNo(arr,size);
	for(int i=0;i<size-1;i++){
		for(int j=0;j<size-i-1;j++){
			c1=j;
			c2=j+1;
			s1=s2=-1;
			Invalidate();
			UpdateWindow();
			Processmsg();
			Sleep(150);

			if(arr[j]>arr[j+1]){
				s1=j;
				s2=j+1;
				Invalidate();
				UpdateWindow();
				Processmsg();
				Sleep(150);
				int temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
				s1=j;
				s2=j+1;

				D.AddNo(arr,size);
				Invalidate();
				UpdateWindow();
				Processmsg();
				Sleep(150);
			}
		}
	}
	s1=s2=c1=c2=-1;
	Invalidate();
	UpdateWindow();
	Processmsg();
	Sleep(150);

}

void CBSortDlg:: selection(){			// Extending Selection Sort funtion and implementation
	D.AddNo(arr,size);
	for(int i=0;i<size-1;i++){
    int min =i;
		for(int j=i+1;j<size;j++){
			c1=min;
			c2=j;
			s1=s2=-1;

			Invalidate();
			UpdateWindow();
			Processmsg();
			Sleep(150);
			if(arr[j] < arr[min]){
				min=j;
				s1=min;
				s2=-1;
				Invalidate();
				UpdateWindow();
				Processmsg();
				Sleep(150);
        }
    }
    if(min!=i){
        s1=i;
        s2= min;
        Invalidate();
        UpdateWindow();
        Processmsg();
        Sleep(150);

        int temp=arr[i];
        arr[i]= arr[min];
        arr[min]=temp;

        D.AddNo(arr,size);
        Invalidate();
        UpdateWindow();
        Processmsg();
        Sleep(150);
    }
}

c1=c2=s1=s2=-1;
Invalidate();
UpdateWindow();
Processmsg();
Sleep(150);
}

void CBSortDlg::insertion(){				// Extending Insertion Sort funtion and implementation
    D.AddNo(arr,size);
    for(int i=1;i<size;i++){
        int j=i;
        while(j>0){
            c1=j-1;
            c2=j;
            s1=s2=-1;
            Invalidate();
            UpdateWindow();
            Processmsg();
            Sleep(150);
            if(arr[j-1]>arr[j]){
                s1=j-1;
                s2=j;
                Invalidate();
                UpdateWindow();
                Processmsg();
                Sleep(150);

                int temp=arr[j-1];
                arr[j-1]=arr[j];
                arr[j]=temp;
                D.AddNo(arr,size);
                Invalidate();
                UpdateWindow();
                Processmsg();
                Sleep(150);
                j--;
            }
			else{
                break;
            }
        }
    }
c1=c2=s1=s2=-1;
    Invalidate();
    UpdateWindow();
    Processmsg();
    Sleep(100);
}

// QUICK SORT implementation

void CBSortDlg::quick(){
    D.AddNo(arr,size);
    quicksort(0,size-1);
    c1=c2=s1=s2=-1;

    Invalidate();
    UpdateWindow();
    Processmsg();
    Sleep(150);
}

void CBSortDlg::quicksort(int low,int high){
    if(low<high){
        int pivotindex=partition(low,high);
        quicksort(low,pivotindex-1);
        quicksort(pivotindex+1,high);
		}
}

int CBSortDlg::partition(int low,int high){
    int pivot=arr[high];
    int i=low-1;
    for(int j=low;j<high; j++){
        c1=j;
        c2=high;
        s1=s2=-1;
        Invalidate();
        UpdateWindow();
        Processmsg();
        Sleep(150);

        if(arr[j]<pivot){
            i++;
            if(i!=j){
                c1=c2=-1;
                s1=i;
                s2=j;
                Invalidate();
                UpdateWindow();
                Processmsg();
                Sleep(150);

                int temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
                D.AddNo(arr,size);
                Invalidate();
                UpdateWindow();
                Processmsg();
                Sleep(150);
            }
        }
    }
    c1=c2=s1=s2=-1;
    if(i+1 !=high){
        s1=i+1;
        s2=high;

        Invalidate();
        UpdateWindow();
        Processmsg();
        Sleep(150);

        int temp=arr[i+1];
        arr[i+1]=arr[high];
        arr[high]=temp;

        D.AddNo(arr,size);
        Invalidate();
        UpdateWindow();
        Processmsg();
        Sleep(150);
    }
    
c1=c2=s1=s2=-1;
    Invalidate();
    UpdateWindow();
    Processmsg();
    Sleep(150);
    return i+1;
}

// Merge sort implementation
void CBSortDlg::mergesort(int left,int right){
    // Breaking of array and calling merge function to sort and piece back
	if(left<right){	
        int mid=left+(right-left)/2;
        mergesort(left,mid);
        mergesort(mid+1,right);
        merge(left,mid,right);
    }
}

//Sorting of elements
void CBSortDlg::merge(int left,int mid,int right){
    int L[10];
    int R[10];
    int n1=mid-left+1;
    int n2=right-mid;
    int i,j,k;

    for(i=0;i<n1;i++){
        L[i]=arr[left+i];
    }
    for(j=0;j<n2;j++){
        R[j]=arr[mid+1+j];
    }
    MD.SetArr(L,n1,R,n2);
    Processmsg();
    Sleep(550);
    i=j=0;
    k=left;

    while(i<n1 && j<n2){
        s1=s2=-1;

        Invalidate();
        UpdateWindow();
        Processmsg();
        Sleep(550);

        if(L[i]<=R[j]){
            arr[k]=L[i];
            MD.AddMValue(L[i]);
            i++;
        }else{
            arr[k]=R[j];
            MD.AddMValue(R[j]);
            j++;
        }

		s1=k;
        s2=-1;
        Invalidate();
        UpdateWindow();
        Processmsg();
        Sleep(550);
        k++;
    }
    while(i<n1){
		s1=s2=-1;

        Invalidate();
        UpdateWindow();
        Processmsg();
        Sleep(550);
        arr[k]= L[i];
        MD.AddMValue(L[i]);
        s1= k;
		s2=-1;
        Invalidate();
        UpdateWindow();
        Processmsg();
        Sleep(550);
        i++;
        k++;
    }

    while(j<n2){
        s1=s2=-1;

        Invalidate();
        UpdateWindow();
        Processmsg();
        Sleep(550);

        arr[k]=R[j];
        MD.AddMValue(R[j]);

        Invalidate();
        UpdateWindow();
        Processmsg();
        Sleep(550);
        j++;
        k++;
    }
    D.AddNo(arr,size);
	s1=s2=-1;
    Invalidate();
    UpdateWindow();
    Processmsg();
    Sleep(550);
}