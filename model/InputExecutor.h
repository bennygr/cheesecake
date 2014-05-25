
#ifndef INPUT_EXEC_H
#define INPUT_EXEC_H
//-----------------------------------------------------------------------------
#include <QList>
#include <QString>
#include <QProcess>
#include <QThread>
//-----------------------------------------------------------------------------
class InputExecutor  : protected QThread
{
	Q_OBJECT
	
	private:
		QString pathToExecutor;
		QProcess *process;
		bool isRunning;
		bool resetUsb;
		void run(); 
		void ResetUsb();

	signals:
		void Started();
		void Stopped();

	public:
		InputExecutor(QString pathToExecutor,bool resetUsb)
			: pathToExecutor(pathToExecutor)
			{
				isRunning = false;
				this->resetUsb = resetUsb; 
				process = NULL; 
			}

		QString getPathToExecutor();

		void Start();
		void Stop();
};
//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
//EOF

