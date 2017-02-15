#pragma once
#include <QtWidgets/QWidget>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qlabel.h>

using Plabel = QLabel*;
using Pbutton = QPushButton*;
using Ptextedit = QTextEdit*;
class WidgetPubTalk :public QWidget
{
public:
	WidgetPubTalk();
	~WidgetPubTalk();

	Pbutton m_button_SendMsg, m_button_Clear, m_button_RecvFile;
	Pbutton m_button_SendFile, m_button_StartPaint;
	Ptextedit m_textedit_view, m_textedit_write;
	Plabel m_label_wrong, m_label_num;

private:


};

WidgetPubTalk::WidgetPubTalk()
{
}

WidgetPubTalk::~WidgetPubTalk()
{
}