// Alpha2048Game.cpp: 实现文件
//

#include "pch.h"
#include "Alpha2048.h"
#include "Alpha2048Game.h"
#include "afxdialogex.h"
#include "MyRect.h"


// Alpha2048Game 对话框

CAlpha2048App *p2 = (CAlpha2048App *)AfxGetApp();

int i, j, k, n;

int nn, m, mx1, mx2, my1, my2;
//实际矩形数组，面板上显示的每个矩形都是CRect类型，声明在这里
CRect* rect[4][4];
//控制是否生成新数字，为true的时候说明有动作，就会生成新数字
bool bHaveDoneSth;

struct MyPoint {
	int x;
	int y;
};
//端点位置
MyPoint point[4][4] = { 0 };
//矩形对象数组，相当于逻辑部分，保存矩形的显示值，坐标
MyRect *myrect[4][4];//原始数据记录
MyRect *myback[4][4];//用户回退时使用
//填充画刷，可以控制矩形填充不同的颜色
CBrush* brush;

//生成一个新数字，随机一个0-16的整数，根据这个整数计算出二维数组的横坐标和竖坐标
//  A/4 是横坐标， A%4 是竖坐标, 当生成的位置有值的时候，重新生成
// 初始值为2， 可以再这里加控制生成2，或 4 。
void GenerateNewNum()
{
	srand((unsigned)time(NULL));
	int A = rand() % 16;
	while (myrect[A / 4][A % 4]->uValue != 0)
	{
		A = rand() % 16;
	}
	myrect[A / 4][A % 4]->uValue = 2;
}
//判断最大值是否达到目标
bool MaxValue()
{
	if (!p2->nMax)
	{
		unsigned int Max = 0;
		for (j = 0; j < 4; j++)
		{
			for (i = 0; i < 4; i++)
			{
				if (myrect[i][j]->uValue > Max)
					Max = myrect[i][j]->uValue;
			}
		}
		if (Max < 2048)
			return false;
		else return true;
	}
	else return false;
}
//游戏结束的条件
bool GameOver()//采用三中可以继续游戏的判定
{
	MaxValue();
	// 存在值为0的矩形，游戏继续
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (myrect[i][j]->uValue == 0 && !MaxValue())
				return false;
		}
	}
	// 行相邻的两个矩形，如果值相同，游戏继续
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4 - 1; j++)
		{
			if (myrect[i][j]->uValue == myrect[i][j + 1]->uValue && !MaxValue())
				return false;
		}
	}
	// 列相邻的两个矩形，如果值相同，游戏继续
	for (j = 0; j < 4; j++)
	{
		for (i = 0; i < 4 - 1; i++)
		{
			if (myrect[i][j]->uValue == myrect[i + 1][j]->uValue && !MaxValue())
				return false;
		}
	}
	// 除了以上情况游戏必定结束
	return true;
}

IMPLEMENT_DYNAMIC(Alpha2048Game, CDialogEx)

Alpha2048Game::Alpha2048Game(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Alpha2048Game, pParent)
{

}

Alpha2048Game::~Alpha2048Game()
{
}

void Alpha2048Game::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Alpha2048Game, CDialogEx)
	ON_WM_PAINT()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// Alpha2048Game 消息处理程序


BOOL Alpha2048Game::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	StartGame();
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Alpha2048Game::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CFont font;
	font.CreateFont(40, 17, 0, 0, 700, false, false, false, CHINESEBIG5_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_MODERN, "微软雅黑");
	//画笔
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	dc.SelectObject(pen);

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			//画矩形
			dc.Rectangle(myrect[i][j]->x1, myrect[i][j]->y1, myrect[i][j]->x2, myrect[i][j]->y2);
			//填充矩形
			rect[i][j] = new CRect(myrect[i][j]->x1, myrect[i][j]->y1, myrect[i][j]->x2, myrect[i][j]->y2);
			dc.SetBkMode(TRANSPARENT);//设置文字背景透明
			dc.SelectObject(font);
			if (myrect[i][j]->uValue == 0)
			{
				brush = new CBrush(RGB(255, 255, 255));
				dc.FillRect(rect[i][j], brush);
				delete brush;
			}
			else if (myrect[i][j]->uValue != 0)
			{
				switch (myrect[i][j]->uValue)
				{
				case 2:	brush = new CBrush(RGB(255, 255, 255)); break;
				case 4:	brush = new CBrush(RGB(255, 225, 200)); break;
				case 8:	brush = new CBrush(RGB(255, 185, 200)); break;
				case 16:brush = new CBrush(RGB(255, 135, 250)); break;
				case 32:brush = new CBrush(RGB(255, 200, 50)); break;
				case 64:brush = new CBrush(RGB(255, 100, 100)); break;
				case 128:brush = new CBrush(RGB(255, 25, 150)); break;
				case 256:brush = new CBrush(RGB(205, 100, 25)); break;
				case 512:brush = new CBrush(RGB(150, 0, 215)); break;
				case 1024:brush = new CBrush(RGB(255, 255, 0)); break;
				case 2048:brush = new CBrush(RGB(255, 0, 0)); break;
				default:brush = new CBrush(RGB(255, 0, 0)); break;
				}
				dc.FillRect(rect[i][j], brush);
				delete brush;

				char num[10] = { '0' };
				_itoa_s(myrect[i][j]->uValue, num, 10);
				dc.DrawText(num, -1, rect[i][j], DT_VCENTER | DT_CENTER | DT_SINGLELINE);

			}
		}
	}
}


void Alpha2048Game::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	case VK_LEFT://将当前情况先存储于myback数组中，按下B时实现回退功能
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				myback[i][j]->uValue = myrect[i][j]->uValue;
			}
		}
		bHaveDoneSth = false;//判断是否有动作，用来控制是否生成新数字
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (myrect[i][j]->uValue != 0)
				{
					for (k = 0; k < j; k++)
					{
						if (myrect[i][k]->uValue == 0)
						{
							bHaveDoneSth = true;
							myrect[i][k]->uValue = myrect[i][j]->uValue;
							myrect[i][j]->uValue = 0;
							break;
						}
					}
				}
			}

			//相加
			for (j = 0; j < 4 - 1; j++)
			{
				if (myrect[i][j]->uValue != 0)
				{
					if (myrect[i][j + 1]->uValue == myrect[i][j]->uValue)
					{
						bHaveDoneSth = true;
						myrect[i][j]->uValue += myrect[i][j + 1]->uValue;
						myrect[i][j + 1]->uValue = 0;
					}
				}
			}

			for (j = 0; j < 4; j++)
			{
				if (myrect[i][j]->uValue != 0)
				{
					for (k = 0; k < j; k++)
					{
						if (myrect[i][k]->uValue == 0)
						{
							bHaveDoneSth = true;
							myrect[i][k]->uValue = myrect[i][j]->uValue;
							myrect[i][j]->uValue = 0;
							break;
						}
					}
				}
			}
		}
		break;

	case VK_UP:
		//将当前情况先存储于myback数组中，按下B时实现回退功能
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				myback[i][j]->uValue = myrect[i][j]->uValue;
			}
		}
		bHaveDoneSth = false;//判断是否有动作，用来控制是否生成新数字
		for (j = 0; j < 4; j++)
		{
			for (i = 0; i < 4; i++)
			{
				if (myrect[i][j]->uValue != 0)
				{
					for (k = 0; k < i; k++)
					{
						if (myrect[k][j]->uValue == 0)
						{
							bHaveDoneSth = true;
							myrect[k][j]->uValue = myrect[i][j]->uValue;
							myrect[i][j]->uValue = 0;
							break;
						}
					}
				}
			}
			for (i = 0; i < 4 - 1; i++)
			{
				if (myrect[i][j]->uValue != 0)
				{
					if (myrect[i + 1][j]->uValue == myrect[i][j]->uValue)
					{
						bHaveDoneSth = true;
						myrect[i][j]->uValue += myrect[i + 1][j]->uValue;
						myrect[i + 1][j]->uValue = 0;
					}
				}
			}
			for (i = 0; i < 4; i++)
			{
				//
				if (myrect[i][j]->uValue != 0)
				{
					for (k = 0; k < i; k++)
					{
						if (myrect[k][j]->uValue == 0)
						{
							bHaveDoneSth = true;
							myrect[k][j]->uValue = myrect[i][j]->uValue;
							myrect[i][j]->uValue = 0;
							break;
						}
					}
				}
			}
		}
		break;

	case VK_RIGHT:
		//将当前情况先存储于myback数组中，按下B时实现回退功能
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				myback[i][j]->uValue = myrect[i][j]->uValue;
			}
		}
		bHaveDoneSth = false;//判断是否有动作，用来控制是否生成新数字
		for (i = 0; i < 4; i++)
		{
			for (j = 4 - 1; j >= 0; j--)
			{
				//
				if (myrect[i][j]->uValue != 0)
				{
					for (k = 4 - 1; k >= j; k--)
					{
						if (myrect[i][k]->uValue == 0)
						{
							bHaveDoneSth = true;
							myrect[i][k]->uValue = myrect[i][j]->uValue;
							myrect[i][j]->uValue = 0;
							break;
						}
					}
				}
			}
			for (j = 4 - 1; j > 0; j--)
			{
				if (myrect[i][j]->uValue != 0)
				{
					if (myrect[i][j - 1]->uValue == myrect[i][j]->uValue)
					{
						bHaveDoneSth = true;
						myrect[i][j]->uValue += myrect[i][j - 1]->uValue;
						myrect[i][j - 1]->uValue = 0;
					}
				}
			}
			for (j = 4 - 1; j >= 0; j--)
			{
				//
				if (myrect[i][j]->uValue != 0)
				{
					for (k = 4 - 1; k >= j; k--)
					{
						if (myrect[i][k]->uValue == 0)
						{
							bHaveDoneSth = true;
							myrect[i][k]->uValue = myrect[i][j]->uValue;
							myrect[i][j]->uValue = 0;
							break;
						}
					}
				}
			}
		}
		break;

	case VK_DOWN:
		//将当前情况先存储于myback数组中，按下B时实现回退功能
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				myback[i][j]->uValue = myrect[i][j]->uValue;
			}
		}
		bHaveDoneSth = false;//判断是否有动作，用来控制是否生成新数字
		for (j = 4 - 1; j >= 0; j--)
		{
			for (i = 4 - 1; i >= 0; i--)
			{
				//
				if (myrect[i][j]->uValue != 0)
				{
					for (k = 4 - 1; k >= i; k--)
					{
						if (myrect[k][j]->uValue == 0)
						{
							bHaveDoneSth = true;
							myrect[k][j]->uValue = myrect[i][j]->uValue;
							myrect[i][j]->uValue = 0;
							break;
						}
					}
				}
			}
			for (i = 4 - 1; i > 0; i--)
			{
				if (myrect[i][j]->uValue != 0)
				{
					if (myrect[i - 1][j]->uValue == myrect[i][j]->uValue)
					{
						bHaveDoneSth = true;
						myrect[i][j]->uValue += myrect[i - 1][j]->uValue;
						myrect[i - 1][j]->uValue = 0;
					}
				}
			}
			for (i = 4 - 1; i >= 0; i--)
			{
				//
				if (myrect[i][j]->uValue != 0)
				{
					for (k = 4 - 1; k >= i; k--)
					{
						if (myrect[k][j]->uValue == 0)
						{
							bHaveDoneSth = true;
							myrect[k][j]->uValue = myrect[i][j]->uValue;
							myrect[i][j]->uValue = 0;
							break;
						}
					}
				}
			}
		}
		break;

	case 'B':
		if (p2->BACK)
		{
			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < 4; j++)
				{
					myrect[i][j]->uValue = myback[i][j]->uValue;
				}
			}
			bHaveDoneSth = false;
		}
		else
		{
			AfxMessageBox("您未选择B键回退功能，该指令无效!\n点击确定关闭此界面以返回游戏。");
			bHaveDoneSth = false;
		}
	default:
		bHaveDoneSth = false;
		break;
	}

	if (bHaveDoneSth)
	{
		GenerateNewNum();
	}

	Invalidate(FALSE);

	if (GameOver())
	{
		if (IDYES == AfxMessageBox("当前游戏结束，是否重新开始游戏？", MB_YESNO | MB_ICONQUESTION))
		{
			StartGame();
			Invalidate();
		}
		else
		{
			GetParent()->SendMessage(WM_CLOSE);
		}
	}
	else
	{
		p2->IsGameOver = false;
	}
	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}


void Alpha2048Game::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (p2->DISS)
	{
		m = point.y / 100;
		n = point.x / 100;
		myrect[m][n]->uValue = 0;
		Invalidate();
	}
	else
	{
		AfxMessageBox("您未选择左键点击消除功能，该指令无效!\n点击确定关闭此界面以返回游戏。");
		bHaveDoneSth = false;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void Alpha2048Game::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	nn++;
	if (p2->TRAN)
	{
		if (nn == 1)
		{
			mx1 = point.y / 100;
			my1 = point.x / 100;
		}
		if (nn == 2)
		{
			mx2 = point.y / 100;
			my2 = point.x / 100;
			int temp = myrect[mx1][my1]->uValue;
			myrect[mx1][my1]->uValue = myrect[mx2][my2]->uValue;
			myrect[mx2][my2]->uValue = temp;
			nn = 0;
			Invalidate();
		}
	}
	else
	{
		AfxMessageBox("您未选择右键点击消除功能，该指令无效!\n点击确定关闭此界面以返回游戏。");
		bHaveDoneSth = false;
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}

void Alpha2048Game::StartGame()
{
	//初始化每个矩形的左上角点的坐标
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			point[i][j].x = j * 100 + 10;
			point[i][j].y = i * 100 + 10;
		}
	}
	//初始化矩形和填充画刷
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			myrect[i][j] = new MyRect(point[i][j].x, point[i][j].y, point[i][j].x + 90, point[i][j].y + 90);
			myback[i][j] = new MyRect(point[i][j].x, point[i][j].y, point[i][j].x + 90, point[i][j].y + 90);
			myrect[i][j]->uValue = 0;
			myback[i][j]->uValue = 0;
		}
	}
	//初始化数字
	srand((unsigned)time(NULL));
	int A = rand() % 16;
	int B = rand() % 16;
	while (B == A)
	{
		B = rand() % 16;
	}
	myrect[A / 4][A % 4]->uValue = 2;
	myrect[B / 4][B % 4]->uValue = 2;
}

BOOL Alpha2048Game::PreTranslateMessage(MSG* pMsg)
{
	//屏蔽ESC退出对话框
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return true;
	//屏蔽ENTER退出对话框
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return true;
	return CDialogEx::PreTranslateMessage(pMsg);
}
