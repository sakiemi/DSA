#include <assert.h>

#include "SortedMap.h"
#include "SMIterator.h"
#include "MyTests.h"
#include <exception>

using namespace std;

bool relatie1(TKey cheie1, TKey cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    }
    else {
        return false;
    }
}

void testAll() {
    SortedMap sm(relatie1);
    assert(sm.size() == 0);
    assert(sm.isEmpty());
    sm.add(1, "Urlati");
    assert(sm.size() == 1);
    assert(!sm.isEmpty());
    assert(sm.search(1) != "");
    TValue v = sm.add(1, "Ploiesti");
    assert(v == "Urlati");
    assert(sm.search(1) == "Ploiesti");
    SMIterator it = sm.iterator();
    it.first();
    while (it.valid()) {
        TElem e = it.getCurrent();
        assert(e.second != "");
        it.next();
    }
    assert(sm.remove(1) == "Ploiesti");
    assert(sm.isEmpty());

}

