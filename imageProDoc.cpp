
// imageProDoc.cpp: CimageProDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "imagePro.h"
#endif

#include "imageProDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CimageProDoc

IMPLEMENT_DYNCREATE(CimageProDoc, CDocument)

BEGIN_MESSAGE_MAP(CimageProDoc, CDocument)
END_MESSAGE_MAP()


// CimageProDoc 생성/소멸

CimageProDoc::CimageProDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CimageProDoc::~CimageProDoc()
{
}

BOOL CimageProDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CimageProDoc serialization

void CimageProDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring()==TRUE)
	{
		ar.Write(ResultImg, 256 * 256);
	}
	else
	{
		CFile* fp = ar.GetFile();
		if (fp->GetLength() == 256 * 256)
		{
			ar.Read(InputImg, 256 * 256);
		}
		else 
		{
			AfxMessageBox(L"256x256 크기의 파일만 사용가능합니다.");
		}
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CimageProDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CimageProDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CimageProDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CimageProDoc 진단

#ifdef _DEBUG
void CimageProDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CimageProDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CimageProDoc 명령



void CimageProDoc::PixelAdd()
{
	// TODO: 여기에 구현 코드 추가.
	int Value = 0;

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			Value = InputImg[x][y] + 40;
			if (Value > 255)
				ResultImg[x][y] = 255;
			else
				ResultImg[x][y] = Value;
		}

	//for (int x = 0; x < 256; x++)
		//for (int y = 0; y < 256; y++)
	//		ResultImg[x][y] = InputImg[x][y] + 100; 
}

void CimageProDoc::PixelSub()
{
	// TODO: 여기에 구현 코드 추가.
	int Value = 0;

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			Value = InputImg[x][y] - 50;
			if (Value < 0)
				ResultImg[x][y] = 0;
			else
				ResultImg[x][y] = Value;
		}
}

void CimageProDoc::PixelMul()
{
	// TODO: 여기에 구현 코드 추가.

	int Value = 0;

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			Value = InputImg[x][y] * 1.5;
			if (Value > 255)
				ResultImg[x][y] = 255;
			else
				ResultImg[x][y] = Value;
		}
}

void CimageProDoc::PixelDiv()
{
	// TODO: 여기에 구현 코드 추가.

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
			ResultImg[x][y] = InputImg[x][y] / 1.5;
			
			
		
}

void CimageProDoc::Binary()
{
	// TODO: 여기에 구현 코드 추가.
	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
			if (InputImg[x][y] < 127)
				ResultImg[x][y] = 0;
			else
				ResultImg[x][y] = 255;
}

void CimageProDoc::Exam1()
{
	// TODO: 여기에 구현 코드 추가.

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
			ResultImg[x][y] = InputImg[x][y];
			
	for (int x = 20; x < 50; x++)
		for (int y = 64; y < 192; y++)
			ResultImg[x + 30][y] = InputImg[x][y];
	
		
}

void CimageProDoc::Exam2()
{
	// TODO: 여기에 구현 코드 추가.

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
			ResultImg[x][y] = InputImg[x][y];

	for(int x = 20; x < 50; x++)
		for (int y = 64; y < 192; y++)
			ResultImg[90 - x][y] = InputImg[x][y];


}



void CimageProDoc::Exam3()
{
	// TODO: 여기에 구현 코드 추가.

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
			ResultImg[x][y] = InputImg[x][y];

	for (int x = 15; x < 20; x++)
		for (int y = 64; y < 192; y++)
			ResultImg[x][y] = 255;

	for (int x = 45; x < 50; x++)
		for (int y = 64; y < 192; y++)
			ResultImg[x][y] = 255;

	for (int x = 15; x < 50; x++)
		for (int y = 64; y < 69; y++)
			ResultImg[x][y] = 255;

	for (int x = 15; x < 50; x++)
		for (int y = 187; y < 192; y++)
			ResultImg[x][y] = 255;
}

void CimageProDoc::LoadTwoImages()
{
	// TODO: 여기에 구현 코드 추가.
	CFile file; // CFile 객체 선언
	CFileDialog dlg(TRUE);


	AfxMessageBox(L"첫 번째 영상파일을 선택하세요!");

	if (dlg.DoModal() == IDOK) 
	{
		file.Open(dlg.GetPathName(), CFile::modeRead);
		file.Read(InputImg, 256 * 256);
		file.Close();
	}

	AfxMessageBox(L"두 번째 영상파일을 선택하세요!");

	if (dlg.DoModal() == IDOK)
	{
		file.Open(dlg.GetPathName(), CFile::modeRead);
		file.Read(InputImg2, 256 * 256);
		file.Close();
	}
}

void CimageProDoc::Two_Image_Add()
{
	// TODO: 여기에 구현 코드 추가.
	LoadTwoImages();

	int data = 0;

	for(int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			data = InputImg[x][y] + InputImg2[x][y];

			if (data > 255)
				ResultImg[x][y] = 255;
			else
				ResultImg[x][y] = data;
		}
}

void CimageProDoc::Two_Image_Minus()
{
	// TODO: 여기에 구현 코드 추가.
	LoadTwoImages();

	int data = 0;

	for(int x=0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			data = InputImg[x][y] - InputImg2[x][y];

			if (data < 0)
				ResultImg[x][y] = 0;
			else
				ResultImg[x][y] = data;
		}
}

void CimageProDoc::Two_Image_Multiple()
{
	// TODO: 여기에 구현 코드 추가.

	LoadTwoImages();

	int data = 0;

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			data = InputImg[x][y] | InputImg2[x][y];

			if (data > 255)
				ResultImg[x][y] = 255;
			else
				ResultImg[x][y] = data;
		}
}


void CimageProDoc::Two_Image_Div()
{
	// TODO: 여기에 구현 코드 추가.

	LoadTwoImages();

	int data = 0;

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			if (InputImg2[x][y] == 0)
			{
				ResultImg[x][y] = InputImg[x][y];
			}
			else 
			{
				ResultImg[x][y] = InputImg[x][y] / InputImg2[x][y];
			}

		}
}

void CimageProDoc::Histogram()
{
	// TODO: 여기에 구현 코드 추가.
	int k, value, m = 0;
	int histo[256];
	int temp[256][256];

	for (int z = 0; z < 256; z++)
	{
		histo[z] = 0;
		for (int w = 0; w < 256; w++)
			temp[z][w] = 0;
	}

	for (int x = 0; x < 256; x++)
		for(int y = 0; y<256; y++)
		{
			k = InputImg[x][y]; // 밝기값
			histo[k] = histo[k] + 1; // 밝기값의 배열에 1을 추가 즉 카운팅 개수
		}

	for (int x = 0; x < 256; x++)
	{
		value = histo[x] / 5;
		
		if (value > 255)
			value = 255;

		for (int y = 0; y < value; y++)
			temp[y][x] = 128;
	}

	for(int x=0; x<256; x++)
		for (int y = 0; y < 256; y++)
		{
			m = (255 - x);
			ResultImg[m][y] = temp[x][y];
		}
		
}

void CimageProDoc::Histo_Strech()
{
	// TODO: 여기에 구현 코드 추가.
	int max = 255;
	int k, min = 0;
	int histo[256];

	for (int z = 0; z < 256; z++)
		histo[z] = 0;

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			k = InputImg[x][y];
			histo[k] = histo[k] + 1;
		}
			

	for (int z = 0; z < 256; z++)
	{
		if (histo[z])
		{
			min = z;
			break;
		}
	}

	for (int z = 255; z > 0; z--)
	{
		if (histo[z])
		{
			max = z;
			break;
		}
	}

	for(int x=0; x<256; x++)
		for (int y = 0; y < 256; y++)
		{
			ResultImg[x][y] = ((InputImg[x][y] - min) * 255) / (max - min);
		}
}

void CimageProDoc::Histo_EQ()
{
	// TODO: 여기에 구현 코드 추가.
	int k, m;
	int sum=0;
	int histo[256];
	int Sum[256];

	// 배열 초기화
	for (int z = 0; z < 256; z++)
	{
		histo[z] = 0;
		Sum[z] = 0;
	}

	// 영상의 히스토그램 계산
	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			k = InputImg[x][y];
			histo[k] = histo[k] + 1;
		}

	// 누적 히스토그램 계산
	for (int w = 0; w < 256; w++)
	{
		sum = sum + histo[w];
		Sum[w] = sum;
	}

	// 정규화 및 결과 영상 매핑과정
	for(int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			m = InputImg[x][y];
			ResultImg[x][y] = unsigned char ((Sum[m] * 255) / (256 * 256));
		}
	
}

void CimageProDoc::Mirror()
{
	// TODO: 여기에 구현 코드 추가.
	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
			ResultImg[x][255 - y] = InputImg[x][y];
} 

void CimageProDoc::Flip()
{
	// TODO: 여기에 구현 코드 추가.
	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
			ResultImg[255-x][y] = InputImg[x][y];
}

void CimageProDoc::ZoomIn_1()
{
	// TODO: 여기에 구현 코드 추가.
	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
			ResultImg[x*2][y*2] = InputImg[x][y];
}

void CimageProDoc::ZoomIn_2()
{
	// TODO: 여기에 구현 코드 추가.
	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			ResultImg[x * 2][y * 2] = InputImg[x][y];
			ResultImg[x * 2][y * 2+1] = InputImg[x][y];
			ResultImg[x * 2 + 1][y * 2] = InputImg[x][y];
			ResultImg[x * 2 + 1][y * 2+1] = InputImg[x][y];
		}
			
}

void CimageProDoc::ZoomIn_3()
{
	// TODO: 여기에 구현 코드 추가.

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 256; y++)
		{
			ResultImg[x * 2][y * 2] = InputImg[x][y];
		}
	
	for(int x=0; x<256; x++)
		for (int y = 0; y < 256; y++)
		{
			ResultImg[x*2][y*2 + 1] = unsigned char((ResultImg[x * 2][y * 2] + ResultImg[x * 2][y * 2 + 2]) / 2);
		}

	for (int x = 0; x < 256; x++)
		for (int y = 0; y < 512; y++)
		{
			ResultImg[x * 2 + 1][y] = unsigned char((ResultImg[x * 2][y] + ResultImg[x * 2 + 2][y]) / 2);
		}

}
