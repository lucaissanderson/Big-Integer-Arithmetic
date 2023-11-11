
#include <assert.h>
#include "BigInteger.h"

using namespace std;

int main(void){

    BigInteger A("6523485630758234007488392857982374523487612398700554");
    BigInteger B("123968906592874596090278485902184945");
    BigInteger D(-123456789);

    BigInteger C = A + B;
    assert((BigInteger)"6523485630758234131457299450856970613766098300885499"==C);

    C = A - B;
    assert((BigInteger)"6523485630758233883519486265107778433209126496515609"==C);

    C = A * B;
    assert((BigInteger)"808709380819427128836855436714943519790054702998868440258385811790158783883667381959530"==C);

    D *= A;
    assert((BigInteger)"-805368589061051205875118937017036977265185708020158169361106"==D);

    C -= C;
    assert((BigInteger)0==C);

    C = A*A;
    assert((BigInteger)"42555864774709154204630605211797210191133917056231437162242562256497242835488006962537992036227759906916"==C);

    C = C-(B*B);
    assert((BigInteger)"42555864774709154204630605211797194822844115223364940654553607785058238545753421857092129281902775253891"==C);

    try {
        BigInteger Z("98509718!!0098274");
    } catch(std::invalid_argument& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }

    try {
        BigInteger Z("");
    } catch(std::invalid_argument& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }

    try {
        BigInteger Z("1234567+8990391");
    } catch(std::invalid_argument& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }

    return 0;
}
