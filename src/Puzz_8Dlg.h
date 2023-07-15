
// Puzz_8Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <stdlib.h>
#include "TreeNode.h"
#include "BSTNode.h"
#include "BST.h"
#include "Queue.h"
#include "afxcmn.h"

/**
 * 
 * @author Amir
 * @version 2013
 * 
 */

// CPuzz_8Dlg dialog
class CPuzz_8Dlg : public CDialogEx
{
	// Construction
public:
	CPuzz_8Dlg(CWnd *pParent = NULL); // standard constructor

	// Dialog Data
	enum
	{
		IDD = IDD_PUZZ_8_DIALOG
	};

protected:
	virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV support

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
	TreeNode *Root;
	TreeNode *targetNode;
	TreeNode *nearFinal;
	string BCp;
	BSTNode *b1;
	BST *bst;
	string temp;
	int nodeNumbers;
	int noStep;
	// CString msg;
	string getInput();
	void NumberOfStep(TreeNode *p);
	void getPath();
	void show(string str);
	string getRight(TreeNode *p);
	string getLeft(TreeNode *p);
	string getUp(TreeNode *p);
	string getDown(TreeNode *p);
	int calcDistance(TreeNode *p);
	int CoorX(int x);
	int CoorY(int y);
	int minDistance;
	int select = 0;
	bool isFinal(TreeNode *p);
	string path[1000];
	void MoreInformation();
	void StateTreeDiagram(TreeNode *p, HTREEITEM hState);
	HTREEITEM hFather;
	// HTREEITEM hState;
	CString stDiagram;
	// TreeNode *getNearFinal(TreeNode *p);
	TreeNode *levelOrder();
	void depthOrder(TreeNode *p, int k);
	CButton Run_Btn;
	afx_msg void OnBnClickedRun();
	CString First_edtCtrl;
	CString Second_edtCtrl;
	CString Third_edtCtrl;
	CString Fourth_edtCtrl;
	CString Fifth_edtCtrl;
	CString Sixth_edtCtrl;
	CString Seventh_edtCtrl;
	CString Eighth_edtCtrl;
	CString Ninth_edtCtrl;
	CButton Show_Btn;
	afx_msg void OnBnClickedShow();
	int MaxTreeSize_edtCtrl;
	int MaxTreeHeight_edtCtrl;
	afx_msg void OnBnClickedLevelorder();
	afx_msg void OnBnClickedDepthorder();
	CButton Fast_Btn;
	afx_msg void OnBnClickedFast();
	CString Msg_stcTxt;
	int NoStep_edtCtrl;
	int NoNode_edtCtrl;
	int NoLevel_edtCtrl;
	CButton Close_Btn;
	//	CTreeCtrl *TreeDiagram;
	afx_msg void OnBnClickedClose();
	//	afx_msg void OnBnClickedStatetree();
	CButton TreeDiagram_Btn;
	afx_msg void OnBnClickedTreedig();
	CTreeCtrl TreeDiagram_TreeC;
	CString EMessage_stcTxt;
};
