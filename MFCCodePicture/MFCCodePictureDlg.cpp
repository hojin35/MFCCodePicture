
// MFCCodePictureDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCCodePicture.h"
#include "MFCCodePictureDlg.h"
#include "afxdialogex.h"
#include<iostream>
#include<fstream>
#include<string>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMFCCodePictureDlg 대화 상자



CMFCCodePictureDlg::CMFCCodePictureDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCODEPICTURE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCodePictureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCCodePictureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCCodePictureDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCCodePictureDlg 메시지 처리기

BOOL CMFCCodePictureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	int nWidth = ::GetSystemMetrics(SM_CXSCREEN);
	int nHeight = ::GetSystemMetrics(SM_CYSCREEN);
	this->MoveWindow(0, 0, nWidth, nHeight - 50);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCCodePictureDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCCodePictureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCCodePictureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCCodePictureDlg::OnBnClickedButton1()
{
	
	CString str = _T("All files(*.*)|*.*|"); // 모든 파일 표시
	// _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);
	CString strPathName;
	if (dlg.DoModal() == IDOK)
	{
		strPathName = dlg.GetPathName();
		// 파일 경로를 가져와 사용할 경우, Edit Control에 값 저장
		SetDlgItemText(IDC_STATIC, strPathName);
	}


	int xCnt = 0;
	int yCnt = 0;
	int windowXSize = ::GetSystemMetrics(SM_CXSCREEN) - 100;
	int windowYSize = ::GetSystemMetrics(SM_CYSCREEN) - 200;

	int cnt = 0;
	LPCTSTR lpszTemp = strPathName;
	CFile file;
	file.Open(lpszTemp, CFile::modeRead);
	UINT length = 1;
	int z = file.GetLength();
	int QQ = file.GetLength();
	z = z / 3;
	int xSlice = 1;
	int ySlice = 1;
	for (int i = 2, j = 1; z >= i * j; i += 2, j += 1)
	{
		xSlice = j;
		ySlice = i;
	}

	int xSize = windowXSize / xSlice;
	int ySize = windowYSize / ySlice;
	while (length > 0)
	{
		char cbuf[3];
		length = file.Read(cbuf, 3);
		CString str1;
		str1 = cbuf;
		str1 = str1.Left(3);
		SetDlgItemText(IDC_STATIC, str1);
		//Sleep(10);

		CClientDC dc(this);
		
		COLORREF color = RGB(str1[0], str1[1], str[2]);
		CBrush brush;
		brush.CreateSolidBrush(color);
		CBrush* oldBrush = dc.SelectObject(&brush);
		dc.Rectangle(xCnt * xSize, yCnt * ySize, xCnt * xSize + xSize, yCnt * ySize + ySize);
		dc.SelectObject(oldBrush);
		brush.DeleteObject();
		xCnt++;
		if (xCnt >= xSlice)
		{
			xCnt = 0;
			yCnt++;
		}
		if (yCnt >= ySlice)
			break;
		cnt++;
	}
	file.Close();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}