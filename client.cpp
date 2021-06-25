#include <iostream>
#include <sstream>
#include <string>
#include <zmq.hpp>
#include <nzmqt/nzmqt.hpp>
#include <QMutex>
using namespace std;

int main()
{
    int ja;
    cout << "Welkom in Covid-19 service...\n\nDeze sevice is soort van geschiedenise informatie (dus geen life)\n\nHier kan je de geografische distributie van COVID-19 wereldwijd weten\nvoor de periode van 1/1/2020 t.e.m 14/12/2020\n" << endl;
    cout << "\nAls je een englse alfabetische lijst van alle landen wenst (ze zijn 214 landen),\ngeef maar '1' in,\nom verder te gaan zonder de lijst geef maar '2' in : " << endl;
    cin >> ja;
    if(ja==1)
    {
    cout <<"Hier is een alfabetische lijst van alle landen in het engels:\n\n"
            "Afghanistan\n"
            "Albania\n"
            "Algeria\n"
            "Andorra\n"
            "Angola\n"
            "Anguilla\n"
            "Antigua_and_Barbuda\n"
            "Argentina\n"
            "Armenia\n"
            "Aruba\n"
            "Australia\n"
            "Austria\n"
            "Azerbaijan\n"
            "Bahamas\n"
            "Bahrain\n"
            "Bangladesh\n"
            "Barbados\n"
            "Belarus\n"
            "Belgium\n"
            "Belize\n"
            "Benin\n"
            "Bermuda\n"
            "Bhutan\n"
            "Bolivia\n"
            "Bonaire, Saint Eustatius and Saba\n"
            "Bosnia_and_Herzegovina\n"
            "Botswana\n"
            "Brazil\n"
            "British_Virgin_Islands\n"
            "Brunei_Darussalam\n"
            "Bulgaria\n"
            "Burkina_Faso\n"
            "Burundi\n"
            "Cambodia\n"
            "Cameroon\n"
            "Canada\n"
            "Cape_Verde\n"
            "Cases_on_an_international_conveyance_Japan\n"
            "Cayman_Islands\n"
            "Central_African_Republic\n"
            "Chad\n"
            "Chile\n"
            "China\n"
            "Colombia\n"
            "Comoros\n"
            "Congo\n"
            "Costa_Rica\n"
            "Cote_dIvoire\n"
            "Croatia\n"
            "Cuba\n"
            "Curaçao\n" //Curaçao//CuraÃ§ao
            "Cyprus\n"
            "Czechia\n"
            "Democratic_Republic_of_the_Congo\n"
            "Denmark\n"
            "Djibouti\n"
            "Dominica\n"
            "Dominican_Republic\n"
            "Ecuador\n"
            "Egypt\n"
            "El_Salvador\n"
            "Equatorial_Guinea\n"
            "Eritrea\n"
            "Estonia\n"
            "Eswatini\n"
            "Ethiopia\n"
            "Falkland_Islands_(Malvinas)\n"
            "Faroe_Islands\n"
            "Fiji\n"
            "Finland\n"
            "France\n"
            "French_Polynesia\n"
            "Gabon\n"
            "Gambia\n"
            "Georgia\n"
            "Germany\n"
            "Ghana\n"
            "Gibraltar\n"
            "Greece\n"
            "Greenland\n"
            "Grenada\n"
            "Guam\n"
            "Guatemala\n"
            "Guernsey\n"
            "Guinea\n"
            "Guinea_Bissau\n"
            "Guyana\n"
            "Haiti\n"
            "Holy_See\n"
            "Honduras\n"
            "Hungary\n"
            "Iceland\n"
            "India\n"
            "Indonesia\n"
            "Iran\n"
            "Iraq\n"
            "Ireland\n"
            "Isle_of_Man\n"
            "Israel\n"
            "Italy\n"
            "Jamaica\n"
            "Japan\n"
            "Jersey\n"
            "Jordan\n"
            "Kazakhstan\n"
            "Kenya\n"
            "Kosovo\n"
            "Kuwait\n"
            "Kyrgyzstan\n"
            "Laos\n"
            "Latvia\n"
            "Lebanon\n"
            "Lesotho\n"
            "Liberia\n"
            "Libya\n"
            "Liechtenstein\n"
            "Lithuania\n"
            "Luxembourg\n"
            "Madagascar\n"
            "Malawi\n"
            "Malaysia\n"
            "Maldives\n"
            "Mali\n"
            "Malta\n"
            "Marshall_Islands\n"
            "Mauritania\n"
            "Mauritius\n"
            "Mexico\n"
            "Moldova\n"
            "Monaco\n"
            "Mongolia\n"
            "Montenegro\n"
            "Montserrat\n"
            "Morocco\n"
            "Mozambique\n"
            "Myanmar\n"
            "Namibia\n"
            "Nepal\n"
            "Netherlands\n"
            "New_Caledonia\n"
            "New_Zealand\n"
            "Nicaragua\n"
            "Niger\n"
            "Nigeria\n"
            "North_Macedonia\n"
            "Northern_Mariana_Islands\n"
            "Norway\n"
            "Oman\n"
            "Pakistan\n"
            "Palestine\n"
            "Panama\n"
            "Papua_New_Guinea\n"
            "Paraguay\n"
            "Peru\n"
            "Philippines\n"
            "Poland\n"
            "Portugal\n"
            "Puerto_Rico\n"
            "Qatar\n"
            "Romania\n"
            "Russia\n"
            "Rwanda\n"
            "Saint_Kitts_and_Nevis\n"
            "Saint_Lucia\n"
            "Saint_Vincent_and_the_Grenadines\n"
            "San_Marino\n"
            "Sao_Tome_and_Principe\n"
            "Saudi_Arabia\n"
            "Senegal\n"
            "Serbia\n"
            "Seychelles\n"
            "Sierra_Leone\n"
            "Singapore\n"
            "Sint_Maarten\n"
            "Slovakia\n"
            "Slovenia\n"
            "Solomon_Islands\n"
            "Somalia\n"
            "South_Africa\n"
            "South_Korea\n"
            "South_Sudan\n"
            "Spain\n"
            "Sri_Lanka\n"
            "Sudan\n"
            "Suriname\n"
            "Sweden\n"
            "Switzerland\n"
            "Syria\n"
            "Taiwan\n"
            "Tajikistan\n"
            "Thailand\n"
            "Timor_Leste\n"
            "Togo\n"
            "Trinidad_and_Tobago\n"
            "Tunisia\n"
            "Turkey\n"
            "Turks_and_Caicos_islands\n"
            "Uganda\n"
            "Ukraine\n"
            "United_Arab_Emirates\n"
            "United_Kingdom\n"
            "United_Republic_of_Tanzania\n"
            "United_States_of_America\n"
            "United_States_Virgin_Islands\n"
            "Uruguay\n"
            "Uzbekistan\n"
            "Vanuatu\n"
            "Venezuela\n"
            "Vietnam\n"
            "Wallis_and_Futuna\n"
            "Western_Sahara\n"
            "Yemen\n"
            "Zambia\n"
            "Zimbabwe"<< endl;
    try
    {
        nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
        nzmqt::ZMQSocket *sub = context->createSocket( nzmqt::ZMQSocket::TYP_SUB, context );
        nzmqt::ZMQSocket *send = context->createSocket( nzmqt::ZMQSocket::TYP_PUSH, context );
        sub->connectTo("tcp://benternet.pxl-ea-ict.be:24042");//"tcp://benternet.backup.pxl-ea-ict.be:24042""tcp://192.168.200.212:5554"
        send->connectTo("tcp://benternet.pxl-ea-ict.be:24041");//"tcp://benternet.backup.pxl-ea-ict.be:24041""tcp://192.168.200.212:5555"
        string naam;
        string aantal_landen;
        string comando;
        string land;
        string dag;
        string maand;
        string begindag;
        string beginmaand;
        string einddag;
        string eindmaand;
        string hallo;
        cout << "\nGeef eens een paar gegevens nu!" << endl;
        getline(cin,hallo);
        cout << "\nGeef je naam in : " << endl;
        getline(cin,naam);

        cout << "\nAls je voor meerdere landen kiest geef eens 1, anders geef eens 2: " << endl;
        cin >> aantal_landen;
        if (aantal_landen == "1")
            {
            string land1;
            string land2;
            string landen;
            string hallo2;
            cout << "\nGeef eens een paar gegevens nu!" << endl;
            getline(cin,hallo2);
            cout << "\ngeef land1 :"<< endl;
            getline(cin,land1);
            cout << "\ngeef land2 :"<< endl;
            getline(cin,land2);
            cout << "\nlanden zijn: "<< land1 << land2 << endl;

            cout << "\nDe commandos zijn:\n1: Voor besmettingen"
                    "\n2: Voor doden"
                    "\n3: Voor besmettingen, doden en het continent van het land\n4: Voor besmettingen, doden, het continent van het land\n   en het cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000"
                    "\n5: Voor besmettingen, doden, het continent van het land,\n   het cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000\n   en geoID van het land"
                    "\n6: Voor besmettingen, doden, het continent van het land,\n   het cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000,\n   geoID van het land en land grondgebied Code\n"
                    "\n7: Voor doden van bepaalde datums "
                    "\nGeef uw gekozen commando tussen 1 en 7 in:   "<< endl;
            getline(cin,comando);
            if (comando == "7"){
                cout << "\nGeef de begindag in :" << endl;
                getline(cin,begindag);
                cout << "\nGeef de einddag in :" << endl;
                getline(cin,einddag);
                cout << "\nGeef de beginmaand in :" << endl;
                getline(cin,beginmaand);
                cout << "\nGeef de eindmaand in :" << endl;
                getline(cin,eindmaand);
                sub->subscribeTo(QString::fromStdString("!corona>" + naam + ">").toUtf8());
                if( !send->isConnected() || !sub->isConnected() )
                    {
                        cerr << "NOT CONNECTED !!!" << endl;
                    }

                nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("?corona>"+naam+">"+comando+">"+land+">"+">"+begindag+">"+einddag+">"+beginmaand+">"+eindmaand).toUtf8());
                send->sendMessage(msg);
                nzmqt::ZMQMessage * incoming = new nzmqt::ZMQMessage();
                while( sub->isConnected() )
                {
                   sub->receiveMessage(incoming,0);
                   QString response = QString(incoming->toByteArray());
                   cout << response.toStdString() <<endl;
                }
            }
            else {cout << "\nGeef de dag in :" << endl;
            getline(cin,dag);
            cout << "\nGeef de maand in :" << endl;
            getline(cin,maand);}
            sub->subscribeTo(QString::fromStdString("!corona>" + naam + ">").toUtf8());
            if( !send->isConnected() || !sub->isConnected() )
                {
                    cerr << "NOT CONNECTED !!!" << endl;
                }
            nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("?corona>"+aantal_landen+">"+naam+">"+comando+">"+land1+">"+land2+">"+dag+">"+maand).toUtf8());//
            send->sendMessage(msg);
            nzmqt::ZMQMessage * incoming = new nzmqt::ZMQMessage();
            while( sub->isConnected() )
            {
               sub->receiveMessage(incoming,0);
               QString response = QString(incoming->toByteArray());
               cout << response.toStdString() <<endl;
            }
            }

        cout << "\nGeef het land in (In het engels en begint met Groot letter) : " << endl;
        getline(cin,land);
        cout << "\nDe commandos zijn:\n1: Voor besmettingen"
                "\n2: Voor doden"
                "\n3: Voor besmettingen, doden en het continent van het land\n4: Voor besmettingen, doden, het continent van het land\n   en het cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000"
                "\n5: Voor besmettingen, doden, het continent van het land,\n   het cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000\n   en geoID van het land"
                "\n6: Voor besmettingen, doden, het continent van het land,\n   het cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000,\n   geoID van het land en land grondgebied Code\n"
                "\n7: Voor doden van bepaalde datums "
                "\nGeef uw gekozen commando tussen 1 en 7 in:   "<< endl;
        getline(cin,comando);
        if (comando == "7"){
            cout << "\nGeef de begindag in :" << endl;
            getline(cin,begindag);
            cout << "\nGeef de einddag in :" << endl;
            getline(cin,einddag);
            cout << "\nGeef de beginmaand in :" << endl;
            getline(cin,beginmaand);
            cout << "\nGeef de eindmaand in :" << endl;
            getline(cin,eindmaand);
            sub->subscribeTo(QString::fromStdString("!corona>" + naam + ">").toUtf8());
            if( !send->isConnected() || !sub->isConnected() )
                {
                    cerr << "NOT CONNECTED !!!" << endl;
                }
            nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("?corona>"+naam+">"+comando+">"+land+">"+begindag+">"+einddag+">"+beginmaand+">"+eindmaand).toUtf8());
            send->sendMessage(msg);
            nzmqt::ZMQMessage * incoming = new nzmqt::ZMQMessage();
            while( sub->isConnected() )
            {
               sub->receiveMessage(incoming,0);
               QString response = QString(incoming->toByteArray());
               cout << response.toStdString() <<endl;
            }
        }
        else {cout << "\nGeef de dag in :" << endl;
        getline(cin,dag);
        cout << "\nGeef de maand in :" << endl;
        getline(cin,maand);}
        sub->subscribeTo(QString::fromStdString("!corona>" + naam + ">").toUtf8());
        if( !send->isConnected() || !sub->isConnected() )
            {
                cerr << "NOT CONNECTED !!!" << endl;
            }
        nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("?corona>"+naam+">"+comando+">"+land+">"+dag+">"+maand).toUtf8());
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
    else if (ja == 2)
    {
        try
        {
            nzmqt::ZMQContext *context = nzmqt::createDefaultContext();
            nzmqt::ZMQSocket *sub = context->createSocket( nzmqt::ZMQSocket::TYP_SUB, context );
            nzmqt::ZMQSocket *send = context->createSocket( nzmqt::ZMQSocket::TYP_PUSH, context );
            sub->connectTo("tcp://benternet.pxl-ea-ict.be:24042");//"tcp://benternet.backup.pxl-ea-ict.be:24042""tcp://192.168.200.212:5554"
            send->connectTo("tcp://benternet.pxl-ea-ict.be:24041");//"tcp://benternet.backup.pxl-ea-ict.be:24041""tcp://192.168.200.212:5555"
            string naam;
            string aantal_landen;
            string comando;
            string land;
            string dag;
            string maand;
            string begindag;
            string beginmaand;
            string einddag;
            string eindmaand;
            string hallo;
            cout << "\nGeef eens een paar gegevens nu!" << endl;
            getline(cin,hallo);
            cout << "\nGeef je naam in : " << endl;
            getline(cin,naam);

            cout << "\nAls je voor meerdere landen kiest geef eens 1, anders geef eens 2: " << endl;
            cin >> aantal_landen;
            if (aantal_landen == "1")
                {
                string land1;
                string land2;
                string landen;
                string hallo2;
                cout << "\nGeef eens een paar gegevens nu!" << endl;
                getline(cin,hallo2);
                cout << "\ngeef land1 :"<< endl;
                getline(cin,land1);
                cout << "\ngeef land2 :"<< endl;
                getline(cin,land2);
                cout << "\nlanden zijn: "<< land1 << land2 << endl;

                cout << "\nDe commandos zijn:\n1: Voor besmettingen"
                        "\n2: Voor doden"
                        "\n3: Voor besmettingen, doden en het continent van het land\n4: Voor besmettingen, doden, het continent van het land\n   en het cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000"
                        "\n5: Voor besmettingen, doden, het continent van het land,\n   het cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000\n   en geoID van het land"
                        "\n6: Voor besmettingen, doden, het continent van het land,\n   het cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000,\n   geoID van het land en land grondgebied Code\n"
                        "\n7: Voor doden van bepaalde datums "
                        "\nGeef uw gekozen commando tussen 1 en 7 in:   "<< endl;
                getline(cin,comando);
                if (comando == "7"){
                    cout << "\nGeef de begindag in :" << endl;
                    getline(cin,begindag);
                    cout << "\nGeef de einddag in :" << endl;
                    getline(cin,einddag);
                    cout << "\nGeef de beginmaand in :" << endl;
                    getline(cin,beginmaand);
                    cout << "\nGeef de eindmaand in :" << endl;
                    getline(cin,eindmaand);
                    sub->subscribeTo(QString::fromStdString("!corona>" + naam + ">").toUtf8());
                    if( !send->isConnected() || !sub->isConnected() )
                        {
                            cerr << "NOT CONNECTED !!!" << endl;
                        }

                    nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("?corona>"+naam+">"+comando+">"+land+">"+">"+begindag+">"+einddag+">"+beginmaand+">"+eindmaand).toUtf8());
                    send->sendMessage(msg);
                    nzmqt::ZMQMessage * incoming = new nzmqt::ZMQMessage();
                    while( sub->isConnected() )
                    {
                       sub->receiveMessage(incoming,0);
                       QString response = QString(incoming->toByteArray());
                       cout << response.toStdString() <<endl;
                    }
                }
                else {cout << "\nGeef de dag in :" << endl;
                getline(cin,dag);
                cout << "\nGeef de maand in :" << endl;
                getline(cin,maand);}
                sub->subscribeTo(QString::fromStdString("!corona>" + naam + ">").toUtf8());
                if( !send->isConnected() || !sub->isConnected() )
                    {
                        cerr << "NOT CONNECTED !!!" << endl;
                    }
                nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("?corona>"+aantal_landen+">"+naam+">"+comando+">"+land1+">"+land2+">"+dag+">"+maand).toUtf8());//
                send->sendMessage(msg);
                nzmqt::ZMQMessage * incoming = new nzmqt::ZMQMessage();
                while( sub->isConnected() )
                {
                   sub->receiveMessage(incoming,0);
                   QString response = QString(incoming->toByteArray());
                   cout << response.toStdString() <<endl;
                }
                }

            cout << "\nGeef het land in (In het engels en begint met Groot letter) : " << endl;
            getline(cin,land);
            cout << "\nDe commandos zijn:\n1: Voor besmettingen"
                    "\n2: Voor doden"
                    "\n3: Voor besmettingen, doden en het continent van het land\n4: Voor besmettingen, doden, het continent van het land\n   en het cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000"
                    "\n5: Voor besmettingen, doden, het continent van het land,\n   het cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000\n   en geoID van het land"
                    "\n6: Voor besmettingen, doden, het continent van het land,\n   het cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000,\n   geoID van het land en land grondgebied Code\n"
                    "\n7: Voor doden van bepaalde datums "
                    "\nGeef uw gekozen commando tussen 1 en 7 in:   "<< endl;
            getline(cin,comando);
            if (comando == "7"){
                cout << "\nGeef de begindag in :" << endl;
                getline(cin,begindag);
                cout << "\nGeef de einddag in :" << endl;
                getline(cin,einddag);
                cout << "\nGeef de beginmaand in :" << endl;
                getline(cin,beginmaand);
                cout << "\nGeef de eindmaand in :" << endl;
                getline(cin,eindmaand);
                sub->subscribeTo(QString::fromStdString("!corona>" + naam + ">").toUtf8());
                if( !send->isConnected() || !sub->isConnected() )
                    {
                        cerr << "NOT CONNECTED !!!" << endl;
                    }
                nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("?corona>"+naam+">"+comando+">"+land+">"+begindag+">"+einddag+">"+beginmaand+">"+eindmaand).toUtf8());
                send->sendMessage(msg);
                nzmqt::ZMQMessage * incoming = new nzmqt::ZMQMessage();
                while( sub->isConnected() )
                {
                   sub->receiveMessage(incoming,0);
                   QString response = QString(incoming->toByteArray());
                   cout << response.toStdString() <<endl;
                }
            }
            else {cout << "\nGeef de dag in :" << endl;
            getline(cin,dag);
            cout << "\nGeef de maand in :" << endl;
            getline(cin,maand);}
            sub->subscribeTo(QString::fromStdString("!corona>" + naam + ">").toUtf8());
            if( !send->isConnected() || !sub->isConnected() )
                {
                    cerr << "NOT CONNECTED !!!" << endl;
                }
            nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("?corona>"+naam+">"+comando+">"+land+">"+dag+">"+maand).toUtf8());
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


    else if (ja != 1 && ja != 2)
    {
      cout << "Onbekende gegevens \nProbeer het eens nog een keer en geef eens of '1' of '2' in ..!" << endl;
//DebugBreak();
    }

  }
