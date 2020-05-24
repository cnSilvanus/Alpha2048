// Alpha2048Info.cpp: 实现文件
//

#include "pch.h"
#include "Alpha2048.h"
#include "Alpha2048Info.h"
#include "afxdialogex.h"
#include "Alpha2048Game.h"


// Alpha2048Info 对话框

CAlpha2048App *p3 = (CAlpha2048App *)AfxGetApp();
Alpha2048Game *pInner;

IMPLEMENT_DYNAMIC(Alpha2048Info, CDialogEx)

Alpha2048Info::Alpha2048Info(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Alpha2048Info, pParent)
{

}

Alpha2048Info::~Alpha2048Info()
{
}

void Alpha2048Info::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Alpha2048Info, CDialogEx)
	ON_BN_CLICKED(AID_RESTART, &Alpha2048Info::OnBnClickedRestart)
	ON_BN_CLICKED(AID_GIVEUP, &Alpha2048Info::OnBnClickedGiveup)
//	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// Alpha2048Info 消息处理程序


BOOL Alpha2048Info::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetTimer(1, 50, NULL);

	if (p3->IRON)
		p3->nType += "铁人";
	else
		p3->nType += "";

	if (p3->BACK)
		p3->nType += "回退";
	else
		p3->nType += "";

	if (p3->DISS)
		p3->nType += "消除";
	else
		p3->nType += "";

	if (p3->BACK)
		p3->nType += "交换";
	else
		p3->nType += "";

	if (!p3->nMax)
		p3->nType += "的普通模式";
	else
		p3->nType += "的无尽模式";

	GetDlgItem(AID_GAMEINFO)->SetWindowText(p3->nType);

	pInner = new Alpha2048Game();
	pInner->Create(IDD_Alpha2048Game, this);
	pInner->ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Alpha2048Info::OnBnClickedRestart()
{
	// TODO: 在此添加控件通知处理程序代码
	if (p3->IsGameOver)
	{
		pInner = new Alpha2048Game();
		pInner->Create(IDD_Alpha2048Game, this);
		pInner->ShowWindow(SW_SHOW);
	}
	else
	{
		if (IDYES == AfxMessageBox(_T("当前游戏还有进行的可能，是否确认重新开始？"), MB_YESNO | MB_ICONQUESTION))
		{
			pInner = new Alpha2048Game();
			pInner->Create(IDD_Alpha2048Game, this);
			pInner->ShowWindow(SW_SHOW);
		}
	}
}


void Alpha2048Info::OnBnClickedGiveup()
{
	// TODO: 在此添加控件通知处理程序代码
	if (p3->IsGameOver)
	{
		this->SendMessage(WM_CLOSE);
	}
	else
	{
		if (IDYES == AfxMessageBox(_T("当前游戏还有进行的可能，是否确认放弃游戏？"), MB_YESNO | MB_ICONQUESTION))
		{
			this->SendMessage(WM_CLOSE);
		}
	}
}


void Alpha2048Info::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	p3->nType = "基于";
	CDialogEx::OnClose();
}


BOOL Alpha2048Info::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//屏蔽ESC退出对话框
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return true;
	//屏蔽ENTER退出对话框
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return true;
	return CDialogEx::PreTranslateMessage(pMsg);
}