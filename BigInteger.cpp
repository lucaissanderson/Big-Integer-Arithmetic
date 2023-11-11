/**********************************
    BigInteger.cpp
    lzsander
    
***********************************/


#include <stdexcept>
#include <cctype>
#include <cmath>
#include "BigInteger.h"


// public/global variables
int p = 9;
long b = pow(10,p);

// Private Helper Protos ------------------------------------------------------

void negateList(List& L);
void sumList(List& S, List A, List B, int sgn);
int normalizeList(List& L);
void shiftList(List& L, int p);
void scalarMultList(List& L, ListElement m);

// Constructors --------------------------------------------------------------

// create BigInt in empty state
BigInteger::BigInteger(){
    signum=0;
}

// create BigInt from long x
BigInteger::BigInteger(long x){

    // check if zero, neg, pos
    if(!x){
        signum=0;
        return;
    } else if(x<0){
        signum=-1;
        x = -x;
    } else signum=1;
    
    while(x>0){
        digits.insertBefore(x%b);
        x /= b;
    }

}

// create BigInt from string s
BigInteger::BigInteger(std::string s){

    if(!s.size()) throw std::invalid_argument("BigInteger: Constructor: empty string");

    // check if zero
    if(!s[0] && s.size()<3){
        signum=0;
        return;
    }

    long group=0;
    int digit=0;
    signum=1;

    // iterate for string length
    for(long len = s.size()-1; len >= 0; len--){
        if(len==1 && !isdigit(s[len])) throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        // check if (-), (+), or invalid character
        if(!isdigit(s[len])){
            if(s[len]=='-') signum=-1;
            else if(s[len]=='+');
            else throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
            // end loop
            break;
        }
        group += (s[len] - '0') * pow(10,digit);
        digit++;
        if(digit >= p){
            digits.insertBefore(group);
            group=0;
            digit=0;
        }
    }
    // flush group
    if(group) digits.insertBefore(group);

    digits.moveBack();
    while(!digits.peekPrev()) digits.eraseBefore();


}

// copy constructor
BigInteger::BigInteger(const BigInteger& N){
    this->signum = N.signum;
    this->digits = N.digits;
}

// Access functions --------------------------------------------------------

// sign() returns sign of this
int BigInteger::sign() const{
    return signum;
}

// compare() 
// returns -1, 1, or 0 if this is less than N, greater than or equal to, resp.
int BigInteger::compare(const BigInteger& N) const{
    // strictly test pos/neg/zero options first
    if(!this->signum && !N.signum) return 0;
    if(this->signum > N.signum) return 1;
    else if(this->signum < N.signum) return -1;

    // test size (effectively order of magnitude)
    if(this->digits.length() > N.digits.length()){
        return this->signum < 0 ? -1 : 1;
    } else if(this->digits.length() < N.digits.length()){
        return this->signum < 0 ? 1 : -1;
    }

    // start with equal
    int eq = 0;
    List A = this->digits;
    List B = N.digits;
    // move from most significant to least signuficant digit
    A.moveBack();
    B.moveBack();
    while(B.position()>0){
        if(A.peekPrev() > B.peekPrev()){
            eq=1;
            break;
        } else if(A.peekPrev() < B.peekPrev()){
            eq=-1;
            break;
        }
        A.movePrev();
        B.movePrev();
    }
    return this->signum < 0 ? -eq : eq;
}


// other functions ------------------------------------------------------------

// return string representation of this bigint
std::string BigInteger::to_string(){
    // placeholder for current "entry" in list
    long entry;
    //number of digits
    int numd=0;
    if(!signum) return "0";
    std::string s = "";
    s += (signum==-1) ? "-" : "";
    for(digits.moveBack(); digits.position()>0; digits.movePrev()){
        // special zero case, print p zeros
        if(!digits.peekPrev()){
            s += std::string(p,'0');
            continue;
        }
        // check for leading zeros
        entry = digits.peekPrev();
        for(;(entry)>0;entry /= 10, numd++);
        if(numd<p && digits.position()<digits.length()){
            s += std::string(p-numd,'0');
        }
        s += std::to_string(digits.peekPrev());
        numd=0;
    }
    return s;
}


// Manipulation procedures -------------------------------------------------

// makeZero()
void BigInteger::makeZero(){
    digits.clear();
    signum=0;
}

// negate()
void BigInteger::negate(){
    if(!signum) return;
    else if(signum>0) signum=-1;
    else signum=1;
}

// BigInteger Arithmetic operations ----------------------------------------

// add()
BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger sum;
    List A = this->digits;
    List B = N.digits;

    if(this->signum < 0) negateList(A);
    if(N.signum < 0) negateList(B);

    sumList(sum.digits, A, B, 1);

    sum.signum = normalizeList(sum.digits) < 0 ? -1 : 1;

    // check if zero
    for(sum.digits.moveFront(); sum.digits.position()<sum.digits.length(); sum.digits.moveNext()){
        if(sum.digits.peekNext()) return sum;
    }

    sum.makeZero();
    return sum;
}

// sub() A-B
BigInteger BigInteger::sub(const BigInteger& N) const{
    // reuse sum, just negate() N
    BigInteger N_not = N;
    N_not.negate();
    BigInteger diff = this->add(N_not);
    return diff;
}

// mult() A*B
BigInteger BigInteger::mult(const BigInteger& N) const{

    BigInteger prod;
    List A = this->digits;
    List B = N.digits;

    // check if either is zero
    if(!N.signum || !this->signum) return prod;

    // classic multiplication tech.
    for(A.moveFront();A.position()<A.length();A.moveNext()){
        List t = B;
        scalarMultList(t, A.peekNext());
        shiftList(t, A.position());
        sumList(prod.digits, prod.digits, t, 1);
        normalizeList(prod.digits);
        
    }

    // assign sign
    if((this->signum < 0 && N.signum < 0) || (this->signum > 0 && N.signum > 0)){
        prod.signum = 1;
    } else {
        prod.signum = -1;
    }

    return prod;

}

// Helpers ---------------------------------------------------------------------

// negateList()
void negateList(List& L){
    for(L.moveFront();L.position()<L.length();L.moveNext()){
        L.setAfter(-L.peekNext());
    }
}

// sumList()
void sumList(List& S, List A, List B, int sgn){

    S.clear();

    // detemine sizes
    int min_size;
    if(A.length()<B.length()) min_size=A.length();
    else min_size=B.length();

    // vector add each element
    A.moveFront();
    B.moveFront();
    while(A.position()<min_size){
        S.insertBefore(A.peekNext() + (sgn * B.peekNext()));
        A.moveNext();
        B.moveNext();
    }

    // flush
    if(B.length()>min_size){
        while(B.position()<B.length()){
            S.insertBefore(sgn * B.peekNext());
            B.moveNext();
        }
    } else if(A.length()>min_size){
        while(A.position()<A.length()){
            S.insertBefore(A.peekNext());
            A.moveNext();
        }
    }


}

// normalizeList()
// pre: not normalizing A-B where B>A
int normalizeList(List& L){


    int c = 0;
    long curr;

    for(L.moveFront();L.position()<L.length()-1;L.moveNext()){
        curr = L.peekNext();
        curr += c;
        // integer division trickery
        if((curr % b)<0){
            if(curr/b == 0){
                c = -1;
                curr = curr + b;
            } else{
                c = curr % b;
                curr = (-(curr / (b-1))*b) + curr;
            }
        } else{
            c = curr / b;
            curr = curr % b;
        }
        L.setAfter(curr);
    }

    // bring down last one
    curr = L.peekNext() + c;
    if(curr<0) c=-1;
    L.setAfter(curr);

    L.moveNext();

    // if we have overflow, carry to the next place 
    if(curr / b){
        L.eraseBefore();
        L.insertBefore(curr % b);
        L.insertAfter(curr / b);
    }


    // if the last one is negative, negate and recurse
    if(L.peekPrev()<0){
        scalarMultList(L, -1);
        normalizeList(L);
    // ensure carry is positive
    } else {
        c = 1;
    }

    // destroy leading zeroes
    L.moveBack();
    while(!L.peekPrev()){
        L.eraseBefore();
        if(!L.length()) break;
    }

    return c;

}

//shiftList() prepends n zero digits to L, muliplying L by base^n
void shiftList(List& L, int n){
    L.moveFront();
    for(int i=0; i<n; i++){
        L.insertBefore(0);
    }
}

// scalarMultList() multiply L (vector) by m.
void scalarMultList(List& L, ListElement m){
    L.moveFront();
    while(L.position()<L.length()){
        L.setAfter(m * L.peekNext());
        L.moveNext();
    }
}

// Overriden Operators -----------------------------------------------------

// operator<<() string into stream
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();
}

// operator==() 
bool operator==( const BigInteger& A, const BigInteger& B ){
    return !A.compare(B) ? true : false;
}

// operator<() less than
bool operator<( const BigInteger& A, const BigInteger& B ){
    return A.compare(B)<0 ? true : false;
}

// operator<=() less than or equal
bool operator<=( const BigInteger& A, const BigInteger& B ){
    return !A.compare(B) || A.compare(B)<0 ? true : false;
}

// operator>() greater than
bool operator>( const BigInteger& A, const BigInteger& B ){
    return A.compare(B)>0 ? true : false;
}

// operator>=() greater than or equal
bool operator>=( const BigInteger&A, const BigInteger& B ){
    return !A.compare(B) || A.compare(B)>0 ? true : false;
}

// operator+() A+B
BigInteger operator+(const BigInteger& A, const BigInteger& B){
    return A.add(B);
}

// operator+=() A = A + B
BigInteger operator+=(BigInteger& A, const BigInteger& B){
    BigInteger sum = A.add(B);
    A = sum;
    return A;
}

// operator-() A-B
BigInteger operator-(const BigInteger& A, const BigInteger& B){
    return A.sub(B);
}

// operator-=() A = A - B
BigInteger operator-=(BigInteger& A, const BigInteger& B){
    BigInteger diff = A.sub(B);
    A = diff;
    return A;
}

// operator*() A*B
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

// operator*=() A=A*B
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    BigInteger prod = A.mult(B);
    A = prod;
    return A;
}
