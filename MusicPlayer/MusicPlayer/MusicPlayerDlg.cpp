
// MusicPlayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include "MusicPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMusicPlayerDlg �Ի���



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


// CMusicPlayerDlg ��Ϣ�������

BOOL CMusicPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_slider.SetRange(0, 1000);
	m_slider.SetPos(200);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMusicPlayerDlg::OnPaint()
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
HCURSOR CMusicPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMusicPlayerDlg::OnBnClickedBtnOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"MP3�ļ�(*.mp3)|*.mp3|WMA�ļ�(*.wma)|*.wma|WAV�ļ�(*.wav)|*.wav|�����ļ�(*.*)|*.*||");
	if (IDCANCEL == dlg.DoModal())
		return;

	//��ȡ·��
	CString strMusicFile = dlg.GetPathName();

	//��
	MCI_OPEN_PARMS mciOpenParams;
	mciOpenParams.lpstrElementName = strMusicFile;
	MCIERROR mciErro =  mciSendCommand(NULL , MCI_OPEN, MCI_OPEN_ELEMENT|MCI_WAIT, (DWORD)&mciOpenParams);
	if (mciErro)
	{
		wchar_t szErrorMsg[256];
		//��ȡ������Ϣ
		mciGetErrorString(mciErro, szErrorMsg, 256);
		MessageBox(szErrorMsg, L"���ֲ�����");
		return;
	}
	m_DeviceID = mciOpenParams.wDeviceID;
	
	//�򿪼�����
	//OnBnClickedBtnPlay();
}

//����
void CMusicPlayerDlg::OnBnClickedBtnPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MCI_PLAY_PARMS mciPlayParms;
	mciPlayParms.dwCallback = NULL;
	mciPlayParms.dwFrom = 0;

	mciSendCommand(m_DeviceID, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)&mciPlayParms);
}


void CMusicPlayerDlg::OnBnClickedBtnPause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_BTN_PAUSE, str);

	if (str == L"��ͣ")
	{
		mciSendCommand(m_DeviceID, MCI_PAUSE, 0, 0);
		SetDlgItemText(IDC_BTN_PAUSE, L"����");
	}
	else if (str == L"����")
	{
		mciSendCommand(m_DeviceID, MCI_RESUME, 0, 0);
		SetDlgItemText(IDC_BTN_PAUSE, L"��ͣ");
	}
}

//ֹͣ
void CMusicPlayerDlg::OnBnClickedBtnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mciSendCommand(m_DeviceID, MCI_STOP, 0, 0);
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);
}


void CMusicPlayerDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��ȡ���㻬���ؼ�λ��
	m_nVolume = m_slider.GetPos() / 10 ;
	UpdateData(FALSE);
	//��������
	MCI_DGV_SETAUDIO_PARMS mciSetVolume;
	mciSetVolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciSetVolume.dwValue = m_slider.GetPos();
	mciSendCommand(m_DeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)&mciSetVolume);
	*pResult = 0;
}


void CMusicPlayerDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
