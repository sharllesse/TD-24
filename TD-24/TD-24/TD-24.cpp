// TD-24.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#include <iostream>
#include <memory>

#pragma region EXO1
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

	unique_ptr_custom tmp_first_ptr(30);

	unique_ptr_custom <int>tmp_second_ptr;

	std::cout << "Classe de unique ptr de int : " << tmp_first_ptr << std::endl;

	std::cout << "Classe de unique ptr de int pas init : " << tmp_second_ptr << std::endl;

	//zizi.get_ptr() = truc.get_ptr();

	//Je remarque qu'il n'est pas possible de copier un unique_ptr
	//En revanche il est possible de transféré la valeur dans un autre unique_ptr
	tmp_second_ptr.get_ptr() = std::move(tmp_first_ptr.get_ptr());

	std::cout << "Inversion des deux valeurs : " << tmp_first_ptr << std::endl;

	std::cout << "Inversion des deux valeurs : " << tmp_second_ptr << std::endl;
}
#pragma endregion

#pragma region EXO2
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
#pragma endregion

#pragma region EXO3
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
#pragma endregion

#pragma region EXO4
#include <vector>

class Item
{
public:
	Item() : m_name("Empty") {}
	Item(std::string _name) : m_name(_name) {}
	~Item() {}

	std::string& get_name() { return m_name; }
private:
	std::string m_name;
};

class Inventory
{
private:
	typedef std::vector<std::unique_ptr<Item>> grid;
	std::vector<std::unique_ptr<Item>> m_grid;
public:
	Inventory() {}
	Inventory(int _case_cout) {
		for (int i = 0; i < _case_cout; i++)
		{
			m_grid.push_back(std::make_unique<Item>());
		}
	}
	~Inventory() {}

	grid& get_grid() { return m_grid; }
};

class Player
{
public:
	Player() : m_inventory(std::make_unique<Inventory>(10)), m_hand_item(std::make_unique<Item>("Hand")) {}
	~Player() {}

	void give_item(int _inventory_case, std::string _name)
	{
		if (_inventory_case < static_cast<int>(m_inventory->get_grid().size()))
			m_inventory->get_grid().at(_inventory_case)->get_name() = _name;
	}

	void take_item_in_hand(int _inventory_case)
	{
		if (_inventory_case < static_cast<int>(m_inventory->get_grid().size()))
		{
			std::string tmp_item("");
			tmp_item = m_inventory->get_grid().at(_inventory_case)->get_name();
			m_inventory->get_grid().at(_inventory_case)->get_name() = m_hand_item->get_name();
			m_hand_item->get_name() = tmp_item;

			if (m_hand_item->get_name() != "Hand")
				std::cout << "You have taken " << tmp_item << " in hand" << std::endl;
			else
				std::cout << "You have nothing in hand" << std::endl;

			if (m_inventory->get_grid().at(_inventory_case)->get_name() == "Hand")
				m_inventory->get_grid().at(_inventory_case)->get_name() = "Empty";

			if (m_hand_item->get_name() == "Empty")
				m_hand_item->get_name() = "Hand";
		}
	}
private:
	std::unique_ptr<Inventory> m_inventory;
	std::unique_ptr<Item> m_hand_item;
};

void Exo4()
{
	Player player;
	player.give_item(0, "Hache");
	player.take_item_in_hand(0);
	player.take_item_in_hand(0);
}
#pragma endregion

int main()
{
	Exo1();

	Exo2();

	Exo3();

	Exo4();
}
