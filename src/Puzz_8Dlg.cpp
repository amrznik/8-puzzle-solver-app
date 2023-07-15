
// Puzz_8Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Puzz_8.h"
#include "Puzz_8Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About


/**
 * 8 puzzle solver as an MFC Desktop Application
 * using Decision Tree and Binary Search Tree to find the solution or the closest solution
 * 
 * @author Amir
 * @version 2013
 * 
 */

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum
	{
		IDD = IDD_ABOUTBOX
	};

protected:
	virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CPuzz_8Dlg dialog

CPuzz_8Dlg::CPuzz_8Dlg(CWnd *pParent /*=NULL*/)
	: CDialogEx(CPuzz_8Dlg::IDD, pParent), First_edtCtrl(_T("")), Second_edtCtrl(_T("")), Third_edtCtrl(_T("")), Fourth_edtCtrl(_T("")), Fifth_edtCtrl(_T("")), Sixth_edtCtrl(_T("")), Seventh_edtCtrl(_T("")), Eighth_edtCtrl(_T("")), Ninth_edtCtrl(_T("")), MaxTreeSize_edtCtrl(0), MaxTreeHeight_edtCtrl(0), Msg_stcTxt(_T("")), NoStep_edtCtrl(0), NoNode_edtCtrl(0), NoLevel_edtCtrl(0), EMessage_stcTxt(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPuzz_8Dlg::DoDataExchange(CDataExchange *pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RUN, Run_Btn);
	DDX_Text(pDX, IDC_FIRST, First_edtCtrl);
	DDX_Text(pDX, IDC_SECOND, Second_edtCtrl);
	DDX_Text(pDX, IDC_THIRD, Third_edtCtrl);
	DDX_Text(pDX, IDC_FOURTH, Fourth_edtCtrl);
	DDX_Text(pDX, IDC_FIFTH, Fifth_edtCtrl);
	DDX_Text(pDX, IDC_SIXTH, Sixth_edtCtrl);
	DDX_Text(pDX, IDC_SEVENTH, Seventh_edtCtrl);
	DDX_Text(pDX, IDC_EIGHTH, Eighth_edtCtrl);
	DDX_Text(pDX, IDC_NINTH, Ninth_edtCtrl);
	DDX_Control(pDX, IDC_Show, Show_Btn);
	DDX_Text(pDX, IDC_MAXTREESIZE, MaxTreeSize_edtCtrl);
	DDX_Text(pDX, IDC_MAXTREEHEIGHT, MaxTreeHeight_edtCtrl);
	DDX_Control(pDX, IDC_FAST, Fast_Btn);
	DDX_Text(pDX, IDC_MSG, Msg_stcTxt);
	DDX_Text(pDX, IDC_NOSTEP, NoStep_edtCtrl);
	DDX_Text(pDX, IDC_NONODE, NoNode_edtCtrl);
	DDX_Text(pDX, IDC_NOLEVEL, NoLevel_edtCtrl);
	DDX_Control(pDX, IDC_CLOSE, Close_Btn);
	DDX_Control(pDX, IDC_TREEDIG, TreeDiagram_Btn);
	DDX_Control(pDX, IDC_CTREEDIG, TreeDiagram_TreeC);
	DDX_Text(pDX, IDC_EMESSAGE, EMessage_stcTxt);
}

BEGIN_MESSAGE_MAP(CPuzz_8Dlg, CDialogEx)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_RUN, &CPuzz_8Dlg::OnBnClickedRun)
ON_BN_CLICKED(IDC_Show, &CPuzz_8Dlg::OnBnClickedShow)
ON_BN_CLICKED(IDC_LEVELORDER, &CPuzz_8Dlg::OnBnClickedLevelorder)
ON_BN_CLICKED(IDC_DEPTHORDER, &CPuzz_8Dlg::OnBnClickedDepthorder)
ON_BN_CLICKED(IDC_FAST, &CPuzz_8Dlg::OnBnClickedFast)
ON_BN_CLICKED(IDC_CLOSE, &CPuzz_8Dlg::OnBnClickedClose)
//	ON_BN_CLICKED(IDC_STATETREE, &CPuzz_8Dlg::OnBnClickedStatetree)
ON_BN_CLICKED(IDC_TREEDIG, &CPuzz_8Dlg::OnBnClickedTreedig)
END_MESSAGE_MAP()

// CPuzz_8Dlg message handlers

BOOL CPuzz_8Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu *pSysMenu = GetSystemMenu(FALSE);
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
	SetIcon(m_hIcon, TRUE);	 // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon

	// while (!GetCheckedRadioButton(IDC_LEVELORDER, IDC_DEPTHORDER))
	// primitiveTerms();
	UpdateData(true);
	Msg_stcTxt = _T("Enter your own Puzzle or Click on Fast and Enjoy!");
	UpdateData(false);

	// TreeDiagram->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
	// CRect(400, 10, 640, 380), this, 0x1221);

	return TRUE; // return TRUE  unless you set the focus to a control
}

void CPuzz_8Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPuzz_8Dlg::OnPaint()
{
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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPuzz_8Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPuzz_8Dlg::OnBnClickedRun()
{
	UpdateData(true);
	Root = new TreeNode(getInput());
	b1 = new BSTNode(Root->value);
	bst = new BST(b1);
	Root->distance = calcDistance(Root);
	minDistance = Root->distance;
	nearFinal = Root;
	nodeNumbers = 1;
	GetDlgItem(IDC_RUN)->EnableWindow(false);
	if (GetCheckedRadioButton(IDC_LEVELORDER, IDC_DEPTHORDER) == IDC_LEVELORDER)
	{
		TreeNode *level = levelOrder();
		if (level != nearFinal)
			targetNode = level;
	}
	else
	{
		int k = MaxTreeHeight_edtCtrl;
		depthOrder(Root, k);
	}
	if (targetNode)
		Msg_stcTxt = _T("Click on 'show' to see the solution");
	else
		Msg_stcTxt = _T("Click on 'show' to see the nearest solution");

	if (targetNode)
		NumberOfStep(targetNode);
	else
		NumberOfStep(nearFinal);

	MoreInformation();

	GetDlgItem(IDC_Show)->EnableWindow(true);
	GetDlgItem(IDC_TREEDIG)->EnableWindow(true);
	UpdateData(false);
}

void CPuzz_8Dlg::OnBnClickedLevelorder()
{
	UpdateData(true);
	GetDlgItem(IDC_MAXTREESIZE)->EnableWindow(true);
	GetDlgItem(IDC_MAXTREEHEIGHT)->EnableWindow(false);
	GetDlgItem(IDC_RUN)->EnableWindow(true);
	UpdateData(false);
}

void CPuzz_8Dlg::OnBnClickedDepthorder()
{
	UpdateData(true);
	GetDlgItem(IDC_MAXTREEHEIGHT)->EnableWindow(true);
	GetDlgItem(IDC_MAXTREESIZE)->EnableWindow(false);
	GetDlgItem(IDC_RUN)->EnableWindow(true);
	UpdateData(false);
}

void CPuzz_8Dlg::OnBnClickedShow()
{
	getPath();
	GetDlgItem(IDC_Show)->EnableWindow(false);
	GetDlgItem(IDC_RUN)->EnableWindow(true);
}

void CPuzz_8Dlg::OnBnClickedFast()
{
	UpdateData(true);
	if (select == 0)
	{
		First_edtCtrl = "5";
		Second_edtCtrl = "6";
		Third_edtCtrl = "2";
		Fourth_edtCtrl = "";
		Fifth_edtCtrl = "3";
		Sixth_edtCtrl = "1";
		Seventh_edtCtrl = "8";
		Eighth_edtCtrl = "7";
		Ninth_edtCtrl = "4";
		select++;
	}
	else if (select == 1)
	{
		First_edtCtrl = "1";
		Second_edtCtrl = "2";
		Third_edtCtrl = "3";
		Fourth_edtCtrl = "4";
		Fifth_edtCtrl = "5";
		Sixth_edtCtrl = "6";
		Seventh_edtCtrl = "7";
		Eighth_edtCtrl = "8";
		Ninth_edtCtrl = "";
		select++;
	}
	else if (select == 2)
	{
		First_edtCtrl = "3";
		Second_edtCtrl = "4";
		Third_edtCtrl = "7";
		Fourth_edtCtrl = "1";
		Fifth_edtCtrl = "";
		Sixth_edtCtrl = "2";
		Seventh_edtCtrl = "5";
		Eighth_edtCtrl = "8";
		Ninth_edtCtrl = "6";
		select++;
	}
	else if (select == 3)
	{
		First_edtCtrl = "";
		Second_edtCtrl = "1";
		Third_edtCtrl = "3";
		Fourth_edtCtrl = "8";
		Fifth_edtCtrl = "5";
		Sixth_edtCtrl = "4";
		Seventh_edtCtrl = "6";
		Eighth_edtCtrl = "7";
		Ninth_edtCtrl = "2";
		select++;
	}
	else if (select == 4)
	{
		First_edtCtrl = "1";
		Second_edtCtrl = "2";
		Third_edtCtrl = "3";
		Fourth_edtCtrl = "8";
		Fifth_edtCtrl = "4";
		Sixth_edtCtrl = "";
		Seventh_edtCtrl = "7";
		Eighth_edtCtrl = "6";
		Ninth_edtCtrl = "5";
		select++;
	}
	else if (select == 5)
	{
		First_edtCtrl = "8";
		Second_edtCtrl = "7";
		Third_edtCtrl = "6";
		Fourth_edtCtrl = "5";
		Fifth_edtCtrl = "4";
		Sixth_edtCtrl = "3";
		Seventh_edtCtrl = "2";
		Eighth_edtCtrl = "1";
		Ninth_edtCtrl = "";
		select++;
	}
	else if (select == 6)
	{
		First_edtCtrl = "2";
		Second_edtCtrl = "4";
		Third_edtCtrl = "5";
		Fourth_edtCtrl = "1";
		Fifth_edtCtrl = "8";
		Sixth_edtCtrl = "";
		Seventh_edtCtrl = "7";
		Eighth_edtCtrl = "6";
		Ninth_edtCtrl = "3";
		select++;
	}
	else if (select == 7)
	{
		First_edtCtrl = "2";
		Second_edtCtrl = "3";
		Third_edtCtrl = "4";
		Fourth_edtCtrl = "";
		Fifth_edtCtrl = "1";
		Sixth_edtCtrl = "5";
		Seventh_edtCtrl = "7";
		Eighth_edtCtrl = "8";
		Ninth_edtCtrl = "6";
		select = 0;
	}
	Msg_stcTxt = _T("Click on 'Run'");
	GetDlgItem(IDC_RUN)->EnableWindow(true);
	UpdateData(false);
}

string CPuzz_8Dlg::getInput()
{
	UpdateData(true);
	int check;
	CString CScheck;
	/*CString CSstrCheck(First_edtCtrl + Second_edtCtrl + Third_edtCtrl + Fourth_edtCtrl +
		Fifth_edtCtrl + Sixth_edtCtrl + Seventh_edtCtrl + Eighth_edtCtrl + Ninth_edtCtrl);
	if (CSstrCheck.SpanIncluding(_T(" 12345678"))){
		First_edtCtrl = "5";
		Second_edtCtrl = "6";
		Third_edtCtrl = "2";
		Fourth_edtCtrl = "";
		Fifth_edtCtrl = "3";
		Sixth_edtCtrl = "1";
		Seventh_edtCtrl = "8";
		Eighth_edtCtrl = "7";
		Ninth_edtCtrl = "4";
		check = 4;
		EMessage_stcTxt = _T("Your Inputs is Wrong and Puzzle fill and solve himself Automatically:)");
	}
	else{*/
	if (First_edtCtrl == "")
		check = 1;
	else if (Second_edtCtrl == "")
		check = 2;
	else if (Third_edtCtrl == "")
		check = 3;
	else if (Fourth_edtCtrl == "")
		check = 4;
	else if (Fifth_edtCtrl == "")
		check = 5;
	else if (Sixth_edtCtrl == "")
		check = 6;
	else if (Seventh_edtCtrl == "")
		check = 7;
	else if (Eighth_edtCtrl == "")
		check = 8;
	else if (Ninth_edtCtrl == "")
		check = 9;
	else
	{
		First_edtCtrl = "5";
		Second_edtCtrl = "6";
		Third_edtCtrl = "2";
		Fourth_edtCtrl = "";
		Fifth_edtCtrl = "3";
		Sixth_edtCtrl = "1";
		Seventh_edtCtrl = "8";
		Eighth_edtCtrl = "7";
		Ninth_edtCtrl = "4";
		check = 4;
		EMessage_stcTxt = _T("Your inputs are wrong and Puzzle fills and solves itself Automatically:)");
	}
	//}
	if (check == 1)
	{
		CScheck = "0";
		CString CSstr(CScheck + Second_edtCtrl + Third_edtCtrl + Fourth_edtCtrl +
					  Fifth_edtCtrl + Sixth_edtCtrl + Seventh_edtCtrl + Eighth_edtCtrl + Ninth_edtCtrl);
		CT2CA A(CSstr);
		string str(A);
		UpdateData(false);
		return str;
	}
	else if (check == 2)
	{
		CScheck = "0";
		CString CSstr(First_edtCtrl + CScheck + Third_edtCtrl + Fourth_edtCtrl +
					  Fifth_edtCtrl + Sixth_edtCtrl + Seventh_edtCtrl + Eighth_edtCtrl + Ninth_edtCtrl);
		CT2CA A(CSstr);
		string str(A);
		UpdateData(false);
		return str;
	}
	else if (check == 3)
	{
		CScheck = "0";
		CString CSstr(First_edtCtrl + Second_edtCtrl + CScheck + Fourth_edtCtrl +
					  Fifth_edtCtrl + Sixth_edtCtrl + Seventh_edtCtrl + Eighth_edtCtrl + Ninth_edtCtrl);
		CT2CA A(CSstr);
		string str(A);
		UpdateData(false);
		return str;
	}
	else if (check == 4)
	{
		CScheck = "0";
		CString CSstr(First_edtCtrl + Second_edtCtrl + Third_edtCtrl + CScheck +
					  Fifth_edtCtrl + Sixth_edtCtrl + Seventh_edtCtrl + Eighth_edtCtrl + Ninth_edtCtrl);
		CT2CA A(CSstr);
		string str(A);
		UpdateData(false);
		return str;
	}
	else if (check == 5)
	{
		CScheck = "0";
		CString CSstr(First_edtCtrl + Second_edtCtrl + Third_edtCtrl + Fourth_edtCtrl +
					  CScheck + Sixth_edtCtrl + Seventh_edtCtrl + Eighth_edtCtrl + Ninth_edtCtrl);
		CT2CA A(CSstr);
		string str(A);
		UpdateData(false);
		return str;
	}
	else if (check == 6)
	{
		CScheck = "0";
		CString CSstr(First_edtCtrl + Second_edtCtrl + Third_edtCtrl + Fourth_edtCtrl +
					  Fifth_edtCtrl + CScheck + Seventh_edtCtrl + Eighth_edtCtrl + Ninth_edtCtrl);
		CT2CA A(CSstr);
		string str(A);
		UpdateData(false);
		return str;
	}
	else if (check == 7)
	{
		CScheck = "0";
		CString CSstr(First_edtCtrl + Second_edtCtrl + Third_edtCtrl + Fourth_edtCtrl +
					  Fifth_edtCtrl + Sixth_edtCtrl + CScheck + Eighth_edtCtrl + Ninth_edtCtrl);
		CT2CA A(CSstr);
		string str(A);
		UpdateData(false);
		return str;
	}
	else if (check == 8)
	{
		CScheck = "0";
		CString CSstr(First_edtCtrl + Second_edtCtrl + Third_edtCtrl + Fourth_edtCtrl +
					  Fifth_edtCtrl + Sixth_edtCtrl + Seventh_edtCtrl + CScheck + Ninth_edtCtrl);
		CT2CA A(CSstr);
		string str(A);
		UpdateData(false);
		return str;
	}
	else if (check == 9)
	{
		CScheck = "0";
		CString CSstr(First_edtCtrl + Second_edtCtrl + Third_edtCtrl + Fourth_edtCtrl +
					  Fifth_edtCtrl + Sixth_edtCtrl + Seventh_edtCtrl + Eighth_edtCtrl + CScheck);
		CT2CA A(CSstr);
		string str(A);
		UpdateData(false);
		return str;
	}
	UpdateData(false);
	return "";
}

void CPuzz_8Dlg::NumberOfStep(TreeNode *p)
{

	path[0] = p->value;
	int i = 1;
	while (p != Root)
	{
		p = p->father;
		path[i] = p->value;
		i++;
	}
	noStep = i - 1;
}

void CPuzz_8Dlg::getPath()
{

	clock_t delay = clock();
	while (noStep >= 0)
	{
		if (clock() - delay > 400)
		{
			show(path[noStep]);
			noStep--;
			UpdateWindow();
			delay = clock();
		}
	}
}

void CPuzz_8Dlg::show(string str)
{
	UpdateData(true);
	First_edtCtrl = str.substr(0, 1).c_str();
	Second_edtCtrl = str.substr(1, 1).c_str();
	Third_edtCtrl = str.substr(2, 1).c_str();
	Fourth_edtCtrl = str.substr(3, 1).c_str();
	Fifth_edtCtrl = str.substr(4, 1).c_str();
	Sixth_edtCtrl = str.substr(5, 1).c_str();
	Seventh_edtCtrl = str.substr(6, 1).c_str();
	Eighth_edtCtrl = str.substr(7, 1).c_str();
	Ninth_edtCtrl = str.substr(8, 1).c_str();
	if (First_edtCtrl == "0")
		First_edtCtrl = "";
	else if (Second_edtCtrl == "0")
		Second_edtCtrl = "";
	else if (Third_edtCtrl == "0")
		Third_edtCtrl = "";
	else if (Fourth_edtCtrl == "0")
		Fourth_edtCtrl = "";
	else if (Fifth_edtCtrl == "0")
		Fifth_edtCtrl = "";
	else if (Sixth_edtCtrl == "0")
		Sixth_edtCtrl = "";
	else if (Seventh_edtCtrl == "0")
		Seventh_edtCtrl = "";
	else if (Eighth_edtCtrl == "0")
		Eighth_edtCtrl = "";
	else if (Ninth_edtCtrl == "0")
		Ninth_edtCtrl = "";
	MessageBeep(0x00000030L);
	UpdateData(false);
}

void CPuzz_8Dlg::MoreInformation()
{
	// UpdateData(true);
	NoStep_edtCtrl = noStep;
	NoNode_edtCtrl = nodeNumbers;
	NoLevel_edtCtrl = bst->noLevel(b1);
	// UpdateData(false);
}

string CPuzz_8Dlg::getRight(TreeNode *p)
{

	BCp = p->value;
	int pos = BCp.find("0");
	if (pos == 2 || pos == 5 || pos == 8)
	{
		return "";
	}
	else
		swap(BCp[pos], BCp[pos + 1]);

	if (bst->AddToTree(BCp))
		return BCp;

	return "";
}

string CPuzz_8Dlg::getLeft(TreeNode *p)
{

	BCp = p->value;
	int pos = BCp.find("0");
	if (pos == 0 || pos == 3 || pos == 6)
	{
		return "";
	}
	else
		swap(BCp[pos - 1], BCp[pos]);

	if (bst->AddToTree(BCp))
		return BCp;

	return "";
}

string CPuzz_8Dlg::getUp(TreeNode *p)
{

	BCp = p->value;
	int pos = BCp.find("0");
	if (pos == 0 || pos == 1 || pos == 2)
	{
		return "";
	}
	else
		swap(BCp[pos - 3], BCp[pos]);

	if (bst->AddToTree(BCp))
		return BCp;

	return "";
}

string CPuzz_8Dlg::getDown(TreeNode *p)
{

	BCp = p->value;
	int pos = BCp.find("0");
	if (pos == 6 || pos == 7 || pos == 8)
	{
		return "";
	}
	else
		swap(BCp[pos], BCp[pos + 3]);

	if (bst->AddToTree(BCp))
		return BCp;

	return "";
}

int CPuzz_8Dlg::CoorX(int x)
{
	if (x == 0 || x == 1 || x == 2)
		return 0;
	if (x == 3 || x == 4 || x == 5)
		return 1;
	if (x == 6 || x == 7 || x == 8)
		return 2;
	return -1;
}

int CPuzz_8Dlg::CoorY(int y)
{
	if (y == 0 || y == 3 || y == 6)
		return 0;
	if (y == 1 || y == 4 || y == 7)
		return 1;
	if (y == 2 || y == 5 || y == 8)
		return 2;
	return -1;
}

int CPuzz_8Dlg::calcDistance(TreeNode *p)
{
	return abs(CoorX(p->value.find("0")) - 1) + abs(CoorY(p->value.find("0")) - 1) +
		   abs(CoorX(p->value.find("1")) - 0) + abs(CoorY(p->value.find("1")) - 0) +
		   abs(CoorX(p->value.find("2")) - 0) + abs(CoorY(p->value.find("2")) - 1) +
		   abs(CoorX(p->value.find("3")) - 0) + abs(CoorY(p->value.find("3")) - 2) +
		   abs(CoorX(p->value.find("4")) - 1) + abs(CoorY(p->value.find("4")) - 2) +
		   abs(CoorX(p->value.find("5")) - 2) + abs(CoorY(p->value.find("5")) - 2) +
		   abs(CoorX(p->value.find("6")) - 2) + abs(CoorY(p->value.find("6")) - 1) +
		   abs(CoorX(p->value.find("7")) - 2) + abs(CoorY(p->value.find("7")) - 0) +
		   abs(CoorX(p->value.find("8")) - 1) + abs(CoorY(p->value.find("8")) - 0);
}

bool CPuzz_8Dlg::isFinal(TreeNode *p)
{

	if (p->value == "123804765")
		return true;
	return false;
}

/*TreeNode *CPuzz_8Dlg::getNearFinal(TreeNode *p){

	if (!p) return Root;
	p->distance = calcDistance(p);
	if (minDistance > p->distance){
		minDistance = p->distance;
		return p;
	}
	TreeNode *nR = getNearFinal(p->right);
	TreeNode *nL = getNearFinal(p->left);
	TreeNode *nU = getNearFinal(p->up);
	TreeNode *nD = getNearFinal(p->down);

	minDistance = min(min(nR->distance, nL->distance),min(nU->distance, nD->distance));
	if (minDistance == nR->distance) return nR;
	else if (minDistance == nL->distance) return nL;
	else if (minDistance == nU->distance) return nU;
	else if (minDistance == nD->distance) return nD;

	return NULL;
}*/

TreeNode *CPuzz_8Dlg::levelOrder()
{

	Queue *Q = new Queue();
	TreeNode *p = Root;
	Q->push(p);
	UpdateData(true);
	Q->max = MaxTreeSize_edtCtrl;
	UpdateData(false);
	while (!isFinal(p) && nodeNumbers < Q->max)
	{
		string right = getRight(p);
		if (right != "" && nodeNumbers < Q->max)
		{
			TreeNode *q = new TreeNode(right);
			q->father = p;
			q->distance = calcDistance(q);
			if (q->distance != 0 && minDistance > q->distance)
			{
				minDistance = q->distance;
				nearFinal = q;
			}
			p->right = q;
			Q->push(q);
			nodeNumbers++;
			if (isFinal(q))
				return q;
		}
		string left = getLeft(p);
		if (left != "" && nodeNumbers < Q->max)
		{
			TreeNode *q = new TreeNode(left);
			q->father = p;
			q->distance = calcDistance(q);
			if (q->distance != 0 && minDistance > q->distance)
			{
				minDistance = q->distance;
				nearFinal = q;
			}
			p->left = q;
			Q->push(q);
			nodeNumbers++;
			if (isFinal(q))
				return q;
		}
		string up = getUp(p);
		if (up != "" && nodeNumbers < Q->max)
		{
			TreeNode *q = new TreeNode(up);
			q->father = p;
			q->distance = calcDistance(q);
			if (q->distance != 0 && minDistance > q->distance)
			{
				minDistance = q->distance;
				nearFinal = q;
			}
			p->up = q;
			Q->push(q);
			nodeNumbers++;
			if (isFinal(q))
				return q;
		}
		string down = getDown(p);
		if (down != "" && nodeNumbers < Q->max)
		{
			TreeNode *q = new TreeNode(down);
			q->father = p;
			q->distance = calcDistance(q);
			if (q->distance != 0 && minDistance > q->distance)
			{
				minDistance = q->distance;
				nearFinal = q;
			}
			p->down = q;
			Q->push(q);
			nodeNumbers++;
			if (isFinal(q))
				return q;
		}
		p = Q->pick();
		if (!p)
			break;
	} // End while

	if (p && isFinal(p))
		return p;
	// else{
	// nearFinal = getNearFinal(Root);
	return nearFinal;
}
void CPuzz_8Dlg::depthOrder(TreeNode *p, int k)
{
	if (isFinal(p) || k == 0)
	{
		if (isFinal(p))
			targetNode = p;
		return;
	}

	string right = getRight(p);
	if (right != "")
	{
		TreeNode *q = new TreeNode(right);
		q->father = p;
		q->distance = calcDistance(q);
		if (q->distance != 0 && minDistance > q->distance)
		{
			minDistance = q->distance;
			nearFinal = q;
		}
		p->right = q;
		nodeNumbers++;
		depthOrder(p->right, k - 1);
	}
	string left = getLeft(p);
	if (left != "")
	{
		TreeNode *q = new TreeNode(left);
		q->father = p;
		q->distance = calcDistance(q);
		if (q->distance != 0 && minDistance > q->distance)
		{
			minDistance = q->distance;
			nearFinal = q;
		}
		p->left = q;
		nodeNumbers++;
		depthOrder(p->left, k - 1);
	}
	string up = getUp(p);
	if (up != "")
	{
		TreeNode *q = new TreeNode(up);
		q->father = p;
		q->distance = calcDistance(q);
		if (q->distance != 0 && minDistance > q->distance)
		{
			minDistance = q->distance;
			nearFinal = q;
		}
		p->up = q;
		nodeNumbers++;
		depthOrder(p->up, k - 1);
	}
	string down = getDown(p);
	if (down != "")
	{
		TreeNode *q = new TreeNode(down);
		q->father = p;
		q->distance = calcDistance(q);
		if (q->distance != 0 && minDistance > q->distance)
		{
			minDistance = q->distance;
			nearFinal = q;
		}
		p->down = q;
		nodeNumbers++;
		depthOrder(p->down, k - 1);
	}
}

void CPuzz_8Dlg::OnBnClickedClose()
{
	CDialogEx::OnCancel();
}

void CPuzz_8Dlg::StateTreeDiagram(TreeNode *p, HTREEITEM hStateFather)
{

	hFather = hStateFather;

	if (p->right)
	{
		stDiagram.Format(_T("Right: %d"), atoi(p->right->value.c_str()));
		hFather = TreeDiagram_TreeC.InsertItem(stDiagram, hStateFather);
		StateTreeDiagram(p->right, hFather);
	}
	if (p->left)
	{
		stDiagram.Format(_T("Left: %d"), atoi(p->left->value.c_str()));
		hFather = TreeDiagram_TreeC.InsertItem(stDiagram, hStateFather);
		StateTreeDiagram(p->left, hFather);
	}
	if (p->up)
	{
		stDiagram.Format(_T("Up: %d"), atoi(p->up->value.c_str()));
		hFather = TreeDiagram_TreeC.InsertItem(stDiagram, hStateFather);
		StateTreeDiagram(p->up, hFather);
	}
	if (p->down)
	{
		stDiagram.Format(_T("Down: %d"), atoi(p->down->value.c_str()));
		hFather = TreeDiagram_TreeC.InsertItem(stDiagram, hStateFather);
		StateTreeDiagram(p->down, hFather);
	}
}

// void CPuzz_8Dlg::OnBnClickedStatetree()
//{
//	HTREEITEM hStateFather = TreeDiagram->InsertItem(_T("State Tree"));
//	stDiagram.Format(_T("%d"), atoi(Root->value.c_str()));
//	hStateFather = TreeDiagram->InsertItem(stDiagram, hStateFather);
//	StateTreeDiagram(Root,hStateFather);
// }

void CPuzz_8Dlg::OnBnClickedTreedig()
{
	TreeDiagram_TreeC.DeleteAllItems();
	HTREEITEM hStateFather = TreeDiagram_TreeC.InsertItem(_T("Tree Diagram"));
	stDiagram.Format(_T("Root: %d"), atoi(Root->value.c_str()));
	hStateFather = TreeDiagram_TreeC.InsertItem(stDiagram, hStateFather);
	StateTreeDiagram(Root, hStateFather);
	GetDlgItem(IDC_TREEDIG)->EnableWindow(false);
}
