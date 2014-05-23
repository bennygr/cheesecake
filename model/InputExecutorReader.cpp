#include <QFileInfoList>
#include <QStringList>
#include "InputExecutorReader.h"

QList<QFileInfo> InputExecutorReader::GetExecutorsFromDirectory(QDir directory)
{
	QStringList fileExtensionFilter;
	fileExtensionFilter.push_back("*.cke");
	return directory.entryInfoList(fileExtensionFilter);
}

