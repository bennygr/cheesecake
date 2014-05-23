#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QFileInfo>
#include "Picture.h"
#include "Session.h"
#include "ui_untitled.h"
#include "InputExecutorReader.h"

class Test : public QMainWindow, public Ui_MainWindow
{
	Q_OBJECT

	private:
		Session *session;
		QTimer *slideTimer;
		InputExecutorReader inputExecutorReader;
		QList<QFileInfo> inputExecutors;
		void LoadPicture(Picture* picture);
		void StartSession();

	protected:
		virtual void  keyPressEvent(QKeyEvent *event);

	private slots:
		void PictureAdded(Picture* picture);
		void FullScreenToggled(bool fullscreen);
		void SlideShowToggled(bool slide);
		void NextPicture();
		void NewSession();
		void CloseSession();

	public:
		Test()
		{
			session = NULL;
			this->setupUi(this);
			this->pictureLabel->setScaledContents(true);
			scrollArea->setWidgetResizable(true);
		}
};

