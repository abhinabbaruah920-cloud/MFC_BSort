#pragma once


// MergeDialog dialog

class MergeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MergeDialog)

public:
	MergeDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~MergeDialog();

	//Declaring Left Array, Right Array and Merged Array(Result) for storing elements
	int LArr[10];
    int RArr[10];
    int MArr[20];

	// Declaring Left sub, Right sub, Merged array for current stored elements
    int LSize;
    int RSize;
    int MSize;

	// Copies the given left and right sub arrays into LArr and RArr
	// n1=left sub array elements and n2= right sub array elements
    void SetArr(int L[], int n1, int R[], int n2);

	// Sets the indexes of the elements currently being compared


	// adding value to Merged array
    void AddMValue(int value);
	//Resets the merge visualization data for the next merge operation
    void RMerge();

// Dialog Data
	enum { IDD = IDD_MERGEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// declaring On Paint function for drawing
	afx_msg void OnPaint();
};
