/*
    hangman.cpp
        
    Method implementations for the hangman class.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author: Aidan Lamkin

    last modified: 3/7/2019
*/

#include "hangman.h"

using namespace std;

// constructor
hangman::hangman() { 
    // TODO: Read in and store words from dictionary.txt
    ifstream dictionary("dictionary.txt");
    if(!dictionary.is_open()){
        cerr << "File did not open" << endl;
    }
    while(!dictionary.eof()){
        string line;
        getline(dictionary, line);
        words.insert(line);
    }
    dictionary.close();
}


// start_new_game()
//
// Setup a new game of hangman.
void hangman::start_new_game(int num_guesses, bool see_words) {
    // TODO: Initialize game state variables
    guesses_remaining = num_guesses;
    display_word = "";
    see = see_words;
    auto it = words.begin();
    string word = *it;
    for(int i = 0; i < word.size(); i++){
        display_word += "-";
    }


}


// process_guess()
//
// Process a player's guess - should return true/false depending on whether
// or not the guess was in the hidden word.  If the guess is incorrect, the
// remaining guess count is decreased.
bool hangman::process_guess(char c) {
    guessed_chars.insert(c);
    set<string> families;
    string pattern = "";
    for(string word: words){
        pattern = "";
        for(int i = 0; i < word.size(); i++){
            if(word[i] == c){
                pattern += c;
            }
            else if(word[i] == display_word[i]){
                pattern += display_word[i];
            }
            else{
                pattern += '-';
            }
        }
        families.insert(pattern);
    }

    int count = 0;
    map<string, int> lengths;
    set<string> words2;
    words2 = words;
    set<string> words3 = words2;

    for(string p: families){
        words2 = words3;
        words3.clear();
        for(string word:words2){
            bool matches_pattern = true;
            for(int i = 0; i < p.size(); i++){
                if(p[i] == '-' && word[i] != c){
                    continue;
                }
                else if(word[i] == p[i]){
                    continue;
                }
                else{
                    matches_pattern = false;
                }

            }
            if(matches_pattern == true){
                count++;
            }
            else{
                words3.insert(word);
            }
        }
        lengths.insert(pair<string,int> (p, count));
        count = 0;
    }

    int max = 0;
    for(auto pair: lengths){
        if(pair.second > max){
            max = pair.second;
            display_word = pair.first;
            pattern = pair.first;
        }
    }

    if(see == true){
        cout << "Words in chosen family: " << max << endl << endl;
    }
    words2.clear();
    for(string word: words){
        bool matches_pattern = true;
        for(int i = 0; i < pattern.size(); i++){
            if(pattern[i] == '-' && word[i] != c){
                continue;
            }
            else if(word[i] == pattern[i]){
                continue;
            }
            else{
                matches_pattern = false;
            }

        }
        if(matches_pattern == true){
            words2.insert(word);
        }
    }
    words = words2;
    if(find(display_word.begin(), display_word.end(), c) != display_word.end()){
        return true;
    }
    else{
        guesses_remaining -= 1;
        return false;
    }
}


// get_display_word()
//
// Return a representation of the hidden word, with unguessed letters
// masked by '-' characters.
string hangman::get_display_word() {
    return display_word;
}


// get_guesses_remaining()
//
// Return the number of guesses remaining for the player.
int hangman::get_guesses_remaining() {
    return guesses_remaining;
}


// get_guessed_chars()
//
// What letters has the player already guessed?  Return in alphabetic order.
string hangman::get_guessed_chars() {
    string guesses;
    for(char letter: guessed_chars){
        guesses += letter;
    }
    return guesses;
}


// was_char_guessed()
//
// Return true if letter was already guessed.
bool hangman::was_char_guessed(char c) {
    for(char letter: guessed_chars){
        if(letter == c){
            return true;
        }
    }
    return false;
}


// is_won()
//
// Return true if the game has been won by the player.
bool hangman::is_won() {
    for(int i = 0; i < display_word.size(); i++){
        if(display_word[i] == '-'){
            return false;
        }
    }
    return true;
}


// is_lost()
//
// Return true if the game has been lost.
bool hangman::is_lost() {
    if(guesses_remaining == 0 && !is_won()){
        return true;
    }
    return false;
}


// get_hidden_word
//
// Return the true hidden word to show the player.
string hangman::get_hidden_word() {
    hidden_word = *words.begin();
    return hidden_word;
}


