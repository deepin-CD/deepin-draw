/*
 * Copyright (C) 2019 ~ %YEAR% Deepin Technology Co., Ltd.
 *
 * Author:     RenRan
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
#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <DPushButton>

DWIDGET_USE_NAMESPACE

class PushButton : public DPushButton
{
    Q_OBJECT
//    Q_PROPERTY(QString normalPic READ normalPic WRITE setNormalPic NOTIFY normalPicChanged)
//    Q_PROPERTY(QString hoverPic READ hoverPic WRITE setHoverPic NOTIFY hoverPicChanged)
//    Q_PROPERTY(QString pressPic READ pressPic WRITE setPressPic NOTIFY pressPicChanged)
//    Q_PROPERTY(QString disablePic READ disablePic WRITE setDisablePic NOTIFY disablePicChanged)
//    Q_PROPERTY(QString checkedPic READ checkedPic WRITE setCheckedPic NOTIFY checkedPicChanged)

//    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
//    Q_PROPERTY(QColor normalColor READ normalColor WRITE setNormalColor NOTIFY normalColorChanged)
//    Q_PROPERTY(QColor hoverColor READ hoverColor WRITE setHoverColor NOTIFY hoverColorChanged)
//    Q_PROPERTY(QColor pressColor READ pressColor WRITE setPressColor NOTIFY pressColorChanged)
//    Q_PROPERTY(QColor disableColor READ disableColor WRITE setDisableColor NOTIFY disableColorChanged)

public:
    explicit PushButton(DWidget *parent = nullptr);

    QString normalPic() const;
    QString hoverPic() const;
    QString pressPic() const;
    QString disablePic() const;
    QString checkedPic() const;

    QString text() const;
    QColor normalColor() const;
    QColor hoverColor() const;
    QColor pressColor() const;
    QColor disableColor() const;

//    int  getSpacing() const;
    void setSpacing(int spacing);

//    bool isCheckable();
    void setCheckable(bool checkeable);
//    void lockedCheckedStatus(bool locked);

//    bool getChecked() const;
    void setChecked(bool checked);

public slots:
//    void setNormalPic(QString normalPic);
//    void setHoverPic(QString hoverPic);
//    void setPressPic(QString pressPic);
//    void setDisablePic(QString disablePic);
//    void setCheckedPic(QString checkedPic);

    void setText(QString text);

//    void setNormalColor(QColor normalColor);
//    void setHoverColor(QColor hoverColor);
//    void setPressColor(QColor pressColor);
//    void setDisableColor(QColor disableColor);

signals:
    void normalPicChanged(QString normalPic);
    void hoverPicChanged(QString hoverPic);
    void pressPicChanged(QString pressPic);
    void disablePicChanged(QString disablePic);
    void textChanged(QString text);

    void normalColorChanged(QColor normalColor);
    void hoverColorChanged(QColor hoverColor);
    void pressColorChanged(QColor pressColor);
    void disableColorChanged(QColor disableColor);

    void clicked();
    void mouseLeave();

    void checkedPicChanged(QString checkedPic);

protected:
//    bool event(QEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
    void enterEvent(QEvent *e) override;
    void leaveEvent(QEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    QString getPixmap() const;
    QColor  getTextColor() const;

private:
    QString m_normalPic;
    QString m_hoverPic;
    QString m_pressPic;
    QString m_disablePic;
    QString m_text;
    QColor m_normalColor;
    QColor m_hoverColor;
    QColor m_pressColor;
    QColor m_disableColor;

    QString m_currentPic;
    QColor m_currentColor;

    bool m_isCheckable;
    bool m_checked;
    bool m_isPressed;
    bool m_isHovered;
    bool m_isLocked;
    int m_spacing;
    QString m_checkedPic;
};

#endif // PUSHBUTTON_H
