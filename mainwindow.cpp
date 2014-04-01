#include "mainwindow.h"
#include "ui_mainwindow.h"

#if (QT_VERSION > 0x50000)
    #include <QtWidgets>
#else
    #include <QtGui>
#endif

class CstTextDocumentLayout : public QAbstractTextDocumentLayout {
    Q_OBJECT

public:
    CstTextDocumentLayout(QTextDocument *document)
        : QAbstractTextDocumentLayout(document)
    {
    }

    QRectF	blockBoundingRect(const QTextBlock & block) const
    {
       QTextBlockFormat fmt = block.blockFormat();
       return QRectF(0, 0, 100, 100);
    }
    QSizeF	documentSize() const
    {
        qDebug() << "document size call";
        return QSizeF(320, 240);
    }
    void draw(QPainter * painter, const PaintContext & context)
    {
        qDebug() << "draw method call";
        QTextDocument *doc = document();

        if (!doc->blockCount()) {
            return;
        }

        QString rs;
        for (QTextBlock blck = doc->begin(); blck != doc->end(); blck = blck.next())
        {
            QString nextText = blck.text();
            rs.append(nextText);
            rs.append("\n");

        }

        QTextOption opt;
        opt.setWrapMode(QTextOption::WordWrap);

        QFont pf = painter->font();
        pf.setStyle(QFont::StyleItalic);
        painter->setFont(pf);

        painter->drawText(context.clip.toRect(), rs, opt);
    }
    QRectF frameBoundingRect(QTextFrame * frame) const
    {
        qDebug() << "frame bounding rect call";
        return QRectF(0, 0, 100, 50);
    }
    int	hitTest(const QPointF & point, Qt::HitTestAccuracy accuracy) const
    {
        qDebug() << "hit test call";
        return -1;
    }
    int	pageCount () const
    {
        qDebug() << "page count call";
        return 1;
    }

    void documentChanged(int position, int charsRemoved, int charsAdded)
    {
        qDebug() << "document changed method";
        emit update(QRectF(0, 0, 100, 100));
    }


};

#include "mainwindow.moc"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEdit->document()->setDocumentLayout(new CstTextDocumentLayout(ui->textEdit->document()));
    QTextDocument *doc = ui->textEdit->document();
    //CstTextDocumentLayout laydata(doc);
    ui->textEdit->document()->setHtml("<!DOCTYPE html>"
                                      "<html>"
                                      "<body>"
                                      "<p><b>This text is bold</b></p>"
                                      "<p><strong>This text is strong</strong></p>"
                                      "<p><em>This text is emphasized</em></p>"
                                      "<p><i>This text is italic</i></p>"
                                      "<p><small>This text is small</small></p>"
                                      "<p>This is<sub> subscript</sub> and <sup>superscript</sup></p>"
                                      "</body>"
                                      "</html>");
}

MainWindow::~MainWindow()
{
    delete ui;
}
