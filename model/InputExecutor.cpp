#include "InputExecutor.h"
#include <iostream>
#include <QApplication>

void InputExecutor::ResetUsb()
{
	//TODO: implementing calling a shell script the
	//rightway: FIXME: this is not executed
	QProcess rp;
	rp.setProcessChannelMode(QProcess::MergedChannels);
	QString rpcmd = QApplication::applicationDirPath()
					+ "/reset/callresetusb";
	std::cout << "{cheeese :) -> resetting USB " 
			  << rpcmd.toStdString()
			  << "...}"
			  << std::endl;
	rp.start(rpcmd);
	if(rp.waitForStarted())
	{
		// Continue reading the data until EOF reached
		QByteArray data;
		while(rp.waitForReadyRead())
			data.append(rp.readAll());

		// Output the data
		qDebug(data.data());
	}

	std::cout << "{cheeese :) -> USB reset done}" << std::endl;
}
void InputExecutor::run() 
{
	this->isRunning = true;
	while(this->isRunning)
	{
		if(this->resetUsb)
		{
			ResetUsb();
		}
		std::cout << "{cheeese :) -> "
		          << this->pathToExecutor.toStdString()
				  << "}" 
				  << std::endl;

		process = new QProcess();
		process->setProcessChannelMode(QProcess::MergedChannels);
		QStringList argv;
		process->start(this->pathToExecutor);
		if(process->waitForStarted())
		{
			emit Started();
			// Continue reading the data until EOF reached
			QByteArray data;
			while(process->waitForReadyRead())
				data.append(process->readAll());

			// Output the data
			qDebug(data.data());
		}

		this->process->waitForFinished(-1);
		int exitCode = this->process->exitCode();
		std::cout << "{cheeese :) ended with code "
				  << exitCode  
				  << " -> "
		          << this->pathToExecutor.toStdString()
				  << "}" 
				  << std::endl;
		delete process;
		process = NULL;
		this->sleep(1); //1 sec
	}

	emit Stopped();
	std::cout << "{cheese :) stopped!}" << std::endl;
}


QString InputExecutor::getPathToExecutor()
{
	return this->pathToExecutor;
}
void InputExecutor::Start()
{
	this->start();
}

void InputExecutor::Stop()
{
	std::cout << "{cheese :) stopping...}" << std::endl;
	if(this->process != NULL)
	{
		this->process->kill();
	}
	isRunning = false;	
}
