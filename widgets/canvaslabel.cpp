#include "canvaslabel.h"

#include <QPainter>

#include "utils/tempfile.h"

CanvasLabel::CanvasLabel(QWidget *parent)
    : QLabel(parent),
      m_shapesWidgetExist(false)
{
}

void CanvasLabel::setCanvasPixmap(QString imageFile)
{
    m_currentFile = imageFile;
    m_currentPixmap = QPixmap(m_currentFile);
    if (!m_currentPixmap.isNull())
    {
        update();
        qDebug() << "CanvasLabel:" << imageFile;
    } else {
        qWarning() << "m_currentPixmap is null";
    }
}

void CanvasLabel::setCanvasPixmap(QPixmap pixmap)
{
    m_currentPixmap = pixmap;
    if (!m_currentPixmap.isNull()) {
        update();
    } else {
        qWarning() << "m_currentPixmap is null";
    }
}

void CanvasLabel::initShapesWidget(QString shape, bool needInited)
{
    if (needInited) {
        m_shapesWidget = new ShapesWidget(this);
        m_shapesWidgetExist = true;
    }
    m_shapesWidget->setCurrentShape(shape);
    m_shapesWidget->resize(this->width(), this->height());
    m_shapesWidget->move(0, 0);
    m_shapesWidget->show();
    qDebug() << "CanvasLabel initShapesWidget.." << m_shapesWidget->geometry();

    connect(m_shapesWidget, &ShapesWidget::reloadEffectImg, this,
            &CanvasLabel::createBlurEffect);
}

void CanvasLabel::setShapeColor(DrawStatus drawstatus, QColor color)
{
    qDebug() << "CanvasLabel setShapeColor:" << color;
    if (!m_shapesWidgetExist)
        return;

    if (drawstatus == DrawStatus::Fill) {
        m_shapesWidget->setBrushColor(color);
    } else {
        m_shapesWidget->setPenColor(color);
    }
}

void CanvasLabel::setShapeLineWidth(int linewidth)
{
    m_shapesWidget->setLineWidth(linewidth);
}

void CanvasLabel::setLineShape(QString lineshape)
{
    m_shapesWidget->setCurrentShape(lineshape);
}

void CanvasLabel::setTextFontsize(int fontsize)
{
    m_shapesWidget->setTextFontsize(fontsize);
}

void CanvasLabel::setBlurLinewidth(int linewidth)
{
    m_shapesWidget->setBlurLinewidth(linewidth);
}

void CanvasLabel::createBlurEffect(const QString &type)
{
    if (type == "blur")
    {
        QPixmap tmpPixmap;
        tmpPixmap = this->grab(rect());

        const int radius = 10;
        int imgWidth = tmpPixmap.width();
        int imgHeight = tmpPixmap.height();
        if (!tmpPixmap.isNull()) {
            tmpPixmap = tmpPixmap.scaled(imgWidth/radius, imgHeight/radius,
                Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            tmpPixmap = tmpPixmap.scaled(imgWidth, imgHeight,
                Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            tmpPixmap.save(TempFile::instance()->getBlurFileName(), "PNG");
        }
    }
}

void CanvasLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter painter(this);

#ifdef QT_DEBUG
    QPixmap drawTestPixmap = QPixmap("/home/ph/Pictures/ddddddddddd.png");
    if (!drawTestPixmap.isNull()) {
        setFixedSize(drawTestPixmap.size());
        painter.drawPixmap(this->rect(), drawTestPixmap);

    }

#endif
    if (m_currentPixmap.isNull()) {
        return ;
    } else {
        setFixedSize(m_currentPixmap.size());
        /* update shapesWidget's size, app crash!
//        if (m_shapesWidgetExist) {
//            m_shapesWidget->resize(this->width(), this->height());
//        }
        */
    }

    painter.drawPixmap(this->rect(), m_currentPixmap);
    createBlurEffect("blur");
}

CanvasLabel::~CanvasLabel()
{
}
