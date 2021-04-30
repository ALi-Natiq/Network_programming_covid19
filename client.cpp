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
