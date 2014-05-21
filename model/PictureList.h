//-----------------------------------------------------------------------------
#ifndef PICTURE_LIST_H
#define PICTURE_LIST_H
//-----------------------------------------------------------------------------
#include <iostream>
#include <QString>
#include <QStringList>
#include <QFileSystemWatcher>
#include "Picture.h"
//-----------------------------------------------------------------------------

class PictureList : public QObject
{
	Q_OBJECT

	private:
		QList<Picture*> pictureList;
		QStringList fileExtensionFilter;
		QFileSystemWatcher *fsWatcher;
		int nextPictureId;

		void AddPicture(Picture* picture);
		void UpdateList(QString path);
		bool PictureExists(QString path);

	private slots:
		void DirectoryChanged(const QString& path);

	signals:
		void PictureAdded(Picture* picture);

	public:

		Picture* GetNextPicture();

		PictureList(QString directory)
		{
			nextPictureId = -1;
			fileExtensionFilter.push_back("*.jpg");
			fileExtensionFilter.push_back("*.JPG");
			fileExtensionFilter.push_back("*.jpeg");
			fileExtensionFilter.push_back("*.JPEG");

			fsWatcher = new QFileSystemWatcher(this);
			fsWatcher->addPath(directory);
			this->connect(fsWatcher, 
						  SIGNAL(directoryChanged(QString)), 
						  this, 
						  SLOT(DirectoryChanged(QString)));
			UpdateList(directory);
		}


};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
//EOF
