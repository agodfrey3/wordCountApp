// Andrew Godfrey
// Word Count / Dictionary Final
// 11/25/2016
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

template<class Type>
class hashTable {
public:
	hashTable(int size = 1000) 
	{
		table = new Node*[size];
		for (int i = 0; i < size; i++)
			table[i] = NULL;
		initDict();
		numWords = 0;
	}
	void initDict()
	{
		ifstream file;
		file.open("C:\\users\\god\\desktop/dictionary.txt");
		if (file)
		{
			string word;
			while (file >> word)
			{
				dictionary.push_back(word);
				setupTable(word, hash(word));
			}
			file.close();
			cout << "Dictionary Initialized successfully!\n";
		}
		else
			cout << "File not found!\n";
	}
	void displayDictionary()
	{
		cout << "\nDictionary: \n";
		for(int i = 0; i < dictionary.size(); i++)
			cout << dictionary[i] << endl;
		cout << endl;
	}
	string mostCommon()
	{
		int max = 0;
		string common;
		for (int i = 0; i < 1000; i++)
		{
			if (table[i] != NULL)
			{
				if (table[i]->next == NULL)
				{
					cout << table[i]->data << ':' << table[i]->count << endl;
					if (table[i]->count > max)
					{
						max = table[i]->count;
						common = table[i]->data;
					}
				}
				else
				{
					Node * tmp = table[i];
					while (tmp != NULL)
					{
						cout << table[i]->data << ':' << table[i]->count << endl;
						if (tmp->count > max)
						{
							max = tmp->count;
							common = tmp->data;
							tmp = *tmp->next;
						}
					}
				}
			}
		}
		return common;
	}
	int hash(string s, int size = 1000)
	{
		int res = 0;
		for (char c : s)
			res += c * 7;
		return (res * 1933) % size;
	}
	void setupTable(Type s, int index)
	{
		if (table[index] == NULL)
		{
			table[index] = new Node;
			table[index]->data = s;
			table[index]->count = 0;
			table[index]->next = NULL;
		}
		else // multiple share same hash code
		{
			Node * tmp = new Node;
			tmp->data = s;
			tmp->count = 0;
			tmp->next = &table[index];
			table[index] = tmp;
		}
	}
	void countWords()
	{
		ifstream file;
		file.open("C:\\users\\god\\desktop/book.txt");
		if (file.is_open())
		{
			string word;
			while (!file.eof())
			{
				while (file >> word)
				{
					if (table[hash(word)]) // this spot contains a word ( it should )
					{
						if (table[hash(word)]->next == NULL && table[hash(word)]->data == word) // no collisions
							table[hash(word)]->count++; // increment the count
						else if(table[hash(word)]->next != NULL)
						{
							Node * tmp = table[hash(word)];
							while (tmp && tmp->data != word) // finds the matching word ( there are other words with the same hash code)
								tmp = *tmp->next;
							if (tmp)
								tmp->count++; // increment the count
						}
					}
				}
			}
			file.close();
		}
		else
			cout << "File not found\n";
	}
private:
	struct Node {
		Type data;
		int count;
		Node** next;
	};
	Node ** table;
	vector<string> dictionary;
	int numWords;
};

int main()
{
	hashTable<string> dictCount; // creates a hash table and initializes it to search for all words in a given dictionary
	dictCount.displayDictionary();
	dictCount.countWords();
	cout << "Most commonly used word: " << dictCount.mostCommon() << endl;
	return 0;
}