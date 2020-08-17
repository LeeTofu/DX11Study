#pragma once

template<typename T>
class Singleton
{
protected:
	Singleton() {};
	
	static T* instance;

public:
	static T* GetInstance();
	void Release();
};

template<typename T>
T* Singleton<T>::instance = nullptr;

template<typename T>
static T* Singleton<T>::GetInstance()
{
	if (instance == nullptr) instance = new T;
	return instance;
}

template<typename T>
void Singleton<T>::Release()
{
	if (instance)
	{
		delete instance;
		instance = null;
	}
}