
// Alpha2048Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Alpha2048.h"
#include "Alpha2048Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Alpha2048Info.h"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:

	bool DISS;
	int BACK;


	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAlpha2048Dlg 对话框

CAlpha2048App * p1 = (CAlpha2048App *)AfxGetApp();

CAlpha2048Dlg::CAlpha2048Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ALPHA2048_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAlpha2048Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAlpha2048Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(AID_NORMAL, &CAlpha2048Dlg::OnBnClickedNormal)
	ON_BN_CLICKED(AID_START, &CAlpha2048Dlg::OnBnClickedStart)
	ON_BN_CLICKED(AID_EXIT, &CAlpha2048Dlg::OnBnClickedExit)
	ON_BN_CLICKED(AID_ENDLESS, &CAlpha2048Dlg::OnBnClickedEndless)
	ON_BN_CLICKED(AID_BACK, &CAlpha2048Dlg::OnBnClickedBack)
	ON_BN_CLICKED(AID_DISS, &CAlpha2048Dlg::OnBnClickedDiss)
	ON_BN_CLICKED(AID_TRAN, &CAlpha2048Dlg::OnBnClickedTran)
	ON_BN_CLICKED(AID_IRON, &CAlpha2048Dlg::OnBnClickedIron)
END_MESSAGE_MAP()


// CAlpha2048Dlg 消息处理程序

BOOL CAlpha2048Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码
	((CButton*)GetDlgItem(AID_NORMAL))->SetCheck(TRUE);//初始选中普通游戏模式
	((CButton*)GetDlgItem(AID_IRON))->SetCheck(TRUE);//初始选中铁人游戏功能
	m_Tip.Create(this);
	m_Tip.AddTool(GetDlgItem(AID_NORMAL),"玩家进行游戏，最高数块达2048即结束游戏。");
	m_Tip.AddTool(GetDlgItem(AID_ENDLESS),"没有数块数字限制，直到无法操作即结束游戏。");
	m_Tip.AddTool(GetDlgItem(AID_BACK),"选择此项，即启用Ｂ键回退一步功能。");
	m_Tip.AddTool(GetDlgItem(AID_TRAN),"选择此项，即启用右键点击交换功能。");
	m_Tip.AddTool(GetDlgItem(AID_DISS),"选择此项，即启用左键点击消除功能。");
	m_Tip.AddTool(GetDlgItem(AID_IRON),"选择此项，即关闭所有辅助游玩功能。");
	m_Tip.AddTool(GetDlgItem(AID_START),"确认你的选择，并开始游戏。");
	m_Tip.AddTool(GetDlgItem(AID_EXIT),"关闭所有界面，并结束游戏。");
	m_Tip.SetDelayTime(100); //设置延迟
	m_Tip.SetTipTextColor(RGB(0, 0, 255)); //设置提示文本的颜色
	m_Tip.SetTipBkColor(RGB(255, 255, 255)); //设置提示框的背景颜色
	m_Tip.Activate(TRUE); //启用提示
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAlpha2048Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAlpha2048Dlg::OnPaint()
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
HCURSOR CAlpha2048Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAlpha2048Dlg::OnBnClickedNormal()
{
	// TODO: 在此添加控件通知处理程序代码
	p1->nMax = false;
}


void CAlpha2048Dlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	Alpha2048Info Game;
	if (!p1->BACK && !p1->DISS && !p1->TRAN && !p1->IRON)
	{
		if (IDYES == AfxMessageBox("当前游戏未选择任何功能，将默认以铁人模式启动。", MB_YESNO | MB_ICONQUESTION))
		{
			p1->IRON = true;
			if (Game.DoModal() == IDOK)
				Invalidate();
		}
	}
	if (Game.DoModal() == IDOK)
		Invalidate();
}


void CAlpha2048Dlg::OnBnClickedExit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


BOOL CAlpha2048Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	// 显示提醒
	if (pMsg->message == WM_MOUSEMOVE)
		m_Tip.RelayEvent(pMsg);
	// 屏蔽ESC退出对话框
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return true;
	// 屏蔽ENTER退出对话框
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return true;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CAlpha2048Dlg::OnBnClickedEndless()
{
	// TODO: 在此添加控件通知处理程序代码
	p1->nMax = true;
}


void CAlpha2048Dlg::OnBnClickedBack()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(AID_BACK))->GetCheck() == BST_CHECKED)
	{
		((CButton*)GetDlgItem(AID_BACK))->SetCheck(TRUE);
		((CButton*)GetDlgItem(AID_IRON))->SetCheck(FALSE);
		p1->BACK = TRUE;
		p1->IRON = FALSE;
	}
	else
	{
		((CButton*)GetDlgItem(AID_BACK))->SetCheck(FALSE);
		p1->BACK = FALSE;
	}
}


void CAlpha2048Dlg::OnBnClickedDiss()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(AID_DISS))->GetCheck() == BST_CHECKED)
	{
		((CButton*)GetDlgItem(AID_DISS))->SetCheck(TRUE);
		((CButton*)GetDlgItem(AID_IRON))->SetCheck(FALSE);
		p1->DISS = TRUE;
		p1->IRON = FALSE;
	}
	else
	{
		((CButton*)GetDlgItem(AID_DISS))->SetCheck(FALSE);
		p1->DISS = FALSE;
	}
}


void CAlpha2048Dlg::OnBnClickedTran()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(AID_TRAN))->GetCheck() == BST_CHECKED)
	{
		((CButton*)GetDlgItem(AID_TRAN))->SetCheck(TRUE);
		((CButton*)GetDlgItem(AID_IRON))->SetCheck(FALSE);
		p1->TRAN = TRUE;
		p1->IRON = FALSE;
	}
	else
	{
		((CButton*)GetDlgItem(AID_TRAN))->SetCheck(FALSE);
		p1->TRAN = FALSE;
	}
}


void CAlpha2048Dlg::OnBnClickedIron()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(AID_IRON))->GetCheck() == BST_CHECKED)
	{
		((CButton*)GetDlgItem(AID_DISS))->SetCheck(FALSE);
		((CButton*)GetDlgItem(AID_BACK))->SetCheck(FALSE);
		((CButton*)GetDlgItem(AID_TRAN))->SetCheck(FALSE);
		((CButton*)GetDlgItem(AID_IRON))->SetCheck(TRUE);
		p1->DISS = FALSE;
		p1->BACK = FALSE;
		p1->TRAN = FALSE;
		p1->IRON = TRUE;
	}
	else
	{
		((CButton*)GetDlgItem(AID_IRON))->SetCheck(FALSE);
		p1->IRON = FALSE;
	}
}
