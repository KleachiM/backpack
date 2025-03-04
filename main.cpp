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
    int maxCost = 0;

    vector<Item> result;

    const int n = items.size() + 1;
    vector<bool> tmp(n, false);
    while (tmp.at(n - 1) != 1){
        int tmpMaxCost = 0;
        int tmpWeight = 0;
        for (int j = 0; j < items.size(); j++) {
            if (tmp.at(j) != true)
                continue;

            tmpWeight += items.at(j).weight;
            tmpMaxCost += items.at(j).cost;
        }

        if (tmpWeight < maxWeight && tmpMaxCost > maxCost) {
            maxCost = tmpMaxCost;
        }

        int i = 0;
        while (tmp.at(i) == 1){
            tmp.at(i) = false;
            i++;
        }
        tmp.at(i) = true;
    }

		copy_if(items.begin(), items.end(), back_inserter(result),
		[&, index = 0] (const Item&) mutable {return tmp[index++]; });

    return result;
}

int main() {
    int maxWeight = 12;

    auto items = getItems();
    auto result = getOptimalItemsSet(maxWeight, items);

		for (auto [cost, weight] : result)
			cout << "Item cost: " << cost << " Item weight: " << weight << endl;

		/*int totalCost = std::accumulate(result.begin(), result.end(), 0, 
                                    [](int sum, const Item& item) {
                                        return sum + item.cost;
                                    });*/
}
