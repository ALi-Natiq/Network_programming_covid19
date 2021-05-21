#include <iostream>
#include <sstream>
#include <string>
#include <zmq.hpp>
#include <nzmqt/nzmqt.hpp>
#include <QMutex>
using namespace std;

int main()
{
    cout << "Covid-19 informatie wereldwijd tussen 1/1/2020 en 14/12/2020 !...\n" << endl;
    try
    {
        nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
        nzmqt::ZMQSocket *sub = context->createSocket( nzmqt::ZMQSocket::TYP_SUB, context );
        nzmqt::ZMQSocket *send = context->createSocket( nzmqt::ZMQSocket::TYP_PUSH, context );
        sub->connectTo("tcp://benternet.backup.pxl-ea-ict.be:24042");//"tcp://benternet.backup.pxl-ea-ict.be:24042""tcp://192.168.200.212:5554"
        send->connectTo("tcp://benternet.backup.pxl-ea-ict.be:24041");//"tcp://benternet.backup.pxl-ea-ict.be:24041""tcp://192.168.200.212:5555"

        string naam;
        string comando;
        string land;
        string dag;
        string maand;
        string jaar;
        cout << "Geef je naam in : " << endl;
        getline(cin,naam);
        cout << "Geef het land in (In het engels en begint met Groot letter) : " << endl;
        getline(cin,land);
        cout << "Geef het comando in:\n1: Voor besmettingen\n2: Voor doden\n3: Voor besmettingen, doden en het continent van het land\n4: Voor besmettingen, doden, het continent van het land en het cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000 " << endl;
        getline(cin,comando);
        cout << "Geef de dag in :" << endl;
        getline(cin,dag);
        cout << "Geef de maand in :" << endl;
        getline(cin,maand);
        //cout << "Geef het jaar in :" << endl;
        //getline(cin,jaar);
        //cout << naam << "," << comando <<"," << land <<endl;
        sub->subscribeTo(QString::fromStdString("!corona>" + naam + ">").toUtf8());
        if( !send->isConnected() || !sub->isConnected() )
            {
                cerr << "NOT CONNECTED !!!" << endl;
            }
        nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("?corona>"+naam+">"+comando+">"+land+">"+dag+">"+maand+">"+jaar).toUtf8());
        send->sendMessage(msg);
        nzmqt::ZMQMessage * incoming = new nzmqt::ZMQMessage();
        while( sub->isConnected() )
        {
           sub->receiveMessage(incoming,0);
           QString response = QString(incoming->toByteArray());
           cout << response.toStdString() <<endl;
        }
    }
    catch( nzmqt::ZMQException &ex )
    {
        std::cerr << "Catched an exception : " << ex.what();
    }
    return 0;
}

//benternet.pxl-ea-ict.be
//127.0.0.1
//"example>answer?>Ali Al abdulwahhab>CORONA-FREE-CHANNEL>094813dfe2f2b60a4d4f656bee5b372821346067>*HATSJU*>"
