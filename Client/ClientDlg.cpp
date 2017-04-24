
// ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientDlg �Ի���




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


// CClientDlg ��Ϣ�������

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitSocket();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClientDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CClientDlg::InitSocket(void)
{
	//2.�����׽���:(af)ָ����ַ��,����TCP/IPЭ����׽���,��ֻ����AF_INET(Ҳ����д��PF_INET)��SOCKE_STREAMָ��������ʽ�׽���
// 	m_socketClient=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
// 	if (INVALID_SOCKET==m_socketClient){
// 		MessageBox("socket ����");
// 		return false;
// 	}
// 	//3.���÷�������ַ
// 	addrServer.sin_addr.S_un.S_addr=inet_addr(SERVERIP);
// 	addrServer.sin_family=AF_INET;
// 	addrServer.sin_port=htons(SERVERPORT);
// 	m_len=sizeof(sockaddr);
// 	m_strMessage+="�ͻ��˳�ʼ�����!!!\r\n";
// 	//SetDlgItemText(IDC_MASSAGE,m_strMessage);
// 	UpdateData(FALSE);//��ؼ���������
 	return true;
}


void CClientDlg::OnBnClickedOk() 
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnOK();
}


void CClientDlg::OnBnClickedConnect()
{
	//2.�����׽���:(af)ָ����ַ��,����TCP/IPЭ����׽���,��ֻ����AF_INET(Ҳ����д��PF_INET)��SOCKE_STREAMָ��������ʽ�׽���
	m_socketClient=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (INVALID_SOCKET==m_socketClient){
		MessageBox("socket ����");
		return ;
	}
	//3.���÷�������ַ
	addrServer.sin_addr.S_un.S_addr=inet_addr(SERVERIP);
	addrServer.sin_family=AF_INET;
	addrServer.sin_port=htons(SERVERPORT);
	m_len=sizeof(sockaddr);
	m_strMessage+="�ͻ��˳�ʼ�����!!!\r\n";

	// TODO: Add your control notification handler code here
	//4.���ӷ�����
	m_ret=connect(m_socketClient,(sockaddr*)&addrServer,m_len);
	if (SOCKET_ERROR==m_ret){
		MessageBox("connect ����");
		return ;
	}
	m_strMessage+="���ӷ������ɹ������濪ʼͨ��...\r\n";
	//UpdateData(FALSE);
	//5.��������
	memset(m_recvBuf,0,sizeof(m_recvBuf));
	m_ret=recv(m_socketClient,m_recvBuf,sizeof(m_recvBuf),0);
	if (SOCKET_ERROR==m_ret){
		MessageBox("recv ����");
		return ;
	}
	CString str_recvBuf;
	str_recvBuf.Format("%s",m_recvBuf);
	m_strMessage+="�ӷ������յ�������Ϣ:\r\n"+str_recvBuf+"\r\n";
	UpdateData(FALSE);

}

void CClientDlg::OnBnClickedBtnOpenfile()
{
	// TODO: Add your control notification handler code here
	CString defaultDir = NULL;   //Ĭ�ϴ򿪵��ļ�·��  
	CString fileName = "test.zip";         //Ĭ�ϴ򿪵��ļ���  
	CString filter = NULL;//"�ļ� (*.doc; *.ppt; *.xls)|(*.doc;*.ppt;*.xls)|*.zip|*||";   //�ļ����ǵ�����  
	CFileDialog openFileDlg(TRUE, defaultDir, fileName, OFN_HIDEREADONLY|OFN_READONLY, filter, NULL);  
	if(openFileDlg.DoModal() == IDOK) {  
		CString filePath = openFileDlg.GetPathName();  
		m_strFileName=filePath;
		UpdateData(FALSE);
	}else{
		MessageBox("openFileDlg.DoModal()����");
		return;
	}
}

void CClientDlg::OnBnClickedBtnSend()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_strFileName=="")
	{
		MessageBox("������Ҫ������ļ�������");
		return;
	}
	fp=fopen(m_strFileName,"rb");
	if(fp == NULL){  
		MessageBox("open file "+m_strFileName+" failed\r\n");
		return ;  
	} 
	m_strMessage+="���ļ���"+m_strFileName+"�ɹ�\r\n\r\n";

	//���ļ������͹�ȥ
	//int fileNameNum=sizeof(m_strFileName);
	m_ret=send(m_socketClient,m_strFileName,512,0);
	if (SOCKET_ERROR==m_ret){
		MessageBox("send �ļ��� ����");
		return ;
	}
	//6.���ļ����һ�δη��뻺�������������һ�δη���temp
	int num=0;
	while(!feof(fp)){//������ϵ��ļ�������������ļ��������򷵻ط�0ֵ�����򷵻�0���ļ�������ֻ�ܱ�clearerr()���
		/*size_t fread ( void *buffer, size_t size, size_t count, FILE *stream) ;
		buffer		   ���ڽ������ݵ��ڴ��ַ
		size		   Ҫ����ÿ����������ֽ�������λ���ֽ�
		count		   Ҫ��count�������ÿ��������size���ֽ�.
		stream		   ������*/
		num=fread(m_sendBuf,1,512,fp);
		m_ret=send(m_socketClient,m_sendBuf,num,0);
		if (SOCKET_ERROR==m_ret){
			MessageBox("send ����");
			return ;
		}
	}
	m_strMessage+="�ļ�����ɹ�!\r\n";
	UpdateData(FALSE);

	//7.�ر��ļ�
	fclose(fp);
	// TODO: Add your control notification handler code here
	//8.shutdown()���������κ����͵��׽ӿڽ�ֹ���ա���ֹ���ͻ��ֹ�շ���
	// �����ر��׽ӿڣ����׽ӿ���ռ�е���Դ����һֱ���ֵ�closesocket()���á�
	// ѡ��SE_SEND,���ʾ�������ٵ��÷��ͺ���
	m_ret=shutdown(m_socketClient,SD_SEND);
	if(m_ret == SOCKET_ERROR){  
		MessageBox("server shutdown failed \r\n"+WSAGetLastError());
		return ;  
	} 
	//m_strMessage+="�׽��ֹرճɹ���";
	UpdateData(FALSE);
}

