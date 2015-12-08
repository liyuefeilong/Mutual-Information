
// 互信息校准测试Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "互信息校准测试.h"
#include "互信息校准测试Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// C互信息校准测试Dlg 对话框



C互信息校准测试Dlg::C互信息校准测试Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C互信息校准测试Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C互信息校准测试Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_TheImage);//自定义控件和IDC界面控件绑定
	DDX_Control(pDX, IDC_VIDEO, m_CamImage);//自定义控件和IDC界面控件绑定
}

BEGIN_MESSAGE_MAP(C互信息校准测试Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_OPEN_PICTURE, &C互信息校准测试Dlg::OnBnClickedOpenPicture)
	ON_BN_CLICKED(IDC_OPEN_VIDEO, &C互信息校准测试Dlg::OnBnClickedOpenVideo)
	ON_BN_CLICKED(IDC_PICTURE_POINT, &C互信息校准测试Dlg::OnBnClickedPicturePoint)
	ON_BN_CLICKED(IDC_VIDEO_POINT, &C互信息校准测试Dlg::OnBnClickedVideoPoint)
	ON_BN_CLICKED(IDC_ADUJST, &C互信息校准测试Dlg::OnBnClickedAdujst)
END_MESSAGE_MAP()


// C互信息校准测试Dlg 消息处理程序

BOOL C互信息校准测试Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	BOOL m_PicturePointdownflag = FALSE; //全景图特征选取标记位初始化为False
	BOOL m_VideoPointdownflag = FALSE;  //视频帧图像特征选取标记位初始化为False

	GetDlgItem(IDC_PICTURE_POINT)->EnableWindow(FALSE); //初始状态,获取特征点按钮是失能的
	GetDlgItem(IDC_VIDEO_POINT)->EnableWindow(FALSE); //初始状态,获取特征点按钮是失能的
	GetDlgItem(IDC_ADUJST)->EnableWindow(FALSE); //初始状态,计算互信息按钮是失能的
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C互信息校准测试Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C互信息校准测试Dlg::OnPaint()
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
HCURSOR C互信息校准测试Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C互信息校准测试Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if ((m_PicturePointdownflag == TRUE) && (m_VideoPointdownflag == FALSE))
	{
	    (this->GetDlgItem(IDC_PICTURE))->GetWindowRect(&m_TheImageRect);
		m_TheImage.GetWindowRect(m_TheImageRect);//获取显示全景图像所在矩形窗的坐标
		ScreenToClient(m_TheImageRect);			//转换为对话框上的坐标
		point.x -= m_TheImageRect.left;//point获取的是鼠标相对对话框客户区左上角的坐标，减去rect_ctr.left和
		point.y -= m_TheImageRect.top;//rect_ctr.top后，即为鼠标相对Picture控件左上角的坐标

		if (m_points2.size() <= 3)	
		{ 
			if (point.x < 0 || point.x > m_TheImageRect.Width() || point.y < 0 || point.y > m_TheImageRect.Height())
			{
				MessageBox("选取的点不在目标图像范围内！");
			}
			else
			{
				char point_x[5];
				char point_y[5];
				char point_num[4];
				_ltoa(point.x, point_x, 10);
				_ltoa(point.y, point_y, 10);
				_itoa(m_points2.size() + 1, point_num, 10);
				char message[20] = "Point ";
				strcat(message, point_num);
				strcat(message, ": ");
				strcat(message, point_x);
				strcat(message, ",");
				strcat(message, point_y);

				MessageBox(message);
				m_points2.push_back(point);
			}
		}
		
		if (m_points2.size() >= 4)
		{
			MessageBox("左图中选取的特征点数目已经达到4个");
			return;
		}
	}
	else if ((m_PicturePointdownflag == TRUE) && (m_VideoPointdownflag == TRUE))
	{
		(this->GetDlgItem(IDC_VIDEO))->GetWindowRect(&m_CamImageRect);
		m_CamImage.GetWindowRect(m_CamImageRect);//获取显示视频帧图像所在矩形窗
		ScreenToClient(m_CamImageRect);			//转换为对话框上的坐标
		point.x -= m_CamImageRect.left;//point获取的是鼠标相对对话框客户区左上角的坐标，减去rect_ctr.left和
		point.y -= m_CamImageRect.top;//rect_ctr.top后，即为鼠标相对Picture控件左上角的坐标

		if (m_points1.size() <= 3)
		{
			if (point.x < 0 || point.x > m_TheImageRect.Width() || point.y < 0 || point.y > m_TheImageRect.Height())
			{
				MessageBox("选取的点不在目标图像范围内！");
			}
			else
			{
				char point_x[5];
				char point_y[5];
				char point_num[5];
				_ltoa(point.x, point_x, 10);
				_ltoa(point.y, point_y, 10);
				_itoa(m_points1.size() + 1, point_num, 10);
				char message[20] = "Point ";
				strcat(message, point_num);
				strcat(message, ": ");
				strcat(message, point_x);
				strcat(message, ",");
				strcat(message, point_y);

				MessageBox(message);
				m_points1.push_back(point);
			}
		}

		if (m_points1.size() >= 4)
		{
			MessageBox("右图中选取的特征点数目已经达到4个");
			GetDlgItem(IDC_ADUJST)->EnableWindow(TRUE);
			MessageBox("可进行互信息匹配");
			return;
		}
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void C互信息校准测试Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值


	CDialogEx::OnMouseMove(nFlags, point);
}


void C互信息校准测试Dlg::OnBnClickedOpenPicture()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlg(
		TRUE, _T("*.bmp;*.jpg；*.jpeg"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.bmp; *.jpg;*.jpeg) |*.bmp; *.jpg; *.jpeg | All Files (*.*) |*.*||"), NULL
		);                                        // 选项图片的约定
	dlg.m_ofn.lpstrTitle = _T("Open Image");    // 打开文件对话框的标题名
	if (dlg.DoModal() != IDOK)                    // 判断是否获得图片
		return;

	CString mPath = dlg.GetPathName();            // 获取图片路径

	TheImage = cvLoadImage(mPath, 1);    // 读取图片、缓存到一个局部变量 ipl 中
	//Mat TheImage = imread(mPath,1);
	ShowMatImgToWnd(GetDlgItem(IDC_PICTURE), TheImage, proportionPicture);
	//DrawPicToHDC(TheImage, IDC_PICTURE);            // 调用显示图片函数    
	UpdateWindow();

	GetDlgItem(IDC_PICTURE_POINT)->EnableWindow(TRUE); // 使获取特征点按钮生效
}


void C互信息校准测试Dlg::OnBnClickedOpenVideo()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlg(
		TRUE, _T("*.bmp;*.jpg；*.jpeg"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.bmp; *.jpg;*.jpeg) |*.bmp; *.jpg; *.jpeg | All Files (*.*) |*.*||"), NULL
		);                                        // 选项图片的约定
	dlg.m_ofn.lpstrTitle = _T("Open Image");    // 打开文件对话框的标题名
	if (dlg.DoModal() != IDOK)                    // 判断是否获得图片
		return;

	CString mPath = dlg.GetPathName();            // 获取图片路径

	CamImage = cvLoadImage(mPath, 1);    // 读取图片、缓存到一个局部变量 ipl 中
	//Mat TheImage = imread(mPath,1);
	ShowMatImgToWnd(GetDlgItem(IDC_VIDEO), CamImage, proportionVideo);
	//DrawPicToHDC(TheImage, IDC_PICTURE);            // 调用显示图片函数    
	UpdateWindow();

	GetDlgItem(IDC_VIDEO_POINT)->EnableWindow(TRUE); // 使获取特征点按钮生效
}


void C互信息校准测试Dlg::OnBnClickedPicturePoint()
{
	// TODO:  在此添加控件通知处理程序代码
	m_PicturePointdownflag = TRUE;
	m_VideoPointdownflag = FALSE;
}


void C互信息校准测试Dlg::OnBnClickedVideoPoint()
{
	// TODO:  在此添加控件通知处理程序代码

	m_VideoPointdownflag = TRUE;
}


void C互信息校准测试Dlg::OnBnClickedAdujst()
{
	// TODO:  在此添加控件通知处理程序代码

	vector<CPoint> Newpoints;// = m_points2; // 需要利用互信息子函数更新得到的匹配点集（要求四个） 
	vector<CPoint> Points1 = m_points1;// 视频帧图像匹配点集（要求四个）
	vector<CPoint> Points2 = m_points2;// 全景图像匹配点集，初始匹配点集（要求四个）

	//Newpoints = Refresh_MacthPoints(Points1, Points2);//查找全景图上四个精确匹配点集
	Refresh_MacthPoints(Points1, Points2);//查找全景图上四个精确匹配点集
	//m_newpoints = Newpoints;
}

// 将图像显示到对应的图像框
void C互信息校准测试Dlg::ShowPointToWnd(CWnd* pWnd, cv::Mat img)
{
	if (img.empty())
		return;
	CDC *pDC = pWnd->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	pWnd->GetClientRect(&rect);   
	IplImage Iimg = img;

	CvvImage cimg;
	cimg.CopyOf(&Iimg); // 复制图片
	cimg.DrawToHDC(hDC, &rect); // 将图片绘制到显示控件的指定区域内
	ReleaseDC(pDC);
}


// 将图像显示到对应的图像框
void C互信息校准测试Dlg::ShowMatImgToWnd(CWnd* pWnd, cv::Mat img, double *proportion)
{
	if (img.empty())
		return;
	CDC *pDC = pWnd->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	pWnd->GetClientRect(&rect);   
	IplImage Iimg = img;
		
	// m_CamImageRect

	int rw = rect.right - rect.left; // 求出图片控件的宽和高   
	int rh = rect.bottom - rect.top;   
	int iw = TheImage.cols; // 读取原始图片的宽和高   
	int ih = TheImage.rows;

	// 计算缩放比例
	proportion[0] = rw * 1.0 / iw;
	proportion[1] = rh * 1.0 / ih;

	CvvImage cimg;
	cimg.CopyOf(&Iimg); // 复制图片
	cimg.DrawToHDC(hDC, &rect); // 将图片绘制到显示控件的指定区域内
	ReleaseDC(pDC);
}


//单幅图像信息熵计算
double C互信息校准测试Dlg::Entropy(Mat img)
{
	double temp[256] = {0.0}; // 初始化

	// 计算每个像素的累积值
	for (int m = 0; m < img.rows; ++m)
	{// 有效访问行列的方式
		const uchar* t = img.ptr<uchar>(m); // 指向图像每一行的首地址
		for (int n = 0; n < img.cols; n++)
		{
			int i = t[n];		   // 获得当前下标的像素值i
			temp[i] = temp[i] + 1; // 图像中像素值i出现的次数
		}
	}

	// 计算每个像素出现的概率
	for (int i = 0; i < 256; ++i)
	{
		temp[i] /= (img.rows * img.cols); // 换算成概率
	}

	double result = 0;
	// 计算图像信息熵
	for (int i = 0; i < 256; ++i)
	{
		if (temp[i] == 0.0)
			result = result;
		else
			result -= temp[i] * (log(temp[i]) / log(2.0));
	}

	return result;

}


// 两幅图像联合信息熵计算
double C互信息校准测试Dlg::ComEntropy(Mat img1, Mat img2, double img1_entropy, double img2_entropy)
{
	double temp[256][256] = {0.0};


	// 计算联合图像像素的累积值
	for (int m1 = 0, m2 = 0; m1 < img1.rows, m2 < img2.rows; ++m1, ++m2)
	{    // 有效访问行列的方式
		const uchar* t1 = img1.ptr<uchar>(m1);
		const uchar* t2 = img2.ptr<uchar>(m2);
		for (int n1 = 0, n2 = 0; n1 < img1.cols, n2 < img2.cols; ++n1, ++n2)
		{
			int i = t1[n1], j = t2[n2];
			temp[i][j] = temp[i][j] + 1;
		}
	}

	// 计算每个联合像素的概率
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			temp[i][j] /= (img1.rows * img1.cols);
		}
	}

	double result = 0.0;
	//计算图像联合信息熵
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)

		{
			if (temp[i][j] == 0.0)
				result = result;
			else
				result = result - temp[i][j] * (log(temp[i][j]) / log(2.0));
		}
	}

	//得到两幅图像的互信息熵
	//img1_entropy = Entropy(img1);
	//img2_entropy = Entropy(img2);
	result = img1_entropy + img2_entropy - result;

	return result;

}


//查找全景图上四个精确匹配点集 return vector<CPoint>
void C互信息校准测试Dlg::Refresh_MacthPoints(vector<CPoint> points1, vector<CPoint> points2)
{
	points1 = m_points1; // 视频帧图像匹配点集
	points2 = m_points2; // 全景图像匹配点集，初始匹配点，需要利用互信息子函数更新

	//// Mat TheImage; //全景图
	//// Mat CamImage; //视频帧图像

	cv::Size mat_size;  // 子图的尺寸
	mat_size.height = 100;
	mat_size.width = 100;

	Mat dst1[4];   // 视频帧图像上截取的四个点的周围子图
	Mat dst2[4];   // 全景图像上截取的四个点的周围子图

	// 在软件图片显示空间中显示的图片是经过缩放的
	// 因此选取的坐标也是缩放后的坐标
	// 需要将坐标转换为实际原图的坐标，存放到以下变量中
	int Point1_x[4],Point1_y[4], Point2_x[4], Point2_y[4];

	// 取子图
	for (int i = 0; i < 4; ++i)
	{
		// 视频帧图像取子图
		Point1_x[i] = int(points1[i].x / proportionVideo[0] - mat_size.width / 2);
		Point1_y[i] = int(points1[i].y / proportionVideo[1] - mat_size.height / 2);
		Rect rect1(Point1_x[i], Point1_y[i], mat_size.width, mat_size.height);
		CamImage(rect1).copyTo(dst1[i]);

		// 全景图像取子图
		Point2_x[i] = int(points2[i].x / proportionPicture[0] - mat_size.width / 2);
		Point2_y[i] = int(points2[i].y / proportionPicture[1] - mat_size.height / 2);
		Rect rect2(Point2_x[i], Point2_y[i], mat_size.width, mat_size.height);
		TheImage(rect2).copyTo(dst2[i]);
		
	}

	/*
	imshow("a1", dst1[0]);
	imshow("b1", dst1[1]);
	imshow("c1", dst1[2]);
	imshow("d1", dst1[3]);
	
	imshow("a2", dst2[0]);
	imshow("b2", dst2[1]);
	imshow("c2", dst2[2]);
	imshow("d2", dst2[3]);
	*/	

	//计算各图像子块的信息熵与四对特征点区域子图的互信息熵
	double OneImaEntropy1[4]; //视频帧图像信息熵
	double OneImaEntropy2[4]; //全景图信息熵
	double TwoImaEntropy[4]; //初始互信息熵

	for (int i = 0; i < 4; ++i)
	{
		OneImaEntropy1[i] = Entropy(dst1[i]);
		OneImaEntropy2[i] = Entropy(dst2[i]);
		TwoImaEntropy[i] = ComEntropy(dst1[i], dst2[i], OneImaEntropy1[i], OneImaEntropy2[i]);
	}

	// 设定视频帧图像的搜索半径
	int ScanScope = 50;
	Mat ScanDst[4];
	vector<CPoint> ScanPoint = points1; // 区域搜索得到的四组精确坐标，首先初始化为手动选取的坐标

	for (int i = 0; i < 4; ++i)
	{
		double ScanImaEntropy = 0.0;
		double ScanTwoImaEntropy = 0.0;
		double MaxEntropy = 0.0;

		// 设定视频帧子块的搜索边界
		int left = int(points1[i].x / proportionVideo[0]) - ScanScope;
		int right = int(points1[i].x / proportionVideo[0]) + ScanScope;
		int top = int(points1[i].y / proportionVideo[1]) - ScanScope;
		int bottom = int(points1[i].y / proportionVideo[1]) + ScanScope;

		for (int j = top; j <= bottom; ++j)
		{
			for (int k = left; k <= right; ++k)
			{
				// 视频帧图像在子图附近搜索
				int ScanPoint_x = int(k - mat_size.width / 2);
				int ScanPoint_y = int(j - mat_size.height / 2);
				Rect rect2(ScanPoint_x, ScanPoint_y, mat_size.width, mat_size.height);
				CamImage(rect2).copyTo(ScanDst[i]);

				// 重新计算搜索子图与全景图对应区域的联合熵
				ScanImaEntropy = Entropy(ScanDst[i]);
				ScanTwoImaEntropy = ComEntropy(dst2[i], ScanDst[i], OneImaEntropy2[i], ScanImaEntropy);

				if (ScanTwoImaEntropy > MaxEntropy)
				{
					// MessageBox("有精确匹配点");
					MaxEntropy = ScanTwoImaEntropy;
					ScanPoint[i].x = k;
					ScanPoint[i].y = j;
				}
			}
		}	
	}

	// 精确扫描后，重新取子图
	Mat dstRes[4];
	for (int i = 0; i < 4; ++i)
	{
		// 视频帧图像重新取精确子图
		int Point1_x = int(ScanPoint[i].x - mat_size.width / 2);
		int Point1_y = int(ScanPoint[i].y - mat_size.height / 2);
		Rect rect2(Point1_x, Point1_y, mat_size.width, mat_size.height);
		CamImage(rect2).copyTo(dstRes[i]);
		
	}

	/*
	// 精确坐标点周围区域显示
	imshow("a3", dstRes[0]);
	imshow("b3", dstRes[1]);
	imshow("c3", dstRes[2]);
	imshow("d3", dstRes[3]);
	*/

	// 以上得出四对精确的匹配点，以下进行投影变换的计算
	// 使用函数getPerspectiveTransform(const Point2f src[], const Point2f dst[]) 
	// http://blog.csdn.net/xiaowei_cqu/article/details/26478135

	vector<Point2f> corners(4); 
	vector<Point2f> corners_trans(4); 

	// 视频帧图像的四个精确匹配点
	corners[0] = Point2f(ScanPoint[0].x, ScanPoint[0].y);  
    corners[1] = Point2f(ScanPoint[1].x, ScanPoint[1].y);  
    corners[2] = Point2f(ScanPoint[2].x, ScanPoint[2].y);  
    corners[3] = Point2f(ScanPoint[3].x, ScanPoint[3].y);

	// 全景图上对应的四个点
	corners_trans[0] = Point2f(Point2_x[0], Point2_y[0]);  
    corners_trans[1] = Point2f(Point2_x[1], Point2_y[1]);  
    corners_trans[2] = Point2f(Point2_x[2], Point2_y[2]);  
    corners_trans[3] = Point2f(Point2_x[3], Point2_y[3]);

	cv::Mat transform = getPerspectiveTransform(corners, corners_trans);  // 算出投影变换矩阵

    Mat img_trans;

	warpPerspective(CamImage, img_trans, transform, CamImage.size(), INTER_LINEAR, BORDER_CONSTANT);

    imwrite("转换后的视频帧图像.BMP", img_trans); 
	imshow("转换后的视频帧图像", img_trans);

}

