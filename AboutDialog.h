#include "ui_about.h"

class AboutDialog : public QDialog, 
					public Ui_AboutDialog
{
	Q_OBJECT
	public:
		AboutDialog()
		{
			this->setupUi(this);
		}
};
