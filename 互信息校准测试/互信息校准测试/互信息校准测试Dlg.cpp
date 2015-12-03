
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

	BOOL m_PicturePointdownflag = TRUE; //全景图特征选取标记位初始化为False
	BOOL m_VideoPointdownflag = FALSE;  //视频帧图像特征选取标记位初始化为False


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
		//(this->GetDlgItem(IDC_PICTURE))->GetWindowRect(&rect_ctr);
		m_TheImage.GetWindowRect(m_TheImageRect);//获取显示全景图像所在矩形窗的坐标
		ScreenToClient(m_TheImageRect);			//转换为对话框上的坐标
		point.x -= m_TheImageRect.left;//point获取的是鼠标相对对话框客户区左上角的坐标，减去rect_ctr.left和
		point.y -= m_TheImageRect.top;//rect_ctr.top后，即为鼠标相对Picture控件左上角的坐标

		if (m_points2.size() <= 3)	
		{ 
			char point_x[4];
			char point_y[4];
			char point_num[4];
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
			m_points2.push_back(point);
		}
		else
		{
			MessageBox("数目已经超过4个了");
			return;
		}
	}
	else if ((m_PicturePointdownflag == TRUE) && (m_VideoPointdownflag == TRUE))
	{
		//(this->GetDlgItem(IDC_VIDEO))->GetWindowRect(&rect_ctr);
		m_CamImage.GetWindowRect(m_CamImageRect);//获取显示视频帧图像所在矩形窗
		ScreenToClient(m_CamImageRect);			//转换为对话框上的坐标
		point.x -= m_CamImageRect.left;//point获取的是鼠标相对对话框客户区左上角的坐标，减去rect_ctr.left和
		point.y -= m_CamImageRect.top;//rect_ctr.top后，即为鼠标相对Picture控件左上角的坐标

		if (m_points1.size() <= 3)
		{
			char point_x[4];
			char point_y[4];
			char point_num[4];
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
		else
		{
			MessageBox("数目已经超过4个了");
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
	ShowMatImgToWnd(GetDlgItem(IDC_PICTURE), TheImage);
	//DrawPicToHDC(TheImage, IDC_PICTURE);            // 调用显示图片函数    
	UpdateWindow();

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
	ShowMatImgToWnd(GetDlgItem(IDC_VIDEO), CamImage);
	//DrawPicToHDC(TheImage, IDC_PICTURE);            // 调用显示图片函数    
	UpdateWindow();


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

	Newpoints = Refresh_MacthPoints(Points1, Points2);//查找全景图上四个精确匹配点集

	m_newpoints = Newpoints;
}


// 将图像显示到对应的图像框
void C互信息校准测试Dlg::ShowMatImgToWnd(CWnd* pWnd, cv::Mat img)
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


//单幅图像信息熵计算
double C互信息校准测试Dlg::Entropy(Mat img)
{
	double temp[256] = {0.0};


	// 计算每个像素的累积值
	for (int m = 0; m<img.rows; m++)
	{// 有效访问行列的方式
		const uchar* t = img.ptr<uchar>(m);
		for (int n = 0; n<img.cols; n++)
		{
			int i = t[n];
			temp[i] = temp[i] + 1;
		}
	}

	// 计算每个像素的概率
	for (int i = 0; i<256; i++)
	{
		temp[i] = temp[i] / (img.rows*img.cols);
	}

	double result = 0;
	// 计算图像信息熵
	for (int i = 0; i<256; i++)
	{
		if (temp[i] == 0.0)
			result = result;
		else
			result = result - temp[i] * (log(temp[i]) / log(2.0));
	}

	return result;

}




// 两幅图像联合信息熵计算
double C互信息校准测试Dlg::ComEntropy(Mat img1, Mat img2, double img1_entropy, double img2_entropy)
{
	double temp[256][256] = {0.0};


	// 计算联合图像像素的累积值
	for (int m1 = 0, m2 = 0; m1 < img1.rows, m2 < img2.rows; m1++, m2++)
	{    // 有效访问行列的方式
		const uchar* t1 = img1.ptr<uchar>(m1);
		const uchar* t2 = img2.ptr<uchar>(m2);
		for (int n1 = 0, n2 = 0; n1 < img1.cols, n2 < img2.cols; n1++, n2++)
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
			temp[i][j] = temp[i][j] / (img1.rows*img1.cols);
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
	img1_entropy = Entropy(img1);
	img2_entropy = Entropy(img2);
	result = img1_entropy + img2_entropy - result;

	return result;

}





//查找全景图上四个精确匹配点集
vector<CPoint> C互信息校准测试Dlg::Refresh_MacthPoints(vector<CPoint> points1, vector<CPoint> points2)
{
	int IMGSIDE = 15; //截取正方形子图的边长一半
	int IMAGESIDE = 15; //局部搜索区域的半径

	points1 = m_points1; // 视频帧图像匹配点集
	points2 = m_points2; // 全景图像匹配点集，初始匹配点，需要利用互信息子函数更新

	//// Mat TheImage; //全景图
	//// Mat CamImage; //视频帧图像

	Mat dst1[4];   // 视频帧图像上截取的四个点的子图
	Mat dst2[4];   // 全景图像上截取的四个点的子图




	cv::Point CLSPoint[4], CRXPoint[4];
	//截取视频帧图像子图
	for (int i = 0; i<4; i++)
	{
		CLSPoint[i].x = points1.at(i).x - IMGSIDE;
		CLSPoint[i].y = points1.at(i).y - IMGSIDE;
		CRXPoint[i].x = points1.at(i).x + IMGSIDE;
		CRXPoint[i].y = points1.at(i).y + IMGSIDE;	
	}

	Rect ROI0(CLSPoint[0], CRXPoint[0]);
	Rect ROI1(CLSPoint[1], CRXPoint[1]);
	Rect ROI2(CLSPoint[2], CRXPoint[2]);
	Rect ROI3(CLSPoint[3], CRXPoint[3]);
	CamImage(ROI0).copyTo(dst1[0]);
	CamImage(ROI1).copyTo(dst1[1]);
	CamImage(ROI2).copyTo(dst1[2]);
	CamImage(ROI3).copyTo(dst1[3]);



	cv::Point TLSPoint[4], TRXPoint[4];
	//截取全景图图像子图
	for (int i = 0; i<4; i++)
	{

		TLSPoint[i].x = points2.at(i).x - IMGSIDE;
		TLSPoint[i].y = points2.at(i).y - IMGSIDE;
		TRXPoint[i].x = points2.at(i).x + IMGSIDE;
		TRXPoint[i].y = points2.at(i).y + IMGSIDE;

	}

	Rect ROI00(TLSPoint[0], TRXPoint[0]);
	Rect ROI11(TLSPoint[1], TRXPoint[1]);
	Rect ROI22(TLSPoint[2], TRXPoint[2]);
	Rect ROI33(TLSPoint[3], TRXPoint[3]);
	TheImage(ROI00).copyTo(dst2[0]);
	TheImage(ROI11).copyTo(dst2[1]);
	TheImage(ROI22).copyTo(dst2[2]);
	TheImage(ROI33).copyTo(dst2[3]);


	//计算对应图像子块的互信息熵
	double OneImaEntropy1[4]; //视频帧图像信息熵
	double OneImaEntropy2[4]; //全景图信息熵
	double TwoImaEntropy[4]; //初始互信息熵

	for (int i = 0; i<4; i++)
	{
		OneImaEntropy1[i] = Entropy(dst1[i]);
		OneImaEntropy2[i] = Entropy(dst2[i]);
		TwoImaEntropy[i] = ComEntropy(dst1[i], dst2[i], OneImaEntropy1[i], OneImaEntropy2[i]);
	}

	vector<CPoint> NewPoints; // 更新的四个匹配点集

	 Rect rect[4][30][30];
	 Mat dst[4][30][30];

	double OneImaEntropy[4][30][30];
	double NewTwoEntropy[4][30][30];

	//全景图像匹配点集的局部区域内搜索精确匹配点集
	for (int i = 0; i < 4; i++)
	{
		for (int j = points2.at(i).x - IMAGESIDE; j <= points2.at(i).x + IMAGESIDE; j++)
		{
			for (int k = points2.at(i).y - IMAGESIDE; k <= points2.at(i).y + IMAGESIDE; k++)
			{
				rect[i][j][k] = Rect(j - IMGSIDE, k - IMGSIDE, 2 * IMGSIDE, 2 * IMGSIDE); //j、k为更新的局部区域图像坐标						  
				TheImage(rect[i][j][k]).copyTo(dst[i][j][k]);

				OneImaEntropy[i][j][k] = Entropy(dst[i][j][k]);
				NewTwoEntropy[i][j][k] = ComEntropy(dst[i][j][k], dst1[i], OneImaEntropy[i][j][k], OneImaEntropy1[i]);

				double MAX = TwoImaEntropy[i];
				//保存互信息熵最大时的匹配点集 
				if (NewTwoEntropy[i][j][k] > MAX)   // 计算所有互信息熵，然后取最大值
				{
					MAX = NewTwoEntropy[i][j][k];
					NewPoints.at(i).x = j;
					NewPoints.at(i).y = k;
				}
			}
		}
	}

	return  NewPoints;

}

