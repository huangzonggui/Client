
// ClientDlg.h : 头文件
//

#pragma once


// CClientDlg 对话框
class CClientDlg : public CDialogEx
{
// 构造
public:
	CClientDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CClientDlg();

// 对话框数据
	enum { IDD = IDD_CLIENT_DIALOG };

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
	CString m_strFileName;
	CString m_strMessage;
	struct sockaddr_in addrServer;
private:
	SOCKET m_socketClient;
public:
	int m_ret;
	int m_len;
	char m_sendBuf[512];
	char m_recvBuf[512];
	FILE *fp;
	bool InitSocket(void);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedBtnOpenfile();
	afx_msg void OnBnClickedBtnSend();
};
