#include <algorithm>
#include <iostream>
#include <vector>
#include "iterator"
#include "numeric"
using namespace std;

struct Item {
    int cost;
    int weight;
};

void printResult(vector<Item> &result);

vector<Item> getItems(){
    return {
            {100, 5},
            {200, 10},
            {150, 7},
            {120, 6},
            {180, 8}
    };
}

vector<Item> getOptimalItemsSet(int maxWeight, const vector<Item>& items){
    vector<Item> optimalItemsSet;

    int maxCost = 0;
    const int n = items.size() + 1;
    vector<bool> tmpBool(n, false), indexesToInclude(n, false);

    while (tmpBool.at(n - 1) != true){
        int tmpMaxCost = 0;
        int tmpWeight = 0;
        for (int j = 0; j < items.size(); j++) {
            if (!tmpBool.at(j))
                continue;
            tmpWeight += items.at(j).weight;
            tmpMaxCost += items.at(j).cost;
        }

        if (tmpWeight < maxWeight && tmpMaxCost > maxCost) {
            maxCost = tmpMaxCost;
            indexesToInclude = tmpBool;
        }
        int i = 0;
        while (tmpBool.at(i) == true){
            tmpBool.at(i) = false;
            i++;
        }
        tmpBool.at(i) = true;
    }

    copy_if(items.begin(), items.end(), back_inserter(optimalItemsSet),
    [&, index = 0] (const Item&) mutable {return indexesToInclude[index++]; });

    return optimalItemsSet;
}

void printResult(vector<Item> &result) {
    for (auto [cost, weight] : result)
        cout << "Item cost: " << cost << " Item weight: " << weight << endl;

    int totalCost = accumulate(result.begin(), result.end(), 0,
                               [](int sum, const Item& item) {
                                   return sum + item.cost;
                               });

    cout << "Max weight: " << totalCost << endl;
}

int main() {
    int maxWeight = 12;

    auto items = getItems();
    auto result = getOptimalItemsSet(maxWeight, items);

    printResult(result);
}