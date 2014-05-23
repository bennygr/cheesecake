
#ifndef INPUT_EXEC_H
#define INPUT_EXEC_H
//-----------------------------------------------------------------------------
#include <QList>
#include <QString>
//-----------------------------------------------------------------------------
class InputExecutor
{
	private:
		QString pathToExecutor;
		QString inputDirectory;
		bool isRunning;

	public:
		InputExecutor(QString pathToExecutor,QString inputDirectory)
			: pathToExecutor(pathToExecutor),
			  inputDirectory(inputDirectory)
			{
				isRunning = false;
			}

		QString getPathToExecutor();

		void Start();
		void Stop();
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
//EOF

