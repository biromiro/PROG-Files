#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <set>
#include <list>

void toUpperStr(std::string& s){
    std::string upper = "";
    for(const auto &elem: s){
        upper += toupper(elem);
    }
    s = upper;
}

std::string transformLine(const std::string& line){
    std::string result = line;
    toUpperStr(result);
    for(size_t i=0; i<result.size(); i++){
        if(!isalpha(result[i])){
            result[i] = ' ';
        }
    }
    return result;
}

void decomposeLine(const std::string& line, std::vector<std::string>& words){
    std::istringstream stream(transformLine(line));
    std::string word = "";
    while(stream >> word){
        words.push_back(word);
    }
}


struct Position{
    int lin,col;
};

class Ship{
public:
    Ship(unsigned int identifier,char symbol,Position position,char direction,size_t size);
    unsigned int getIdentifier() const;

    char getSymbol() const;

    void setSymbol(char symbol);

    const Position &getPosition() const;

    void setPosition(const Position &position);

    char getDirection() const;

    void setDirection(char direction);

    size_t getOfsizex() const;

    void setOfsizex(size_t ofsizex);

    void setIdentifier(unsigned int identifier);

    bool operator<(const Ship &s) const;
private:
    unsigned int _identifier;
    char _symbol;
    Position _position;
    char _direction;
    size_t _ofsizex;
};

Ship::Ship(unsigned int identifier, char symbol, Position position, char direction, size_t size)
    : _identifier(identifier), _symbol(symbol), _position(position), _direction(direction), _ofsizex(size)
{}

unsigned int Ship::getIdentifier() const {
    return _identifier;
}

void Ship::setIdentifier(unsigned int identifier) {
    _identifier = identifier;
}

char Ship::getSymbol() const {
    return _symbol;
}

void Ship::setSymbol(char symbol) {
    _symbol = symbol;
}

const Position &Ship::getPosition() const {
    return _position;
}

void Ship::setPosition(const Position &position) {
    _position = position;
}

char Ship::getDirection() const {
    return _direction;
}

void Ship::setDirection(char direction) {
    _direction = direction;
}

size_t Ship::getOfsizex() const {
    return _ofsizex;
}

void Ship::setOfsizex(size_t ofsizex) {
    _ofsizex = ofsizex;
}

bool Ship::operator<(const Ship &s) const{
    return _identifier<s.getIdentifier();
}

class Board{
public:
    Board(size_t numLines=10,size_t numColumns=10);
    bool putShip(const Ship&s);//add ship to board,if possible
    // ...OTHERMETHODS
private:
    bool canPutShip(Position pos,char dir,size_t size);
    size_t numLines,numColumns;
    std::vector<std::vector<int>> board;//eachelement=shipidor ‐1
    std::vector<Ship> ships;
    //...OTHERATTRIBUTESAND/ORMETHODS
};

Board::Board(size_t numLines, size_t numColumns){
    std::vector<std::vector<int>> x(numLines, std::vector<int>(numColumns,-1));
    this->numColumns = numColumns;
    this->numLines = numLines;
    board = x;
    Position pos = {3,3};
    std::cout << canPutShip(pos, 'H' , 5);
}

bool Board::canPutShip(Position pos, char dir, size_t size) {
    switch(dir){
        case 'H':
            if(pos.col + size >  numColumns){return false;}
            for(size_t i=0; i<size; i++){
                if(board[pos.lin][pos.col+1] != -1){
                    return false;
                }
            }
            return true;
        case 'V':
            if(pos.lin + size >  numLines){return false;}
            for(size_t i=0; i<size; i++){
                if(board[pos.lin+i][pos.col] != -1){
                    return false;
                }
            }
            return true;

    }
}

bool Board::putShip(const Ship &s) {
    if(canPutShip(s.getPosition(),s.getDirection(),s.getOfsizex())){
        switch (s.getDirection()) {
            case 'H':
                for(size_t i=s.getPosition().col; i < s.getPosition().col + s.getOfsizex(); i++){
                    board[s.getPosition().lin][i] = s.getOfsizex();
                }
                break;
            case 'V':
                for(size_t i=s.getPosition().lin; i < s.getPosition().lin + s.getOfsizex(); i++){
                    board[i][s.getPosition().col] = s.getOfsizex();
                }
        }
        ships.push_back(s);
        return true;
    } else { return false;}
}

float average(const int grades[], int numStudents){
    size_t i = 0, sum=0;
    while(i < numStudents){
        sum += grades[i];
        i++;
    }
    return (float)sum/numStudents;
}
void readGrades(int grades[],int numStudents){
    for(size_t i=0; i<numStudents; i++){
        std::cin >> grades[i];
    }
}


int main() {
    /*std::string s;
    std::vector<std::string> vec;
    std::ifstream f1("C:\\Users\\nrtc\\Desktop\\text.txt");
    while(getline(f1,s)){
        decomposeLine(s,vec);
    }
    std::ofstream f2("C:\\Users\\nrtc\\Desktop\\words.txt");
    std::set<std::string> setkekw(vec.begin(),vec.end());
    for(const auto &elem: setkekw){
        f2 << elem << "\n";
    }*/

    /*unsigned long identifier;
    char direction, symbol;
    Position position;
    size_t size;
    Board board1(10,20);
    std::cout << "Please insert the ship identifier, symbol, position(line and column), direction and size" << std::endl;
    std::cin >> identifier >> symbol >> position.lin >> position.col >> direction >> size;
    Ship ship1(identifier,symbol,position,direction,size);
    if(!board1.putShip(ship1)) {
        throw std::invalid_argument("Can't put ship");
    }
    std::cout << "ehhhe";*/

    /*int num;
    std::cout << "Please input the number of students" << std::endl;
    std::cin >> num;
    int* grades =  new int[num];
    readGrades(grades, num);
    std::cout << average(grades,num);
    */
    std::set<Ship> ships;
    ships.insert(Ship(3,'s',{1,2},'H',3));
    ships.insert(Ship(1,'s',{1,2},'H',3));
    ships.insert(Ship(2,'s',{1,2},'H',3));
    return 0;
}
