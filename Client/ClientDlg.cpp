
// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientDlg 对话框




CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
	, m_strFileName(_T(""))
	, m_strMessage(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ret = 0;
	m_len = 0;
	m_socketClient = 0;
}

CClientDlg::~CClientDlg(){
	if (m_socketClient)
		closesocket(m_socketClient);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILENAME, m_strFileName);
	DDX_Text(pDX, IDC_MASSAGE, m_strMessage);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CONNECT, &CClientDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_BTN_OPENFILE, &CClientDlg::OnBnClickedBtnOpenfile)
	ON_BN_CLICKED(IDC_BTN_SEND, &CClientDlg::OnBnClickedBtnSend)
END_MESSAGE_MAP()


// CClientDlg 消息处理程序

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitSocket();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClientDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CClientDlg::InitSocket(void)
{
	//2.创建套接字:(af)指定地址族,对于TCP/IP协议的套接字,它只能是AF_INET(也可以写成PF_INET)、SOCKE_STREAM指定产生流式套接字
// 	m_socketClient=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
// 	if (INVALID_SOCKET==m_socketClient){
// 		MessageBox("socket 错误");
// 		return false;
// 	}
// 	//3.设置服务器地址
// 	addrServer.sin_addr.S_un.S_addr=inet_addr(SERVERIP);
// 	addrServer.sin_family=AF_INET;
// 	addrServer.sin_port=htons(SERVERPORT);
// 	m_len=sizeof(sockaddr);
// 	m_strMessage+="客户端初始化完成!!!\r\n";
// 	//SetDlgItemText(IDC_MASSAGE,m_strMessage);
// 	UpdateData(FALSE);//向控件传递数据
 	return true;
}


void CClientDlg::OnBnClickedOk() 
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnOK();
}


void CClientDlg::OnBnClickedConnect()
{
	//2.创建套接字:(af)指定地址族,对于TCP/IP协议的套接字,它只能是AF_INET(也可以写成PF_INET)、SOCKE_STREAM指定产生流式套接字
	m_socketClient=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (INVALID_SOCKET==m_socketClient){
		MessageBox("socket 错误");
		return ;
	}
	//3.设置服务器地址
	addrServer.sin_addr.S_un.S_addr=inet_addr(SERVERIP);
	addrServer.sin_family=AF_INET;
	addrServer.sin_port=htons(SERVERPORT);
	m_len=sizeof(sockaddr);
	m_strMessage+="客户端初始化完成!!!\r\n";

	// TODO: Add your control notification handler code here
	//4.连接服务器
	m_ret=connect(m_socketClient,(sockaddr*)&addrServer,m_len);
	if (SOCKET_ERROR==m_ret){
		MessageBox("connect 错误");
		return ;
	}
	m_strMessage+="连接服务器成功，下面开始通信...\r\n";
	//UpdateData(FALSE);
	//5.接受数据
	memset(m_recvBuf,0,sizeof(m_recvBuf));
	m_ret=recv(m_socketClient,m_recvBuf,sizeof(m_recvBuf),0);
	if (SOCKET_ERROR==m_ret){
		MessageBox("recv 错误");
		return ;
	}
	CString str_recvBuf;
	str_recvBuf.Format("%s",m_recvBuf);
	m_strMessage+="从服务器收到以下信息:\r\n"+str_recvBuf+"\r\n";
	UpdateData(FALSE);

}

void CClientDlg::OnBnClickedBtnOpenfile()
{
	// TODO: Add your control notification handler code here
	CString defaultDir = NULL;   //默认打开的文件路径  
	CString fileName = "test.zip";         //默认打开的文件名  
	CString filter = NULL;//"文件 (*.doc; *.ppt; *.xls)|(*.doc;*.ppt;*.xls)|*.zip|*||";   //文件过虑的类型  
	CFileDialog openFileDlg(TRUE, defaultDir, fileName, OFN_HIDEREADONLY|OFN_READONLY, filter, NULL);  
	if(openFileDlg.DoModal() == IDOK) {  
		CString filePath = openFileDlg.GetPathName();  
		m_strFileName=filePath;
		UpdateData(FALSE);
	}else{
		MessageBox("openFileDlg.DoModal()出错");
		return;
	}
}

void CClientDlg::OnBnClickedBtnSend()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_strFileName=="")
	{
		MessageBox("请输入要传输的文件名！！");
		return;
	}
	fp=fopen(m_strFileName,"rb");
	if(fp == NULL){  
		MessageBox("open file "+m_strFileName+" failed\r\n");
		return ;  
	} 
	m_strMessage+="打开文件："+m_strFileName+"成功\r\n\r\n";

	//将文件名发送过去
	//int fileNameNum=sizeof(m_strFileName);
	m_ret=send(m_socketClient,m_strFileName,512,0);
	if (SOCKET_ERROR==m_ret){
		MessageBox("send 文件名 错误");
		return ;
	}
	//6.将文件拆分一次次放入缓冲区，向服务器一次次发送temp
	int num=0;
	while(!feof(fp)){//检测流上的文件结束符，如果文件结束，则返回非0值，否则返回0，文件结束符只能被clearerr()清除
		/*size_t fread ( void *buffer, size_t size, size_t count, FILE *stream) ;
		buffer		   用于接收数据的内存地址
		size		   要读的每个数据项的字节数，单位是字节
		count		   要读count个数据项，每个数据项size个字节.
		stream		   输入流*/
		num=fread(m_sendBuf,1,512,fp);
		m_ret=send(m_socketClient,m_sendBuf,num,0);
		if (SOCKET_ERROR==m_ret){
			MessageBox("send 错误");
			return ;
		}
	}
	m_strMessage+="文件传输成功!\r\n";
	UpdateData(FALSE);

	//7.关闭文件
	fclose(fp);
	// TODO: Add your control notification handler code here
	//8.shutdown()函数用于任何类型的套接口禁止接收、禁止发送或禁止收发。
	// 并不关闭套接口，且套接口所占有的资源将被一直保持到closesocket()调用。
	// 选择SE_SEND,则表示不允许再调用发送函数
	m_ret=shutdown(m_socketClient,SD_SEND);
	if(m_ret == SOCKET_ERROR){  
		MessageBox("server shutdown failed \r\n"+WSAGetLastError());
		return ;  
	} 
	//m_strMessage+="套接字关闭成功！";
	UpdateData(FALSE);
}

