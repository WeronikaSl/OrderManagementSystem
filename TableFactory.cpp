#include "TableFactory.hpp"

#include "Customers.hpp"
#include "Products.hpp"
#include "Orders.hpp"

std::unique_ptr<Table> TableFactory::getTable(TableType tableType)
{
	std::unique_ptr<Table> result{ nullptr };

	switch (tableType)
	{
	case TableType::CUSTOMERS:
		result = std::make_unique<Customers>();
		break;
	case TableType::PRODUCTS:
		result = std::make_unique<Products>();
		break;
	case TableType::ORDERS:
		result = std::make_unique<Orders>();
		break;
	//default:
		 //TODO implement error handling
	}

    return result;
}
