#include <QMouseEvent>
#include <QApplication>
#include <QScrollBar>
#include <qmath.h>

#include "graphicsviewzoom.h"

GraphicsviewZoom::GraphicsviewZoom(QGraphicsView* view)
    : QObject(view)
    , m_view(view)
{
    m_view->viewport()->installEventFilter(this);
    m_view->setMouseTracking(true);
    m_modifiers = Qt::ControlModifier;
    m_zoomFactorBase = 1.0015;
}

void GraphicsviewZoom::gentleZoom(double factor)
{
    m_view->scale(factor, factor);
    m_view->centerOn(m_targetScenePos);
    QPointF deltaViewportPos = m_targetViewportPos -
            QPointF(m_view->viewport()->width() / 2.0, m_view->viewport()->height() / 2.0);
    QPointF viewportCenter = m_view->mapFromScene(m_targetScenePos) - deltaViewportPos;
    m_view->centerOn(m_view->mapToScene(viewportCenter.toPoint()));
    emit zoomed();
}

void GraphicsviewZoom::setModifiers(Qt::KeyboardModifiers modifiers)
{
    m_modifiers = modifiers;
}

void GraphicsviewZoom::setZoomFactorBase(double value)
{
    m_zoomFactorBase = value;
}

bool GraphicsviewZoom::eventFilter(QObject *object, QEvent *event)
{
    Q_UNUSED(object)

    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QPointF delta = m_targetViewportPos - mouseEvent->pos();
        if (qAbs(delta.x()) > 5 || qAbs(delta.y()) > 5)
        {
            m_targetViewportPos = mouseEvent->pos();
            m_targetScenePos = m_view->mapToScene(mouseEvent->pos());
        }
    }
    else if (event->type() == QEvent::Wheel)
    {
        QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);
        if (QApplication::keyboardModifiers() == m_modifiers)
        {
            if (wheelEvent->orientation() == Qt::Vertical)
            {
                double angle = wheelEvent->angleDelta().y();
                double factor = qPow(m_zoomFactorBase, angle);
                gentleZoom(factor);
                return true;
            }
        }
    }

    return false;
}
