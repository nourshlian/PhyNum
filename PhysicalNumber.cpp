#include<iostream>
#include <cstdlib>
#include"Unit.h"
#include <string>
#include"PhysicalNumber.h"


using namespace ariel;
using namespace std;


PhysicalNumber::PhysicalNumber(double _value , Unit _unit) : _value(_value), _unit(_unit) {}

double PhysicalNumber::getValue(){
    return this->_value;
}

Unit PhysicalNumber::getUnit(){
    return this->_unit;
}

PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber& ps) const{
    if(this->_unit == ps._unit)
        return PhysicalNumber(this->_value + ps._value ,this->_unit);
    
    else if(abs((int)this->_unit - (int)ps._unit) <= 2 ){

        double tmp = this->_value;
        switch (this->_unit)
        {
            case Unit::CM:
                switch (ps._unit)
                {
                    case Unit::M:
                        tmp += (ps._value*100);
                        break;
                
                    case Unit::KM:
                        tmp += (ps._value*1000*100);
                        break;
                }
            break;
        
            case Unit::M:
                switch (ps._unit)
                {
                    case Unit::CM:
                        tmp += (ps._value/100);
                        break;

                    case Unit::KM:
                        tmp += (ps._value*1000);
                        break;
                    
                }
            break;
            
            case Unit::KM:
                switch (ps._unit)
                {
                    case Unit::CM:
                        tmp += ( ps._value/100/1000);
                        break;

                    case Unit::M:
                        tmp += ( ps._value/1000);
                        break;
                
                }
            break;

            case Unit::G:
                 switch (ps._unit)
                {
                    case Unit::KG:
                        tmp += ( ps._value*1000);
                        break;

                    case Unit::TON:
                        tmp += ( ps._value*1000*1000);
                        break;
                
                }
            break;

            case Unit::KG:
                switch (ps._unit)
                {
                    case Unit::G:
                        tmp += (ps._value/1000);
                        break;

                    case Unit::TON:
                        tmp += (ps._value*1000);
                        break;    
                }
            break;

            case Unit::TON:
                switch (ps._unit)
                {
                    case Unit::G:
                        tmp += (ps._value/1000/1000);
                        break;

                    case Unit::KG:
                        tmp += (ps._value/1000);
                        break;    
                }
            break;

            case Unit::SEC:
                switch (ps._unit)
                {
                    case Unit::MIN:
                        tmp += (ps._value*60);
                        break;
                
                    case Unit::HOUR:
                        tmp += (ps._value*3600);
                        break;
                }
            break;
        
            case Unit::MIN:
                switch (ps._unit)
                {
                    case Unit::SEC:
                        tmp += (ps._value/60);
                        break;

                    case Unit::HOUR:
                        tmp += (ps._value*60);
                        break;
                    
                }
            break;
            
            case Unit::HOUR:
                switch (ps._unit)
                {
                    case Unit::SEC:
                        tmp += ( ps._value/3600);
                        break;

                    case Unit::MIN:
                        tmp += ( ps._value/60);
                        break;
                
                }
            break;

        }





    return PhysicalNumber(tmp , this->_unit);
    }
    else throw std::invalid_argument("error"); 
    
}

PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber& ps) const{
    PhysicalNumber tmp = PhysicalNumber(ps._value * -1, ps._unit);
    return (*this) + tmp ;

}

PhysicalNumber PhysicalNumber::operator+() const{return PhysicalNumber(this->_value, this->_unit);}
PhysicalNumber PhysicalNumber::operator-() const{return PhysicalNumber(- this->_value, this->_unit);}

PhysicalNumber& PhysicalNumber::operator+= (const PhysicalNumber& ps){
    PhysicalNumber x = (*this) + ps;
    this->_value = x._value;
    return *this;
}

PhysicalNumber& PhysicalNumber::operator-= (const PhysicalNumber& ps){
    PhysicalNumber x = (*this) - ps;
    this->_value = x._value;
    return *this;
}

PhysicalNumber& PhysicalNumber::operator= (const PhysicalNumber& ps){
    this->_value = ps._value;
    this->_unit = ps._unit;
    return *this;
}

bool PhysicalNumber::operator==(const PhysicalNumber& ps){
    PhysicalNumber temp = *this - ps;
    if(temp._value == 0)
        return true;
    return false;
}

bool PhysicalNumber::operator<(const PhysicalNumber& ps){
    PhysicalNumber temp = *this - ps;
    if(temp._value < 0)
        return true;
    return false;
} 

bool PhysicalNumber::operator<=(const PhysicalNumber& ps){
    PhysicalNumber temp = *this - ps;
    if(temp._value <= 0)
        return true;
    return false;
} 
bool PhysicalNumber::operator>(const PhysicalNumber& ps){
    PhysicalNumber temp = *this - ps;
    if(temp._value > 0)
        return true;
    return false;
}

bool PhysicalNumber::operator>=(const PhysicalNumber& ps){
    PhysicalNumber temp = *this - ps;
    if(temp._value >= 0)
        return true;
    return false;
}

bool PhysicalNumber::operator!=(const PhysicalNumber& ps){
    if(*this == ps)
        return false;
    return true;
}

const PhysicalNumber PhysicalNumber::operator++(int) {
    PhysicalNumber temp(*this);
    this->_value ++ ;
    return temp;
}

const PhysicalNumber PhysicalNumber::operator--(int) { 
    PhysicalNumber temp(*this);
    this->_value -- ;
    return temp;
}

PhysicalNumber& PhysicalNumber::operator++() {
    ++ this->_value;
    return *this;
}   
 
PhysicalNumber& PhysicalNumber::operator--() { 
    -- this->_value;
    return *this;
}
std::ostream& ariel::operator<<(std::ostream& os , const PhysicalNumber& ps){
    string s = "";
    switch(ps._unit){
        case Unit::CM : s = "[cm]"; break;
        case Unit::M : s = "[m]"; break;
        case Unit::KM : s = "[km]"; break;

        case Unit::SEC : s = "[sec]"; break;
        case Unit::MIN : s = "[min]"; break;
        case Unit::HOUR : s = "[hour]"; break;

        case Unit::G : s = "[g]"; break;
        case Unit::KG : s = "[kg]"; break;
        case Unit::TON : s = "[ton]"; break;
    }
    return os << ps._value << s;
}

std::istream& ariel::operator>>(std::istream& is, PhysicalNumber& ps) {
    std::string in;
    is >> in;

    string temp[] = {"cm", "m", "km", "g", "kg", "ton", "sec", "min", "hour"};
    int first = in.find('[');
    int last = in.find(']');

    if(first == -1 || last == -1 || first > last){
        throw "Invalid input";
    }
    bool isOk = false;
    string value = in.substr(0, first);
    string unit = in.substr(first+1, last - first - 1 );
    //auto temp_size = std::size(temp);
    double val = stod(value);
    for(int i=0; i<9; i++){
        if(unit == temp[i]){
            isOk = true;
            ps._value = val;
            switch (i)
            {
                case 0: ps._unit = Unit::CM; break;
                case 1: ps._unit = Unit::M; break;
                case 2: ps._unit = Unit::KM; break;
                case 3: ps._unit = Unit::G; break;
                case 4: ps._unit = Unit::KG; break;
                case 5: ps._unit = Unit::TON; break;
                case 6: ps._unit = Unit::SEC; break;
                case 7: ps._unit = Unit::MIN; break;
                case 8: ps._unit = Unit::HOUR; break;
            
            }
        }
    }
    if(isOk == false)
        throw "Invalid input";
return is;
}


// int main(){

// PhysicalNumber x = PhysicalNumber(10,Unit::M);
// PhysicalNumber y = PhysicalNumber(5,Unit::M);
// //PhysicalNumber z;
// cout <<( x > y )<< endl ;



// // cout << x._value;

// return 0;
//  }