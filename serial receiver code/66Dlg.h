// 66Dlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_66DLG_H__48B086B4_4F9E_4C37_9A56_05A8D473CF07__INCLUDED_)
#define AFX_66DLG_H__48B086B4_4F9E_4C37_9A56_05A8D473CF07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy66Dlg dialog

class CMy66Dlg : public CDialog
{
// Construction
public:
	char ConvertHexChar(char ch);
	int String2Hex(CString str, CByteArray &senddata);

	CMy66Dlg(CWnd* pParent = NULL);	// standard constructor
	//~CMy66Dlg();
	CFile cf;
	bool blStarted;

	bool openSerial(short );
	void closeSerial();
	bool ShowSelectDirectoryDlg(const CString & strDlgTitle);
	int start_time;
	int current_time;

// Dialog Data
	//{{AFX_DATA(CMy66Dlg)
	enum { IDD = IDD_MY66_DIALOG };
	CEdit	m_ctlRxData;
	CButton	m_ctrlHexDisplay;
	CButton	m_ctrlHexSend;
	CString	m_strRXData;
	CString	m_strTXData;
	CMSComm	m_ctrlComm;
	CString	m_strSavePath;
	short	m_shortSerialNo;
	int		m_intEndFlag;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy66Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy66Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnComm();
	afx_msg void OnButtonManualsend();
	afx_msg void OnChangeEditTxdata();
	afx_msg void OnChangeEditRxdata();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonSavepath();
	afx_msg void OnButtonClose();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_66DLG_H__48B086B4_4F9E_4C37_9A56_05A8D473CF07__INCLUDED_)
