//-----------------------------
// ListTest.cpp
// Test Harness for List.cpp
// lzsander
//-----------------------------


#include<stdexcept>
#include<assert.h>
#include"List.h"

using namespace std;

int main(){

    // basic contruction

    List L;

    cout << "cursor at " << L.position() << endl;
    cout << "length is " << L.length() << endl;
    try{
        cout << "front is " << L.front() << endl;
    } catch(length_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        cout << "back is " << L.back() << endl;
    }catch(length_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        cout << "peekPrev() : " << L.peekPrev() << endl;
    }catch(range_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }

    // adding elements

    // | 9 8 7 6 5
    L.insertAfter(5);
    L.insertAfter(6);
    L.insertAfter(7);
    L.insertAfter(8);
    L.insertAfter(9);

    cout << "pos : " << L.position() << endl;
    cout << "length : " << L.length() << endl;
    
    for(L.moveFront();L.position()<L.length();){
        cout << L.moveNext();
    }
    cout << endl;

    for(L.moveFront();L.position()<L.length();L.moveNext()){
        try{
            cout << L.peekNext();
        }catch(range_error& e){
            cout << e.what() << endl;
            cout << "   continuing without interruption" << endl;
        }
    }
    cout << endl;

    L.moveFront();
    L.eraseAfter();

    
    for(L.moveFront();L.position()<L.length();){
        cout << L.moveNext();
    }
    cout << endl;

    L.clear();
    cout << L.length() << endl;

    // 1 2 3 4 5 6 7 8 9 | 10 9 8 7 6 5 4 3 2
    for(long i=1; i<10; i++){
        L.insertBefore(i);
        L.insertAfter(i+1);
    }

    for(L.moveFront();L.position()<L.length();){
        cout << L.moveNext() << " ";
    }
    cout << endl;

    cout << L.position() << endl;
    // 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9
    for(long i=10;i>0;i--){
        L.setBefore(i);
        L.movePrev();
    }

    for(L.moveFront();L.position()<L.length();){
        cout << L.moveNext() << " ";
    }
    cout << endl;

    // test copy and equals
    List A = L;
    for(A.moveFront();A.position()<A.length();){
        cout << A.moveNext() << " ";
    }
    cout << endl;
    
    

    // other functions
    L.moveFront();
    cout << L.findNext(9) << endl;

    cout << L.findPrev(3) << endl;

    // 1 2 3 4 5 6 7 8 9
    L.cleanup();
    for(L.moveFront();L.position()<L.length();){
        cout << L.moveNext() << " ";
    }
    cout << endl;
    
    List C = L.concat(A);
    for(C.moveFront();C.position()<C.length();){
        cout << C.moveNext() << " ";
    }
    cout << endl;
    
    // test to_string
    cout << C << endl;

    // test equals()
    List B = A;
    assert(B.equals(A));
    assert(!B.equals(C));

    // test operations
    cout << "B = " << B << endl;
    B = C;
    cout << "B = C = " << B << endl;
    assert(B==C);

    A.clear();
    B.clear();
    C.clear();

    List D;

    // tests from examples
   long i, n=10;

   for(i=1; i<=n; i++){
      A.insertAfter(i);
      B.insertAfter(11-i);
      C.insertBefore(i);
      D.insertBefore(11-i);
   }

   cout << endl;
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   A.moveBack();
   B.moveBack();
   C.moveFront();
   D.moveFront();

   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;

   cout << endl << "B: ";
   for(i=1; i<=7; i++){
      cout << B.movePrev() << " ";
   }
   cout << endl << "B.position() = " << B.position() << endl;
   
   cout << endl << "C: ";
   for(i=1; i<=7; i++){
      cout << C.moveNext() << " ";
   }
   cout << endl << "C.position() = " << C.position() << endl;

   cout << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==D is " << (C==D?"true":"false") << endl;
   cout << "D==A is " << (D==A?"true":"false") << endl;
   cout << endl;

   cout << B.findNext(5) << endl;
   cout << B << endl;
// 1 2 3 4 5 | 6 7 8 9 10
   B.eraseBefore();
// 1 2 3 4 | 6 7 8 9 10
   B.eraseAfter();
// 1 2 3 4 | 7 8 9 10
   cout << B << endl;
   cout << B.position() << endl;
   cout << B.findPrev(2) << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl; 
   cout << B.findNext(20) << endl; 
   cout << B.position() << endl;
   cout << B.findPrev(20) << endl;
   cout << B.position() << endl;
   cout << endl;

   for( i=10; i>=1; i--){
      A.insertAfter(i);
      A.movePrev();
   }
   cout << "A = " << A << endl;
   for( i=1; i<=15; i++){
      A.moveNext();
   }
   cout << A.position() << endl;
   A.cleanup();
   cout << "A = " << A << endl;
   cout << A.position() << endl;
   cout << endl;

   List E = A;
   cout << "E==A is " << (E==A?"true":"false") << endl;

   cout << endl;

   List F = A.concat(B);
   cout << "F = " << F << endl;
   cout << "length: " << F.length() << endl;
   cout << "front: " << F.front() << endl;
   cout << "back: " << F.back() << endl;
   cout << "position: " << F.position() << endl;
   for( i=1; i<=7; i++){
      cout << "peekNext: " << F.peekNext() << endl;
      F.insertBefore(-i);
      cout << F.moveNext() << endl; 
   }
   cout << "F = " << F << endl;

   cout << endl;

   cout << "test exceptions: " << endl;
   cout << "A = " << A << endl;
   A.moveFront();
   try{
      A.peekPrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.movePrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setBefore(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseBefore();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.moveBack();
   try{
      A.peekNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.moveNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setAfter(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseAfter();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.clear();
   try{
      A.front();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.back();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;


    return 0;
}
