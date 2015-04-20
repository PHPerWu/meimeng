
// meimengDlg.cpp : 实现文件
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



// CmeimengDlg 对话框




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


// CmeimengDlg 消息处理程序

BOOL CmeimengDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

		

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


//设置opencv显示函数
void CmeimengDlg::DrawPicToHDC(IplImage *img, UINT ID)
	{
		CDC *pDC = GetDlgItem(ID)->GetDC();
		HDC hDC= pDC->GetSafeHdc();
		CRect rect;GetDlgItem(ID)->GetClientRect(&rect);
		CvvImage cimg;cimg.CopyOf( img ); // 复制图片
		cimg.DrawToHDC( hDC, &rect ); // 将图片绘制到显示控件的指定区域内ReleaseDC( pDC );
	}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmeimengDlg::OnPaint()
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

		/*设置背景颜色*/
        CRect rect; 
        CPaintDC dc(this); 
        GetClientRect(rect); 
        dc.FillSolidRect(rect,RGB(255,180,43));  //颜色可以自己随便设置
		/*设置背景颜色结束*/

		/*设置中路背景*/
		

		char *path="D:\\我的文档\\Visual Studio 2010\\Projects\\xiuxiu\\xiuxiu\\res\\mid.jpg";
		IplImage *image=NULL; //原始图像
		if(image) cvReleaseImage(&image);
		image = cvLoadImage(path,1); //显示图片
		//MessageBox(_T("欢迎使用美萌！"));
		DrawPicToHDC(image, IDC_STATIC_PIC);

		  /*设置中路背景结束*/

		CDialogEx::OnPaint();


	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmeimengDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


char *path="D:\\img\\zw.bmp";

void CmeimengDlg::OnBnClickedOpen()
{
	IplImage *image=NULL; //原始图像
	if(image) cvReleaseImage(&image);
	image = cvLoadImage(path,1); //显示图片
	DrawPicToHDC(image, IDC_STATIC_PIC);
	// TODO: 在此添加控件通知处理程序代码
}


void CmeimengDlg::OnBnClickedWhite()
{
	IplImage *Limage ;
	
	
	Mat Mimage=imread(path);
	
	Limage=&(IplImage)Mimage;
	//result=Mat::zeros( Mimage.size(), Mimage.type() );//定义一个同样大小的矩阵
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

	// TODO: 在此添加控件通知处理程序代码
	DrawPicToHDC(LFimage, IDC_STATIC_PIC);
}
