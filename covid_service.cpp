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
#include <json.hpp>
using namespace nlohmann;
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
        sub->connectTo("tcp://benternet.pxl-ea-ict.be:24042");//"tcp://benternet.backup.pxl-ea-ict.be:24042""tcp://192.168.200.212:5554"
        send->connectTo("tcp://benternet.pxl-ea-ict.be:24041");//"tcp://benternet.backup.pxl-ea-ict.be:24041""tcp://192.168.200.212:5555"
        sub->subscribeTo("?corona>");
        cout << "Covid-19 Service is running ..." << endl;
        nzmqt::ZMQMessage * incoming = new nzmqt::ZMQMessage();
        string naam;
        string comando;
        string land;
        string dag;
        string maand;
        string begindag;
        string einddag;
        string beginmaand;
        string eindmaand;
        const int DAY=1 ;
        const int MONTH=2 ;
        const int CASES=4 ;
        const int DEATHS=5 ;
        const int LAND=6 ;
        const int GEOID=7;
        const int country_territory_Code=8;
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
               vector<vector<string>> data = parse2DCsvFile("C:\\COVID-19-geographic-disbtribution-worldwide.csv");
               if(parts[2]=="7")
               {
               int teller=0;
               for (vector<string> record : data)
                {
                   begindag=parts[4].toStdString();
                   einddag=parts[5].toStdString();
                   beginmaand=parts[6].toStdString();
                   eindmaand=parts[7].toStdString();
                   json j =json::array();
                   //json k =json::array();
                   if((teller >=0 && parts[2]=="7" && parts[3].toStdString()==record[LAND]) && ! ((stoi(record[MONTH]) < stoi(beginmaand)) ||
                           (stoi(record[MONTH]) > stoi(eindmaand)) ||
                           (stoi(record[MONTH]) == stoi(beginmaand) && stoi(record[DAY]) < stoi(begindag))  ||
                           (stoi(record[MONTH]) == stoi(eindmaand) && stoi(record[DAY]) > stoi(einddag))))

                   {
                     json i,m;
                     i["doden van: " + land +" op "+ record[DAY] +"/"+ record[MONTH] + " 2020"] = record[DEATHS];
                     //m["land"]=record[LAND];
                     j.push_back(i);
                     //k.push_back(m);
                     naam=parts[1].toStdString();
                     cout << naam << " heeft je service net gebruikt!"<< endl;
                     nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + j.dump()).toUtf8());
                     send->sendMessage(msg);
                   }
                   teller ++;
               }
               }

            for (vector<string> record : data)
                {
                   if(islower(parts[3].toStdString()[0]))
                   {
                   naam=parts[1].toStdString();
                   cout << naam << " heeft je service net gebruikt!"<< endl;
                   nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + naam + ", Sorry! .. Eerste letter van het land dat je ingegeven hebt is klein, het moet GROOT zijn! .. Probeer eens nog een keer! ").toUtf8());
                   send->sendMessage(msg);
                   break;
                   }
                   else if(parts[3].toStdString() != "Afghanistan" &&
                           parts[3].toStdString() != "Albania" &&
                           parts[3].toStdString() != "Algeria" &&
                           parts[3].toStdString() != "Andorra" &&
                           parts[3].toStdString() != "Angola" &&
                           parts[3].toStdString() != "Anguilla" &&
                           parts[3].toStdString() != "Antigua_and_Barbuda" &&
                           parts[3].toStdString() != "Argentina" &&
                           parts[3].toStdString() != "Armenia" &&
                           parts[3].toStdString() != "Aruba" &&
                           parts[3].toStdString() != "Australia" &&
                           parts[3].toStdString() != "Austria" &&
                           parts[3].toStdString() != "Azerbaijan" &&
                           parts[3].toStdString() != "Bahamas" &&
                           parts[3].toStdString() != "Bahrain" &&
                           parts[3].toStdString() != "Bangladesh" &&
                           parts[3].toStdString() != "Barbados" &&
                           parts[3].toStdString() != "Belarus" &&
                           parts[3].toStdString() != "Belgium" &&
                           parts[3].toStdString() != "Belize" &&
                           parts[3].toStdString() != "Benin" &&
                           parts[3].toStdString() != "Bermuda" &&
                           parts[3].toStdString() != "Bhutan" &&
                           parts[3].toStdString() != "Bolivia" &&
                           parts[3].toStdString() != "Bonaire, Saint Eustatius and Saba" &&
                           parts[3].toStdString() != "Bosnia_and_Herzegovina" &&
                           parts[3].toStdString() != "Botswana" &&
                           parts[3].toStdString() != "Brazil" &&
                           parts[3].toStdString() != "British_Virgin_Islands" &&
                           parts[3].toStdString() != "Brunei_Darussalam" &&
                           parts[3].toStdString() != "Bulgaria" &&
                           parts[3].toStdString() != "Burkina_Faso" &&
                           parts[3].toStdString() != "Burundi" &&
                           parts[3].toStdString() != "Cambodia" &&
                           parts[3].toStdString() != "Cameroon" &&
                           parts[3].toStdString() != "Canada" &&
                           parts[3].toStdString() != "Cape_Verde" &&
                           parts[3].toStdString() != "Cases_on_an_international_conveyance_Japan" &&
                           parts[3].toStdString() != "Cayman_Islands" &&
                           parts[3].toStdString() != "Central_African_Republic" &&
                           parts[3].toStdString() != "Chad" &&
                           parts[3].toStdString() != "Chile" &&
                           parts[3].toStdString() != "China" &&
                           parts[3].toStdString() != "Colombia" &&
                           parts[3].toStdString() != "Comoros" &&
                           parts[3].toStdString() != "Congo" &&
                           parts[3].toStdString() != "Costa_Rica" &&
                           parts[3].toStdString() != "Cote_dIvoire" &&
                           parts[3].toStdString() != "Croatia" &&
                           parts[3].toStdString() != "Cuba" &&
                           parts[3].toStdString() != "Curaçao" && //Curaçao//CuraÃ§ao
                           parts[3].toStdString() != "Cyprus" &&
                           parts[3].toStdString() != "Czechia" &&
                           parts[3].toStdString() != "Democratic_Republic_of_the_Congo" &&
                           parts[3].toStdString() != "Denmark" &&
                           parts[3].toStdString() != "Djibouti" &&
                           parts[3].toStdString() != "Dominica" &&
                           parts[3].toStdString() != "Dominican_Republic" &&
                           parts[3].toStdString() != "Ecuador" &&
                           parts[3].toStdString() != "Egypt" &&
                           parts[3].toStdString() != "El_Salvador" &&
                           parts[3].toStdString() != "Equatorial_Guinea" &&
                           parts[3].toStdString() != "Eritrea" &&
                           parts[3].toStdString() != "Estonia" &&
                           parts[3].toStdString() != "Eswatini" &&
                           parts[3].toStdString() != "Ethiopia" &&
                           parts[3].toStdString() != "Falkland_Islands_(Malvinas)" &&
                           parts[3].toStdString() != "Faroe_Islands" &&
                           parts[3].toStdString() != "Fiji" &&
                           parts[3].toStdString() != "Finland" &&
                           parts[3].toStdString() != "France" &&
                           parts[3].toStdString() != "French_Polynesia" &&
                           parts[3].toStdString() != "Gabon" &&
                           parts[3].toStdString() != "Gambia" &&
                           parts[3].toStdString() != "Georgia" &&
                           parts[3].toStdString() != "Germany" &&
                           parts[3].toStdString() != "Ghana" &&
                           parts[3].toStdString() != "Gibraltar" &&
                           parts[3].toStdString() != "Greece" &&
                           parts[3].toStdString() != "Greenland" &&
                           parts[3].toStdString() != "Grenada" &&
                           parts[3].toStdString() != "Guam" &&
                           parts[3].toStdString() != "Guatemala" &&
                           parts[3].toStdString() != "Guernsey" &&
                           parts[3].toStdString() != "Guinea" &&
                           parts[3].toStdString() != "Guinea_Bissau" &&
                           parts[3].toStdString() != "Guyana" &&
                           parts[3].toStdString() != "Haiti" &&
                           parts[3].toStdString() != "Holy_See" &&
                           parts[3].toStdString() != "Honduras" &&
                           parts[3].toStdString() != "Hungary" &&
                           parts[3].toStdString() != "Iceland" &&
                           parts[3].toStdString() != "India" &&
                           parts[3].toStdString() != "Indonesia" &&
                           parts[3].toStdString() != "Iran" &&
                           parts[3].toStdString() != "Iraq" &&
                           parts[3].toStdString() != "Ireland" &&
                           parts[3].toStdString() != "Isle_of_Man" &&
                           parts[3].toStdString() != "Israel" &&
                           parts[3].toStdString() != "Italy" &&
                           parts[3].toStdString() != "Jamaica" &&
                           parts[3].toStdString() != "Japan" &&
                           parts[3].toStdString() != "Jersey" &&
                           parts[3].toStdString() != "Jordan" &&
                           parts[3].toStdString() != "Kazakhstan" &&
                           parts[3].toStdString() != "Kenya" &&
                           parts[3].toStdString() != "Kosovo" &&
                           parts[3].toStdString() != "Kuwait" &&
                           parts[3].toStdString() != "Kyrgyzstan" &&
                           parts[3].toStdString() != "Laos" &&
                           parts[3].toStdString() != "Latvia" &&
                           parts[3].toStdString() != "Lebanon" &&
                           parts[3].toStdString() != "Lesotho" &&
                           parts[3].toStdString() != "Liberia" &&
                           parts[3].toStdString() != "Libya" &&
                           parts[3].toStdString() != "Liechtenstein" &&
                           parts[3].toStdString() != "Lithuania" &&
                           parts[3].toStdString() != "Luxembourg" &&
                           parts[3].toStdString() != "Madagascar" &&
                           parts[3].toStdString() != "Malawi" &&
                           parts[3].toStdString() != "Malaysia" &&
                           parts[3].toStdString() != "Maldives" &&
                           parts[3].toStdString() != "Mali" &&
                           parts[3].toStdString() != "Malta" &&
                           parts[3].toStdString() != "Marshall_Islands" &&
                           parts[3].toStdString() != "Mauritania" &&
                           parts[3].toStdString() != "Mauritius" &&
                           parts[3].toStdString() != "Mexico" &&
                           parts[3].toStdString() != "Moldova" &&
                           parts[3].toStdString() != "Monaco" &&
                           parts[3].toStdString() != "Mongolia" &&
                           parts[3].toStdString() != "Montenegro" &&
                           parts[3].toStdString() != "Montserrat" &&
                           parts[3].toStdString() != "Morocco" &&
                           parts[3].toStdString() != "Mozambique" &&
                           parts[3].toStdString() != "Myanmar" &&
                           parts[3].toStdString() != "Namibia" &&
                           parts[3].toStdString() != "Nepal" &&
                           parts[3].toStdString() != "Netherlands" &&
                           parts[3].toStdString() != "New_Caledonia" &&
                           parts[3].toStdString() != "New_Zealand" &&
                           parts[3].toStdString() != "Nicaragua" &&
                           parts[3].toStdString() != "Niger" &&
                           parts[3].toStdString() != "Nigeria" &&
                           parts[3].toStdString() != "North_Macedonia" &&
                           parts[3].toStdString() != "Northern_Mariana_Islands" &&
                           parts[3].toStdString() != "Norway" &&
                           parts[3].toStdString() != "Oman" &&
                           parts[3].toStdString() != "Pakistan" &&
                           parts[3].toStdString() != "Palestine" &&
                           parts[3].toStdString() != "Panama" &&
                           parts[3].toStdString() != "Papua_New_Guinea" &&
                           parts[3].toStdString() != "Paraguay" &&
                           parts[3].toStdString() != "Peru" &&
                           parts[3].toStdString() != "Philippines" &&
                           parts[3].toStdString() != "Poland" &&
                           parts[3].toStdString() != "Portugal" &&
                           parts[3].toStdString() != "Puerto_Rico" &&
                           parts[3].toStdString() != "Qatar" &&
                           parts[3].toStdString() != "Romania" &&
                           parts[3].toStdString() != "Russia" &&
                           parts[3].toStdString() != "Rwanda" &&
                           parts[3].toStdString() != "Saint_Kitts_and_Nevis" &&
                           parts[3].toStdString() != "Saint_Lucia" &&
                           parts[3].toStdString() != "Saint_Vincent_and_the_Grenadines" &&
                           parts[3].toStdString() != "San_Marino" &&
                           parts[3].toStdString() != "Sao_Tome_and_Principe" &&
                           parts[3].toStdString() != "Saudi_Arabia" &&
                           parts[3].toStdString() != "Senegal" &&
                           parts[3].toStdString() != "Serbia" &&
                           parts[3].toStdString() != "Seychelles" &&
                           parts[3].toStdString() != "Sierra_Leone" &&
                           parts[3].toStdString() != "Singapore" &&
                           parts[3].toStdString() != "Sint_Maarten" &&
                           parts[3].toStdString() != "Slovakia" &&
                           parts[3].toStdString() != "Slovenia" &&
                           parts[3].toStdString() != "Solomon_Islands" &&
                           parts[3].toStdString() != "Somalia" &&
                           parts[3].toStdString() != "South_Africa" &&
                           parts[3].toStdString() != "South_Korea" &&
                           parts[3].toStdString() != "South_Sudan" &&
                           parts[3].toStdString() != "Spain" &&
                           parts[3].toStdString() != "Sri_Lanka" &&
                           parts[3].toStdString() != "Sudan" &&
                           parts[3].toStdString() != "Suriname" &&
                           parts[3].toStdString() != "Sweden" &&
                           parts[3].toStdString() != "Switzerland" &&
                           parts[3].toStdString() != "Syria" &&
                           parts[3].toStdString() != "Taiwan" &&
                           parts[3].toStdString() != "Tajikistan" &&
                           parts[3].toStdString() != "Thailand" &&
                           parts[3].toStdString() != "Timor_Leste" &&
                           parts[3].toStdString() != "Togo" &&
                           parts[3].toStdString() != "Trinidad_and_Tobago" &&
                           parts[3].toStdString() != "Tunisia" &&
                           parts[3].toStdString() != "Turkey" &&
                           parts[3].toStdString() != "Turks_and_Caicos_islands" &&
                           parts[3].toStdString() != "Uganda" &&
                           parts[3].toStdString() != "Ukraine" &&
                           parts[3].toStdString() != "United_Arab_Emirates" &&
                           parts[3].toStdString() != "United_Kingdom" &&
                           parts[3].toStdString() != "United_Republic_of_Tanzania" &&
                           parts[3].toStdString() != "United_States_of_America" &&
                           parts[3].toStdString() != "United_States_Virgin_Islands" &&
                           parts[3].toStdString() != "Uruguay" &&
                           parts[3].toStdString() != "Uzbekistan" &&
                           parts[3].toStdString() != "Vanuatu" &&
                           parts[3].toStdString() != "Venezuela" &&
                           parts[3].toStdString() != "Vietnam" &&
                           parts[3].toStdString() != "Wallis_and_Futuna" &&
                           parts[3].toStdString() != "Western_Sahara" &&
                           parts[3].toStdString() != "Yemen" &&
                           parts[3].toStdString() != "Zambia" &&
                           parts[3].toStdString() != "Zimbabwe")// ||
                   {
                   naam=parts[1].toStdString();
                   cout << naam << " heeft je service net gebruikt!"<< endl;
                   nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + naam + ", Sorry! ..  Je hebt de naam van het land fout geschreven,\nOF het land bestaat niet in de aarde!...\nProbeer eens nog een keer... ").toUtf8());
                   send->sendMessage(msg);
                   break;
                   }

                   else if(parts[2]!="1" && parts[2]!="2" && parts[2]!="3" && parts[2]!="4" && parts[2]!="5" && parts[2]!="6"&& parts[2]!="7")
                   {
                   naam=parts[1].toStdString();
                   cout << naam << " heeft je service net gebruikt!"<< endl;
                   nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + naam + ", Sorry! .. Het commando bestaat niet!.. Het moet tussen 1 en 7 zijn! ").toUtf8());
                   send->sendMessage(msg);
                   break;
                   }


                    else if(parts[2]=="1" && record[LAND]==parts[3].toStdString() && record[DAY]==parts[4].toStdString() && record[MONTH]==parts[5].toStdString() )
                    {
                    naam=parts[1].toStdString();
                    cout << naam << " heeft je service net gebruikt!"<< endl;
                    nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "\nHallo " + naam + "\n"+"Aantal besmettingen " + " van " + land + " op " + dag + "/" + maand + "/" + "2020" + ": " + record[CASES]).toUtf8());
                    send->sendMessage(msg);
                    break;
                    }

                    else if(parts[2]=="2" && record[LAND]==parts[3].toStdString() && record[DAY]==parts[4].toStdString() && record[MONTH]==parts[5].toStdString() )
                    {
                    naam=parts[1].toStdString();
                    cout << naam << " heeft je service net gebruikt!"<< endl;
                    nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "\nHallo " + naam + ", aantal doden "  + " van " + land + " op " + dag + "/" + maand + "/" + "2020" + ": " + record[DEATHS]).toUtf8());
                    send->sendMessage(msg);
                    break;
                    }

                    else if(parts[2]=="3" && record[LAND]==parts[3].toStdString() && record[DAY]==parts[4].toStdString() && record[MONTH]==parts[5].toStdString() )
                    {
                    naam=parts[1].toStdString();
                    cout << naam << " heeft je service net gebruikt!"<< endl;
                    nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "\nHallo " + naam + "\n"+"Aantal besmettingen " + "van " + land +  " op " + dag + "/" + maand + "/" + "2020" + ": " + record[CASES] +"\n"+"Aantal doden: " + record[DEATHS] +  "\nContinent van "+ land +": "  + record[CONTINENT]).toUtf8());
                    send->sendMessage(msg);
                    break;
                    }

                    else if(parts[2]=="4" && record[LAND]==parts[3].toStdString() && record[DAY]==parts[4].toStdString() && record[MONTH]==parts[5].toStdString() )
                    {
                    naam=parts[1].toStdString();
                    cout << naam << " heeft je service net gebruikt!"<< endl;
                    nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "\nHallo " + naam + "\n"+"Aantal besmettingen " + "van " + land +  " op " + dag + "/" + maand + "/" + "2020" + ": " + record[CASES] +"\n"+"Aantal doden: " + record[DEATHS] +  "\nContinent van "+ land +": "  + record[CONTINENT] + "\nCumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000: " + record[CUMULATIVE]).toUtf8());
                    send->sendMessage(msg);
                    break;
                    }

                    else if(parts[2]=="5" && record[LAND]==parts[3].toStdString() && record[DAY]==parts[4].toStdString() && record[MONTH]==parts[5].toStdString() )
                    {
                    naam=parts[1].toStdString();
                    cout << naam << " heeft je service net gebruikt!"<< endl;
                    nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "\nHallo " + naam + "\n"+"Aantal besmettingen " + "van " + land +  " op " + dag + "/" + maand + "/" + "2020" + ": " + record[CASES] +"\n"+"Aantal doden: " + record[DEATHS] +  "\nContinent van "+ land +": "  + record[CONTINENT] + "\nCumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000: " + record[CUMULATIVE] + "\ngeoID van " + land + ": " + record[GEOID] ).toUtf8());
                    send->sendMessage(msg);
                    break;
                    }

                    else if(parts[2]=="6" && record[LAND]==parts[3].toStdString() && record[DAY]==parts[4].toStdString() && record[MONTH]==parts[5].toStdString() )
                    {
                    naam=parts[1].toStdString();
                    cout << naam << " heeft je service net gebruikt!"<< endl;
                    nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "\nHallo " + naam + "\n"+"Aantal besmettingen " + "van " + land +  " op " + dag + "/" + maand + "/" + "2020" + ": " + record[CASES] +"\n"+"Aantal doden: " + record[DEATHS] +  "\nContinent van "+ land +": "  + record[CONTINENT] + "\nCumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000: " + record[CUMULATIVE] + "\ngeoID van " + land + ": " + record[GEOID] +  "\nLand grondgebied Code: " + record[country_territory_Code]).toUtf8());
                    send->sendMessage(msg);
                    break;
                    }

               }
           }
        }
    }

    catch( nzmqt::ZMQException &ex )
    {
        std::cerr << "Catched an exception : " << ex.what();
    }


    return 0;
}
