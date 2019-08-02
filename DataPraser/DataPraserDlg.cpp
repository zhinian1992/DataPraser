
// DataPraserDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "DataPraser.h"
#include "DataPraserDlg.h"
#include "afxdialogex.h"
#include "PraseCenter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

PraseCenter praser;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
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


// CDataPraserDlg 对话框



CDataPraserDlg::CDataPraserDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DATAPRASER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDataPraserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDataPraserDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE, &CDataPraserDlg::OnBnClickedButtonOpenFile)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_TEMPLETE, &CDataPraserDlg::OnBnClickedButtonSelectTemplete)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_PATH, &CDataPraserDlg::OnBnClickedButtonSavePath)
	ON_BN_CLICKED(IDC_BUTTON_PRASE, &CDataPraserDlg::OnBnClickedButtonPrase)
	ON_MESSAGE(WM_WRITELOG,&CDataPraserDlg::OnLogMessage)
END_MESSAGE_MAP()


// CDataPraserDlg 消息处理程序

BOOL CDataPraserDlg::OnInitDialog()
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
	GetDlgItem(IDC_EDIT_SAVE_PATH)->SetWindowText("默认保存路径为待解析文件同级目录");

	CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO1);

	praser.SetLogReceiver(this->GetSafeHwnd());

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDataPraserDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDataPraserDlg::OnPaint()
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
HCURSOR CDataPraserDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/// <summary>
/// load files button clicked
/// </summary>
void CDataPraserDlg::OnBnClickedButtonOpenFile()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_FILE)->SetWindowText("");

	std::vector<CString> files = praser.LoadDataFiles();
	if(!files.empty()){
		CString sALL;
		std::vector<CString>::iterator iter = files.begin();
		for(;iter != files.end();iter++){
			sALL.Append("\<");
			sALL.Append(*iter);
			sALL.Append("\>");
		}
		GetDlgItem(IDC_EDIT_FILE)->SetWindowText(sALL);
	}
	else{
		MessageBox("Error:load files failed!");
	}

}

/// <summary>
/// load templete file button clicked
/// </summary>
void CDataPraserDlg::OnBnClickedButtonSelectTemplete()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_TEMPLETE)->SetWindowText("");

	CString file = praser.LoadTempleteFile();

	if(file.IsEmpty()){
		MessageBox("Error:load templete file failed!");
	}
	else{
		GetDlgItem(IDC_EDIT_TEMPLETE)->SetWindowText(file);
	}
}


void CDataPraserDlg::OnBnClickedButtonSavePath()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_SAVE_PATH)->SetWindowText("");

	CString file = praser.SetSaveFilePath();

	if(file.IsEmpty()){
		MessageBox("Error:set save file path failed!");
	}
	else{
		GetDlgItem(IDC_EDIT_SAVE_PATH)->SetWindowText(file);
	}
}


void CDataPraserDlg::OnBnClickedButtonPrase()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck()){
		praser.SetDataFileType(true);

		CString split;
		GetDlgItemText(IDC_EDIT_SPLIT,split);
		if(split.IsEmpty()){
			MessageBox("Error:multiple data prasing , spilt charactor cannot be null!");
			return;
		}
		else{
			praser.SetMultipleDataSplit(split);
		}	
	}
	if(!praser.ParseDataFiles())
		MessageBox("Error:prase data file failed!");
}

/// <summary>
/// write log message handler
///	add message to the end of IDC_EDIT_LOG 
/// </summary>
LRESULT CDataPraserDlg::OnLogMessage(WPARAM wParam, LPARAM lParam)
{
	CString *log;
	log = (CString *)lParam;
	((CEdit*)GetDlgItem(IDC_EDIT_LOG))->SetSel(GetDlgItem(IDC_EDIT_LOG)->GetWindowTextLength(),GetDlgItem(IDC_EDIT_LOG)->GetWindowTextLength());
	((CEdit*)GetDlgItem(IDC_EDIT_LOG))->ReplaceSel((LPCTSTR)*log);
	return 0;
}
