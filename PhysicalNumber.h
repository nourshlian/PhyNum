#ifndef PHYSICALNUMBER_H
#define PHYSICALNUMBER_H

#include <iostream>
#include "Unit.h"

namespace ariel {

	class PhysicalNumber {

        private:
            double _value;
		    Unit _unit;
		  



	    public:
		     PhysicalNumber(double, Unit);
             PhysicalNumber() =default;

            double getValue();
            Unit getUnit();

            PhysicalNumber operator+() const;
            PhysicalNumber operator-() const;

            PhysicalNumber operator+(const PhysicalNumber&) const;
            PhysicalNumber operator-(const PhysicalNumber&) const;

            PhysicalNumber& operator+=(const PhysicalNumber&) ;
            PhysicalNumber& operator-=(const PhysicalNumber&) ;
            PhysicalNumber& operator=(const PhysicalNumber&);

            bool operator==(const PhysicalNumber&); 
		        bool operator<(const PhysicalNumber&); 
		        bool operator!=(const PhysicalNumber&);
		        bool operator<=(const PhysicalNumber&); 
		        bool operator>=(const PhysicalNumber&); 
		        bool operator>(const PhysicalNumber&);

            const PhysicalNumber operator++(int); 
		        const PhysicalNumber operator--(int);
		
		        PhysicalNumber& operator++(); 
		        PhysicalNumber& operator--();

            friend std::ostream& operator<<(std::ostream&, const PhysicalNumber&);
		        friend std::istream& operator>>(std::istream&, PhysicalNumber&);




    };
    std::ostream& operator<<(std::ostream&, const PhysicalNumber&);
    std::istream& operator>>(std::istream&, PhysicalNumber&);

}
#endif