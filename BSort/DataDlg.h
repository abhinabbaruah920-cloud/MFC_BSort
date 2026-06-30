#pragma once


// DataDlg dialog

class DataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DataDlg)

public:
	DataDlg(CWnd* pParent = NULL);   // standard constructor
	CListBox list;
	void AddNo(int arr[],int size);
	
	virtual ~DataDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList1();
};
