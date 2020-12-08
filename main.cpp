#include <iostream>
#include<stdlib.h>
#include<cstring>
#include<fstream>
#include <time.h>
#include<map>
#include <ctime>
#include <iomanip>

using namespace std;
int num; // number of character occurrences in case this character is found
//search function for specific character in the word then return all occurrences
int* searchInWord(char c, string word)
{
    int count=0;
    int j=0;
    int *indexs = new int[100];
    num = 0;
    for(int i=0; i<word.size(); i++)
    {
        if(c==word.at(i))
        {
            indexs[j] = i;
            j++;
            num++;
        }
    }
    return indexs;
}
// read all words from the file and return how many word found
int input(string words[])
{
    ifstream in_stream;
    in_stream.open("words.txt");
    int i=0;
    while (!in_stream.eof())
    {
        in_stream>>words[i] ;
        i++;
    }
    return i;
}

void draw_hangman(int t)
{
    switch(t)
    {
    case 6:
        cout<<endl<<endl<<
            "   +----+     "<<endl<<
            "   |    |     "<<endl<<
            "   |    O     "<<endl<<
            "   |   /|\\    "<<endl<<
            "   |   / \\   "<<endl<<
            "   |Your Dead "<<endl<<
            "  ============"<<endl<<endl;
        break;

    case 5:
        cout<<endl<<endl<<
            "   +---+  "<<endl<<
            "   |   |  "<<endl<<
            "   |   O  "<<endl<<
            "   |  /|\\ "<<endl<<
            "   |    \\ "<<endl<<
            "   |       "<<endl
            <<"  ============"<<endl<<endl;
        break;

    case 4:
        cout<<endl<<endl<<
            "   +---+  "<<endl<<
            "   |   |  "<<endl<<
            "   |   O  "<<endl<<
            "   |  /|\\ "<<endl<<
            "   |      "<<endl<<
            "   |      "<<endl<<
            "  ============="<<endl<<endl;
        break;

    case 3:
        cout<<endl<<endl<<
            "   +----+  "<<endl<<
            "   |    |  "<<endl<<
            "   |    O  "<<endl<<
            "   |   /|  "<<endl<<
            "   |       "<<endl<<
            "   |       "<<endl<<
            "  ============="<<endl<<endl;
        break;

    case 2:
        cout<<endl<<endl<<
            "   +----+  "<<endl<<
            "   |    |  "<<endl<<
            "   |    O  "<<endl<<
            "   |    |  "<<endl<<
            "   |       "<<endl<<
            "   |       "<<endl<<
            "  ============="<<endl<<endl;
        break;

    default:
        cout<<endl<<endl<<
            "   +----+  "<<endl<<
            "   |    |  "<<endl<<
            "   |       "<<endl<<
            "   |       "<<endl<<
            "   |       "<<endl<<
            "   |       "<<endl<<
            "  ============="<<endl<<endl;
    }
}

void launch_Game()
{
    // inialize all letters to unchosen case using hashmap
    map<char, int> all_alphabets;
    for(char c ='a'; c<'z'; c++)
        all_alphabets[c]=0;
    for(char c ='A'; c<'Z'; c++)
        all_alphabets[c]=0;
    int r;
    string words[50];
    //read all word from the file
    int num_counts = input(words);
    //generate random number to pick random word from the file
    srand(time(NULL));
    r  = rand() % num_counts ;
    string word  = words[r];
    string gussedWord="";
    for(int i=0; i<word.size(); i++)
        gussedWord+="-";
    cout<<"Guessed Word\n";
    // draw blank word
    cout<<gussedWord<<endl;
    // return all occurences of the word
    int trails = 1; // number of player trails
    char ch;
    do
    {
        if(gussedWord==word)
        {
            cout<<"#####################\n";
            cout<<"#       You Win     #\n";
            cout<<"#####################\n";
            break;
        }
        //insert the gussed character
        cout << "Player1: You Have "<<6-trails <<" Trails(chances for 5 Errors)\n";
        cout <<"Guess a Letter: ";
        cin>>ch;

        if(!isalpha(ch)) // check input character is alphabet or not
        {
            cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
            cout<<"X   please enter letters only [a-z] or [A-Z]    X\n";
            cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
        }
        else
        {
            if(all_alphabets[ch]==0)
            {
                all_alphabets[ch]=1;// if the character is inserted first time, mark it as inserted for the next times
                int *index = searchInWord(ch,word);
                if(num == 0) // in case character does not belong to the word
                {
                    trails++;
                    if(trails==6)
                    {
                        cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
                        cout<<"  your Trials are finished\nThe Guessed word is " << word<<"\n";
                        cout<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
                    }
                    else
                        cout<< "Sorry, Your character is not in the Guessed Word\n";
                    cout<<"Player 2:\n";
                    draw_hangman(trails);
                }
                else
                {
                    cout<<"Guessed Word\n";
                    // fill the blank word by inserted character
                    for(int i=0; i < num; i ++)
                        gussedWord[index[i]] = word[index[i]];
                    cout<<gussedWord<<endl;
                }
            }
            else
            {
                cout<<"You are choose this letter later, please choose another letter\n";
            }
        }
    }
    while(trails<6);
}

int main()
{
    cout<<"==================================\n";
    cout<<"=      H A N G M A N G A M E     =\n";
    cout<<"==================================\n";
    while(true)
    {
        launch_Game();
        cout<<"Do You Want to play Again?(y/n): ";
        char res;
        cin>>res;
        if(res =='n')
            break;
    }
}
