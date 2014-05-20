#include <QMainWindow>
#include <QGraphicsScene>
#include "Picture.h"
#include "PictureList.h"
#include "ui_untitled.h"

class Test : public QMainWindow, public Ui_MainWindow
{
	Q_OBJECT

	public:
		Test();
	private:
		PictureList *pictureList;
		void LoadPicture(Picture* picture);
	private slots:
		void PictureAdded(Picture* picture);
};

