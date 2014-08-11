// 66.h : main header file for the 66 application
//

#if !defined(AFX_66_H__AAB948D2_1C4E_44E3_B59D_75073595412B__INCLUDED_)
#define AFX_66_H__AAB948D2_1C4E_44E3_B59D_75073595412B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy66App:
// See 66.cpp for the implementation of this class
//

class CMy66App : public CWinApp
{
public:
	CMy66App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy66App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy66App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_66_H__AAB948D2_1C4E_44E3_B59D_75073595412B__INCLUDED_)
