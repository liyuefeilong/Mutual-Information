
// 互信息校准测试Dlg.h : 头文件
//

#pragma once
#include "cv.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include "opencv2/calib3d/calib3d.hpp"
#include "highgui.h"
#include "CvvImage.h"
#include <vector>
#include "afxwin.h"

using namespace cv;
using namespace std;


// C互信息校准测试Dlg 对话框
class C互信息校准测试Dlg : public CDialogEx
{
// 构造
public:
	C互信息校准测试Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:


	vector<CPoint> m_newpoints; // 需要利用互信息子函数更新得到的匹配点集（要求四个） 
	vector<CPoint> m_points1;// 视频帧图像匹配点集（要求四个）
	vector<CPoint> m_points2;// 全景图像匹配点集，初始匹配点集（要求四个）

	Mat TheImage; //全景图
	Mat CamImage; //视频帧图像

	CStatic m_TheImage;//是全景图界面的显示窗口
	CStatic m_CamImage;//是视频帧图像界面的显示窗口

	CRect m_TheImageRect;//显示全景窗口的矩形窗
	CRect m_CamImageRect;//显示视频窗口的矩形窗

	

	CvCapture *capture;


public:
	BOOL m_PicturePointdownflag; //全景图特征选取标记位
	BOOL m_VideoPointdownflag;  //视频帧图像特征选取标记位


public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedOpenPicture();
	afx_msg void OnBnClickedOpenVideo();
	afx_msg void OnBnClickedPicturePoint();
	afx_msg void OnBnClickedVideoPoint();
	afx_msg void OnBnClickedAdujst();

public:

	void ShowMatImgToWnd(CWnd* pWnd, cv::Mat img);

	double Entropy(Mat img);//单幅图像信息熵计算	
	double ComEntropy(Mat img1, Mat img2, double img1_entropy, double img2_entropy);// 两幅图像联合信息熵计算	
	vector<CPoint> Refresh_MacthPoints(vector<CPoint> points1, vector<CPoint> points2);//查找全景图上四个精确匹配点集


};
