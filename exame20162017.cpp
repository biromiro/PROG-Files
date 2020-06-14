#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class Date{
public:
    friend ostream &operator<<(ostream &f, const Date &date);
    friend istream &operator>>(istream &f, const Date &date);
    friend bool operator<(const Date& left, const Date& right);
        Date(int y=1, int m=1, int d=1);

    int getY() const {
        return y;
    }

    void setY(int y) {
        Date::y = y;
    }

    int getM() const {
        return m;
    }

    void setM(int m) {
        Date::m = m;
    }

    int getD() const {
        return d;
    }

    void setD(int d) {
        Date::d = d;
    }

    bool operator==(const Date &rhs) const;

    bool operator!=(const Date &rhs) const;

private:
    int y, m, d;
};

ostream &operator<<(ostream &f, const Date &date) {
    f << date.y << "-" << date.m << "-" << date.d;
    return f;
}

bool operator<(const Date&left, const Date& right){
    string date2 = (to_string(right.getY()) + to_string(right.getM()) + to_string(right.getD()));
    string date1 = (to_string(left.getY()) + to_string(left.getM()) + to_string(left.getD()));

    return date1 < date2;
}

istream &operator>>(istream &f, Date& date){
    string dateString;
    char sep1, sep2;
    int year, month, day;

    getline(f, dateString);

    istringstream dateS(dateString);

    dateS >> year >> sep1 >> month >> sep2 >> day;

    if(sep1 != '-' || sep2 != '-' || year <= 0 || month <=0 || day <= 0){
        runtime_error descript("invalid date");
        throw descript;
    }

    date = Date(year, month, day);

    return f;
}

Date::Date(int y, int m, int d) {
    this->y = y;
    this->m = m;
    this->d = d;
}
template <class T>
class Image{
public:
    Image(size_t nLins=0, size_t nCols=0, T pixVal = 0);
    void setPixel(size_t lin, size_t col, T pixVal);
    bool read(string fileName);
    Image getRegion(size_t lin, size_t col, size_t nLins, size_t nCols) const;
    T getPixel(size_t lin, size_t col) const;
private:
    vector<vector<T>> img;
};

template <class T>
Image<T>::Image(size_t nLins, size_t nCols, T pixVal) {
    img.resize(nLins, vector<T>(nCols, pixVal));
}

template <class T>
void Image<T>::setPixel(size_t lin, size_t col, T pixVal) {
    img.at(lin).at(col) = pixVal;
}

template <class T>
bool Image<T>::read(string fileName) {
    ifstream f(fileName);
    if(f){
       vector<vector<T>> pixels;
       string str;
       size_t lins=0, cols=0;
       bool first = true;
       while(getline(f,str)){
           stringstream ss(str);
           T value;
           vector<T> pixelLine;
           while(ss >> value){
               if(first){
                   cols++;
               }
               pixelLine.push_back(value);
           }
           first = false;
           pixels.push_back(pixelLine);
           lins++;
       }
       Image img1(lins,cols);
       for(size_t i=0; i<lins; i++){
           for(size_t j=0; j<cols; j++){
               img1.setPixel(i,j,pixels.at(i).at(j));
           }
       }
       *this = img1;
       return true;
    }else{ return false;}
}

template <class T>
Image<T> Image<T>::getRegion(size_t lin, size_t col, size_t nLins, size_t nCols) const {
    Image img1(nLins,nCols);
    for(size_t i=lin; i<(lin+nLins); i++){
        for(size_t j=col; j<(col+nCols); j++){
            img1.setPixel(i,j,getPixel(i,j));
        }
    }
    return img1;
}

template <class T>
T Image<T>::getPixel(size_t lin, size_t col) const {
    return img.at(lin).at(col);
}

int main(){
    Date d1;
    string file;
    multimap<Date,Image<float>> imgByDate;
    cout << "Insira uma data no formato YYYY-MM-DD: ";
    cin >> d1;
    cout << "Insira o nome dos ficheiros que contêm as imagens (\"stop\" para parar): ";
    cin >> file;
    while(file != "stop"){
        Image<float> img;
        img.read(file);
        imgByDate.insert(make_pair(d1,img));
        cout << "Insira o nome dos ficheiros que contêm as imagens (\"stop\" para parar): ";
        cin >> file;
    }
    return 0;
}











/* ex2
int main(){
    Date d1,d2;

    try{
        cout << "Insira a data no formato YYYY-MM-DD: ";
        cin >> d1;
        cout << "Insira a 2ª data: ";
        cin >> d2;
    } catch (runtime_error& descript) {
        cerr << descript.what();
        exit(1);
    }
    if(d1<d2){
        cout << d1 << " is before " << d2;
    }else if(d1==d2){
        cout << d1 << " and " << d2 << " are the same";
    }else{
        cout << d1 << " is after " << d2;
    }
}

bool Date::operator==(const Date &rhs) const {
    return y == rhs.y &&
           m == rhs.m &&
           d == rhs.d;
}

bool Date::operator!=(const Date &rhs) const {
    return !(rhs == *this);
}
*/






















/* ex1
 #include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>

using namespace std;
struct alphabetical{
    bool operator()(const string& s1, const string&s2){
        string toUpper1 = s1, toUpper2 = s2;
        transform(toUpper1.begin(), toUpper1.end(), toUpper1.begin(), ::toupper);
        transform(toUpper2.begin(), toUpper2.end(), toUpper2.begin(), ::toupper);
        return toUpper1 < toUpper2;
    }
};


void simplify(const string &name, string &sName){
    stringstream iss(name);
    string last;

    iss >> sName;

    while(iss >> last);

    if(!(last == "")){
        sName += (" " + last);
    }
}

void readAndSimplify(){
    ifstream fr("C:\\Users\\nrtc\\Desktop\\people1.txt");

    if(!fr){
        cerr << "people1.txt not found" << endl;
        exit(1);
    }

    ofstream fw("C:\\Users\\nrtc\\Desktop\\people2.txt");
    string simplified, line;
    set<string,alphabetical> words;

    while(getline(fr,line)){
        simplify(line,simplified);
        words.insert(simplified);
    }

    for(const auto& elem: words){
        fw << elem << endl;
    }
}

int main() {
    readAndSimplify();
    return 0;
}

 */