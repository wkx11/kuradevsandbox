// ImageConverter.h

#pragma once

using namespace System;

namespace UFOHunt{ namespace Lib {
	// cv::Matクラスのマネージコードへの受け渡し構造体
	public ref struct ImageConverterData_cvMat  {
	public:
		enum class DEPTH : char {
			CVMAT_DEPTH_8U,
			CVMAT_DEPTH_8S,
			CVMAT_DEPTH_16U,
			CVMAT_DEPTH_16S,
			CVMAT_DEPTH_32S,
			CVMAT_DEPTH_32F,
			CVMAT_DEPTH_64F,
			CVMAT_DEPTH_USRTYPE1
		};
		
		enum class TYPE {
			CVMAT_8UC1 = CV_MAKETYPE(CV_8U,1),
			CVMAT_8UC2 = CV_MAKETYPE(CV_8U,2),
			CVMAT_8UC3 = CV_MAKETYPE(CV_8U,3),
			CVMAT_8UC4 = CV_MAKETYPE(CV_8U,4),
			CVMAT_8SC1 = CV_MAKETYPE(CV_8S,1),
			CVMAT_8SC2 = CV_MAKETYPE(CV_8S,2),
			CVMAT_8SC3 = CV_MAKETYPE(CV_8S,3),
			CVMAT_8SC4 = CV_MAKETYPE(CV_8S,4),
			CVMAT_16UC1 = CV_MAKETYPE(CV_16U,1),
			CVMAT_16UC2 = CV_MAKETYPE(CV_16U,2),
			CVMAT_16UC3 = CV_MAKETYPE(CV_16U,3),
			CVMAT_16UC4 = CV_MAKETYPE(CV_16U,4),
			CVMAT_16SC1 = CV_MAKETYPE(CV_16S,1),
			CVMAT_16SC2 = CV_MAKETYPE(CV_16S,2),
			CVMAT_16SC3 = CV_MAKETYPE(CV_16S,3),
			CVMAT_16SC4 = CV_MAKETYPE(CV_16S,4),
			CVMAT_32SC1 = CV_MAKETYPE(CV_32S,1),
			CVMAT_32SC2 = CV_MAKETYPE(CV_32S,2),
			CVMAT_32SC3 = CV_MAKETYPE(CV_32S,3),
			CVMAT_32SC4 = CV_MAKETYPE(CV_32S,4),
			CVMAT_32FC1 = CV_MAKETYPE(CV_32F,1),
			CVMAT_32FC2 = CV_MAKETYPE(CV_32F,2),
			CVMAT_32FC3 = CV_MAKETYPE(CV_32F,3),
			CVMAT_32FC4 = CV_MAKETYPE(CV_32F,4),
			CVMAT_64FC1 = CV_MAKETYPE(CV_64F,1),
			CVMAT_64FC2 = CV_MAKETYPE(CV_64F,2),
			CVMAT_64FC3 = CV_MAKETYPE(CV_64F,3),
			CVMAT_64FC4 = CV_MAKETYPE(CV_64F,4)
		};

	public:
		static ImageConverterData_cvMat^ Create(int rows, int cols, int flags, uchar *data) {
			ImageConverterData_cvMat^ dst = gcnew ImageConverterData_cvMat;

			dst->rows      = rows;
			dst->cols      = cols;
			dst->elemSize  = CV_ELEM_SIZE(flags);
			dst->elemSize1 = CV_ELEM_SIZE1(flags);
			dst->type      = (TYPE)CV_MAT_TYPE(flags);
			dst->depth     = (DEPTH)CV_MAT_DEPTH(flags);
			dst->channels  = CV_MAT_CN(flags);
			dst->data      = data;
			dst->refcount  = 0;
			dst->isContinuous = 0 != (flags & CV_MAT_CONT_FLAG);

			return dst;
		}
		static ImageConverterData_cvMat^ Create(int rows, int cols, int flags, uchar *data, int *refcount, uchar *datastart, uchar *dataend) {
			ImageConverterData_cvMat^ dst = Create(rows, cols, flags, data);

			dst->refcount  = refcount;
			dst->datastart = datastart;
			dst->dataend   = dataend;

			dst->addref();

			return dst;
		}
		~ImageConverterData_cvMat() { this->release(); }
		void addref()
		{
			if (refcount)
				CV_XADD(refcount, 1);
		}
		void release()
		{
			if( refcount && CV_XADD(refcount, -1) == 1 )
				cv::fastFree(datastart);
			data = datastart = dataend = 0;
			step = rows = cols = 0;
			refcount = 0;
		}
		// CvMat構造体形式でデータを返す。64bit環境だと多分データ壊れます。
		void *ToCvMat() 
		{
			CvMat *dst = ::cvCreateMatHeader(rows, cols, (int)type);
			dst->data.ptr = data;
			if (refcount)
				dst->refcount = refcount;
			return (void *)dst;
		}
	public:
		// the number of rows and columns
		int rows, cols;

		// the magic signature
		int elemSize;
		int elemSize1;
		TYPE type;
		
		// continuity flag
		bool isContinuous;
		// depth
		DEPTH depth;
		// number of channels
		int channels;

		// a distance between successive rows in bytes; includes the gap if any
		size_t step;

		// pointer to the data
		uchar *data;

		// pointer to the reference counter;
		// when matrix points to user-allocated data, the pointer is NULL
		int *refcount;

		// helper fields used in locateROI and adjustROI
		uchar *datastart;
		uchar *dataend;
	};
	public ref class ImageConverter
	{
		// TODO: このクラスの、ユーザーのメソッドをここに追加してください。
	public:
		static System::Drawing::Bitmap^ Mat2DotNetBMP(ImageConverterData_cvMat^ mat);
		static ImageConverterData_cvMat^ DotNetIMG2Mat(System::Drawing::Image^ img);
		static ImageConverterData_cvMat^ DotNetBMP2Mat(System::Drawing::Bitmap^ bmp);
	};
}}
