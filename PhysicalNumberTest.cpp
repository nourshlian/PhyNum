/**
 * Examples of automatic tests for the exercise on physical numbers.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <sstream>
using std::cout, std::endl, std::istringstream;
#include "PhysicalNumber.h"
using ariel::PhysicalNumber, ariel::Unit;
#include "badkan.hpp"

int main() {
  badkan::TestCase testcase;
  int grade=0;
  int signal = setjmp(badkan::longjmp_buffer);
  if (signal == 0) {

    // BASIC TESTS - DO NOT CHANGE
    PhysicalNumber a(2, Unit::KM);
    PhysicalNumber b(300, Unit::M);
    PhysicalNumber c(2, Unit::HOUR);
    PhysicalNumber d(30, Unit::MIN);
    PhysicalNumber e(2, Unit::TON);

    PhysicalNumber j(2, Unit::TON);
    PhysicalNumber h(1300, Unit::KG);
    PhysicalNumber i(140, Unit::G);
    PhysicalNumber g(5, Unit::SEC);
    PhysicalNumber f(10, Unit::CM);


    testcase
    .setname("Basic output")
    .CHECK_OUTPUT(a, "2[km]")
    .CHECK_OUTPUT(b, "300[m]")

    .setname("Compatible dimensions")
    .CHECK_OUTPUT(b+a, "2300[m]")
    .CHECK_OUTPUT((a+=b), "2.3[km]")
    .CHECK_OUTPUT(a, "2.3[km]")
    .CHECK_OUTPUT(a+a, "4.6[km]")
    .CHECK_OUTPUT(b-b, "0[m]")
    .CHECK_OUTPUT(c, "2[hour]")
    .CHECK_OUTPUT(d, "30[min]")
    .CHECK_OUTPUT(d+c, "150[min]")

    .setname("Incompatible dimensions")
    .CHECK_THROWS(a+c)
    .CHECK_THROWS(e+a)

    .CHECK_THROWS(a+d)
    .CHECK_THROWS(b+c)
    .CHECK_THROWS(b+d)

    .setname("Basic input")
    .CHECK_OK(istringstream("700[kg]") >> a)
    .CHECK_OUTPUT((a += PhysicalNumber(1, Unit::TON)), "1700[kg]")

    // YOUR TESTS - INSERT AS MANY AS YOU WANT
    //.CHECK_OUTPUT((b-=b), "0[m]")

    .CHECK_THROWS(g+f)
    .CHECK_THROWS(g+=h)
    .CHECK_THROWS(c-e)
    .CHECK_THROWS(c-=a)
    .CHECK_OK(j = PhysicalNumber(2, Unit::KM))
    .CHECK_OUTPUT(j, "2[km]")
    .CHECK_OUTPUT(b, "300[m]")
    .CHECK_OUTPUT(b-b, "0[m]")
    .CHECK_OUTPUT(b, "300[m]")
    .CHECK_OUTPUT((b-=b), "0[m]")
    .CHECK_OK(b += PhysicalNumber(1, Unit::CM))
    .CHECK_OUTPUT((b+=b), "0.02[m]")
    .CHECK_OUTPUT(b, "0.02[m]")
    .CHECK_OUTPUT(+b, "0.02[m]")
    .CHECK_OUTPUT(-b, "-0.02[m]")
    .CHECK_EQUAL(j > j, false)
    .CHECK_EQUAL(j > b, true)
    .CHECK_OK(b = j)
    .CHECK_EQUAL(b == j, true)
    .CHECK_EQUAL(b != j, false)
    .CHECK_OUTPUT(b, "2[km]")
    .CHECK_EQUAL(b >= j, true)
    .CHECK_EQUAL(b <= j, true)
    .CHECK_OK(b += PhysicalNumber(1, Unit::CM))
    .CHECK_EQUAL(b != j, true)
    .CHECK_EQUAL(b >= j, true)
    .CHECK_EQUAL(b <= j, false)
    .CHECK_OK(b -= PhysicalNumber(2, Unit::CM))
    .CHECK_THROWS(b - PhysicalNumber(2, Unit::KG))
    .CHECK_EQUAL(b <= j, true)
    .CHECK_EQUAL(b >= j, false)
    .CHECK_OK(b += PhysicalNumber(1, Unit::CM))
    .CHECK_THROWS(b + PhysicalNumber(1, Unit::HOUR))
    .CHECK_EQUAL(b++ , j)
    .CHECK_EQUAL(b != j, true)
    .CHECK_EQUAL(b, ++j)
    .CHECK_EQUAL(b == j, true)
    .CHECK_OUTPUT(j, "3[km]")
    .CHECK_OUTPUT(++j, "4[km]")
    .CHECK_OUTPUT(j++, "4[km]")
    .CHECK_OUTPUT(j, "5[km]")

    .CHECK_OK(istringstream("0[kg]") >> a)
    .CHECK_THROWS(istringstream("10[]kg") >> a)
    .CHECK_THROWS(istringstream("cm[90]") >> a)
    .CHECK_THROWS(istringstream("[ton]") >> a)
    .CHECK_THROWS(istringstream("15[]") >> a)
    .CHECK_THROWS(istringstream("30[ m ]") >> a)
    .CHECK_THROWS(istringstream("25[kg]c") >> a)
    .CHECK_THROWS(istringstream("40[g") >> a)
    .CHECK_THROWS(istringstream("70g]") >> a)
    .CHECK_THROWS(istringstream("80]g[") >> a)
    .CHECK_THROWS(istringstream("78[][g]") >> a)
    .CHECK_THROWS(istringstream("31[cm][]") >> a)
    .CHECK_THROWS(istringstream("[hour]") >> a)
    .CHECK_THROWS(istringstream("[sec]108") >> a)
    .CHECK_THROWS(istringstream("43[[cm]") >> a)
    .CHECK_THROWS(istringstream("27[ton]]") >> a)
    .CHECK_THROWS(istringstream("54[c m]") >> a)
    .CHECK_THROWS(istringstream("2k0[g]") >> a)
    .CHECK_THROWS(istringstream("20k[g]") >> a)
    .CHECK_OK(istringstream("-20[g]") >> a)
    .CHECK_THROWS(istringstream("k-30[kg]") >> a)
    .CHECK_THROWS(istringstream("-11[mc]") >> a)

      .setname("...")

      .print(cout, /*show_grade=*/false);
      grade = testcase.grade();
    } else {
      testcase.print_signal(signal);
      grade = 0;
    }
    cout <<  "*** Grade: " << grade << " ***" << endl;
    return grade;
}
