//-----------------------------------------------------------------------------
#ifndef INPUT_EXEC_READER_H
#define INPUT_EXEC_READER_H
//-----------------------------------------------------------------------------
#include <QList>
#include <QDir>
#include <QFileInfo>
#include "InputExecutor.h"
//-----------------------------------------------------------------------------
class InputExecutorReader
{
	public:
		QList<QFileInfo> GetExecutorsFromDirectory(QDir directory);
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
//EOF

