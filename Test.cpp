#include "Test.h"
#include <iostream>
#include <QPixmap>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>

Test::Test()
{
	this->setupUi(this);
	this->pictureList = new PictureList("/home/bgr/Bilder/Wallpaper/");
	this->connect(pictureList, 
				  SIGNAL(PictureAdded(Picture*)), 
				  this, 
				  SLOT(PictureAdded(Picture*)));
	this->pictureLabel->setScaledContents(true);
	scrollArea->setWidgetResizable(true);
}


void Test::PictureAdded(Picture* picture)
{
	LoadPicture(picture);
}

void Test::LoadPicture(Picture* picture)
{
	QPixmap pixMap;
	pixMap.load(picture->GetFullPath());
	this->pictureLabel->setPixmap(pixMap);
}

void Test::FullScreenToggled(bool fullscreen)
{
	std::cout << fullscreen << std::endl;
	if(fullscreen)
	{
		this->showFullScreen();
		this->statusbar->setVisible( false );
		this->menubar->hide();
	}
	else 
	{
		this->showMaximized(); 
		this->statusbar->setVisible( true );
		this->menubar->show();
	}
}

void  Test::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Escape || 
	   event->key() == Qt::Key_F11 && actionFullscreen->isEnabled())
	{
		FullScreenToggled(false);	
	}
	else if(event->key() == Qt::Key_F11 &&
	        actionFullscreen->isEnabled())
	{
		FullScreenToggled(true);	
	}
}
