#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

//ex3

class Time{
public:
    Time(size_t hours=0, size_t minutes=0, size_t seconds=0);
    Time(const std::string &time);
    void setH(size_t hours) {h = hours;};
    void setM(size_t minutes) {m = minutes;};
    void setS(size_t seconds) {s = seconds;};
    inline size_t getH() const {return h;};
    size_t getM() const {return m;};
    size_t getS() const {return s;};
    string getStr() const;
    Time operator+(const Time& t) const;
    Time operator-(const Time& t) const;
private:
    size_t h,m,s;
};

Time::Time(size_t hours, size_t minutes, size_t seconds) {
    h = hours;
    m = minutes;
    s = seconds;
}

Time::Time(const std::string &time) {
    stringstream ss(time);
    char separator;
    ss >> h >> separator >> m >> separator >> s;
}

string Time::getStr() const {
    stringstream ss;
    ss << setw(2) << setfill('0') << h << ':' << setw(2) << setfill('0') << m << ':' << setw(2) << setfill('0') << s;
    return ss.str();
}

Time Time::operator+(const Time &t) const {
    size_t resultH, resultM, resultS;
    resultS = (s + t.getS())%60;
    resultM = (m + t.getM() + (s + t.getS())/60) %60;
    resultH = (h + t.getH() + (m + t.getM() + (s + t.getS())/60)/60) %24;
    return Time(resultH,resultM,resultS);
}

Time Time::operator-(const Time &t) const {
    int resultH, resultM, divM=0, resultS, divS=0;
    resultS = (s - t.getS());
    resultS %= 60;
    if (resultS < 0){
        resultS += 60;
        divS = 1;
    }
    resultM = (m - t.getM() - divS);
    resultM %= 60;
    if (resultM < 0){
        resultM += 60;
        divM = 1;
    }
    resultH = (h - t.getH() - divM);
    resultH %= 24;
    if (resultH < 0){
        resultH += 24;
    }
    return Time((size_t)resultH,(size_t)resultM,(size_t)resultS);
}


int main(){

    //ex 4

    ifstream f1("C:\\Users\\nrtc\\Desktop\\temp.txt");
    bool first = true;
    string a, timeToConvert,status;
    char equalSign;
    float temperature, temperatureBefore = -99999, diff;
    Time time, timeBefore, timeRising("00:00:00"), timeRisen;

    if(!f1){
        cerr << "The file could not be opened.";
        exit(1);
    }

    while(getline(f1,a)){

        stringstream iss(a);
        iss >> timeToConvert >> equalSign >> temperature;
        timeToConvert += ":00";
        time = Time(timeToConvert);

        if(first){
            cout << fixed << setprecision(1);
            std::cout << time.getStr().substr(0,5) << " = " << temperature << endl;

            timeBefore = Time(timeToConvert);
            temperatureBefore = temperature;
            first = false;

        }else{

            diff = temperature - temperatureBefore;

            if(diff<0){
                status = "desceu durante " + (time - timeBefore).getStr().substr(0,5);

            }else if(diff>0){
                timeRisen = time - timeBefore;
                status = "subiu durante " + timeRisen.getStr().substr(0,5);
                timeRising = timeRising + timeRisen;

            } else {
                status = "estável durante " + (time - timeBefore).getStr().substr(0,5);

            }
            std::cout << time.getStr().substr(0,5) << " = " << temperature << " - " << status << endl;
            timeBefore = Time(timeToConvert);
            temperatureBefore = temperature;

        }
    }

    std::cout << "A TEMPERATURA SUBIU DURANTE " << timeRising.getStr().substr(0,5) << endl;
    return 0;
}


/*
  Time time1("01:02:30"), time2("00:00:00"), time3;
    time3 = time2-time1;
    cout << time3.getStr();
 */


/* ex2
template<class T>
int count(const vector<T> &v, T value){
    int count = 0;
    for(const auto &elem: v){
        if(elem == value)
            count+=1;
    }
    return count;
}

int count(int a[] ,int value, int n){
    int count = 0;
    for(size_t i=0; i<n; i++ ){
        if(a[i] == value){
            count += 1;
        }
    }
    return count;
}



int main() {
    vector<char> v;
    char value;
    while(cin>>value){
        v.push_back(value);
    }
    cin.ignore();
    cin.clear();
    std::cout << std::count(v.begin(),v.end(),'0');

    int a[100];
    int value, i=0;
    while(cin>>value){
        a[i] = value;
        i++;
    }
    cin.ignore();
    cin.clear();
    std::cout << count(a,3,(sizeof(a)/sizeof(int)));
return 0;
}
*/
