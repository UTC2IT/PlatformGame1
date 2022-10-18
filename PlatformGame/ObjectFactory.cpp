#include"stdafx.h"
#include "ObjectFactory.h"
ObjectFactory* ObjectFactory::sInstance = nullptr;

Entity* ObjectFactory::CreateObject(std::string type, Properties* props)
{
	Entity* object = nullptr;

	auto it = mTypeRegistry.find(type);//tìm type class 


	if (it != mTypeRegistry.end())
	{ //chạy đến cuối m_TypeRegistry
		object = it->second(props);
	}
	return object;
}

void ObjectFactory::RegisterType(std::string className, std::function<Entity* (Properties* props)> type)
{
	mTypeRegistry[className] = type;
}

ObjectFactory* ObjectFactory::getInstance()
{
	return sInstance = (sInstance != nullptr) ? sInstance : new ObjectFactory();
}