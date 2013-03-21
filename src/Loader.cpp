/*
 * Loader.cpp
 *
 *  Created on: 19.03.2013
 *      Author: UnSchtalch
 */
#include <png.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

bool loadPNGImage(char* name, int &outWidth, int &outHeght, bool &outHasAlpha,
		GLubyte **outData)
{
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	FILE *fp;

	if ((fp = fopen(name, "rb")) == NULL)  //everything clear
		return false;

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	//if we've got not PNG image
	if (png_ptr == NULL)
	{
		fclose(fp);
		return false;
	}

	info_ptr = png_create_info_struct(png_ptr);
	//the same as before
	if (info_ptr == NULL)
	{
		fclose(fp);
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		return false;
	}

	//Huston, we've got a problem in file reading
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
		fclose(fp);
		return false;
	}

	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, sig_read);

	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, png_voidp_NULL);

	outWidth = info_ptr->width;
	outHeght = info_ptr->height;
	switch (info_ptr->color_type)
	{
		case PNG_COLOR_TYPE_RGBA:
		{
			outHasAlpha = true;
			break;
		}
		case PNG_COLOR_TYPE_RGB:
		{
			outHasAlpha = false;
			break;
		}
		default:
		{
			png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
			fclose(fp);
			return false;
		}
	}

	unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	*outData = (unsigned char*)malloc(row_bytes* outHeght);
	png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

	for(int i = 0; i< outHeght; i++)
	{
		memcpy(*outData+(row_bytes * (outHeght - 1 - i)), row_pointers[i], row_bytes);
	}

	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
	fclose(fp);
	return true;
}

