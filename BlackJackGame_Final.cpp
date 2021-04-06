// BlackJackGame.cpp
//

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cassert>
#include <sstream>
using namespace std;


class Card
{

	
public:
	enum suit { HEARTS, SPADES, CLUBS, DIAMONDS }; // Масть карты. 	 
	enum card_value { ACE = 1, TWO , THREE, FOUR, FIVE , SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};

	
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
	int GetValue() 
	{
		if ((Value == KING) || (Value == QUEEN) || (Value == JACK))

		return 10;

		else
			return Value;
		

	};
	bool GetShirt() const
	{
		return shirt;
	};

	

	//	 Написать перегрузку оператора вывода для класса Card.Если карта перевернута рубашкой вверх(мы ее не видим), 
	//	 вывести ХХ, если мы ее видим, вывести масть и номинал карты.
	//	 Также для класса GenericPlayer написать перегрузку оператора вывода, который должен отображать имя игрока и его карты, а также общую сумму очков его карт.

	friend ostream& operator<< (ostream& out, const Card& card)	
	{

		if (card.shirt == true) // елси true --shirt(рубашкой вверх)
			out << "XX";
		else
		{
			
			
			
			if (card.Value == 1)
				cout << "ACE ";
			else if (card.Value == 2)
				cout << "TWO ";
			else if (card.Value == 3)
				cout << "THREE ";
			else if (card.Value == 4)
				cout << "FOUR ";
			else if (card.Value == 5)
				cout << "FIVE ";
			else if (card.Value == 6)
				cout << "SIX ";
			else if (card.Value == 7)
				cout << "SEVEN ";
			else if (card.Value == 8)
				cout << "EIGHT ";
			else if (card.Value == 9)
				cout << "NINE ";
			else if (card.Value == 10)
				cout << "TEN ";
			else if (card.Value == 11)
				cout << "JACK ";
			else if (card.Value == 12)
				cout << "QUEEN ";
			else if (card.Value == 13)
				cout << "KING ";


			if (card.Suit == 0)
				cout << "HEARTS";
			else if (card.Suit == 1)
				cout << "SPADES";
			else if (card.Suit == 2)
				cout << "CLUBS";
			else if (card.Suit == 3)
				cout << "DIAMONDS";
		}

		return out;
	};

protected:


	bool shirt; // булево shirt, елси true -- shirt(рубашкой вверх). иначе  false -- картинкой вверх.

	suit Suit;      // масть карты
		 //  bool shirt;    // можно тоже  enum?
	card_value Value; // значение карты  - value
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
	GenericPlayer() : m_name("House")
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


	friend ostream& operator<< (ostream& out, const GenericPlayer& player)
	{
		out << endl << player.m_name << "  score: " << player.GetValueHand() << "  ";

		if (player.card_hand.empty() != true)
			{
				vector<Card*>::const_iterator it;
				for (it = player.card_hand.begin(); it != player.card_hand.end(); ++it)
				{
					if (player.card_hand.empty() != true)
						out << *(*it) << "  ";

				}

				return out;
			}

		else 
			{
			out << "Hand emty";
					return out;
			}

	};
};



// Реализовать класс House, который представляет дилера. Этот класс наследует от класса GenericPlayer. У него есть 2 метода:
// virtual bool IsHitting() const - метод указывает, нужна ли дилеру еще одна карта.Если у дилера не больше 16 очков, то он берет еще одну карту.
// void FlipFirstCard() - метод переворачивает первую карту дилера.

class House : public GenericPlayer
{

public:
	virtual ~House()
	{};
	bool IsHitting() const override
	{ 
		if (GetValueHand() <= 16)  // проверяем кол-во очков, меньше или рано 16 - еще карту.
			return true;  // возвращаем тру - значит дилер должен взять карту. 
		else
			return false; //  как только наберёт 17 очков или выше	
	};

	void FlipFirstCard() 
	{		
			card_hand[0]->Flip(); //перевернет первую карту 
	};


};
//	Реализовать класс Player, который наследует от класса GenericPlayer.У этого класса будет 4 метода:
//	virtual bool IsHitting() const - реализация чисто виртуальной функции базового класса. Метод спрашивает у пользователя, нужна ли ему еще одна карта и возвращает ответ пользователя в виде true или false.
//	void Win() const - выводит на экран имя игрока и сообщение, что он выиграл.
//	void Lose() const - выводит на экран имя игрока и сообщение, что он проиграл.
//	void Push() const - выводит на экран имя игрока и сообщение, что он сыграл вничью.

class Player : public GenericPlayer
{
public:
	Player(string s) : GenericPlayer(s)
	{};

	virtual ~Player()
	{};
	bool IsHitting() const override
	{
		bool r;
		char question;

		while (1)
		{	
			cout << endl << m_name << " ";
			cout << "need a card? enter Y or N" << endl; // Зададим вопрос 
			
			cin >> question; // пользователь введет символ
			
			r = isalpha(question);  // теперь я умею проверять веденный символ

			if (r == true) // если получен символ проверим какой из 
			{
				if ((question == 'Y') || (question == 'y'))
				{
					return true;
					break; // незабыть разорвать цикл
				}					
				if ((question == 'N') || (question == 'n'))
					return false;
					break;
			}
		}
	};


	void Win() const 
	{
		cout << m_name << " Win !" << endl;
	};
	void Lose() const
	{
		cout << m_name << " Lose !" << endl;
	};
	void Push() const
	{
		cout << m_name << " Draw !" << endl;
	};


};

// 3. Создать класс Deck, который наследует от класса Hand и представляет собой колоду карт.Класс Deck имеет 4 метода:
// vold Populate() - Создает стандартную колоду из 52 карт, вызывается из конструктора.
// void Shuffle() - Метод, который тасует карты, можно использовать функцию из алгоритмов STL random_shuffle
// vold Deal(Hand& aHand) - метод, который раздает в руку одну карту
// void AddltionalCards(GenericPlayer& aGenerlcPlayer) - раздает игроку дополнительные карты до тех пор, пока он может и хочет их получать
// Обратите внимание на применение полиморфизма.В каких методах применяется этот принцип ООП ?

class Deck : public Hand
{
public: 
	Deck()
	{};
	virtual ~Deck()
	{};

	void Populate()
	{
		
		for (int s = Card::HEARTS; s <= Card::DIAMONDS; ++s)
		{
			for (int val = Card::ACE; val <= Card::KING; ++val)
			{
				AddHand(new Card(false, static_cast<Card::suit>(s), static_cast<Card::card_value>(val)));  // рука коллекция принимает все 52 крты (т.е. колода)
			}
		}
		
	};
	void Shuffle()
	{
		random_shuffle(card_hand.begin(), card_hand.end());
	};

	void Deal(Hand& aHand) // раздает карты конкретному игроку
	{
		if (!(card_hand.empty()))
		{
			aHand.AddHand((card_hand.back())); 
			card_hand.pop_back();
		}
		else
		{
			cout << "Out of cards. Unable to deal.";
		}

	};
	void AddltionalCards(GenericPlayer& aGenerlcPlayer)
	{
		while (!(aGenerlcPlayer.IsBoosted()) && aGenerlcPlayer.IsHitting())
		{
			Deal(aGenerlcPlayer);
			cout << aGenerlcPlayer << endl;

			if (aGenerlcPlayer.IsBoosted())
			{
				aGenerlcPlayer.Bust();
			}
			

		}

	};

};
// Реализовать класс Game, который представляет собой основной процесс игры.У этого класса будет 3 поля:
// колода карт, рука дилера, вектор игроков.
// Конструктор класса принимает в качестве параметра вектор имен игроков и создает объекты самих игроков.В конструкторе создается колода карт и затем перемешивается.
// Также класс имеет один метод play().В этом методе раздаются каждому игроку по две стартовые карты, а первая карта дилера прячется.Далее выводится на экран информация о картах каждого игра, в т.ч.и для дилера.Затем раздаются игрокам дополнительные карты.Потом показывается первая карта дилера и дилер набирает карты, если ему надо.После этого выводится сообщение, кто победил, а кто проиграл.В конце руки всех игроков очищаются.



class Game
{
protected:
	Deck m_Deck;
	House m_House;
	vector<Player> m_Players;

public:
	Game(const vector<string>& names)
	{
		// создает вектор игроков из вектора с именами
		vector<string>::const_iterator pName;
		for (pName = names.begin(); pName != names.end(); ++pName)
		{
			m_Players.push_back(Player(*pName));
		}

		// запускает генератор случайных чисел
		srand(static_cast<unsigned int>(time(0)));
		m_Deck.Populate();
		m_Deck.Shuffle();
	}

	~Game()
	{};

	void Play()
	{
		{
			// раздает каждому по две стартовые карты
			vector<Player>::iterator pPlayer;
			for (int i = 0; i < 2; ++i)
			{
				for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
				{
					m_Deck.Deal(*pPlayer);
				}
				m_Deck.Deal(m_House);
				
			}

			// прячет первую карту дилера
			m_House.FlipFirstCard();

			// открывает руки всех игроков
			for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
			{
				cout << *pPlayer << endl;
			}
			cout << m_House << endl;

			// раздает игрокам дополнительные карты
			for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
			{
				m_Deck.AddltionalCards(*pPlayer);

			}

			// показывает первую карту дилера
			m_House.FlipFirstCard();
			cout << endl << m_House;

			// раздает дилеру дополнительные карты
			m_Deck.AddltionalCards(m_House);

			if (m_House.IsBoosted())
			{
				// все, кто остался в игре, побеждают
				for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
				{
					if (!(pPlayer->IsBoosted()))
					{
						pPlayer->Win();
					}
				}
			}
			else
			{
				// сравнивает суммы очков всех оставшихся игроков с суммой очков дилера
				for (pPlayer = m_Players.begin(); pPlayer != m_Players.end();
					++pPlayer)
				{
					if (!(pPlayer->IsBoosted()))
					{
						if (pPlayer->GetValueHand() > m_House.GetValueHand())
						{
							pPlayer->Win();
						}
						else if (pPlayer->GetValueHand() < m_House.GetValueHand())
						{
							pPlayer->Lose();
						}
						else
						{
							pPlayer->Push();
						}
					}
				}

			}

			// очищает руки всех игроков
			for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer)
			{
				pPlayer->ClearHand();
			}
			m_House.ClearHand();
		}

		

	};



};

int main()
{

	cout << "\t\tWelcome to Blackjack!\n\n";

	int numPlayers = 0;
	while (numPlayers < 1 || numPlayers > 7)
	{
		cout << "How many players? (1 - 7): ";
		cin >> numPlayers;
	}

	vector<string> names;
	string name;
	for (int i = 0; i < numPlayers; ++i)
	{
		cout << "Enter player name: ";
		cin >> name;
		names.push_back(name);
	}

	cout << endl;

	// игровой цикл
	Game aGame(names);
	char again = 'y';
	while (again != 'n' && again != 'N')
	{
		
		aGame.Play();
		cout << endl << "Do you want to play again? (Y/N): ";
		cin >> again;
	}
	
		

	return 0;
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
