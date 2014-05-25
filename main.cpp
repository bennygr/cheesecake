#include <QApplication>
#include <iostream>
#include "Test.h"
#include "Config.h"

int main(int argc, char** argv)
{
	bool start = Config::ParseArguments(argc,argv); 
	if(start)
	{
		QApplication app(argc,argv);
		Test *t = new Test();
		if(Config::FullScreen)
			t->FullScreenToggled(true);
		if(Config::StartSlideShow)
			t->SlideShowToggled(true);
		if(!Config::SessionDir.isEmpty())
			t->CreateSession(Config::SessionDir);

		t->show();
		int ret = app.exec();
		delete t;
		t = NULL;
		return ret;
	}
	return 0;
}

