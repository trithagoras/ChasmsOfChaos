#include "container.h"
#include "item.h"
#include "contentprovider.h"
#include <iostream>

void ItemContainer::add_item(const std::string& itemName, int amt) {
	std::cout << "Added " << amt << " " << itemName << " to inventory." << std::endl;
	// check if item already exists in map. If it does, then we can just increment amt.
	if (internalDs.contains(itemName)) {
		internalDs[itemName].second += amt;
		std::cout << "You now have " << internalDs[itemName].second << " " << itemName << "." << std::endl;
		return;
	}

	auto& content = ContentProvider::get_instance();
	auto& item = content.get_item(itemName);
	auto itemp = std::make_unique<Item>(item);
	internalDs[itemName] = std::make_pair(std::move(itemp), amt);
}
void ItemContainer::remove_item(const std::string& itemName, int amt) {
	std::cout << "Removed " << amt << " " << itemName << " from inventory." << std::endl;
	// if item not in map, ignore and return early
	if (!internalDs.contains(itemName)) {
		return;
	}

	internalDs[itemName].second -= amt;
	std::cout << "You now have " << internalDs[itemName].second << " " << itemName << "." << std::endl;
	if (internalDs[itemName].second < 1) {
		std::cout << "Deleted " << itemName << " from inventory." << std::endl;
		internalDs.erase(itemName);
	}
}