#include <iostream>
#include<string.h>

using namespace std;

struct words_stats
{
	int deleted_words;
	int remaining_words;
};

words_stats Dop(char str[], char word[]);
bool is_word(char next_last_ch);

int main()
{
	char str[1000];
	char wrd[100];
	cout << "Enter string: ";
	gets_s(str);
	cout << "Enter word: ";
	gets_s(wrd);

	words_stats cur_words_stats = Dop(str, wrd);

	cout << "Deleted words: " << cur_words_stats.deleted_words << endl;
	cout << "Remaining words: " << cur_words_stats.remaining_words << endl;

}

words_stats Dop(char str[], char word[])
{
	words_stats words_stats = { 0, 0 };

	int word_len = strlen(word);
	int str_len = strlen(str);

	for (int i = 0; i < str_len; i++)
	{
		if (strncmp(&str[i], word, word_len) == 0 && (str[i - 1] == ' ' || i == 0) && (is_word(str[i + word_len]) || str[i + word_len] == '\0'))
		{
			words_stats.deleted_words++;

			for (int j = 0; j < word_len; j++)
			{
				for (int k = i + 1; k <= str_len; k++)
				{
					str[k - 1] = str[k];
				}
				str_len--;
			}

		}
	}

	cout << "Result: ";
	puts(str);

	char* cn = nullptr;
	char* wrd;
	char dlm[] = " ,.?:;()";

	wrd = strtok_s(str, dlm, &cn);

	while (wrd != NULL)
	{
		words_stats.remaining_words++;
		wrd = strtok_s(NULL, dlm, &cn);
	}

	return words_stats;
}

bool is_word(char next_last_ch)
{
	char dlms[] = " ,.?:;()";

	for (char dlm : dlms)
	{
		if (next_last_ch == dlm)
		{
			return true;
		}
	}

	return false;
}
