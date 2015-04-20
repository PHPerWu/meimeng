
// meimengDlg.h : ͷ�ļ�
//

#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/types_c.h>  
#include <opencv2/imgproc/imgproc_c.h>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/imgcodecs/imgcodecs_c.h>  
#include <iostream>
#include "Resource.h"
#include "afxcmn.h"
#include "afxwin.h"

using namespace cv;
using namespace std; 


// CmeimengDlg �Ի���
class CmeimengDlg : public CDialogEx
{
// ����
public:
	CmeimengDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MEIMENG_DIALOG };

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
	afx_msg void OnBnClickedOpen();
	afx_msg void DrawPicToHDC(IplImage *img, UINT ID);
	afx_msg void OnBnClickedWhite();
	afx_msg void OnBnClickedShark();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
