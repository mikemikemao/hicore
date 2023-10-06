// SipDemoDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSipDemoDlg �Ի���




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


// CSipDemoDlg ��Ϣ�������

BOOL CSipDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	HPR_Init();
	parser_init();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSipDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSipDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSipDemoDlg::OnBnClickedBtnRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (UpdateData() == 0)
	{
		return;
	}

	ClientMgr::getInstance()->sendCalling(mNetwork, mCallHz);
	SetTimer(4, 1000, NULL);
}

void CSipDemoDlg::OnBnClickedBtnExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mNetwork.stop();
}

void CSipDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
