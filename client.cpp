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
        sub->connectTo("tcp://192.168.200.212:5554");
        send->connectTo("tcp://192.168.200.212:5555");
        sub->subscribeTo("corona>doden>");
        string naam;
        string comando;
        string land;
        cout << "Geef je naam in " << endl;
        getline(cin,naam);
        cout << "Geef je comando in " << endl;
        getline(cin,comando);
        cout << "Geef het land in " << endl;
        getline(cin,land);

        cout << naam << "," << comando <<"," << land <<endl;


        while(1){

        }

        if( !send->isConnected() || !sub->isConnected() )
            {
                cerr << "NOT CONNECTED !!!" << endl;
            }
        nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("?corona>"+naam+">"+comando+">"+land+">").toUtf8());
        send->sendMessage(msg);
        //nzmqt::ZMQMessage * incoming = new nzmqt::ZMQMessage();

//        while( sub->isConnected() )
//        {
//           sub->receiveMessage(incoming,0);
//           QString response = QString(incoming->toByteArray());
//           cout << response.toStdString() <<endl;
//           // cout << incoming->toByteArray().toStdString() << endl;
//        }
    }
    catch( nzmqt::ZMQException &ex )
    {
        std::cerr << "Catched an exception : " << ex.what();
    }
    return 0;
}

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

int main()
{
    const int DAY=1 ;
    const int MONTH=2 ;
    const int YEAR=3 ;
    const int CASES=4 ;
    const int DEATHS=5 ;
    const int LAND=6 ;

    string day;
    string month;
    string year;
    string country;
    string command;
    cout << "Geef de dag in " << endl;
    getline(cin,day);
    cout << "Geef de maand in " << endl;
    getline(cin,month);
    cout << "Geef het jaar in " << endl;
    getline(cin,year);
    cout << "Geef het land in (Begint met Groot letter) " << endl;
    getline(cin,country);
    cout << "Geef het comando in : Voor besmettingen: 1 , Voor doden: 2 " << endl;
    getline(cin,command);

    vector<vector<string>> data = parse2DCsvFile("C:\\COVID-19-geographic-disbtribution-worldwide.csv");

    for (vector<string> record : data) { //for each loop
       //for (string x : record)
        if(command=="1")
        {
            if (record[DAY]==day &&record[MONTH]==month && record[YEAR]==year && record[LAND]==country)
            cout <<"Land: " << record[LAND] <<"\n" << "Datum: "<< record[DAY] <<"/" << record[MONTH] <<"/" << record[YEAR] << "\n" << "Aantal besmetten: "<< record[CASES]<< endl;
            //else
            //cout << "Er zijn geen besmettingen voor dit datum" << endl;
        }

        if(command=="2")
        {
            if (record[DAY]==day &&record[MONTH]==month && record[YEAR]==year && record[LAND]==country)
            cout <<"Land: " << record[LAND] <<"\n" << "Datum: "<< record[DAY] <<"/" << record[MONTH] <<"/" << record[YEAR] << "\n" << "Aantal doden: "<< record[DEATHS]<< endl;
            //else
            //cout << "Er zijn geen doden voor dit datum" << endl;
        }


    }

    return 0;
}
