#include "InputExecutor.h"
#include <QProcess>
#include <iostream>

QString InputExecutor::getPathToExecutor()
{
	return this->pathToExecutor;
}
void InputExecutor::Start()
{
	std::cout << "Starting executor: " 
			  << this->pathToExecutor.toStdString() 
			  << " for input directory "
			  << this->inputDirectory.toStdString()
			  << std::endl;
	QProcess *process = new QProcess();
	process->setProcessChannelMode(QProcess::MergedChannels);
	QStringList argv;
	argv.push_back(this->pathToExecutor);
	argv.push_back(this->inputDirectory);
	process->start("/bin/bash",argv);
	//process->start(this->pathToExecutor,argv);
	if(!process->waitForStarted())
	{
		std::cout << "failed to start process" << std::endl;
		return;
	}
	
	// Continue reading the data until EOF reached
	QByteArray data;
	while(process->waitForReadyRead())
	    data.append(process->readAll());

	// Output the data
	qDebug(data.data());
	qDebug("Done!");
}

void InputExecutor::Stop()
{
	isRunning = false;	
}
