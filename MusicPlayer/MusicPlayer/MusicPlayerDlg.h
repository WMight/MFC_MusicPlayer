
// MusicPlayerDlg.h : ͷ�ļ�
//

#pragma once
#include<mmsystem.h>
#include<Digitalv.h>
#include "afxcmn.h"
#pragma comment(lib, "winmm.lib")

// CMusicPlayerDlg �Ի���
class CMusicPlayerDlg : public CDialogEx
{
// ����
public:
	CMusicPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MUSICPLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	MCIDEVICEID m_DeviceID;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnBnClickedBtnStop();
	CSliderCtrl m_slider;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	int m_nVolume;
	afx_msg void OnEnChangeEdit1();
};
