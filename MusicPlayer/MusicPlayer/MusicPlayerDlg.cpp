
// MusicPlayerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include "MusicPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMusicPlayerDlg 对话框



CMusicPlayerDlg::CMusicPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MUSICPLAYER_DIALOG, pParent)
	, m_nVolume(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_DeviceID = 0;
}

void CMusicPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Text(pDX, IDC_EDIT1, m_nVolume);
}

BEGIN_MESSAGE_MAP(CMusicPlayerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CMusicPlayerDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_PLAY, &CMusicPlayerDlg::OnBnClickedBtnPlay)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CMusicPlayerDlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_STOP, &CMusicPlayerDlg::OnBnClickedBtnStop)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CMusicPlayerDlg::OnNMCustomdrawSlider1)
	ON_EN_CHANGE(IDC_EDIT1, &CMusicPlayerDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CMusicPlayerDlg 消息处理程序

BOOL CMusicPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_slider.SetRange(0, 1000);
	m_slider.SetPos(200);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMusicPlayerDlg::OnPaint()
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
HCURSOR CMusicPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMusicPlayerDlg::OnBnClickedBtnOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"MP3文件(*.mp3)|*.mp3|WMA文件(*.wma)|*.wma|WAV文件(*.wav)|*.wav|所有文件(*.*)|*.*||");
	if (IDCANCEL == dlg.DoModal())
		return;

	//获取路径
	CString strMusicFile = dlg.GetPathName();

	//打开
	MCI_OPEN_PARMS mciOpenParams;
	mciOpenParams.lpstrElementName = strMusicFile;
	MCIERROR mciErro =  mciSendCommand(NULL , MCI_OPEN, MCI_OPEN_ELEMENT|MCI_WAIT, (DWORD)&mciOpenParams);
	if (mciErro)
	{
		wchar_t szErrorMsg[256];
		//获取错误信息
		mciGetErrorString(mciErro, szErrorMsg, 256);
		MessageBox(szErrorMsg, L"音乐播放器");
		return;
	}
	m_DeviceID = mciOpenParams.wDeviceID;
	
	//打开即播放
	//OnBnClickedBtnPlay();
}

//播放
void CMusicPlayerDlg::OnBnClickedBtnPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	MCI_PLAY_PARMS mciPlayParms;
	mciPlayParms.dwCallback = NULL;
	mciPlayParms.dwFrom = 0;

	mciSendCommand(m_DeviceID, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)&mciPlayParms);
}


void CMusicPlayerDlg::OnBnClickedBtnPause()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItemText(IDC_BTN_PAUSE, str);

	if (str == L"暂停")
	{
		mciSendCommand(m_DeviceID, MCI_PAUSE, 0, 0);
		SetDlgItemText(IDC_BTN_PAUSE, L"继续");
	}
	else if (str == L"继续")
	{
		mciSendCommand(m_DeviceID, MCI_RESUME, 0, 0);
		SetDlgItemText(IDC_BTN_PAUSE, L"暂停");
	}
}

//停止
void CMusicPlayerDlg::OnBnClickedBtnStop()
{
	// TODO: 在此添加控件通知处理程序代码
	mciSendCommand(m_DeviceID, MCI_STOP, 0, 0);
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);
}


void CMusicPlayerDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	//获取当点滑动控件位置
	m_nVolume = m_slider.GetPos() / 10 ;
	UpdateData(FALSE);
	//发送命令
	MCI_DGV_SETAUDIO_PARMS mciSetVolume;
	mciSetVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciSetVolume.dwValue = m_slider.GetPos();
	mciSendCommand(m_DeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)&mciSetVolume);
	*pResult = 0;
}


void CMusicPlayerDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
