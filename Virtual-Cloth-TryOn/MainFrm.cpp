
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "Virtual-Cloth-TryOn.h"

#include "MainFrm.h"
#include "View3D.h"
#include "HumanBodySetting.h"
#include "ClothFileOpen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_MENU_HUMAN_BODY_SETTING, &CMainFrame::OnMenuHumanBodySetting)
	ON_COMMAND(ID_CLOTH_FILE_OPEN, &CMainFrame::OnClothFileOpen)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO:  在此添加成员初始化代码
	m_p3DView = NULL;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO:  如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


BOOL CMainFrame::CreateViews()
{
	CView* pActiveView = GetActiveView();
	UINT   active_gwl = ::GetWindowLong(pActiveView->m_hWnd, GWL_ID);
	m_p3DView = (View3D*)pActiveView;

	::SetWindowLong(m_p3DView->m_hWnd, GWL_ID, active_gwl);
	m_p3DView->ShowWindow(SW_SHOW);
	SetActiveView(m_p3DView);
	RecalcLayout();


	return TRUE;
}
// CMainFrame 消息处理程序



void CMainFrame::OnMenuHumanBodySetting()
{

	m_p3DView->m_Render.Render();


	m_pHumanBodySettingDlg = new HumanBodySetting();
	m_pHumanBodySettingDlg->m_HumanBodySettingMain.m_p3DView = m_p3DView;
	m_pHumanBodySettingDlg->Create(IDD_HUMAN_BODY_SETTING, this);
	m_pHumanBodySettingDlg->ShowWindow(SW_SHOW);



	//Render();

	//m_pFeatureCylinderDlg = new FeatureCylinderSettingDlg();

	////ModelView指针传入特征面对话框中 gaoyu 2014-6-26
	//m_pFeatureCylinderDlg->pModelView = this;
	//m_pFeatureCylinderDlg->Create(IDD_FEATURECYLINDERSETTINGDLG, this);
	//m_pFeatureCylinderDlg->ShowWindow(SW_SHOW);
	////m_Gmodel指针传入特征面对话框中 gaoyu 2014-6-27
	//m_pFeatureCylinderDlg->pGmodel = GetDocument()->m_Gmodel;


	// TODO:  在此添加命令处理程序代码
}


void CMainFrame::OnClothFileOpen()
{
	// TODO:  在此添加命令处理程序代码
	m_pClothFileOpenDlg = new ClothFileOpen();
	m_pClothFileOpenDlg->Create(IDD_CLOTH_FILE_OPEN, this);
	m_pClothFileOpenDlg->ShowWindow(SW_SHOW);
}
