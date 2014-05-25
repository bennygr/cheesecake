#include "Test.h"
#include <iostream>
#include <QPixmap>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include "InputExecutor.h"

void Test::LoadPicture(Picture* picture)
{
	if(picture != NULL)
	{
		QPixmap pixMap;
		pixMap.load(picture->GetFullPath());
		this->pictureLabel->setPixmap(pixMap);
	}
	else
	{
		this->pictureLabel->setPixmap(NULL);
	}
}

void Test::StartSession()
{
	this->connect(session, 
			SIGNAL(PictureAdded(Picture*)), 
			this, 
			SLOT(PictureAdded(Picture*)));
	this->session->Start();
	if(this->actionSlideshow->isChecked())
	{
		SlideShowToggled(true);
	}
	statusLabel->setText("Session started");
	actionNew->setEnabled(false);
	actionClose->setEnabled(true);
	actionNex_picture->setEnabled(true);
}

void Test::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Escape || 
	   (event->key() == Qt::Key_F11 && actionFullscreen->isEnabled()))
	{
		FullScreenToggled(false);	
	}
	else if(event->key() == Qt::Key_Return)
	{
		NextPicture();		
	}
	else if(event->key() == Qt::Key_F11 &&
	        actionFullscreen->isEnabled())
	{
		FullScreenToggled(true);	
	}
}

void Test::PictureAdded(Picture* picture)
{
	if(this->actionSlideshow->isChecked())
		this->slideTimer->stop();

	LoadPicture(picture);

	if(this->actionSlideshow->isChecked())
		this->slideTimer->start(this->slideTime);
}

void Test::FullScreenToggled(bool fullscreen)
{
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

void Test::SlideShowToggled(bool slide)
{
	this->actionSlideshow->setChecked(slide);
	if(session != NULL)
	{
		if(!slide && this->slideTimer != NULL)
		{
			this->slideTimer->stop();
			delete this->slideTimer;
			this->slideTimer = NULL;
			this->statusLabel->setText("Slide show stopped.");
		}
		else if(slide)
		{
			this->slideTimer = new QTimer(this);
			connect(slideTimer,
					SIGNAL(timeout()),
					this,
					SLOT(NextPicture()));
			this->slideTimer->start(this->slideTime);
			this->statusLabel->setText("Slide show started.");
		}
	}
}

void Test::NextPicture()
{
	if(this->session != NULL)
	{
		Picture* picture = this->session->GetNextPicture();
		if(picture != NULL)
		{
			LoadPicture(picture);
		}
	}
}

void Test::NewSession()
{
	CreateSession("");
}

void Test::CreateSession(QString sessionDir)
{
	if(session != NULL)
	{
		CloseSession();
	}

	if(sessionDir.isEmpty())	
	{
		sessionDir = QFileDialog::getExistingDirectory ();
	}

    if ( sessionDir.isNull() == false )
	{
		if(!sessionDir.endsWith(QDir::separator()))
		{
			sessionDir += QDir::separator();
		}

		LoadPicture(NULL);
		QString executor ="gphoto2 --capture-tethered --filename " + 
			sessionDir + 
			"%H%M%S.%C";
		this->session = new Session(sessionDir,executor,false);
		this->pictureLabel->setScaledContents(true);
		StartSession();
	}
}

void Test::CloseSession()
{
	if(session != NULL)
	{
		SlideShowToggled(false);
		session->Stop();
		delete session;
		session = NULL;
		statusLabel->setText("Session closed");
		LoadPicture(NULL);
		actionNew->setEnabled(true);
		actionNex_picture->setEnabled(false);
		actionClose->setEnabled(false);
		this->pictureLabel->setScaledContents(false);
		LoadPicture(this->welcome);
	}
}

void Test::About()
{
	about->setModal(true);
	about->show();
}
