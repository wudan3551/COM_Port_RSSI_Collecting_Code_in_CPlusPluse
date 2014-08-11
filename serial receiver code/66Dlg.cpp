// 66Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "66.h"
#include "66Dlg.h"
#include "time.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy66Dlg dialog

CMy66Dlg::CMy66Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy66Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy66Dlg)
	m_strRXData = _T("");
	m_strTXData = _T("");
	m_strSavePath = _T("F:\\zy\\data\\");
	m_shortSerialNo = 6;
	m_intEndFlag = 101;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	start_time = 0;
}

void CMy66Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy66Dlg)
	DDX_Control(pDX, IDC_EDIT_RXDATA, m_ctlRxData);
	DDX_Control(pDX, IDC_CHECK_HEXDISPLAY, m_ctrlHexDisplay);
	DDX_Control(pDX, IDC_CHECK_HEXSEND, m_ctrlHexSend);
	DDX_Text(pDX, IDC_EDIT_RXDATA, m_strRXData);
	DDX_Text(pDX, IDC_EDIT_TXDATA, m_strTXData);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	DDX_Text(pDX, IDC_EDIT_SAVEPATH, m_strSavePath);
	DDX_Text(pDX, IDC_EDIT_PORTNO, m_shortSerialNo);
	DDX_Text(pDX, IDC_EDIT_ENDFLAG, m_intEndFlag);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy66Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy66Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MANUALSEND, OnButtonManualsend)
	ON_EN_CHANGE(IDC_EDIT_TXDATA, OnChangeEditTxdata)
	ON_EN_CHANGE(IDC_EDIT_RXDATA, OnChangeEditRxdata)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_SAVEPATH, OnButtonSavepath)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy66Dlg message handlers

BOOL CMy66Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	blStarted = false;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy66Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy66Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy66Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CMy66Dlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CMy66Dlg)
	ON_EVENT(CMy66Dlg, IDC_MSCOMM1, 1 /* OnComm */, OnComm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CMy66Dlg::OnComm() 
{
	// TODO: Add your control notification handler code here
	VARIANT variant_inp;
    COleSafeArray safearray_inp;
	LONG len,k;
	BYTE rxdata[2048]; //create a BYTE array, An 8-bit integer that is not signed.
	CString strtemp,str,sub,rxtemp;
    SYSTEMTIME t;

	if(m_ctrlComm.GetCommEvent()==2) //value 2 means receive buffer is not empty.
	{
		variant_inp=m_ctrlComm.GetInput(); //reading buffer
		safearray_inp=variant_inp; // turn VARIANT type variable into ColeSafeArray type variable
		len=safearray_inp.GetOneDimSize();
		for(k=0;k<len;k++)
			safearray_inp.GetElement(&k,(rxdata+k));//turn to BYTE type array
		for(k=0;k<len;k++) //turn the array to Cstring type
		{
			BYTE bt= rxdata[k]; 
		//	if(m_ctrlHexDisplay.GetCheck())
				if(bt==m_intEndFlag)//process receive data, when the data match with the EndFlag, add a time tag at the end of data.
				{
					if (m_strRXData.GetLength() >1024*8)
					{
						m_strRXData = "";
					}
					m_strRXData += "\r\n";
					GetSystemTime(&t);
					strtemp.Format("%d, %d, %d, %d, \n",t.wHour+8,t.wMinute,t.wSecond,t.wMilliseconds);
					//sub.Format("%d, ",bt);
                    //strtemp+=sub;
				}
				else
				{
					strtemp.Format("%d, ",bt);
					rxtemp.Format("%d, ",bt);
					m_strRXData += rxtemp;
				} 
			str+=strtemp;
		}
	}

	DWORD dwBytesToSave=str.GetLength();

	//cf.Seek((LONG)cf.GetLength(),CFile::begin);
	if(cf.GetPosition() < 1024*8)
		cf.Seek((LONG)0,CFile::current);
	else{
		//cf.SeekToBegin();
		//cf.Close();
		if(!cf.Open(cf.GetFilePath(),CFile::modeCreate |CFile::modeReadWrite | CFile::shareDenyNone))
		{
			AfxMessageBox(_T("Can not create file : " + m_strSavePath + strtemp + ".csv !!!" ));
		}
	}
	
	cf.Write((LPCTSTR)str,dwBytesToSave);
    str=_T("");

	GetSystemTime(&t);
	current_time = t.wMinute*60 + t.wSecond;
	if(current_time - start_time > 60) {
		if (blStarted)
		{
			cf.Close();
			closeSerial();
			blStarted = false;
		}
	}

	UpdateData(FALSE); 
	m_ctlRxData.LineScroll(m_ctlRxData.GetLineCount());
}

void CMy66Dlg::OnButtonManualsend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); 
	if(m_ctrlHexSend.GetCheck())
	{
		CByteArray hexdata;
		int len=String2Hex(m_strTXData,hexdata); 
		m_ctrlComm.SetOutput(COleVariant(hexdata)); 
	}
	else 
		m_ctrlComm.SetOutput(COleVariant(m_strTXData));
}

void CMy66Dlg::OnChangeEditTxdata() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

int CMy66Dlg::String2Hex(CString str, CByteArray &senddata)
{
	int hexdata,lowhexdata;
    int hexdatalen=0;
    int len=str.GetLength();
    senddata.SetSize(len/2);
    for(int i=0;i<len;)
	{
		char lstr,hstr=str[i];
		if(hstr==' ')
		{
			i++;
			continue;
		}
		i++;
		if(i>=len)
			break;
		lstr=str[i];
		hexdata=ConvertHexChar(hstr);
		lowhexdata=ConvertHexChar(lstr);
		if((hexdata==16)||(lowhexdata==16))
			break;
		else 
			hexdata=hexdata*16+lowhexdata;
		i++;
		senddata[hexdatalen]=(char)hexdata;
		hexdatalen++;
	}
	senddata.SetSize(hexdatalen);
	return hexdatalen;
}

char CMy66Dlg::ConvertHexChar(char ch)
{
	if((ch>='0')&&(ch<='9'))
		return ch-0x30;
	else if((ch>='A')&&(ch<='F'))
		return ch-'A'+10;
	else if((ch>='a')&&(ch<='f'))
		return ch-'a'+10;
	else return (-1);

}

void CMy66Dlg::OnChangeEditRxdata() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CMy66Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//OnComm() ;
	CDialog::OnTimer(nIDEvent);
}

void CMy66Dlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

void CMy66Dlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(blStarted)
	{
		AfxMessageBox(_T("The pro has started!!!"));
		return;
	}
	if (m_shortSerialNo == -1)
	{
		AfxMessageBox(_T("Pls input port number, then click start button!!"));
		return;
	}
	if (m_strSavePath == "")
	{
		AfxMessageBox(_T("Pls select the file path!!!"));
		return;
	}
	if (m_intEndFlag == -1)
	{
		AfxMessageBox(_T("Pls input end flag"));
		return;
	}
	{
		SYSTEMTIME tm;
		CString strtemp;
		GetSystemTime(&tm);
		strtemp.Format("%02d-%02d-%02d-%02d-%03d", tm.wMonth, tm.wDay, tm.wHour+8, tm.wMinute, tm.wSecond);
		//if(!cf.Open(m_strSavePath + strtemp + ".csv",CFile::modeCreate |CFile::modeReadWrite | CFile::modeNoTruncate | CFile::shareDenyNone))
		if(!cf.Open(m_strSavePath + strtemp + ".csv",CFile::modeCreate |CFile::modeReadWrite | CFile::shareDenyNone))
		{
			AfxMessageBox(_T("Can not create file : " + m_strSavePath + strtemp + ".csv !!!" ));
		}
		start_time = tm.wMinute*60 + tm.wSecond;
	}
	m_strRXData = "";
	UpdateData(FALSE);
	if (!openSerial(m_shortSerialNo))
	{
		AfxMessageBox(_T("Not start"));
		return;
	}
	blStarted = true;
}

void CMy66Dlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	if (blStarted)
	{
		cf.Close();
		closeSerial();
		blStarted = false;
	}
}

bool CMy66Dlg::openSerial(short i)
{
	if(m_ctrlComm.GetPortOpen())
		m_ctrlComm.SetPortOpen(FALSE);
	
	m_ctrlComm.SetCommPort(i); 
	m_ctrlComm.SetSettings("115200,n,8,1"); 
	m_ctrlComm.SetInputMode(1); 
	m_ctrlComm.SetRThreshold(1); 
	m_ctrlComm.SetInputLen(0); 

	if( !m_ctrlComm.GetPortOpen())
	{
		m_ctrlComm.SetPortOpen(TRUE);
		m_ctrlComm.GetInput();
		return true;
	}
	else
	{
		AfxMessageBox("cannot open serial port");
		return false;
	}
}

void CMy66Dlg::closeSerial()
{
	if (m_ctrlComm.GetPortOpen())
	{
		m_ctrlComm.SetPortOpen(FALSE);
	}
}

void CMy66Dlg::OnButtonSavepath() 
{
	// TODO: Add your control notification handler code here
	if(!ShowSelectDirectoryDlg(_T("Pls select saving path...")))
	{
		m_strSavePath = "";
	}
}

bool CMy66Dlg::ShowSelectDirectoryDlg(const CString & strDlgTitle)
{
	CString str;
	BROWSEINFO bi;
	char name[MAX_PATH];
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.hwndOwner = GetSafeHwnd();
	bi.pszDisplayName = name;
	bi.lpszTitle = strDlgTitle;
	//bi.ulFlags = BIF_USENEWUI;
	bi.ulFlags = BIF_RETURNFSANCESTORS;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if(idl == NULL)
		return false;
	SHGetPathFromIDList(idl, str.GetBuffer(MAX_PATH));
	str.ReleaseBuffer();
	m_strSavePath = str;
	if(str.GetAt(str.GetLength()-1)!='\\')
		m_strSavePath+="\\";
	UpdateData(FALSE);
	return true;
}

void CMy66Dlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}
