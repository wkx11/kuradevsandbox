// これは メイン DLL ファイルです。

#include "stdafx.h"

#include "ImageConverter.h"

namespace UFOHunt{ namespace Lib {

	// cv::MatをDrawing::Bitmapへ変換
	System::Drawing::Bitmap^ ImageConverter::Mat2DotNetBMP(ImageConverterData_cvMat^ mat)
	{
#pragma region バッファにメモリを割り当てる
		System::Drawing::Bitmap ^dst = nullptr;
		switch (mat->channels) {
		case 4:
			if (mat->elemSize1 == 1)
				dst = gcnew System::Drawing::Bitmap(
					mat->cols, mat->rows, System::Drawing::Imaging::PixelFormat::Format32bppArgb);
			else if (mat->elemSize1 == 2)
				dst = gcnew System::Drawing::Bitmap(
					mat->cols, mat->rows, System::Drawing::Imaging::PixelFormat::Format64bppArgb);
			break;
		case 3:
			if (mat->elemSize1 == 1)
				dst = gcnew System::Drawing::Bitmap(
					mat->cols, mat->rows, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
			else if (mat->elemSize1 == 2)
				dst = gcnew System::Drawing::Bitmap(
					mat->cols, mat->rows, System::Drawing::Imaging::PixelFormat::Format48bppRgb);
			break;
		case 1:
			if (mat->elemSize1 == 2)
				dst = gcnew System::Drawing::Bitmap(
					mat->cols, mat->rows, System::Drawing::Imaging::PixelFormat::Format16bppGrayScale);
		default:
			dst = gcnew System::Drawing::Bitmap(
				mat->cols, mat->rows, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
		}
#pragma endregion

		// 直接アクセス開始
		System::Drawing::Imaging::BitmapData ^data = dst->LockBits(
			*(gcnew System::Drawing::Rectangle(0, 0, dst->Width, dst->Height)), 
			System::Drawing::Imaging::ImageLockMode::ReadWrite, 
			dst->PixelFormat
		);

#pragma region データのコピー処理
		// Bitmap互換の連続データの場合は単純memcpyを行う
		if ((dst->PixelFormat != System::Drawing::Imaging::PixelFormat::Format24bppRgb
			 || (mat->channels == 3 && mat->elemSize1 == 1 && dst->PixelFormat == System::Drawing::Imaging::PixelFormat::Format24bppRgb))
			 && mat->isContinuous) {
			memcpy(data->Scan0.ToPointer(), mat->data, mat->rows * mat->cols * mat->channels);
		// Bitmap互換でisContinuousフラグが立ってない(不連続データ)場合は1列ごとにコピー
		} else if (dst->PixelFormat != System::Drawing::Imaging::PixelFormat::Format24bppRgb
			 || (mat->channels == 3 && mat->elemSize1 == 1 && dst->PixelFormat == System::Drawing::Imaging::PixelFormat::Format24bppRgb)) {
			uchar *dp = (uchar *)data->Scan0.ToPointer();
			size_t copystep = mat->elemSize * mat->rows;
			for (int i = 0; i < mat->rows; i++)
				memcpy(dp + copystep * i, mat->data + mat->step * i, copystep);
		// memcpyできない場合は画素毎にコピー処理を行う
		} else {
			if (mat->channels == 1) { // 単色画像(グレースケール)の場合
				if (mat->elemSize1 == 1) { // 8bit時は高速化の為に加算処理を減らす
					uchar *p = (uchar *)data->Scan0.ToPointer();
					for (int i = 0; i < mat->rows * mat->cols; i++) {
						*(p + i * 3) = *(p + i * 3 + 1) = *(p + i * 3 + 2) = *(mat->data + i);
					}
				} else {
					uchar *p = (uchar *)data->Scan0.ToPointer();
					for (int i = 0; i < mat->rows * mat->cols; i++) {
						*(p + i * 3) = *(p + i * 3 + 1) = *(p + i * 3 + 2) = *(mat->data + i * mat->elemSize1 + mat->elemSize);
					}
				}
			} else if (mat->channels == 2) { // 用途不明だけど2要素のMatの場合
				if (mat->elemSize1 == 1) { // 8bit長の場合はRとGへそのまま展開
					uchar *p = (uchar *)data->Scan0.ToPointer();
					for (int i = 0; i < mat->rows * mat->cols; i++) {
						memcpy(p + i * 3, mat->data + i * 2, 2);
						*(p + i * 3 + 2) = 0;
					}
				} else if (mat->elemSize1 = 2) { // 16bit長の場合はRとGへ上位8bitのみコピー。1/256してる。
					uchar *p = (uchar *)data->Scan0.ToPointer();
					for (int i = 0; i < mat->rows * mat->cols * 2; i++) {
						*(p + i * 3) = *(mat->data + i * 4 + 1);
						*(p + i * 3 + 1) = *(mat->data + i * 4 + 3);
						*(p + i * 3 + 2) = 0;
					}
				}
			}
		}
#pragma endregion

		// 直接アクセス終了
		dst->UnlockBits(data);

		return dst;
	}

	// Drawing::Imageをcv::Matへ変換(Bitmapからより低速)
	ImageConverterData_cvMat^ ImageConverter::DotNetIMG2Mat(System::Drawing::Image^ img)
	{
		return DotNetBMP2Mat(gcnew System::Drawing::Bitmap(img));
	}

	// Drawing::Bitmapをcv::Matへ変換
	ImageConverterData_cvMat^ ImageConverter::DotNetBMP2Mat(System::Drawing::Bitmap^ bmp)
	{
		cv::Mat dst(bmp->Height, bmp->Width, CV_8UC3);

		// 直接アクセス開始
		System::Drawing::Imaging::BitmapData ^data = bmp->LockBits(
			*(gcnew System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height)), 
			System::Drawing::Imaging::ImageLockMode::ReadOnly, 
			bmp->PixelFormat
		);

		// データのコピー
		if (System::Drawing::Imaging::PixelFormat::Format24bppRgb == bmp->PixelFormat) {
			memcpy(dst.data, data->Scan0.ToPointer(), bmp->Width * bmp->Height * 3);
		} else if (System::Drawing::Imaging::PixelFormat::Format32bppArgb == bmp->PixelFormat) {
			uchar *pm = dst.data;
			uchar *pb = (uchar *)data->Scan0.ToPointer();
			for (int i = 0; i < bmp->Width * bmp->Height; i++) {
				memcpy(pm + i * 3, pb + i * 4, 3);
			}
		} else {
			uchar *pm = dst.data;
			uchar *pb = (uchar *)data->Scan0.ToPointer();
			for (int i = 0; i < bmp->Width * bmp->Height; i++) {
				*(pm + i * 3) = *(pm + i * 3 + 1) = *(pm + i * 3 + 2) = *(pb + i);
			}
		}

		// 直接アクセス終了
		bmp->UnlockBits(data);

		return ImageConverterData_cvMat::Create(dst.rows, dst.cols, dst.flags, dst.data, dst.refcount, dst.datastart, dst.dataend);
	}
}}