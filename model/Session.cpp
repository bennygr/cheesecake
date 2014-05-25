#include "Session.h"
#include <QDir>
#include <QFileInfo>
#include <QList>

//-----------------------------------------------------------------------------

void Session::AddPicture(Picture* picture)
{
	this->pictureList.push_back(picture);
	std::cout << picture->GetFullPath().toStdString() << " added " << std::endl;
	emit PictureAdded(picture);
}

bool Session::PictureExists(QString path)
{
	for(int i=0;i < this->pictureList.length();i++)
	{
		if(pictureList.at(i)->GetFullPath() == path)
		{
			return true;
		}
	}
	return false;
}

void Session::Start()
{
	this->executor->Start();
}

void Session::Stop()
{
	this->executor->Stop();
}

Picture* Session::GetNextPicture()
{
	if(this->pictureList.length() == 0)
		return NULL;
	if(this->nextPictureId >= this->pictureList.length())
		this->nextPictureId = 0;
	return this->pictureList.at(this->nextPictureId++);
}

void Session::UpdateList(QString path)
{
	QDir *dir = new QDir(path);
	QFileInfoList files = dir->entryInfoList(this->fileExtensionFilter);
	for(int i=0; i<files.length();i++)
	{
		if(!PictureExists(files.at(i).absoluteFilePath()))
		{
			Picture *newPicture = new Picture(files.at(i).absoluteFilePath());
			this->AddPicture(newPicture);
		}
	}

	// Remove all odd numbers from a QList<int> 
	QMutableListIterator<Picture*> iter(this->pictureList);
	while (iter.hasNext()) 
	{
		Picture *pic = iter.next();
		if(!QFile::exists(pic->GetFullPath()))
		{
			iter.remove();
			std::cout << "removed " << pic->GetFullPath().toStdString() << std::endl;
			delete pic;
			pic = 0;
		}
	}

	//initial set of next picture
	if(this->nextPictureId == -1 && this->pictureList.count() > 0)
		this->nextPictureId = 0;
}

void Session::DirectoryChanged(const QString& path)
{
	UpdateList(path);
}

//-----------------------------------------------------------------------------
//EOF
