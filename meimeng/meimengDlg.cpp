
// meimengDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "meimeng.h"
#include "meimengDlg.h"
#include "afxdialogex.h"

#include "D://opencv//CvvImage.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/types_c.h>  
#include <opencv2/imgproc/imgproc_c.h>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/imgcodecs/imgcodecs_c.h>  
#include "Resource.h"
 

#include "string"
#include <iostream>

using namespace cv;
using namespace std; 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CmeimengDlg �Ի���




CmeimengDlg::CmeimengDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmeimengDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmeimengDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmeimengDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &CmeimengDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_WHITE, &CmeimengDlg::OnBnClickedWhite)
	ON_BN_CLICKED(IDC_SHARK, &CmeimengDlg::OnBnClickedShark)
END_MESSAGE_MAP()


// CmeimengDlg ��Ϣ�������

BOOL CmeimengDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

		

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


//����opencv��ʾ����
void CmeimengDlg::DrawPicToHDC(IplImage *img, UINT ID)
	{
		CDC *pDC = GetDlgItem(ID)->GetDC();
		HDC hDC= pDC->GetSafeHdc();
		CRect rect;GetDlgItem(ID)->GetClientRect(&rect);
		CvvImage cimg;cimg.CopyOf( img ); // ����ͼƬ
		cimg.DrawToHDC( hDC, &rect ); // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������ReleaseDC( pDC );
	}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmeimengDlg::OnPaint()
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

		/*���ñ�����ɫ*/
        CRect rect; 
        CPaintDC dc(this); 
        GetClientRect(rect); 
        dc.FillSolidRect(rect,RGB(255,180,43));  //��ɫ�����Լ��������
		/*���ñ�����ɫ����*/

		/*������·����*/
		

		char *path="D:\\�ҵ��ĵ�\\Visual Studio 2010\\Projects\\xiuxiu\\xiuxiu\\res\\mid.jpg";
		IplImage *image=NULL; //ԭʼͼ��
		if(image) cvReleaseImage(&image);
		image = cvLoadImage(path,1); //��ʾͼƬ
		//MessageBox(_T("��ӭʹ�����ȣ�"));
		DrawPicToHDC(image, IDC_STATIC_PIC);

		  /*������·��������*/

		CDialogEx::OnPaint();


	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmeimengDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


char *path="D:\\img\\zw.bmp";

void CmeimengDlg::OnBnClickedOpen()
{
	IplImage *image=NULL; //ԭʼͼ��
	if(image) cvReleaseImage(&image);
	image = cvLoadImage(path,1); //��ʾͼƬ
	DrawPicToHDC(image, IDC_STATIC_PIC);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CmeimengDlg::OnBnClickedWhite()
{
	IplImage *Limage ;
	
	
	Mat Mimage=imread(path);
	
	Limage=&(IplImage)Mimage;
	//result=Mat::zeros( Mimage.size(), Mimage.type() );//����һ��ͬ����С�ľ���
	double alpha=0.9;
	double beta=1-alpha;
	for(int i=0;i<Mimage.rows;i++)
	{
		for(int j=0;j<Mimage.cols;j++)
		{
			 for( int c = 0; c < 3; c++ )
            {
                //Mimage.at<Vec3b>(i,j)[c] = saturate_cast<uchar>( alpha*( Mimage.at<Vec3b>(i,j)[c] ) + beta );
				Mimage.at<Vec3b>(i,j)[c] =alpha*Mimage.at<Vec3b>(i,j)[c]+beta*255; 
            }
		}
	}

	DrawPicToHDC(Limage, IDC_STATIC_PIC);
}


void CmeimengDlg::OnBnClickedShark()
{
	int MAX_KERNEL_LENGTH = 31;
	IplImage *Limage ;
	Mat Mimage=imread(path);
	Limage=&(IplImage)Mimage;

	IplImage *LFimage ;
	Mat MFimage;


	for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    { 
		bilateralFilter ( Mimage, MFimage, i, i*2, i/2 );

	}
	LFimage=&(IplImage)MFimage;

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DrawPicToHDC(LFimage, IDC_STATIC_PIC);
}
