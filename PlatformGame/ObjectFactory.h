#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H
#include "Entity.h"

class ObjectFactory
{
private:
	ObjectFactory() {};
	static ObjectFactory* sInstance;
	std::map < std::string, std::function<Entity* (Properties* props) >> mTypeRegistry;
public:
	Entity* CreateObject(std::string type, Properties* props);
	void RegisterType(std::string className, std::function<Entity* (Properties* props)> type);//thông tin về hàm function(con trỏ hàm) std::function<tên hàm* (tham số hàm)> tên con trỏ hàm  https://howkteam.vn/course/khoa-hoc-lap-trinh-c-can-ban/con-tro-ham-trong-c-function-pointers-3916
	static ObjectFactory* getInstance();


};
template <class Type>//cho phép bạn định nghĩa một hàm, một lớp mà không cần chỉ ra đối số kiểu dữ liệu là gì. Tuỳ vào kiểu dữ liệu mà người dùng truyền vào thì nó sẽ hoạt động theo kiểu dữ liệu đó.
class Registrar
{
public:
	Registrar(std::string className);
};

#endif

template<class Type>
inline Registrar<Type>::Registrar(std::string className)
{
	ObjectFactory::getInstance()->RegisterType(className, [](Properties* props)->Entity* { return new Type(props); });//lambda function [](Properties* props)->GameObject* { return new Type(props); } hàm ẩn danh không cần định nghĩa,->GameObject là kiểu trả về của hàm lambda https://en.cppreference.com/w/cpp/language/lambda
}
