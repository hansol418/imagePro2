
// imageProDoc.h: CimageProDoc 클래스의 인터페이스
//


#pragma once


class CimageProDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CimageProDoc() noexcept;
	DECLARE_DYNCREATE(CimageProDoc)

// 특성입니다.
public:
	unsigned char InputImg[256][256];		// 입력영상 저장공간
	unsigned char InputImg2[256][256];		// 또 다른 입력영상 저장공간
	unsigned char ResultImg[512][512];		// 결과영상 저장공간

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CimageProDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	void PixelAdd();
	void PixelSub();
	void PixelMul();
	void PixelDiv();
	void Binary();
	void Exam1();
	void Exam2();

	void Exam3();
	void LoadTwoImages();
	void Two_Image_Add();
	void Two_Image_Minus();
	void Two_Image_Multiple();
	void Two_Image_Div();
	void Histogram();
	void Histo_Strech();
	void Histo_EQ();
	void Mirror();
	void ZoomIn_1();
	void Flip();
	void ZoomIn_2();
	void ZoomIn_3();
};
