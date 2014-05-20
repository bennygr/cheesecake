#include "PictureList.h"
#include <QDir>
#include <QFileInfo>
#include <QList>

//-----------------------------------------------------------------------------

void PictureList::AddPicture(Picture* picture)
{
	this->pictureList.push_back(picture);
	std::cout << picture->GetFullPath().toStdString() << " added " << std::endl;
}

bool PictureList::PictureExists(QString path)
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

Picture* PictureList::GetNextPicture()
{
	if(this->pictureList.length() > 0)
		return this->pictureList.at(0);
	return NULL;
}

void PictureList::UpdateList(QString path)
{
	QDir *dir = new QDir(path);
	QFileInfoList files = dir->entryInfoList(this->fileExtensionFilter);
	for(int i=0; i<files.length();i++)
	{
		if(!PictureExists(files.at(i).absoluteFilePath()))
		{
			Picture *newPicture = new Picture(files.at(i).absoluteFilePath());
			this->AddPicture(newPicture);
			emit PictureAdded(newPicture);
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
}

void PictureList::DirectoryChanged(const QString& path)
{
	UpdateList(path);
}

//-----------------------------------------------------------------------------
//EOF
