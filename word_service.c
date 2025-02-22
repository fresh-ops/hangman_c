#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "global.h"
#include "word_service.h"

categories_t load_categories(const char *filename){
	categories_t categories;
	int level;
	FILE *file = fopen(filename,"r");

	fscanf(file,"%d",&categories.categories_cnt);
	for(int i = 0; i < categories.categories_cnt;i++){
		fscanf(file,"%s",&categories.category_words[i].category);
		for(int j = 0; j < MAX_LVL; j++){
			fscanf(file,"%d",&level);
			fscanf(file,"%d",&categories.category_words[i].words_lvls[level].words_cnt);
			for(int k = 0; k < categories.category_words[i].words_lvls[level].words_cnt; k++){
				fscanf(file,"%s",categories.category_words[i].words_lvls[level].words[k]);
			}
		}
	}
	
	return categories;
}