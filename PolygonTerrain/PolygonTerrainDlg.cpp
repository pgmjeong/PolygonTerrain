
// PolygonTerrainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PolygonTerrain.h"
#include "PolygonTerrainDlg.h"
#include "afxdialogex.h"
#include "PolygonMethod.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CPolygonTerrainDlg dialog



CPolygonTerrainDlg::CPolygonTerrainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_POLYGONTERRAIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPolygonTerrainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPolygonTerrainDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//    ON_BN_CLICKED(IDOK, &CPolygonTerrainDlg::OnBnClickedOk)
//    ON_BN_CLICKED(IDC_BUTTON2, &CPolygonTerrainDlg::OnBnClickedButton2)
//    ON_COMMAND(IDC_STATIC, &CPolygonTerrainDlg::OnStatic)
ON_WM_LBUTTONDOWN()
ON_WM_RBUTTONDOWN()
ON_COMMAND(ID__MENU_POLYGON1, &CPolygonTerrainDlg::OnMenuPolygon1)
ON_COMMAND(ID__MENU_POLYGON2, &CPolygonTerrainDlg::OnMenuPolygon2)
ON_BN_CLICKED(IDC_BUTTON2, &CPolygonTerrainDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPolygonTerrainDlg message handlers

BOOL CPolygonTerrainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPolygonTerrainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPolygonTerrainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting
        CPen Pen, *oldPen;

        RECT rc;
        GetDlgItem(IDC_STATIC)->GetClientRect(&rc);
        int w = (rc.right - rc.left);
        int h = (rc.bottom - rc.top);

        GetDlgItem(IDC_STATIC)->GetWindowRect(&rc);
        this->ScreenToClient(&rc);
        dc.SetMapMode(MM_ISOTROPIC);
        dc.SetViewportOrg(rc.left + w / 2, rc.top + h / 2);
        dc.SetWindowExt(w, h);
        dc.SetViewportExt(w, -h);

        Pen.CreatePen(PS_SOLID, 1, RGB(100, 100, 100));
        oldPen = dc.SelectObject(&Pen);
        dc.MoveTo(-w / 2, 0);
        dc.LineTo( w / 2, 0);

        dc.MoveTo(0, -h / 2);
        dc.LineTo(0,  h / 2);
        dc.SelectObject(oldPen);
        Pen.DeleteObject();

        PrintPolygon(dc, m_vecPolygon, RGB(0, 0, 0));
        PrintPolygon(dc, m_vecP1, RGB(255, 0, 0));
        PrintPolygon(dc, m_vecP2, RGB(0, 0, 255));
        PrintPolygon(dc, m_vecP3, RGB(255, 255, 0));

		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPolygonTerrainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPolygonTerrainDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    RECT rc;
    GetDlgItem(IDC_STATIC)->GetClientRect(&rc);
    int w = (rc.right - rc.left);
    int h = (rc.bottom - rc.top);

    GetDlgItem(IDC_STATIC)->GetWindowRect(&rc);
    this->ScreenToClient(&rc);

    if ((rc.top <= point.y) && (point.y <= rc.bottom))
    {
        if ((rc.left <= point.x) && (point.x <= rc.right))
        {
            int cx = rc.left + w / 2;
            int cy = rc.top + h / 2;

            POINT pt = { point.x - cx, cy - point.y };
            m_vecPolygon.emplace_back(pt);

            InvalidateRect(&rc, TRUE);
        }
    }

    CDialog::OnLButtonUp(nFlags, point);
}


void CPolygonTerrainDlg::PrintPolygon(CPaintDC& dc, std::vector<POINT>& polygon, COLORREF crColor)
{
    if (polygon.empty()) { return; }

    CPen Pen, *oldPen;
    CBrush Brush, *oldBrush;

    Pen.CreatePen(PS_SOLID, 3, crColor);
    oldPen = dc.SelectObject(&Pen);

    Brush.CreateStockObject(NULL_BRUSH);
    oldBrush = dc.SelectObject(&Brush);

    dc.Polygon(&polygon[0], polygon.size());

    for (auto& v : polygon)
    {
        dc.Ellipse(v.x - 3, v.y - 3, v.x + 3, v.y + 3);
    }

    dc.SelectObject(oldBrush);
    dc.SelectObject(oldPen);

    Brush.DeleteObject();
    Pen.DeleteObject();
}


void CPolygonTerrainDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    CMenu menu;

    menu.LoadMenu(IDR_MENU1);

    CMenu *p_sub_menu = menu.GetSubMenu(0);

    CPoint pos;
    GetCursorPos(&pos);

    p_sub_menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pos.x, pos.y, this);

    menu.DestroyMenu();

    CDialog::OnRButtonDown(nFlags, point);
}


void CPolygonTerrainDlg::OnMenuPolygon1()
{
    // TODO: Add your command handler code heret
    m_vecP1 = std::move(m_vecPolygon);
    RECT rc;
    GetDlgItem(IDC_STATIC)->GetWindowRect(&rc);
    this->ScreenToClient(&rc);
    InvalidateRect(&rc, TRUE);
}


void CPolygonTerrainDlg::OnMenuPolygon2()
{
    // TODO: Add your command handler code heret
    m_vecP2 = std::move(m_vecPolygon);

    RECT rc;
    GetDlgItem(IDC_STATIC)->GetWindowRect(&rc);
    this->ScreenToClient(&rc);
    InvalidateRect(&rc, TRUE);
}


void CPolygonTerrainDlg::OnBnClickedButton2()
{
    // TODO: Add your control notification handler code here
    std::vector<point2d> clip_boundry;
    std::vector<point2d> polygon;

    if (m_vecP1.size() < 3) { return; }
    if (m_vecP2.size() < 3) { return; }

    clip_boundry.emplace_back(point2d(m_vecP1[0].x, m_vecP1[0].y));
    clip_boundry.emplace_back(point2d(m_vecP1[1].x, m_vecP1[1].y));
    clip_boundry.emplace_back(point2d(m_vecP1[2].x, m_vecP1[2].y));
    if (IsOrientation(clip_boundry) == oriCW)
    {
        clip_boundry.clear();
        auto j = 0;
        for (auto i = m_vecP1.size()-1; (0 <= i && i < m_vecP1.size()); --i)
        {
            clip_boundry.emplace_back(point2d(m_vecP1[j].x, m_vecP1[j].y));
            j = i;
        }
    }
    else
    {
        clip_boundry.clear();
        std::transform(m_vecP1.begin(), m_vecP1.end(), std::back_inserter(clip_boundry), [](POINT& v)->point2d {
            return { v.x, v.y };
        });
    }
    std::transform(m_vecP2.begin(), m_vecP2.end(), std::back_inserter(polygon), [](POINT& v)->point2d {
        return { v.x, v.y };
    });

    SutherlandHodgman(clip_boundry, polygon);

    m_vecP3.clear();
    std::transform(polygon.begin(), polygon.end(), std::back_inserter(m_vecP3), [](point2d& v)->POINT {
        return { v.x, v.y };
    });

    RECT rc;
    GetDlgItem(IDC_STATIC)->GetWindowRect(&rc);
    this->ScreenToClient(&rc);
    InvalidateRect(&rc, TRUE);
}
