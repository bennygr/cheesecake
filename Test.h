#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QFileInfo>
#include "Picture.h"
#include "Session.h"
#include "ui_untitled.h"
#include "AboutDialog.h"

class Test : public QMainWindow, public Ui_MainWindow
{
	Q_OBJECT

	private:
		Session *session;
		QTimer *slideTimer;
		void LoadPicture(Picture* picture);
		void StartSession();
		QLabel *statusLabel;
		Picture *welcome;
		AboutDialog *about;
		int slideTime;

	protected:
		virtual void  keyPressEvent(QKeyEvent *event);

	private slots:
		void PictureAdded(Picture* picture);
		void NextPicture();
		void CloseSession();
		void NewSession();
		void About();
	public slots:
		void FullScreenToggled(bool fullscreen);
		void SlideShowToggled(bool slide);
		void CreateSession(QString sessionDir);

	public:
		Test()
		{
			this->session = NULL;
			this->slideTimer = NULL;
			this->slideTime = 3000; //3 seconds
			this->welcome = new Picture(QApplication::applicationDirPath() + "/welcome.png");
			this->statusLabel = new QLabel();
			this->statusLabel->setText("cheesecake");
			this->setupUi(this);
			this->statusBar()->addPermanentWidget(statusLabel,100);
			this->pictureLabel->setScaledContents(false);
			this->about = new AboutDialog();
			scrollArea->setWidgetResizable(true);
			actionClose->setEnabled(false);
			actionNex_picture->setEnabled(false);
			LoadPicture(this->welcome);
		}

		virtual ~Test()
		{
			CloseSession();
		}
};

