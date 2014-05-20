#include <QApplication>
#include <iostream>
#include "Test.h"

int main(int argc, char** argv)
{
	QApplication app(argc,argv);
	Test *t = new Test();
	t->show();
	return app.exec();
}

