// SipDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SipDemo.h"
#include "SipDemoDlg.h"
#include <hpr/HPR_Hpr.h>
#include <osipparser2/osip_parser.h>
#include "ClientMgr.h"

#pragma comment(lib,"hpr.lib")
#pragma comment(lib,"hlog.lib")
#pragma comment(lib,"osipparser.lib")
#pragma comment(lib,"vld.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSipDemoDlg 对话框




CSipDemoDlg::CSipDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSipDemoDlg::IDD, pParent)
	, mServerIp(168829541)
	, mServerPort(5060)
	, mStartNo(0)
	, mTotalNum(0)
	, mTotalNumShow(0)
	, mOnlineNum(0)
	, mSuccCall(0)
	, mCallHz(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSipDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_IPAddress(pDX, IDC_IPADDR_SVR_IP, mServerIp);
	DDX_Text(pDX, IDC_EDIT_SVR_PORT, mServerPort);
	DDX_Text(pDX, IDC_EDIT_START_NO, mStartNo);
	DDX_Text(pDX, IDC_EDIT_TOTAL_NUM, mTotalNum);
	DDX_Text(pDX, IDC_EDIT_TOTAL_NUM_SHOW, mTotalNumShow);
	DDX_Text(pDX, IDC_EDIT_ONLINE_NUM, mOnlineNum);
	DDX_Text(pDX, IDC_EDIT_SUCCESS_CALL, mSuccCall);
	DDX_Text(pDX, IDC_EDIT_CALL_HZ, mCallHz);
}

BEGIN_MESSAGE_MAP(CSipDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_REGISTER, &CSipDemoDlg::OnBnClickedBtnRegister)
	ON_BN_CLICKED(IDC_BTN_CALL, &CSipDemoDlg::OnBnClickedBtnCall)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CSipDemoDlg::OnBnClickedBtnExit)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSipDemoDlg 消息处理程序

BOOL CSipDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	HPR_Init();
	parser_init();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSipDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSipDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSipDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSipDemoDlg::OnBnClickedBtnRegister()
{
	// TODO: 在此添加控件通知处理程序代码
	if (UpdateData() == 0)
	{
		return;
	}
	mNetwork.start(mServerIp, mServerPort);
	ClientMgr::createInstance()->init(mStartNo, mTotalNum);
	mTotalNumShow = mTotalNum;

	ClientMgr::getInstance()->sendRegister(mNetwork);
	//mHaveRegister = TRUE;
	SetTimer(1, 10*1000, NULL);
	SetTimer(2, 2*60*1000, NULL);
	SetTimer(3, 5*60*1000, NULL);

}

void CSipDemoDlg::OnBnClickedBtnCall()
{
	// TODO: 在此添加控件通知处理程序代码
	if (UpdateData() == 0)
	{
		return;
	}

	ClientMgr::getInstance()->sendCalling(mNetwork, mCallHz);
	SetTimer(4, 1000, NULL);
}

void CSipDemoDlg::OnBnClickedBtnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	mNetwork.stop();
}

void CSipDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		mOnlineNum = ClientMgr::getInstance()->getOnlineNum();
		mSuccCall = ClientMgr::getInstance()->getDelayNumber();

		UpdateData(FALSE);
		if (mOnlineNum < mTotalNumShow)
		{
			ClientMgr::getInstance()->sendRegister(mNetwork);
		}
	}
	else if (nIDEvent == 2)
	{
		ClientMgr::getInstance()->sendHeartbeat(mNetwork);
	}
	else if (nIDEvent == 3)
	{
		ClientMgr::getInstance()->checkOnline();
	}
	else if (nIDEvent == 4)
	{
		ClientMgr::getInstance()->sendCalling(mNetwork, mCallHz);
	}
	CDialog::OnTimer(nIDEvent);
}
