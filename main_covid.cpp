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
#include <set>
#include <iterator>
#include <algorithm>
using namespace nlohmann;
using namespace std;
int aantal_landen = 1;
int aantal_dagen = 1;
string message;
string message2;
bool besmettingen_toegevoegd=false;
bool doden_toegevoegd=false;
void read_record();
void * context; //Global context, because you only need one !
class CSVWriter
{
    std::string fileName;
    std::string delimeter;
    int linesCount;
public:
    CSVWriter(std::string filename, std::string delm = ",") :
            fileName(filename), delimeter(delm), linesCount(0)
    {}
    /*
     * Member function to store a range as comma seperated value
     */
    template<typename T>
    void addDatainRow(T first, T last);
};
template<typename T>
void CSVWriter::addDatainRow(T first, T last)
{
    std::fstream file;
    // Open the file in truncate mode if first line else in Append Mode
    file.open(fileName, std::ios::out | (linesCount ? std::ios::app : std::ios::trunc));
    // Iterate over the range and add each lement to file seperated by delimeter.
    for (; first != last; )
    {
        file << *first;
        if (++first != last)
            file << delimeter;
    }
    file << "\n";
    linesCount++;
    // Close the file
    file.close();
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

int main() {
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
        string cases;
        string deaths;
        const int DAY=1 ;
        const int MONTH=2 ;
        const int CASES=4 ;
        const int DEATHS=5 ;
        const int LAND=6 ;
        const int GEOID=7;
        const int YEAR=3;
        const int country_territory_Code=8;
        const int CONTINENT=10 ;
        const int CUMULATIVE=11 ;

        while( sub->isConnected() )
        {
           sub->receiveMessage(incoming,0);
           QString response = QString(incoming->toByteArray());
           aantal_dagen = 1;
           aantal_landen = 1;
           for (int i=0 ;i < response.size();i++)
           {
               if(response.at(i) == QChar(','))
               {
                   aantal_dagen++;
               }

           }
//           for (int i=0 ;i < response.size();i++)
//           {
//               if(response.at(i) == QChar(','))
//               {
//                   aantal_landen++;
//               }

//           }

           string landen [aantal_landen];
           bool errors[aantal_landen];
           string dagen [aantal_dagen];
           bool errors_dagen[aantal_dagen];

           QStringList parts;
           QStringList lijstlanden;
           QStringList lijstdagen;
           parts.clear();
           lijstlanden.clear();
           lijstdagen.clear();
           message="";

           parts = response.split(">");
           if (parts[0]=="?corona")
           {
               comando=parts[2].toStdString();
               land=parts[3].toStdString();
               //dag=parts[4].toStdString();
               maand=parts[5].toStdString();
               //cases=parts[6].toStdString();
               //deaths=parts[7].toStdString();
               //lijstlanden = parts[3].split(",");
               lijstdagen = parts[4].split(",");
//               for(int i =0 ; i<aantal_landen;i++)
//               {
//                   landen[i] = lijstlanden[i].toStdString();
//                   errors[i]= true;
//               }

               for(int i =0 ; i<aantal_dagen;i++)
               {
                   dagen[i] = lijstdagen[i].toStdString();
                   errors_dagen[i]= true;
               }

               if (parts[2]=="8")//||parts[2]=="9"
               {
                   land=landen[0];
                   vector<vector<string>> data = parse2DCsvFile("C:\\COVID-19-geographic-disbtribution-worldwide.csv");

                    CSVWriter writer("C:\\COVID-19-geographic-disbtribution-worldwide.csv");
                    for (vector<string> record : data){
                        if (record[LAND]==land && record[DAY]==dag && record[MONTH]==maand && record[YEAR]=="2020")//overschrijven als het wel bestaat
                        {
                            std::vector<std::string> dataList_2 = { record[0], record[1], record[2],record[3],cases,record[5],record[6],record[7],record[8],record[9],record[10],record[11] };
                            writer.addDatainRow(dataList_2.begin(), dataList_2.end());
                            besmettingen_toegevoegd=true;
                        }
                        else{ //oude data terug toevoegen
                            std::vector<std::string> dataList_2 = { record[0], record[1], record[2],record[3],record[4],record[5],record[6],record[7],record[8],record[9],record[10],record[11] };
                            writer.addDatainRow(dataList_2.begin(), dataList_2.end());
                        }
                    }
                    if (besmettingen_toegevoegd==false){ //nieuwe data toevoegen als dit niet overschrijven is
                       std::vector<std::string> dataList_1 = { "", dag, maand,"2020",cases,"",land,"","","","","" };
                       writer.addDatainRow(dataList_1.begin(), dataList_1.end());
                    }
                    else{ //resetten
                        besmettingen_toegevoegd=false;
                    }
               }

               if (parts[2]=="9")
               {
                   land=landen[0];
                   vector<vector<string>> data = parse2DCsvFile("C:\\COVID-19-geographic-disbtribution-worldwide.csv");

                    CSVWriter writer("C:\\COVID-19-geographic-disbtribution-worldwide.csv");
                    for (vector<string> record : data){
                        if (record[LAND]==land && record[DAY]==dag && record[MONTH]==maand && record[YEAR]=="2020")//overschrijven als het wel bestaat
                        {
                            std::vector<std::string> dataList_2 = { record[0], record[1], record[2],record[3],record[4],deaths,record[6],record[7],record[8],record[9],record[10],record[11] };
                            writer.addDatainRow(dataList_2.begin(), dataList_2.end());
                            doden_toegevoegd=true;
                        }
                        else{ //oude data terug toevoegen
                            std::vector<std::string> dataList_2 = { record[0], record[1], record[2],record[3],record[4],record[5],record[6],record[7],record[8],record[9],record[10],record[11] };
                            writer.addDatainRow(dataList_2.begin(), dataList_2.end());
                        }
                    }
                    if (doden_toegevoegd==false){ //nieuwe data toevoegen als dit niet overschrijven is
                       std::vector<std::string> dataList_1 = { "", dag, maand,"2020","",deaths,land,"","","","","" };
                       writer.addDatainRow(dataList_1.begin(), dataList_1.end());
                    }
                    else{ //resetten
                        doden_toegevoegd=false;
                    }
               }
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
                   if(teller >=0 && parts[2]=="7"  && ! ((stoi(record[MONTH]) < stoi(beginmaand)) ||
                           (stoi(record[MONTH]) > stoi(eindmaand)) ||
                           (stoi(record[MONTH]) == stoi(beginmaand) && stoi(record[DAY]) < stoi(begindag))  ||
                           (stoi(record[MONTH]) == stoi(eindmaand) && stoi(record[DAY]) > stoi(einddag))))

                   {
                       for(int i=0;i<aantal_landen;i++)
                       {
                           if (record[LAND] == landen[i])
                           {
                               json l,m;
                               l["doden van: " + landen[i] +" op "+ record[DAY] +"/"+ record[MONTH] + " 2020"] = record[DEATHS];
                               //m["land"]=record[LAND];
                               j.push_back(l);
                               errors[i]=false;
                               naam=parts[1].toStdString();

                               nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + j.dump()).toUtf8());
                               send->sendMessage(msg);
                           }
                       }
                       //
                     //k.push_back(m);

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
                   /*else if(parts[3].toStdString() != "Afghanistan" &&
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
                   }*/

                   else if(parts[2]!="1" && parts[2]!="2" && parts[2]!="3" && parts[2]!="4" && parts[2]!="5" && parts[2]!="6"&& parts[2]!="7"&& parts[2]!="8"&& parts[2]!="9")
                   {
                   naam=parts[1].toStdString();
                   cout << naam << " heeft je service net gebruikt!"<< endl;
                   nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + naam + ", Sorry! .. Het commando bestaat niet!.. Het moet tussen 1 en 7 zijn! ").toUtf8());
                   send->sendMessage(msg);
                   break;
                   }

//Commando 1
                   else if(parts[2]=="1" && record[LAND]==parts[3].toStdString() && record[MONTH]==parts[5].toStdString() )
                   {

                           json j =json::array();
                           //json k =json::array();

                               for(int i=0;i<aantal_dagen;i++)
                               {
                                   if (record[DAY] == dagen[i])
                                   {
                                       json l,m;
                                       l["besmettingen van: " + land +" op "+ dagen[i] +"/"+ record[MONTH] + " 2020"] = record[CASES];
                                       //m["land"]=record[LAND];
                                       j.push_back(l);
                                       message += j.dump();
                                       errors[i]=false;
                                       naam=parts[1].toStdString();
//                                       nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + j.dump()).toUtf8());
//                                       send->sendMessage(msg);
                                   }




                               }
                               //
                             //k.push_back(m);
                   }

                   //Commando 2
                                      else if(parts[2]=="2" && record[LAND]==parts[3].toStdString() && record[MONTH]==parts[5].toStdString() )
                                      {

                                              json j =json::array();
                                              //json k =json::array();

                                                  for(int i=0;i<aantal_dagen;i++)
                                                  {
                                                      if (record[DAY] == dagen[i])
                                                      {
                                                          json l,m;
                                                          l["doden van: " + land +" op "+ dagen[i] +"/"+ record[MONTH] + " 2020"] = record[DEATHS];
                                                          //m["land"]=record[LAND];
                                                          j.push_back(l);
                                                          message += j.dump();
                                                          errors[i]=false;
//                                                          naam=parts[1].toStdString();
//                                                          nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + j.dump()).toUtf8());
//                                                          send->sendMessage(msg);
                                                      }




                                                  }
                                                  //
                                                //k.push_back(m);
                                      }

//Commando 3

                   else if(parts[2]=="3" && record[LAND]==parts[3].toStdString() && record[MONTH]==parts[5].toStdString() )
                   {

                           json j =json::array();
                           json k =json::array();
                           json c =json::array();

                               for(int i=0;i<aantal_dagen;i++)
                               {
                                   if (record[DAY] == dagen[i])
                                   {
                                       json l,m,n;
                                       l["besmettingen van: " + land +" op "+ dagen[i] +"/"+ record[MONTH] + " 2020"] = record[CASES];
                                       m["doden van : "+ land]=record[DEATHS];
                                       n["continent"]=record[CONTINENT];
                                       j.push_back(l);
                                       j.push_back(m);
                                       j.push_back(n);
                                        message += j.dump();
                                       naam=parts[1].toStdString();
//                                     nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + message).toUtf8());
//                                     send->sendMessage(msg);

                                   }
                               }
                   }
//Commando 4

else if(parts[2]=="4" && record[LAND]==parts[3].toStdString() && record[MONTH]==parts[5].toStdString() )
 {
    json j =json::array();
    json k =json::array();
    json c =json::array();
    json d =json::array();

  for(int i=0;i<aantal_dagen;i++)
     {
        if (record[DAY] == dagen[i])
            {
                json l,m,n,o;
                l["besmettingen van: " + land +" op "+ dagen[i] +"/"+ record[MONTH] + " 2020"] = record[CASES];
                m["doden van : "+ land]=record[DEATHS];
                n["continent"]=record[CONTINENT];
                o["cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000"]=record[CUMULATIVE];
                j.push_back(l);
                j.push_back(m);
                j.push_back(n);
                j.push_back(o);
                message += j.dump();
                naam=parts[1].toStdString();
//              nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + message).toUtf8());
//              send->sendMessage(msg);

            }
   }
 }

                   //Commando 5

                   else if(parts[2]=="5" && record[LAND]==parts[3].toStdString() && record[MONTH]==parts[5].toStdString() )
                    {
                       json j =json::array();
                       json k =json::array();
                       json c =json::array();
                       json d =json::array();
                       json e =json::array();

                     for(int i=0;i<aantal_dagen;i++)
                        {
                           if (record[DAY] == dagen[i])
                               {
                                   json l,m,n,o,p;
                                   l["besmettingen van: " + land +" op "+ dagen[i] +"/"+ record[MONTH] + " 2020"] = record[CASES];
                                   m["doden van : "+ land]=record[DEATHS];
                                   n["continent"]=record[CONTINENT];
                                   o["cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000"]=record[CUMULATIVE];
                                   p["geoID van: "+ land]=record[GEOID];
                                   j.push_back(l);
                                   j.push_back(m);
                                   j.push_back(n);
                                   j.push_back(o);
                                   j.push_back(p);
                                   message += j.dump();
                                   naam=parts[1].toStdString();
                   //              nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + message).toUtf8());
                   //              send->sendMessage(msg);

                               }
                      }
                    }

                   //Commando 6

                   else if(parts[2]=="6" && record[LAND]==parts[3].toStdString() && record[MONTH]==parts[5].toStdString() )
                    {
                       json j =json::array();
                       json k =json::array();
                       json c =json::array();
                       json d =json::array();
                       json e =json::array();
                       json f =json::array();

                     for(int i=0;i<aantal_dagen;i++)
                        {
                           if (record[DAY] == dagen[i])
                               {
                                   json l,m,n,o,p,q;
                                   l["besmettingen van: " + land +" op "+ dagen[i] +"/"+ record[MONTH] + " 2020"] = record[CASES];
                                   m["doden van : "+ land]=record[DEATHS];
                                   n["continent"]=record[CONTINENT];
                                   o["cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000"]=record[CUMULATIVE];
                                   p["geoID van: "+ land]=record[country_territory_Code];
                                   q["het land grondgebied Code van: "+ land]=record[GEOID];
                                   j.push_back(l);
                                   j.push_back(m);
                                   j.push_back(n);
                                   j.push_back(o);
                                   j.push_back(p);
                                   j.push_back(q);
                                   message += j.dump();
                                   naam=parts[1].toStdString();
                   //              nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "Hallo " + message).toUtf8());
                   //              send->sendMessage(msg);

                               }
                      }
                    }

//                    else if(parts[2]=="1" && record[LAND]==parts[3].toStdString() && record[MONTH]==parts[5].toStdString() )
//                    {
//                        for(int i=0;i<aantal_dagen;i++)
//                        {
//                            if (record[DAY] == dagen[i])
//                            {
//                                message += "Het aantal besmettingen in " + dagen[i] + " is " ;
//                                message += record[CASES];
//                                message += "\n\r";
//                                errors[i]=false;
//                            }
//                        }
//                    }
//Commando 2
                    else if(parts[2]=="2" && record[DAY]==parts[4].toStdString() && record[MONTH]==parts[5].toStdString() )
                    {
                       for(int i=0;i<aantal_landen;i++)
                       {
                           if (record[LAND] == landen[i])
                           {
                               message += "Het aantal doden in " + landen[i] + " is " ;
                               message += record[DEATHS];
                               message += "\n\r";
                               errors[i]=false;
                           }
                       }
                    }
//Commando 3
                    else if(parts[2]=="3" && record[DAY]==parts[4].toStdString() && record[MONTH]==parts[5].toStdString() )
                    {
                       for(int i=0;i<aantal_landen;i++)
                       {
                           if (record[LAND] == landen[i])
                           {
                               message += "Het aantal besmettingen in " + landen[i] + " is " ;
                               message += record[CASES];
                               message += " Het aantal doden is " ;
                               message += record[DEATHS];
                               message += " Het continent van " + landen[i] + " is " ;
                               message += record[CONTINENT];
                               message += "\n\r";
                               errors[i]=false;
                           }
                       }
                    }
//Commando 4
                    else if(parts[2]=="4" && record[DAY]==parts[4].toStdString() && record[MONTH]==parts[5].toStdString() )
                    {
                    for(int i=0;i<aantal_landen;i++)
                    {
                        if (record[LAND] == landen[i])
                        {
                            message += "Het aantal besmettingen in " + landen[i] + " is " ;
                            message += record[CASES];
                            message += " Het aantal doden is " ;
                            message += record[DEATHS];
                            message += " Het continent van " + landen[i] + " is " ;
                            message += record[CONTINENT];
                            message += " Het cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000 is ";
                            message += record[CUMULATIVE];
                            message += "\n\r";
                            errors[i]=false;
                        }
                    }
                    }
//Commando 5
                    else if(parts[2]=="5" && record[DAY]==parts[4].toStdString() && record[MONTH]==parts[5].toStdString() )
                    {
                       for(int i=0;i<aantal_landen;i++)
                       {
                           if (record[LAND] == landen[i])
                           {
                               message += "Het aantal besmettingen in " + landen[i] + " is " ;
                               message += record[CASES];
                               message += " Het aantal doden is " ;
                               message += record[DEATHS];
                               message += " Het continent van " + landen[i] + " is " ;
                               message += record[CONTINENT];
                               message += " Het cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000 is ";
                               message += record[CUMULATIVE];
                               message += " Het geoID is ";
                               message += record[country_territory_Code];
                               message += "\n\r";
                               errors[i]=false;
                           }
                       }
                    }
//Commando 6
                    else if(parts[2]=="6" && record[DAY]==parts[4].toStdString() && record[MONTH]==parts[5].toStdString() )
                    {
                       for(int i=0;i<aantal_landen;i++)
                       {
                           if (record[LAND] == landen[i])
                           {
                               message += "Het aantal besmettingen in " + landen[i] + " is " ;
                               message += record[CASES];
                               message += " Het aantal doden is " ;
                               message += record[DEATHS];
                               message += " Het continent van " + landen[i] + " is " ;
                               message += record[CONTINENT];
                               message += " Het cumulatief aantal voor 14 dagen Covid-19 gevallen per 100.000 is ";
                               message += record[CUMULATIVE];
                               message += " Het geoID is ";
                               message += record[country_territory_Code];
                               message += " Het land grondgebied Code is ";
                               message += record[GEOID];
                               message += "\n\r";
                               errors[i]=false;
                           }
                       }
                    }

               }
                if (comando=="8"){
                    for(int i=0;i<aantal_landen;i++)
                    {
                        cout<<"record " <<to_string(i+1)<< " toegevoegd" <<endl;
                    }
                    naam=parts[1].toStdString();
                    cout << naam << " heeft je service net gebruikt!"<< endl;
                    nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "\nHallo " + naam +"\n\r"+ "het commando is uitgevoerd").toUtf8());
                    send->sendMessage(msg);
                }
                else if (comando=="9"){
                    for(int i=0;i<aantal_landen;i++)
                    {
                        cout<<"record " <<to_string(i+1)<< " toegevoegd" <<endl;
                    }
                    naam=parts[1].toStdString();
                    cout << naam << " heeft je service net gebruikt!"<< endl;
                    nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "\nHallo " + naam +"\n\r"+ "het commando is uitgevoerd").toUtf8());
                    send->sendMessage(msg);
                }
                else if(comando=="7"){
                    ;
                }
                else
                {
//                for(int i =0 ; i<aantal_landen;i++)
//                {
//                    if(errors[i]==true)
//                    {
//                       message+= "Er zijn geen record gevonden voor " + landen[i] + "\n\r";
//                    }
//                }
                naam=parts[1].toStdString();
               cout << naam << " heeft je service net gebruikt!"<< endl;
                nzmqt::ZMQMessage msg = nzmqt::ZMQMessage(QString::fromStdString("!corona>" + naam + ">" + "\nHallo " + naam +"\n\r"+ message).toUtf8());
                send->sendMessage(msg);
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
