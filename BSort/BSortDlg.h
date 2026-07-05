
// BSortDlg.h : header file
//

#include "DataDlg.h"
#pragma once


// CBSortDlg dialog
class CBSortDlg : public CDialogEx
{
// Construction
public:
	CBSortDlg(CWnd* pParent = NULL);	// standard constructor
	
	// Declaring variables for Array and CPaintDC
	int arr[15];
	int size;
	int c1,c2,s1,s2;
	// Object Creation for Data Dialog box
	DataDlg D;
	// Message Processing Function
	void Processmsg();
	// Object Creation for ComboBox: DropList
	CComboBox comboAlgo;
	// DEclaring Functions for Sorting
	void bubble();
	void selection();
	void insertion();
	//Quick Sort Function Declaration
	void quick();
	int partition(int low,int high);
	void quicksort(int low,int high);

// Dialog Data
	enum { IDD = IDD_BSORT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedImport();
	afx_msg void OnCbnSelchangeCombo1();
};
