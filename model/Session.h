//-----------------------------------------------------------------------------
#ifndef SESSION_H
#define SESSION_H
//-----------------------------------------------------------------------------
#include <iostream>
#include <QString>
#include <QStringList>
#include <QFileSystemWatcher>
#include "InputExecutor.h"
#include "Picture.h"
//-----------------------------------------------------------------------------

class Session : public QObject
{
	Q_OBJECT

	private:
		QList<Picture*> pictureList;
		QStringList fileExtensionFilter;
		QFileSystemWatcher *fsWatcher;
		int nextPictureId;
		InputExecutor *executor;

		void AddPicture(Picture* picture);
		void UpdateList(QString path);
		bool PictureExists(QString path);

	private slots:
		void DirectoryChanged(const QString& path);

	signals:
		void PictureAdded(Picture* picture);

	public:
		Session(QString directory,QString executorPath)
		{
			this->executor = new InputExecutor(executorPath,directory);
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

		Picture* GetNextPicture();
		void Start();
		void Stop();

};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
//EOF
