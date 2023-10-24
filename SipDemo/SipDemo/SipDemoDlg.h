// SipDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "Network.h"

// CSipDemoDlg �Ի���
class CSipDemoDlg : public CDialog
{
// ����
public:
	CSipDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SIPDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnRegister();
public:
	DWORD mServerIp;
	UINT mServerPort;
	Network mNetwork;
	UINT mStartNo;
	UINT mTotalNum;
	UINT mTotalNumShow;
	UINT mOnlineNum;
	DWORD mSuccCall;
	afx_msg void OnBnClickedBtnCall();
	UINT mCallHz;
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
