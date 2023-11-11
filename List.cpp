//-----------------------------------------------------------------------
//  List.cpp
//  Implementation file for List ADT
//  lzsander
//-----------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

// Private Constructor

// From Queue.cpp on examples

// Node constructor
List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors ------------------------------------

// Creates a new List in the empty state.
List::List(){
    // initialize dummy nodes (front/back)
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy Constructor
List::List(const List& L){
    // create empty list
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    // fill entries
    if(!L.length()) return;
    Node* N = L.frontDummy->next;
    Node* M = new Node(N->data);
    frontDummy->next = M;
    M->prev = frontDummy;
    afterCursor = M;
    while(N->next != L.backDummy){
        N = N->next;
        M->next = new Node(N->data);
        M->next->prev = M;
        M = M->next;
    }
    M->next = backDummy;
    backDummy->prev = M;
    num_elements = L.length();
}

// Destructor
List::~List(){
    clear();
    delete frontDummy;
    delete backDummy;
}

// Access functions ----------------------------------------------------------------

// length()
// Returns length of this List
int List::length() const{
    return(num_elements);
}

// front()
// Returns the font element in this LIst.
// pre: length()>0
ListElement List::front() const{
    if(length()<=0) throw std::length_error("List: front(): empty list");
    return(frontDummy->next->data);
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    if(length()<=0) throw std::length_error("List: back(): empty list");
    return(backDummy->prev->data);
}

// position()
// Returns the position of the cursor in this List: 0<=position<=length()
int List::position() const{
    return(pos_cursor);
}

// peekNext()
// Returns the element after the cursor
// pre: position()<length()
ListElement List::peekNext() const{
    if(position()>=length()) throw std::range_error("List: peekNext(): cursor at back");
    return(afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor
// pre: position()>0
ListElement List::peekPrev() const{
    if(position()<=0) throw std::range_error("List: peekPrev(): cursor at front");
    return(beforeCursor->data);
}


// Maniupulation functions ---------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    if(length()>0){
        moveFront();
        while(afterCursor!=backDummy){
            eraseAfter();
        }
    }
}

// moveFront()
// Moves cursor to position 0 in this List
void List::moveFront(){
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

// moveBack();
// Moves cursor to position length() in this List.
void List::moveBack(){
    pos_cursor = length();
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

// moveNext()
// Moves cursor to next higher position. Returns the List element that 
// was passed over.
// pre: position()<length()
ListElement List::moveNext(){
    if(position()>=length()) throw std::range_error("List: moveNext(): cursor at back");
    ListElement x = afterCursor->data;
    pos_cursor++;
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    return x;
}

// movePrev()
// Advances cursor to next lower position. Returns the Lst element that 
// was passsed over
// pre: position()>0
ListElement List::movePrev(){
    if(position()<=0) throw std::range_error("List: movePrev(): cursor at front");
    ListElement x = beforeCursor->data;
    pos_cursor--;
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    return x;
}

// insertAfter()
// Insterts x after cursor
void List::insertAfter(ListElement x){
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements++;
}

// insertBefore()
// INserts x before cursor
void List::insertBefore(ListElement x){
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    num_elements++;
    // advance position
    pos_cursor++;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    if(position()>=length()) throw std::range_error("List: eraseAfter(): cursor at back");
    Node* N = afterCursor;
    afterCursor = N->next;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    delete N;
    num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if(position()<=0) throw std::range_error("List: eraseBefore(): cursor at front");
    Node* N = beforeCursor;
    beforeCursor = N->prev;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    delete N;
    num_elements--;
    pos_cursor--;
}

// setAfter()
// set next element's data to x
// pre: position()<length()
void List::setAfter(ListElement x){
    if(position()>=length()) throw std::range_error("List: setAfter(): cursor at back");
    afterCursor->data = x;
}

// setBefore()
// set previous element's data to x
// pre: position()>0
void List::setBefore(ListElement x){
    if(position()<=0) throw std::range_error("List: setBefore(): cursor at front");
    afterCursor->data = x;
}

// Other fucntions -------------------------------------------------------------------------------

// findNext()
int List::findNext(ListElement x){
    while(position()<length()){
        if(moveNext()==x) return(position());
    }
    return -1;
}

// findPrev()
int List::findPrev(ListElement x){
    while(position()>0){
        if(movePrev()==x) return(position());
    }
    return -1;
}

// cleanup()
void List::cleanup(){
    List A;
    int index = 0;
    Node* N = this->frontDummy->next;
    Node* M; // intermediate node
    while(N!=this->backDummy){
        M = N->next;
        A.moveFront();
        if(A.findNext(N->data)==-1){ 
            A.insertAfter(N->data);
            index++;
        } else {
            if(N==afterCursor) afterCursor = N->next;
            else if(N==beforeCursor) beforeCursor = N->prev;
            if(index<position()) pos_cursor--;
            N->next->prev = N->prev;
            N->prev->next = N->next;
            delete N;
            num_elements--;
        }
        N = M;
    }
}

// concat()
List List::concat(const List& L) const{
    List O;
    Node* N = this->frontDummy->next;
    Node* M = L.frontDummy->next;
    while(N!=this->backDummy){
        O.insertBefore(N->data);
        N = N->next;
    }
    while(M!=L.backDummy){
        O.insertBefore(M->data);
        M = M->next;
    }
    O.moveFront();
    return O;
}

// to_string()
std::string List::to_string()const{
    Node* N = nullptr;
    std::string s = "(";

    for(N=frontDummy->next;N!=backDummy;N=N->next){
        s += std::to_string(N->data)+(N==backDummy->prev?"":", ");
    }

    s += ")";

    return s;
}

// equals()
bool List::equals(const List& R)const{
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;
    
    eq = ( this->length() == R.length() );
    N = this->frontDummy;
    M = R.frontDummy;
    while( eq && N!=this->backDummy){
        eq = (N->data==M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// operator<<()
std::ostream& operator<<( std::ostream& stream, const List& L){
    return stream << L.List::to_string();
}

// operator==()
bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

// operator=()
List& List::operator=( const List& L ){
    if(this!=&L) {
        // make copy of L
        List temp = L;
        
        // swap the copy's fields with fields of this
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(num_elements, temp.num_elements);
    }

    // return this with the new data installed
    return *this;
}
