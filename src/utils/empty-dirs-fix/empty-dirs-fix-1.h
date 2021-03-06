#ifndef EMPTY_DIRS_FIX_1_H
#define EMPTY_DIRS_FIX_1_H

#include <QDialog>
#include "models/profile.h"



namespace Ui
{
	class EmptyDirsFix1;
}



class EmptyDirsFix1 : public QDialog
{
	Q_OBJECT

	public:
		explicit EmptyDirsFix1(Profile *profile, QWidget *parent = Q_NULLPTR);
		~EmptyDirsFix1();

	public slots:
		void next();

	private:
		Ui::EmptyDirsFix1 *ui;
};

#endif // EMPTY_DIRS_FIX_1_H
