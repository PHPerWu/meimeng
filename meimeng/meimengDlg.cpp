
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
	ON_WM_DRAWITEM()
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


void CmeimengDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	
	//switch(nIDCtl)//判断不同按钮的ID
	//{
	//	case 1002:
			if(1002==nIDCtl)
			{
				CDC ButtonDC; 
				CBitmap bitmapTrans; 
				BITMAP bmp; 
				CDC mem; 
				CRect rc; 
				//得到用于绘制按钮的DC 
				ButtonDC.Attach(lpDrawItemStruct->hDC); 
				//准备用于向按钮区域传输位图 
				mem.CreateCompatibleDC(&ButtonDC); 
				//获取按钮所占的矩形大小 
				rc=lpDrawItemStruct->rcItem; 
				//获取按钮目前所处的状态，根据不同的状态绘制不同的按钮 
				UINT state = lpDrawItemStruct->itemState; 
				//如果按钮已经得到焦点，绘制选中状态下的按钮 
				if(state&ODS_FOCUS) 
				{ 
					bitmapTrans.LoadBitmap(IDB_BITMAP2); 
					bitmapTrans.GetBitmap(&bmp); 
					CBitmap *old=mem.SelectObject(&bitmapTrans); 
					//向按钮所在位置传输位图 
					//使用StretcnBlt的目的是为了让位图随按钮的大小而改变 
					ButtonDC.StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&mem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); 
					mem.SelectObject(old); 
					bitmapTrans.DeleteObject(); 
					//设置文字背景为透明 
					ButtonDC.SetBkMode(TRANSPARENT); 
					CString str1("");
					ButtonDC.DrawText(str1,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 
				} 
				else
				{ 
					bitmapTrans.LoadBitmap(IDB_BITMAP12); 
					CBitmap *old2 = mem.SelectObject(&bitmapTrans); 
					bitmapTrans.GetBitmap(&bmp); 
					CBitmap *old=mem.SelectObject(&bitmapTrans); 
					ButtonDC.StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&mem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); 
					ButtonDC.SetBkMode(TRANSPARENT); 
					CString str2("");
					ButtonDC.DrawText(str2,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 
					mem.SelectObject(old2); 
					bitmapTrans.DeleteObject(); 
					CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
				}
			}//case 1002结束

		/*case 1005:*/
			else if(1005==nIDCtl)
			{
				CDC ButtonDC; 
				CBitmap bitmapTrans; 
				BITMAP bmp; 
				CDC mem; 
				CRect rc; 
				//得到用于绘制按钮的DC 
				ButtonDC.Attach(lpDrawItemStruct->hDC); 
				//准备用于向按钮区域传输位图 
				mem.CreateCompatibleDC(&ButtonDC); 
				//获取按钮所占的矩形大小 
				rc=lpDrawItemStruct->rcItem; 
				//获取按钮目前所处的状态，根据不同的状态绘制不同的按钮 
				UINT state = lpDrawItemStruct->itemState; 
				//如果按钮已经得到焦点，绘制选中状态下的按钮 
				if(state&ODS_FOCUS) 
				{ 
					bitmapTrans.LoadBitmap(IDB_BITMAP5); 
					bitmapTrans.GetBitmap(&bmp); 
					CBitmap *old=mem.SelectObject(&bitmapTrans); 
					//向按钮所在位置传输位图 
					//使用StretcnBlt的目的是为了让位图随按钮的大小而改变 
					ButtonDC.StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&mem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); 
					mem.SelectObject(old); 
					bitmapTrans.DeleteObject(); 
					//设置文字背景为透明 
					ButtonDC.SetBkMode(TRANSPARENT); 
					CString str1("");
					ButtonDC.DrawText(str1,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 
				} 
				else
				{ 
					bitmapTrans.LoadBitmap(IDB_BITMAP15); 
					CBitmap *old2 = mem.SelectObject(&bitmapTrans); 
					bitmapTrans.GetBitmap(&bmp); 
					CBitmap *old=mem.SelectObject(&bitmapTrans); 
					ButtonDC.StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&mem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); 
					ButtonDC.SetBkMode(TRANSPARENT); 
					CString str2("");
					ButtonDC.DrawText(str2,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 
					mem.SelectObject(old2); 
					bitmapTrans.DeleteObject(); 
					CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
				}
			}//case 1005结束

			else if(1001==nIDCtl)
			{
				CDC ButtonDC; 
				CBitmap bitmapTrans; 
				BITMAP bmp; 
				CDC mem; 
				CRect rc; 
				//得到用于绘制按钮的DC 
				ButtonDC.Attach(lpDrawItemStruct->hDC); 
				//准备用于向按钮区域传输位图 
				mem.CreateCompatibleDC(&ButtonDC); 
				//获取按钮所占的矩形大小 
				rc=lpDrawItemStruct->rcItem; 
				//获取按钮目前所处的状态，根据不同的状态绘制不同的按钮 
				UINT state = lpDrawItemStruct->itemState; 
				//如果按钮已经得到焦点，绘制选中状态下的按钮 
				if(state&ODS_FOCUS) 
				{ 
					bitmapTrans.LoadBitmap(IDB_BITMAP1); 
					bitmapTrans.GetBitmap(&bmp); 
					CBitmap *old=mem.SelectObject(&bitmapTrans); 
					//向按钮所在位置传输位图 
					//使用StretcnBlt的目的是为了让位图随按钮的大小而改变 
					ButtonDC.StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&mem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); 
					mem.SelectObject(old); 
					bitmapTrans.DeleteObject(); 
					//设置文字背景为透明 
					ButtonDC.SetBkMode(TRANSPARENT); 
					CString str1("");
					ButtonDC.DrawText(str1,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 
				} 
				else
				{ 
					bitmapTrans.LoadBitmap(IDB_BITMAP11); 
					CBitmap *old2 = mem.SelectObject(&bitmapTrans); 
					bitmapTrans.GetBitmap(&bmp); 
					CBitmap *old=mem.SelectObject(&bitmapTrans); 
					ButtonDC.StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&mem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); 
					ButtonDC.SetBkMode(TRANSPARENT); 
					CString str2("");
					ButtonDC.DrawText(str2,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 
					mem.SelectObject(old2); 
					bitmapTrans.DeleteObject(); 
					CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
				}
			}//case 1001结束
			
			else if(1003==nIDCtl)
			{
				CDC ButtonDC; 
				CBitmap bitmapTrans; 
				BITMAP bmp; 
				CDC mem; 
				CRect rc; 
				//得到用于绘制按钮的DC 
				ButtonDC.Attach(lpDrawItemStruct->hDC); 
				//准备用于向按钮区域传输位图 
				mem.CreateCompatibleDC(&ButtonDC); 
				//获取按钮所占的矩形大小 
				rc=lpDrawItemStruct->rcItem; 
				//获取按钮目前所处的状态，根据不同的状态绘制不同的按钮 
				UINT state = lpDrawItemStruct->itemState; 
				//如果按钮已经得到焦点，绘制选中状态下的按钮 
				if(state&ODS_FOCUS) 
				{ 
					bitmapTrans.LoadBitmap(IDB_BITMAP3); 
					bitmapTrans.GetBitmap(&bmp); 
					CBitmap *old=mem.SelectObject(&bitmapTrans); 
					//向按钮所在位置传输位图 
					//使用StretcnBlt的目的是为了让位图随按钮的大小而改变 
					ButtonDC.StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&mem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); 
					mem.SelectObject(old); 
					bitmapTrans.DeleteObject(); 
					//设置文字背景为透明 
					ButtonDC.SetBkMode(TRANSPARENT); 
					CString str1("");
					ButtonDC.DrawText(str1,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 
				} 
				else
				{ 
					bitmapTrans.LoadBitmap(IDB_BITMAP13); 
					CBitmap *old2 = mem.SelectObject(&bitmapTrans); 
					bitmapTrans.GetBitmap(&bmp); 
					CBitmap *old=mem.SelectObject(&bitmapTrans); 
					ButtonDC.StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&mem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); 
					ButtonDC.SetBkMode(TRANSPARENT); 
					CString str2("");
					ButtonDC.DrawText(str2,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 
					mem.SelectObject(old2); 
					bitmapTrans.DeleteObject(); 
					CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
				}
			}//case 1003结束

			else if(1004==nIDCtl)
			{
				CDC ButtonDC; 
				CBitmap bitmapTrans; 
				BITMAP bmp; 
				CDC mem; 
				CRect rc; 
				//得到用于绘制按钮的DC 
				ButtonDC.Attach(lpDrawItemStruct->hDC); 
				//准备用于向按钮区域传输位图 
				mem.CreateCompatibleDC(&ButtonDC); 
				//获取按钮所占的矩形大小 
				rc=lpDrawItemStruct->rcItem; 
				//获取按钮目前所处的状态，根据不同的状态绘制不同的按钮 
				UINT state = lpDrawItemStruct->itemState; 
				//如果按钮已经得到焦点，绘制选中状态下的按钮 
				if(state&ODS_FOCUS) 
				{ 
					bitmapTrans.LoadBitmap(IDB_BITMAP4); 
					bitmapTrans.GetBitmap(&bmp); 
					CBitmap *old=mem.SelectObject(&bitmapTrans); 
					//向按钮所在位置传输位图 
					//使用StretcnBlt的目的是为了让位图随按钮的大小而改变 
					ButtonDC.StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&mem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); 
					mem.SelectObject(old); 
					bitmapTrans.DeleteObject(); 
					//设置文字背景为透明 
					ButtonDC.SetBkMode(TRANSPARENT); 
					CString str1("");
					ButtonDC.DrawText(str1,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 
				} 
				else
				{ 
					bitmapTrans.LoadBitmap(IDB_BITMAP14); 
					CBitmap *old2 = mem.SelectObject(&bitmapTrans); 
					bitmapTrans.GetBitmap(&bmp); 
					CBitmap *old=mem.SelectObject(&bitmapTrans); 
					ButtonDC.StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&mem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); 
					ButtonDC.SetBkMode(TRANSPARENT); 
					CString str2("");
					ButtonDC.DrawText(str2,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 
					mem.SelectObject(old2); 
					bitmapTrans.DeleteObject(); 
					CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
				}
			}//case 1004结束

			else if(1006==nIDCtl)
			{
				CDC ButtonDC; 
				CBitmap bitmapTrans; 
				BITMAP bmp; 
				CDC mem; 
				CRect rc; 
				//得到用于绘制按钮的DC 
				ButtonDC.Attach(lpDrawItemStruct->hDC); 
				//准备用于向按钮区域传输位图 
				mem.CreateCompatibleDC(&ButtonDC); 
				//获取按钮所占的矩形大小 
				rc=lpDrawItemStruct->rcItem; 
				//获取按钮目前所处的状态，根据不同的状态绘制不同的按钮 
				UINT state = lpDrawItemStruct->itemState; 
				//如果按钮已经得到焦点，绘制选中状态下的按钮 
				if(state&ODS_FOCUS) 
				{ 
					bitmapTrans.LoadBitmap(IDB_BITMAP6); 
					bitmapTrans.GetBitmap(&bmp); 
					CBitmap *old=mem.SelectObject(&bitmapTrans); 
					//向按钮所在位置传输位图 
					//使用StretcnBlt的目的是为了让位图随按钮的大小而改变 
					ButtonDC.StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&mem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); 
					mem.SelectObject(old); 
					bitmapTrans.DeleteObject(); 
					//设置文字背景为透明 
					ButtonDC.SetBkMode(TRANSPARENT); 
					CString str1("");
					ButtonDC.DrawText(str1,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 
				} 
				else
				{ 
					bitmapTrans.LoadBitmap(IDB_BITMAP16); 
					CBitmap *old2 = mem.SelectObject(&bitmapTrans); 
					bitmapTrans.GetBitmap(&bmp); 
					CBitmap *old=mem.SelectObject(&bitmapTrans); 
					ButtonDC.StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&mem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); 
					ButtonDC.SetBkMode(TRANSPARENT); 
					CString str2("");
					ButtonDC.DrawText(str2,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 
					mem.SelectObject(old2); 
					bitmapTrans.DeleteObject(); 
					CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
				}
			}//case 1006结束

			else if(1007==nIDCtl)
			{
				CDC ButtonDC; 
				CBitmap bitmapTrans; 
				BITMAP bmp; 
				CDC mem; 
				CRect rc; 
				//得到用于绘制按钮的DC 
				ButtonDC.Attach(lpDrawItemStruct->hDC); 
				//准备用于向按钮区域传输位图 
				mem.CreateCompatibleDC(&ButtonDC); 
				//获取按钮所占的矩形大小 
				rc=lpDrawItemStruct->rcItem; 
				//获取按钮目前所处的状态，根据不同的状态绘制不同的按钮 
				UINT state = lpDrawItemStruct->itemState; 
				//如果按钮已经得到焦点，绘制选中状态下的按钮 
				if(state&ODS_FOCUS) 
				{ 
					bitmapTrans.LoadBitmap(IDB_BITMAP7); 
					bitmapTrans.GetBitmap(&bmp); 
					CBitmap *old=mem.SelectObject(&bitmapTrans); 
					//向按钮所在位置传输位图 
					//使用StretcnBlt的目的是为了让位图随按钮的大小而改变 
					ButtonDC.StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&mem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); 
					mem.SelectObject(old); 
					bitmapTrans.DeleteObject(); 
					//设置文字背景为透明 
					ButtonDC.SetBkMode(TRANSPARENT); 
					CString str1("");
					ButtonDC.DrawText(str1,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 
				} 
				else
				{ 
					bitmapTrans.LoadBitmap(IDB_BITMAP17); 
					CBitmap *old2 = mem.SelectObject(&bitmapTrans); 
					bitmapTrans.GetBitmap(&bmp); 
					CBitmap *old=mem.SelectObject(&bitmapTrans); 
					ButtonDC.StretchBlt(rc.left,rc.top,rc.right,rc.bottom,&mem,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY); 
					ButtonDC.SetBkMode(TRANSPARENT); 
					CString str2("");
					ButtonDC.DrawText(str2,&rc,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 
					mem.SelectObject(old2); 
					bitmapTrans.DeleteObject(); 
					CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
				}
			}//case 1007结束

	//switch结束
    /*CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct); */
}
