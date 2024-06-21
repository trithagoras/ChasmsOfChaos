#pragma once
#include <map>
#include "item.h"
#include <memory>

template <class T>
class Container {
protected:
	virtual void add_item(const std::string& itemName, int amt) = 0;	// todo: there should be a result in the instance where you can pick up some but not all items due to inventory space
	virtual void remove_item(const std::string& itemName, int amt) = 0;	// todo: as above
	std::map<std::string, std::pair<std::unique_ptr<T>, int>> internalDs;	// name -> (Item*, qty)
};

class ItemContainer : public Container<Item> {
public:
	void add_item(const std::string& itemName, int amt) override;
	void remove_item(const std::string& itemName, int amt) override;
};