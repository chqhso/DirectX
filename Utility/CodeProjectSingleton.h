#ifndef CODE_PROJECT_SINGLETON_H
#define CODE_PROJECT_SINGLETON_H

template<typename T>
class CodeProjectSingleton{
public:
	static T* Instance(){
		if (m_pInstance == nullptr) m_pInstance = new T;
		return m_pInstance;
	}
	static void DestroyInstance(){
		delete m_pInstance;
		m_pInstance = nullptr;
	}
private:
	static T* m_pInstance;
};

template<typename T> T* CodeProjectSingleton<T>::m_pInstance = 0;

#endif