
// MusicPlayerDlg.h : 头文件
//

#pragma once
#include<mmsystem.h>
#include<Digitalv.h>
#include "afxcmn.h"
#pragma comment(lib, "winmm.lib")

// CMusicPlayerDlg 对话框
class CMusicPlayerDlg : public CDialogEx
{
// 构造
public:
	CMusicPlayerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MUSICPLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
