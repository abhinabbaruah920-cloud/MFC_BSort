#pragma once


// MergeDialog dialog

class MergeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MergeDialog)

public:
	MergeDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~MergeDialog();

	int LArr[10];
    int RArr[10];
    int MArr[10];

    int LSize;
    int RSize;
    int MSize;

    // Current compared elements
    int CLeft;
    int CRight;

    // Functions called from CBSortDlg
    void SetArr(int L[], int n1, int R[], int n2);
    void SetComp(int LIndex,int RIndex);
    void AddMValue(int value);
    void RMerge();

// Dialog Data
	enum { IDD = IDD_MERGEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
