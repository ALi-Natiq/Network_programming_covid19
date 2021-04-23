#include <stdio.h>
#include <iostream>
#include <zmq.h>
#include <zmq.hpp>
#include <nzmqt/nzmqt.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair

//https://ar-carrefour.blogspot.com/?m=1#

using namespace std;
void read_record();
void * context; //Global context, because you only need one !

int main()
{
    try
    {
        nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
        nzmqt::ZMQSocket *rcv = context->createSocket( nzmqt::ZMQSocket::TYP_PULL, context );
        nzmqt::ZMQSocket *publ = context->createSocket( nzmqt::ZMQSocket::TYP_PUB, context );
        //nzmqt::ZMQSocket *sub = context->createSocket( nzmqt::ZMQSocket::TYP_SUB, context );
       // nzmqt::ZMQSocket *send = context->createSocket( nzmqt::ZMQSocket::TYP_PUSH, context );
        nzmqt::ZMQSocket *socket = context->createSocket( nzmqt::ZMQSocket::TYP_REQ, context );
        //sub->connectTo("tcp://192.168.200.212:5554");
        //send->connectTo("tcp://192.168.200.212:5555");
        rcv->connectTo("tcp://192.168.200.212:5554");
        publ->connectTo("tcp://192.168.200.212:555");
        socket->connectTo("tcp://192.168.200.212:5555");
        nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString("corona>doden>Ali>").toUtf8());
        publ->sendMessage(msg);

        cout << "Sending message ..." << endl;
       // nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString("Test456").toUtf8());
        socket->sendMessage(msg);
        cout << "Sending message ..." << endl;

        nzmqt::ZMQMessage * incoming = new nzmqt::ZMQMessage();
        while(socket->isConnected());
        while( rcv->isConnected() )
        {
           rcv->receiveMessage(incoming,0);
           QString response = QString(incoming->toByteArray());
           cout << response.toStdString() <<endl;
           // cout << incoming->toByteArray().toStdString() << endl;
        }
    }

    catch( nzmqt::ZMQException &ex )
    {
        std::cerr << "Catched an exception : " << ex.what();
    }


    return 0;
}

void read_record()
{

   // File pointer
   fstream fin;

   // Open an existing file
   fin.open("COVID-19-geographic-disbtribution-worldwide.csv", ios::in);

   // Get the roll number
   // of which the data is required
   int rollnum, roll2, count = 0;
   cout << "Enter the roll number "
        << "of the country to display details: ";
   cin >> rollnum;

   // Read the Data from the file
   // as String Vector
   vector<string> row;
   string line, word, temp;

   while (fin >> temp) {

       row.clear();

       // read an entire row and
       // store it in a string variable 'line'
       getline(fin, line);

       // used for breaking words
       stringstream s(line);

       // read every column data of a row and
       // store it in a string variable, 'word'
       while (getline(s, word, ', ')) {

           // add all the column data
           // of a row to a vector
           row.push_back(word);
       }

       // convert string to integer for comparision
       roll2 = stoi(row[0]);

       // Compare the roll number
       if (roll2 == rollnum) {

           // Print the found data
           count = 1;
           cout << "cases " << row[0] << " : \n";
           cout << "deaths: " << row[1] << "\n";
           cout << "continentExp: " << row[2] << "\n";
           cout << "Cumulative_number_for_14_days_of_COVID-19_cases_per_100000: " << row[3] << "\n";
           cout << "countryterritoryCode: " << row[4] << "\n";
           cout << "year: " << row[5] << "\n";
           break;
       }
   }
   if (count == 0)
       cout << "Record not found\n";
}
