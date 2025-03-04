#include <iostream>
#include "iterator"
using namespace std;

struct Item {
    uint cost;
    uint weight;
};

vector<Item> getItems(){
    return {
            {100, 5},
            {200, 10},
            {150, 7},
            {120, 6},
            {180, 8}
    };
}

vector<Item> getOptimalItemsSet(uint maxWeight, vector<Item> items){
    uint maxCost = 0;
    vector<int> indexesOfMaxCost;

    int n = items.size() + 1;
    vector<int> tmp(n, 0);
    while (tmp.at(n - 1) != 1){
//        copy(tmp.begin(), tmp.end(), ostream_iterator<int>(cout, " "));
//        cout << endl;
        uint tmpMaxCost = 0;
        uint tmpWeight = 0;
        for (int j = 0; j < items.size(); j++) {
            if (tmp.at(j) != 1)
                continue;

            tmpWeight += items.at(j).weight;
            tmpMaxCost += items.at(j).cost;
        }

        if (tmpWeight < maxWeight && tmpMaxCost > maxCost) {
            maxCost = tmpMaxCost;
            indexesOfMaxCost = tmp;
        }

        int i = 0;
        while (tmp.at(i) == 1){
            tmp.at(i) = 0;
            i++;
        }
        tmp.at(i) = 1;
    }

    cout << "Max cost is: " << maxCost << endl << "Indexes: " << endl;
    copy(indexesOfMaxCost.begin(), indexesOfMaxCost.end(), ostream_iterator<int>(cout, " "));

    return getItems();
}

int main() {
    uint maxWeight = 12;

    auto items = getItems();
    auto result = getOptimalItemsSet(maxWeight, items);
}
