/*
 * Copyright (C) 2019 ~ %YEAR% Deepin Technology Co., Ltd.
 *
 * Author:     WangXin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "cgraphicsproxywidget.h"
//#include "cgraphicstextitem.h"
#include "cgraphicsitem.h"
#include "cgraphicsview.h"
#include "cdrawscene.h"
#include "ctextedit.h"

#include <QComboBox>
#include <QTextEdit>
#include <QDebug>
#include <QApplication>
#include "application.h"
CGraphicsProxyWidget::CGraphicsProxyWidget(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QGraphicsProxyWidget(parent, wFlags)
{
}

CGraphicsItem *CGraphicsProxyWidget::parentDrawItem()
{
    return dynamic_cast<CGraphicsItem *>(parentItem());
}

//void CGraphicsProxyWidget::addFriendWidget(QWidget *pFriendWdg)
//{
//    if (pFriendWdg == nullptr)
//        return;

//    _friendWidgets.insert(pFriendWdg);
//}

void CGraphicsProxyWidget::focusOutEvent(QFocusEvent *event)
{
    //QGuiApplication::inputMethod()->reset();
    //QGraphicsProxyWidget::focusOutEvent(event);

    //文字编辑控件失去焦点事件需要做的事:
    //1.去掉输入法预览界面[实际是QtBUG-88016]
    //2.某一些文字属性控件强占焦点导致的焦点丢失,不应该将焦点转让
    //3.还有一些文字属性控件强占焦点导致的焦点丢失,会在强占完成后将焦点转移回来,所以需要暂时隐藏光标
    //4.焦点丢失后,应该选中所有文字

    //1.掉输入法预览界面
    QGuiApplication::inputMethod()->reset();

    if (widget() == nullptr || parentDrawItem() == nullptr)
        return QGraphicsProxyWidget::focusOutEvent(event);

    qDebug() << "new focus object = " << dApp->focusObject() << "is same = "
             << (dApp->focusObject() == widget())
             << "parent = " << widget()->parent()
             << "active widget = " << dApp->activePopupWidget();

    //2.字体下拉菜单的属性修改(如字体族,字体style)导致的焦点丢失不应该响应
    if (dApp->focusObject() == widget() || dApp->activePopupWidget() != nullptr) {
        qDebug() << "return dApp->focusObject() = " << dApp->focusObject() << "dApp->activePopupWidget() = " << dApp->activePopupWidget()
                 << "active window = " << dApp->activeWindow();
        //2.1保证按键响应到textedit控件的底层(从而才能将key事件传递给textedit)
        if (parentDrawItem()->curView() != nullptr) {
            parentDrawItem()->curView()->setFocus();
        }

        //2.2保证自身的焦点
        this->setFocus();
        widget()->setFocus();
        event->accept();
        return;
    }

    //3.焦点移动到了改变字体大小的combox上(准确点其实应该判断那个控件的指针),要隐藏光标,大小修改完成后再显示(参见字体修改后的makeEditabel)
    if (qobject_cast<QComboBox *>(dApp->focusObject()) != nullptr) {

        this->setFocus();

        if (qobject_cast<CTextEdit *>(widget()) != nullptr) {
            CTextEdit *pTextEditor = qobject_cast<CTextEdit *>(widget());
            pTextEditor->setTextInteractionFlags(pTextEditor->textInteractionFlags() & (~Qt::TextEditable));
        }
        return;
    }

    qDebug() << "CGraphicsProxyWidget::focusOutEvent ----- ";

    QGraphicsProxyWidget::focusOutEvent(event);

    //4.需要全选所有文字便于外面单击图元的时候修改的是整体的属性
    if (parentDrawItem() && parentDrawItem()->drawScene()) {
        if (qobject_cast<CTextEdit *>(widget()) != nullptr) {
            CTextEdit *pTextEditor = qobject_cast<CTextEdit *>(widget());
            pTextEditor->selectAll();
        }
        widget()->hide();
        parentDrawItem()->drawScene()->notSelectItem(parentDrawItem());
    }
}

void CGraphicsProxyWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsProxyWidget::paint(painter, option, widget);
}
