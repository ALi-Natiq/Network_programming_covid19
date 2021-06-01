#include <sstream> //istringstream
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <cstring>
#include <utility> // std::pair
#include <zmq.h>
#include <zmq.hpp>
#include <nzmqt/nzmqt.hpp>
using namespace std;
void read_record();
void * context; //Global context, because you only need one !

vector<vector<string>> parse2DCsvFile(string inputFileName) {
    vector<vector<string> > data;
    ifstream inputFile(inputFileName);
    int l = 0;
    while (inputFile) {
        l++;
        string line;
        if (!getline(inputFile, line)) break;
        if (line[0] != '#') {
            istringstream lineStream(line);
            vector<string> record;
            while (lineStream) {
                string cel;
                if (!getline(lineStream, cel, ','))
                    break;
                try {
                    //cout << cel << endl ;
                    record.push_back(cel);
                }
                catch (const std::invalid_argument e) {
                    cout << "NaN found in file " << inputFileName << " cel " << l
                         << endl;
                    e.what();
                }
            }
            data.push_back(record);
        }
    }
    if (!inputFile.eof()) {
        cerr << "Could not read file " << inputFileName << "\n";
        __throw_invalid_argument("File not found.");
    }
    return data;
}

int main(int argc, const char * argv[]) {
  std::vector<std::string> listRestaurants;
    try
    {
        nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
        nzmqt::ZMQSocket *sub = context->createSocket( nzmqt::ZMQSocket::TYP_SUB, context );
        nzmqt::ZMQSocket *send = context->createSocket( nzmqt::ZMQSocket::TYP_PUSH, context );
        sub->connectTo("tcp://benternet.backup.pxl-ea-ict.be:24042");//"tcp://192.168.200.212:5554"
        send->connectTo("tcp://benternet.backup.pxl-ea-ict.be:24041");//"tcp://192.168.200.212:5555"
        sub->subscribeTo("?corona>");
        cout << "Covid-19 Service is running ..." << endl;

        nzmqt::ZMQMessage * incoming = new nzmqt::ZMQMessage();
        string naam;
        string comando;
        string land;
        string dag;
        string maand;
        string jaar;
        const int DAY=1 ;
        const int MONTH=2 ;
        const int YEAR=3 ;
        const int CASES=4 ;
        const int DEATHS=5 ;
        const int LAND=6 ;
        const int CONTINENT=10 ;
        const int CUMULATIVE=11 ;
        while( sub->isConnected() )
        {
           sub->receiveMessage(incoming,0);
           QString response = QString(incoming->toByteArray());   
           QStringList parts =  response.split(">");
           if (parts[0]=="?corona")
           {
               comando=parts[2].toStdString();
               land=parts[3].toStdString();
               dag=parts[4].toStdString();
               maand=parts[5].toStdString();
               jaar=parts[6].toStdString();

               if(((parts[2]=="1" || parts[2]=="2" || parts[2]=="3" || parts[2]=="4") && islower(parts[3].toStdString()[0])))
               {
               naam=parts[1].toStdString();
               nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + naam + ", Sorry! .. Eerste letter van het land dat je ingegeven hebt is klein, het moet GROOT zijn! .. Probeer eens nog een keer! ").toUtf8());
               send->sendMessage(msg);
               }

               if((parts[2]=="1" || parts[2]=="2" || parts[2]=="3" || parts[2]=="4" ) && ((parts[4].toStdString())>="15" && parts[5].toStdString()=="12"))
               {
               naam=parts[1].toStdString();
               cout << "Hallo " << naam <<"," << "Je bent op de juiste kanaal!"<< endl;
               nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + naam + ", Sorry! ... De datum die je ingegeven hebt is buiten de grenzen van de database! ").toUtf8());
               send->sendMessage(msg);
               }

               vector<vector<string>> data = parse2DCsvFile("C:\\COVID-19-geographic-disbtribution-worldwide.csv");
               for (vector<string> record : data)
                {

                    if(parts[2]=="1" && record[LAND]==parts[3].toStdString() && record[DAY]==parts[4].toStdString() && record[MONTH]==parts[5].toStdString() )//&& record[YEAR]==parts[6].toStdString()
                    {
                    naam=parts[1].toStdString();
                    cout << "Hallo " << naam <<"," << "Je bent op de juiste kanaal!"<< endl;
                    nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + naam + "\n"+"Aantal besmettingen " + " van " + land + " op " + dag + "/" + maand + "/" + "2020" + " is " + record[CASES]).toUtf8());
                    send->sendMessage(msg);                       
                    }

                    if(parts[2]=="2" && record[LAND]==parts[3].toStdString() && record[DAY]==parts[4].toStdString() && record[MONTH]==parts[5].toStdString() )//&& record[YEAR]==parts[6].toStdString()
                    {
                    naam=parts[1].toStdString();
                    cout << "Hallo " << naam <<"," << "Je bent op de juiste kanaal!"<< endl;
                    nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + naam + ", aantal doden "  + " van " + land + " op " + dag + "/" + maand + "/" + "2020" + " is " + record[DEATHS]).toUtf8());
                    send->sendMessage(msg);
                    }

                    if(parts[2]=="3" && record[LAND]==parts[3].toStdString() && record[DAY]==parts[4].toStdString() && record[MONTH]==parts[5].toStdString() )//&& record[YEAR]==parts[6].toStdString()
                    {
                    naam=parts[1].toStdString();
                    cout << "Hallo " << naam <<"," << "Je bent op de juiste kanaal!"<< endl;
                    nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + naam + "\n"+"Aantal besmettingen " + " van " + land +  " (Continent: " + record[CONTINENT]+")"+ " op " + dag + "/" + maand + "/" + "2020" + " is " + record[CASES] +"\n"+"Aantal doden: " + record[DEATHS]).toUtf8());
                    send->sendMessage(msg);
                    }

                    if(parts[2]=="4" && record[LAND]==parts[3].toStdString() && record[DAY]==parts[4].toStdString() && record[MONTH]==parts[5].toStdString() )//&& record[YEAR]==parts[6].toStdString()
                    {
                    naam=parts[1].toStdString();
                    cout << "Hallo " << naam <<"," << "Je bent op de juiste kanaal!"<< endl;
                    nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + naam + "\n"+"Aantal besmettingen " + " van " + land +  " (Continent: " + record[CONTINENT]+")"+ " op " + dag + "/" + maand + "/" + "2020" + " is " + record[CASES] +"\n"+"Aantal doden: " + record[DEATHS]+"\n"+"Cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000: " + record[CUMULATIVE]).toUtf8());
                    send->sendMessage(msg);
                    }

               }
           }
           //cout << response.toStdString() <<endl;
           //cout << incoming->toByteArray().toStdString() << endl;
        }
    }

    catch( nzmqt::ZMQException &ex )
    {
        std::cerr << "Catched an exception : " << ex.what();
    }


    return 0;
}
