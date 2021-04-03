// BlackJackGame.cpp
//

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cassert>
using namespace std;

enum suit { HEARTS, SPADES, CLUBS, DIAMONDS }; // Масть карты. 	 
enum card_value { ACE = 1, KING = 10, QUEEN = 10, JACK = 10, TEN = 10, NINE = 9, EIGHT = 8, SEVEN = 7, SIX = 6, FIVE = 5, FOUR = 4, THREE = 3, TWO = 2 };

class Card
{
protected:
	bool shirt; // булево shirt, елси true -- shirt(рубашкой вверх). иначе  false -- картинкой вверх.
	
	suit Suit;      // масть карты
		 //  bool shirt;    // можно тоже  enum?
	card_value Value; // значение карты  - value
public:

	

	Card(bool shi, suit sui, card_value val) : shirt(shi), Suit(sui), Value(val)
	{};
	~Card()
	{};

	void Flip()
	{
		if (shirt == true)// рубашка = true  - рубашкой вверх  
		{
			shirt = false; // переварачивем картинкой вверх
		}
		else // было картинкой вверх
		{
			shirt = true;  // переварачивем  рубашкой вверх
		}
	};
	card_value GetValue() const
	{
		return Value;
	};
	bool GetShirt() const
	{
		return shirt;
	};

	void Print_card()  // Проверить что получилось.
	{
		cout << "shirt up?: " << shirt << endl;
		if (Suit == 0)
		{
			cout << "Suit: HEARTS " << Suit << endl;
		}
		if (Suit == 1)
		{
			cout << "Suit: SPADES " << Suit << endl;
		}
		if (Suit == 2)
		{
			cout << "Suit: CLUBS " << Suit << endl;
		}
		if (Suit == 3)
		{
			cout << "Suit: DIAMONDS " << Suit << endl;
		}

		cout << "Value: " << Value << endl;
		cout << endl;

	};

};
class Hand
{

protected:
	vector <Card*> card_hand;

public:

	Hand() : card_hand(0)
	{

	};
	virtual ~Hand()
	{};

	void AddHand(Card* cd)  //этот метод будет добавлять указатель в конец вектора.
	{

		card_hand.push_back(cd);
	};

	void ClearHand() //этот метод который буудет очищать руку от карт
	{
		assert(card_hand.size() >= 0);

		vector<Card*>::iterator it = card_hand.begin();
		for (it = card_hand.begin(); it != card_hand.end(); ++it)
		{
			delete* it;
			*it = 0;
		}

		card_hand.clear();
		
		
	};
	bool GetShirt(Card* n) const
	{
		return  n->GetShirt();
	};


	int GetValueHand() const //  возвращает сумму очков карт руки, 
	{
		//для того чтобы дать сумму очков сложим все эл.ты вектора. 
		int Scoring_points = 0;
		
		bool ace = 0;


		if (card_hand.empty())
		{
			return 0;
		}
			
		vector<Card*>::const_iterator it;
		for (it = card_hand.begin(); it != card_hand.end(); it++)
		{


			if ((*it)->GetShirt() == 1)  // есликарта лежат рубашкой вверх --   + 0 очков
			{
				Scoring_points += 0;
			}
			else
			{

				Scoring_points += (*it)->GetValue();
			}
		}
			for (it = card_hand.begin(); it != card_hand.end(); ++it)
			{
				if ((*it)->GetValue() == 1)
				{
					ace = 1;
				}
				// если рука держит туз и сумма довольно маленькая, туз дает 11 очков
				if (ace && Scoring_points <= 11)
				{
					// добавляем только 10 очков, поскольку мы уже добавили
					// за каждый туз по одному очку
					Scoring_points += 10;
					ace = 0;
				}
			}

			

				
			
		

		return Scoring_points;   // возвращаем сумму очков.

		
	};

};



//  Создать класс GenericPlayer, в который добавить поле name - имя игрока.Также добавить 3 метода:
//	IsHitting() - чисто виртуальная функция, возвращает информацию, нужна ли игроку еще одна карта.
//	IsBoosted() - возвращает bool значение, есть ли у игрока перебор
//	Bust() - выводит на экран имя игрока и объявляет, что у него перебор.

class GenericPlayer : public Hand
{
protected:
	string m_name;

public:
	GenericPlayer() : m_name("Name")
	{};

	GenericPlayer(string name) : m_name(name)
	{};
	virtual ~GenericPlayer()
	{};


    virtual bool IsHitting() const = 0;

	bool IsBoosted() const  // Перебор
	{
		if (GetValueHand() > 21) // вызываем подсчет очков, если набрано более 21 (22 и больше), возвращаем true - перебор истина.
			return true;
		else
			return false;
	};

	void Bust()const
	{
		if (IsBoosted() == 1) // проверяем перебор и если вернулось 1, тогда выводим. 
		cout << m_name << " bust " << GetValueHand() << " points" << endl;
	};



};

int main()
{
    int  points;

	Card* card1 = new Card(false, HEARTS, KING);
	Card* card2 = new Card(false, DIAMONDS, NINE);
	Card* card5 = new Card(false, DIAMONDS, SEVEN);
	card5->Print_card();




	Hand hand1;
	hand1.AddHand(card5);
	hand1.AddHand(card2);
	hand1.AddHand(card1);
	
	
	


	cout << "in hand: ";
	


	cout << endl;
	cout << "---------" << endl;

	
	points = hand1.GetValueHand();
	cout << "points: " << points << endl;

	




	delete card1;
	delete card2;
	delete card5;
	
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
