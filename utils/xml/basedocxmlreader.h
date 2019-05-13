#ifndef BASEDOCXMLREADER_H
#define BASEDOCXMLREADER_H
#include <QFile>
#include <QDomDocument>
#include <QDebug>

class BaseDocXmlReader
{
public:
    BaseDocXmlReader();
    virtual ~BaseDocXmlReader();

    //数据清除
    virtual void dataClear() = 0;

    //读取具体内容
    virtual bool readDetails() = 0;

    //读Xml配置文件
    bool read(const QString &fileName);

    //是否存在根节点
    bool isExistRootTagName(const QString& strRoot);

    //查找其下第一个子节点
    void firstChildElement(const QString &oldTagName, const QString &newTagName);

    //查找子节点的第一个Tag的名称
    QString findFirstChildTag(const QString &strTagName);

    //判断此节点是否存在
    bool isExistNodeTagName(const QString &tagName);

    //保留当前节点Dom
    void pushFirstTopElement(const QString& tagName);

    //将保存的节点Dom取出
    void popFirstTopElement(const QString& tagName);

    //下一个节点
    void nextSiblingElement(const QString &tagName);

    //获取此节点Tag信息
    QString getStrTagName(const QString &tagName);

    //获取此节点的Text
    QString getStrText(const QString& tagName);

    //获取此节点的Attribute信息
    QString getStrAttribute(const QString& tagName, const QString& strAttr);

    //获取此节点的Attribute信息
    quint16 getIntAttribute(const QString& tagName, const QString& strAttr);

private:
    //设置m_pDoc信息
    bool setContent(QFile *file);
    bool readStart(const QString &fileName);
    bool readStop();
    void clearDomEles();
private:
    QDomDocument* m_pDoc;
    QMap<QString, QDomElement> m_mapDomElement;
    QFile *m_file;
    QMap<QString, QDomElement>  m_firstDomElement;
};

#endif // BASEDOCXMLREADER_H
