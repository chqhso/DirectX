#ifndef GPG_SINGLETON_H
#define GPG_SINGLETON_H

template<class T>
class GPGSingleton{
	static T* m_pInstance;
public:
	GPGSingleton(){
		assert(!m_pInstance);
		int offset = (int)(T*)1 - (int)(GPGSingleton<T>*)(T*)1;
		m_pInstance = (T*)((int)this + offset);
	}
	~GPGSingleton() { assert(m_pInstance); m_pInstance = 0; }
	static T& GetInstance() { assert(m_pInstance); return (*m_pInstance); }
	static T* GetInstancePtr() { return m_pInstance; }
};

template<class T>
T* GPGSingleton<T>::m_pInstance = 0;

#endif