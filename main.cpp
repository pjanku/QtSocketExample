#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

void acceptConnection(){

}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTcpServer server;
    server.listen(QHostAddress("127.0.0.1"),1234);
    if (server.isListening()){
        qDebug()<<"Opened";
    }else{
        qDebug() << "Closed";
    }


    QObject::connect(&server,&QTcpServer::newConnection,[&](){
        qDebug() <<  "New connection is detected!";
        QTcpSocket *socket =  server.nextPendingConnection();
       if (socket->isOpen() ) qDebug()<<"New connection is opened";
       socket->write("Hello world fromt QT Socket app\n");

       int numRead = 0, numReadTotal = 0;
       char buffer[50];
       forever{
           numRead  = socket->read(buffer, 50);
           socket->flush();
           socket->write("Zprava:");
           socket->write(buffer);
           qDebug() << "zprava:" << buffer;
           if (numRead == 0 && !socket->waitForReadyRead())
                        break;
       }

    });

   // server.close();

    return a.exec();
}
