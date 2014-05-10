#include <string>
#include <iostream>

#include <locale.h>

#include <opencv2/opencv.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft Visual Studio 12.0\\VC\\lib\\freetype.lib")

#include "opencv_win.h"

using namespace std;

int main(int argc, char** argv){

	setlocale(LC_ALL, "JPN");

	//string font_name = "C:\\ManualInstall\\Font\\GN-KillGothic.ttf";
	string font_name = "C:\\ManualInstall\\Font\\TowerGothic.otf";
	//string font_name = "C:\\ManualInstall\\Font\\HGRPRE.TTC";
	FT_Library library;

	FT_Error error = FT_Init_FreeType(&library);
	if (error){
		cerr << "failed to init freetype library." << endl;
		return 1;
	}

	FT_Face face;
	error = FT_New_Face(library,
	"C:\\ManualInstall\\Font\\TowerGothic.otf",
		0,
		&face);
	if (error = FT_Err_Unknown_File_Format){
		cerr << "failed to load font file. unknown file format. file path is " << font_name << endl;
		return 2;
	}
	if (error){
		cerr << "failed to load font file. unknown error." << endl;
		return error;
	}

	/*
	error = FT_Set_Char_Size(
		face,
		0, 16 * 64, 300, 300);
		*/
	error = FT_Set_Pixel_Sizes(
		face, 0, 16);
	FT_ULong glyph_index = FT_Get_Char_Index(face, 'A');

	error = FT_Load_Glyph(
		face,
		glyph_index,
		FT_LOAD_DEFAULT);
	error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

	//string fname("Yotsubato_v01_000-a.jpg");

	//cv::Mat image = cv::imread(fname);
	cv::Mat image(face->glyph->bitmap.rows, face->glyph->bitmap.width, CV_8UC3);
	
	unsigned char *buffer = face->glyph->bitmap.buffer;
	for (int i = 0; i < image.rows; i++){

		unsigned char *line = image.ptr(i);
		for (int h = 0; h < image.cols; h++){
			
			unsigned char *pix = line + 3 * h;
			pix[0] = *buffer;
			buffer++;
		}
	}


	string wname("test");
	cv::namedWindow(wname);
	cv::imshow(wname, image);
	cv::waitKey();


}