#include <cstdio>
#include <cassert>
#include "OptimizableTga.h"
#include <fstream>

typedef struct
{
	unsigned char red, green, blue;
}
RGB_t;
Optimizable::Tga32::Tga32()
{
}


Optimizable::Tga32::~Tga32()
{
}

Optimizable::Tga32::Image::Image()
{
}


Optimizable::Tga32::Image::~Image()
{
	delete myImage;
}


Optimizable::Tga32::Image *Optimizable::Tga32::Load( const char* aName )
{
	FILE *fp = NULL;
	Image *myImage;
	unsigned char *buffer;
	TgaHeader header;
	unsigned char *source;
	unsigned char *destination;
	
	myImage = new Image(); //allocates return object
	
	fopen_s(&fp, aName, "rb" );
	assert( fp != NULL );
	
	fread(&header,sizeof(header),1,fp); // loads the header
	
	myImage->myWidth	= header.myWidth;
	myImage->myHeight	= header.myHeight;
	
	if( header.myBpp == 32 )
	{
		myImage->myImage	= new unsigned char [myImage->myHeight * myImage->myWidth * 4];
		buffer				= new unsigned char [myImage->myHeight * myImage->myWidth * 4];
		
		fread( buffer, myImage->myHeight * myImage->myWidth * 4, 1, fp ); // loads the image
		
		fclose( fp );
		
		source = buffer;

		destination = myImage->myImage;

		FlipImageData(header, source, destination);

		delete [] (buffer);

		myImage->myBitDepth=32;
		return(myImage);
	}
	
	return( NULL );
}


void Optimizable::Tga32::FlipImageData( const TgaHeader& header, unsigned char* source, unsigned char* destination )
{
	int x;
	int positionSource;
	int positionSourceY, positionSourceX;
	int totalSize = header.myWidth * header.myHeight;
	int width = header.myWidth;
	int height = header.myHeight;
	int heightMinusOne = height - 1;

	int xOffset;
	for (x = 0; x < totalSize; x++)
	{
		xOffset = x * 4;
		positionSourceY = heightMinusOne - (x / width);
		positionSourceX = x % (width);

		positionSource = (positionSourceY * width + positionSourceX) * 4;

		destination[xOffset] = source[positionSource];
		destination[xOffset + 1] = source[positionSource + 1];
		destination[xOffset + 2] = source[positionSource + 2];
		destination[xOffset + 3] = source[positionSource + 3];
	}
}

void Optimizable::Tga32::Save(const char* aName, int myWidth, int myHeight, int myBitDepth, unsigned char* myData)
{
	std::ofstream oS(aName, std::ios::out | std::ios::binary);

	oS.put(0);
	oS.put(0);
	oS.put(2);                         /* uncompressed RGB */
	oS.put(0); 	oS.put(0);
	oS.put(0); 	oS.put(0);
	oS.put(0);
	oS.put(0); 	oS.put(0);           /* X origin */
	oS.put(0); 	oS.put(0);           /* y origin */
	oS.put((myWidth & 0x00FF));
	oS.put((myWidth & 0xFF00) / 256);
	oS.put((myHeight & 0x00FF));
	oS.put((myHeight & 0xFF00) / 256);
	oS.put(myBitDepth);                        /* 24 bit bitmap */
	oS.put(0);
	int size = myHeight*myWidth * sizeof(char) * 4;
	oS.write((const char*)myData, myHeight*myWidth * sizeof(char) * 4);
	oS.close();
}
