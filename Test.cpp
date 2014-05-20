#include "Test.h"
#include <iostream>
#include <QPixmap>
#include <QGraphicsPixmapItem>

Test::Test()
{
	this->setupUi(this);
	this->pictureList = new PictureList("/home/bgr/Bilder/Wallpaper/");
	this->connect(pictureList, 
				  SIGNAL(PictureAdded(Picture*)), 
				  this, 
				  SLOT(PictureAdded(Picture*)));
}


void Test::PictureAdded(Picture* picture)
{
	LoadPicture(picture);
}

void Test::LoadPicture(Picture* picture)
{
	this->pictureLabel->setScaledContents(true);
	QPixmap pixMap;
	pixMap.load(picture->GetFullPath());
	this->pictureLabel->setPixmap(pixMap);
	this->pictureLabel->adjustSize();
}
