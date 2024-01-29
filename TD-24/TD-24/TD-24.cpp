// TD-24.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#include <iostream>
#include <memory>

template<class T>
class unique_ptr_custom
{
private:
	std::unique_ptr<T> m_ptr;
public:
	unique_ptr_custom() {}
	unique_ptr_custom(T _value) { m_ptr = std::make_unique<T>(_value); }
	~unique_ptr_custom() {}

	auto& get_ptr() { return m_ptr; }

	template<typename T>
	friend std::ostream& operator<<(std::ostream& os, const unique_ptr_custom<T>& uptr);
};
template<typename T>
std::ostream& operator<<(std::ostream& os, const unique_ptr_custom<T>& uptr)
{
	if (uptr.m_ptr != nullptr)
		return os << *uptr.m_ptr;
	else
		return os << "nullptr";
}

void Exo1()
{
	std::unique_ptr<int> tmp_int_ptr = std::make_unique<int>(30);

	std::cout << "Simple unique ptr de int : " << *tmp_int_ptr << std::endl;

	unique_ptr_custom truc(30);

	unique_ptr_custom <int>zizi;

	std::cout << "Classe de unique ptr de int : " << truc << std::endl;

	std::cout << "Classe de unique ptr de int pas init : " << zizi << std::endl;
	
	//zizi.get_ptr() = truc.get_ptr();

	//Je remarque qu'il n'est pas possible de copier un unique_ptr
	//En revanche il est possible de transféré la valeur dans un autre unique_ptr
	zizi.get_ptr() = std::move(truc.get_ptr());

	std::cout << "Inversion des deux valeurs : " << truc << std::endl;

	std::cout << "Inversion des deux valeurs : " << zizi << std::endl;
}

class Super_Objet
{
public:
	Super_Objet() : m_first_int(10), m_second_int(20), m_third_int(30) {}
	~Super_Objet() {}
	
	int m_first_int;
	int m_second_int;
	int m_third_int;
private:
	
};

void Exo2()
{
	Super_Objet tmp_super_objet;

	std::cout << "Before using the ptr : " << tmp_super_objet.m_first_int << " " << tmp_super_objet.m_second_int << " " << tmp_super_objet.m_third_int << std::endl;

	std::shared_ptr<Super_Objet*> first_ptr = std::make_shared<Super_Objet*>(&tmp_super_objet);
	std::shared_ptr<Super_Objet*> second_ptr = std::make_shared<Super_Objet*>(&tmp_super_objet);
	std::shared_ptr<Super_Objet*> third_ptr = std::make_shared<Super_Objet*>(&tmp_super_objet);

	(*first_ptr)->m_first_int = 100;
	(*second_ptr)->m_second_int = 200;
	(*third_ptr)->m_third_int = 300;

	std::cout << "After using the ptr : " << tmp_super_objet.m_first_int << " " << tmp_super_objet.m_second_int << " " << tmp_super_objet.m_third_int << std::endl;
}

template<class F, class S, class T>
struct Random_Struct
{
	std::shared_ptr<F> m_first_ptr;
	std::shared_ptr<S> m_second_ptr;
	std::shared_ptr<T> m_third_ptr;
};

void Exo3()
{
}

void Exo4()
{
}

int main()
{
	Exo1();

	Exo2();

	Exo3();

	Exo4();
}
