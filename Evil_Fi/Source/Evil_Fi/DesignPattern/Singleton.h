#pragma once

template < typename T >
class TSingleton
{
protected:
	TSingleton()
	{

	}
	virtual ~TSingleton()
	{

	}

public:
	static T* GetInstance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new T;
		return m_pInstance;
	};

	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	};

private:
	static T* m_pInstance;
};

template <typename T> T* TSingleton<T>::m_pInstance = nullptr;