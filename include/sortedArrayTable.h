#include "table.h"
#include "myvector.h"
#include <string>

class SortedArrayTable : public Table {
private:
    myVector<std::pair<std::string, Polynomial>> data;
    size_t opCount = 0;

    size_t findInsertPos(const std::string& key) const;

public:
    void insert(const std::string& key, const Polynomial& value) override;
    Polynomial* find(const std::string& key) override;
    void remove(const std::string& key) override;
    void printStats() const override;
};