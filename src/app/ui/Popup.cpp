/*
JuffEd - An advanced text editor
Copyright 2007-2010 Mikhail Murzin

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License 
version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "Popup.h"

static const int AlphaSolid       = 220;
static const int AlphaTransparent = 150;
static const int Height           = 80;
static const int StepCount        = 40;

Popup::Popup(QWidget* parent) : QFrame(parent) {
	setFrameShape(QFrame::Box);
	setFrameShadow(QFrame::Raised);
	
	setGeometry(0, -Height, 100, Height);
	hidden_ = true;
	
	messageL_ = new QLabel("");
	messageL_->setAlignment(Qt::AlignCenter);
	messageL_->setWordWrap(true);
	
	timerL_ = new QLabel("");
	timerL_->setMaximumWidth(30);
	timerL_->setAlignment(Qt::AlignCenter);
	
	QHBoxLayout* hBox = new QHBoxLayout(this);
	hBox->addWidget(messageL_);
	hBox->addWidget(timerL_);
	hBox->setContentsMargins(2, 2, 2, 2);
	
	setAlpha(AlphaTransparent);
	
	timer_ = new QTimer();
	connect(timer_, SIGNAL(timeout()), SLOT(onTimer()));
	
	timeLine_ = new QTimeLine(300);
	timeLine_->setFrameRange(0, StepCount);
	connect(timeLine_, SIGNAL(frameChanged(int)), SLOT(makeStep(int)));
}

void Popup::popup(const QString& msg, int seconds) {
	timerTicks_ = seconds;
	messageL_->setText(msg);
	timerL_->setText(QString::number(timerTicks_));
	timer_->start(1000);
	
	hidden_ = true;
	timeLine_->start();
}

void Popup::setAlpha(int alpha) {
	setStyleSheet(QString("QFrame {border: 1px solid gray; border-radius: 4px; background-color: rgb(240, 240, 240, %1);}").arg(alpha));
	messageL_->setStyleSheet(QString("QFrame {border: 0px; background-color: rgb(255, 255, 255, 0);}"));
	timerL_->setStyleSheet(QString("QFrame {border: 0px; background-color: rgb(255, 255, 255, 0);}"));
}

void Popup::enterEvent(QEvent* event) {
	setAlpha(AlphaSolid);
	QFrame::enterEvent(event);
}

void Popup::leaveEvent(QEvent* event) {
	setAlpha(AlphaTransparent);
	QFrame::leaveEvent(event);
}

void Popup::mousePressEvent(QMouseEvent*) {
	timer_->stop();
	dismiss();
}

void Popup::onTimer() {
	timerTicks_--;
	timerL_->setText(QString::number(timerTicks_));
	if ( timerTicks_ == 0 ) {
		timer_->stop();
		dismiss();
	}
}

void Popup::makeStep(int frame) {
	static const int step = Height / StepCount;
	if ( hidden_ )
		setGeometry(80, step * frame - Height, width(), 80);
	else
		setGeometry(80, step * (StepCount - frame) - Height, width(), 80);
}

void Popup::dismiss() {
	timeLine_->stop();
	hidden_ = false;
	timeLine_->start();
}
