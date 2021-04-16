#include <iostream>
#include <zmq.hpp>
#include <nzmqt/nzmqt.hpp>
#include <QMutex>
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    try
    {
        nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
        nzmqt::ZMQSocket *sub = context->createSocket( nzmqt::ZMQSocket::TYP_SUB, context );
        nzmqt::ZMQSocket *send = context->createSocket( nzmqt::ZMQSocket::TYP_PUSH, context );
        sub->connectTo("tcp://localhost:5555"); // Nu dus in plaats van "tcp://benternet.pxl-ea-ict.be:24042" om gewoon locaal te testen
        send->connectTo("tcp://localhost:5556"); // Nu dus in plaats van "tcp://benternet.pxl-ea-ict.be:24041" om gewoon locaal te testen
        sub->subscribeTo("");

        if( !send->isConnected() || !sub->isConnected() )
            {
                cerr << "NOT CONNECTED !!!" << endl;
            }
        nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString("").toUtf8());
        send->sendMessage(msg);
        nzmqt::ZMQMessage * incoming = new nzmqt::ZMQMessage();

        while( sub->isConnected() )
        {
           sub->receiveMessage(incoming,0);
            cout << incoming->toByteArray().toStdString() << endl;
        }
    }
    
    while(COVID-19-geographic-disbtribution-worldwide.good())
{

    getline(file, ID, ',');
    cout << "date: " << date << " " ; 

    getline(file, nome, ',') ;
    cout << "day: " << day << " " ;

    getline(file, idade, ',') ;
    cout << "mounth: " << mounth << " "  ; 

    getline(file, genero, ' ') ; 
    cout << "year: " <<  year<< " "  ;

}
    catch( nzmqt::ZMQException &ex )
    {
        std::cerr << "Catched an exception : " << ex.what();
    }
    return 0;
}
