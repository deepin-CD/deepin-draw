#ifndef CGRAPHICSMASICOITEM_H
#define CGRAPHICSMASICOITEM_H

#include "cgraphicsrectitem.h"
#include "cgraphicspenitem.h"
#include "cpictureitem.h"
#include <QPainterPath>

class CSizeHandleRect;

class CGraphicsMasicoItem : public CGraphicsPenItem
{
public:
    explicit CGraphicsMasicoItem(QGraphicsItem *parent = nullptr);
    explicit CGraphicsMasicoItem(const QPointF &startPoint, QGraphicsItem *parent = nullptr);

    /**
     * @brief  返回模糊图元的类型值
     */
    int  type() const override;

    /**
     * @brief  刷新模糊图像
     */
    void updateMasicPixmap();

    /**
     * @brief  刷新设置模糊图像
     */
    void updateMasicPixmap(const QPixmap &pixmap);

    /**
     * @brief  重载自身的形状(相比于pen图元,去掉了两端的样式)
     */
    QPainterPath getSelfOrgShape() const override;

    /**
     * @brief  刷新模糊的路径
     */
    void updateBlurPath();

    /**
     * @brief  模糊的路径
     */
    QPainterPath blurPath();

    /**
     * @brief  模糊的类型
     */
    EBlurEffect getBlurEffect() const;

    /**
     * @brief  设置模糊的类型
     */
    void setBlurEffect(EBlurEffect effect);

    /**
     * @brief  模糊的线宽
     */
    int getBlurWidth() const;

    /**
     * @brief  设置模糊的线宽
     */
    void setBlurWidth(int width);

    /**
     * @brief  获取图源的数据信息
     */
    CGraphicsUnit getGraphicsUnit(EDataReason reson) const override;

    /**
     * @brief  加载图源数据信息
     */
    void loadGraphicsUnit(const CGraphicsUnit &data) override;



//    QPixmap blurPix();

private:
    QList<QGraphicsItem *> filterItems(QList<QGraphicsItem *> items);

private:
    enum EBlurAlp {EFreeBlur, EOnlyImag, Q3Alp = EFreeBlur, Q4Alp = EOnlyImag, EBlurCount};
    void updateBlurPixmap(EBlurAlp tp = Q4Alp);

    void freeBlurUpdate();
    void onlyImageBlurUpdate();

protected:
    /**
     * @brief  重载绘制
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    /**
     * @brief  重载可穿透
     */
    bool isPosPenetrable(const QPointF &posLocal) override;
private:
    QPixmap      m_pixmap;
    QPainterPath m_blurPath;
    EBlurEffect  m_nBlurEffect;   //0是模糊  1是马赛克
};

#endif // CGRAPHICSMASICOITEM_H
