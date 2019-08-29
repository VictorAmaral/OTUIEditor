#ifndef OTUICWIDGET_H
#define OTUICWIDGET_H

#include <memory>
#include <QImage>
#include <QPainter>

namespace OTUI {
    class CWidget
    {
    public:
        CWidget();
        CWidget(QString widgetId, QString imagePath);
        virtual ~CWidget();

    public:
        virtual void draw(QPainter*) {}

    public:
        bool operator == (const CWidget &Ref) const
        {
            return(this->getId() == Ref.getId());
        }

        QString getId() const { return m_id; }
        void setId(QString id) {
            m_id = id;
        }

        QImage image() const { return m_image; }

        int x() const { return m_rect.x(); }
        int y() const { return m_rect.y(); }
        int width() const { return m_rect.x() + m_rect.width() - m_rect.left(); }
        int height() const { return m_rect.y() + m_rect.height() - m_rect.top(); }
        QPoint getPos() const { return m_rect.topLeft(); }
        QPoint getSize() const { return QPoint(m_rect.width(), m_rect.height()); }
        QRect* getRect() { return &m_rect; }
        QRect getParentRect() const { return QRect(m_rect.left() + m_parent->getRect()->left(),
                                             m_rect.top() + m_parent->getRect()->top(),
                                             m_rect.right(), m_rect.bottom()); }
        void setRect(int left, int top, int right, int bottom) {
            m_rect.setRect(left, top, right, bottom);
        }
        void setRect(QRect rect) {
            m_rect = rect;
        }
        void setPos(QPoint topLeft) {
            m_rect.moveTopLeft(topLeft);
        }

        QPoint getImageSize() const { return m_imageSize; }
        void setImageSize(int width, int height) {
            m_imageSize.setX(width);
            m_imageSize.setY(height);
        }

        QRect getImageCrop() const { return m_imageCrop; }
        void setImageCrop(int left, int top, int right, int bottom) {
            m_imageCrop.setRect(left, top, right, bottom);
        }
        void setImageCrop(QRect crop) {
            m_imageCrop = crop;
        }

        QRect getImageBorder() const { return m_imageBorder; }
        void setImageBorder(QRect border) {
            m_imageBorder = border;
        }

        OTUI::CWidget* getParent() const { return m_parent; }
        void setParent(OTUI::CWidget* parent) {
            m_parent = parent;
        }

        std::vector<std::unique_ptr<OTUI::CWidget>> const& getChildren() const { return m_children; }
        void addChild(std::unique_ptr<OTUI::CWidget>& child) {
            m_children.push_back(std::move(child));
        }

    private:
        QString m_id;
        QRect m_rect;

        QImage m_image;
        QPoint m_imageSize;
        QRect m_imageCrop;
        QRect m_imageBorder;

        OTUI::CWidget* m_parent = nullptr;
        std::vector<std::unique_ptr<OTUI::CWidget>> m_children;
    };
}

#endif // OTUICWIDGET_H