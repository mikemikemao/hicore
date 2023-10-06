// SipDemoDlg.h : 头文件
//

#pragma once
#include "Network.h"

// CSipDemoDlg 对话框
class CSipDemoDlg : public CDialog
{
// 构造
public:
	CSipDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SIPDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
