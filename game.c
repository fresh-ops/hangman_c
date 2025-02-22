#pragma once

#include "ui_service.h"
#include "word_service.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int get_random(int max){
    int res = rand() % max;
    return res;
};

int select_category(categories_t *categories){
    printf("Choose category: ");
    for (int i = 0; i < categories->categories_cnt; i++){
        printf("%d) %s\n",i ,categories->category_words[i].category);
    }
    int res;
    scanf("%d", res);
    return res;
};

int select_level(){
    printf("Choose level: 0 - easy, 1 - medium, 2 - hard");
    int res;
    scanf("%d", res);
    return res;
};

void initialize_game(game_t *game, categories_t *categories) {
    int categoryInd = select_category(categories);
    category_words_t category = categories->category_words[categoryInd];
    strcpy(game->category, category.category);
    game->level = select_level();
    words_level_t level = category.words_lvls[game->level];
    int max = level.words_cnt; // где взять
    int wordInd = get_random(max);
    strcpy(game->word, level.words[wordInd]);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        game->chosen_alphas[i] = '.';
    }
    for (int i = 0; i < MAX_WORD_LEN; i++) {
        game->guessed_word[i] = '_';
    }
    game->tries_left = MAX_TRIES;
    game->hangman_state = MAX_TRIES;
}

void check_guess(game_t *game, char guess){
    int guessed = 0;
    for (int i = 0; i < strlen(game->word);i++){
        if (guess == game->word[i]){
            game->guessed_word[i] = guess;
            guessed = 1;
        }
    }
    if (!guessed) {
        game->tries_left--;
        game->hangman_state--;
    }
    
};

int is_game_won(game_t *game){
    if (!strcmp(game->word, game->guessed_word) && game->hangman_state != 0){ return 1;}
    else return 0;
}

void play_game(game_t *game){
    while (!is_game_won(game) || game->tries_left != 0){
        printf("Введите букву");
        char ltr;
        scanf("%c", &ltr);
        check_guess(&game, ltr);
    }
    printf("Игра окончена\n");
    if (is_game_won(game)) {
        printf("Вы выиграли\n");
    } else {
        printf("Вы проиграли. Загаданное слово %s\n", game->word);
    }
}