#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QVariant>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

   /* QJsonObject jobj;
    jobj.insert("title",QJsonValue::fromVariant("T_monkey"));
    jobj.insert("body",QJsonValue::fromVariant("B_humain"));
    jobj.insert("userId",QJsonValue::fromVariant(33));

    QJsonDocument doc(jobj);
    qDebug() << doc.toJson();*/

    QNetworkRequest req(QUrl("https://jsonplaceholder.typicode.com/posts/1"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager man;

    //QNetworkReply *reply = man.post(req,doc.toJson());
    QNetworkReply *reply = man.get(req);

    while(!reply->isFinished()){
        qApp->processEvents();
    }

    QByteArray responseBytes = reply->readAll();
    //qDebug() << responseBytes;
    //qDebug() << "*****************************";

    QString str = QString(responseBytes);
    QByteArray jsonBytes = str.toLocal8Bit();

    auto jsonDoc = QJsonDocument::fromJson(jsonBytes);
    QJsonObject json_obj = jsonDoc.object();
    QVariantMap json_map = json_obj.toVariantMap();

     qDebug() << json_map["id"].toInt();
     qDebug() << json_map["title"].toString();


    return a.exec();
}
