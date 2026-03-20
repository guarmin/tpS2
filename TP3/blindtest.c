
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "blindtest.h"

/* -------------------------------------------------- */
/* OUTILS SUR LES CHAINES                             */
/* -------------------------------------------------- */

/* Supprime les caractères de fin de ligne (\n ou \r) d'une chaîne */
void trim_newline(char *s)
{
    size_t len = strlen(s);

    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r'))
    {
        s[len - 1] = '\0';
        len--;
    }
}

/*
Normalise une chaîne :
- supprime les espaces inutiles
- convertit en minuscules
Permet de comparer deux réponses sans tenir compte
des majuscules et des espaces.
*/
void normalize_string(char *dest, const char *src)
{
    int i = 0;
    int j = 0;
    int prev_space = 0;

    while (src[i] != '\0' && isspace((unsigned char)src[i]))
    {
        i++;
    }

    while (src[i] != '\0')
    {
        unsigned char c = (unsigned char)src[i];

        if (isspace(c))
        {
            prev_space = 1;
        }
        else
        {
            if (prev_space && j > 0)
            {
                dest[j++] = ' ';
            }
            dest[j++] = (char)tolower(c);
            prev_space = 0;
        }

        i++;
    }

    dest[j] = '\0';
}

/*
Compare deux chaînes après normalisation.
Retourne 1 si elles sont équivalentes, sinon 0.
*/
int string_equals_normalized(const char *a, const char *b)
{
    char na[256];
    char nb[256];

    normalize_string(na, a);
    normalize_string(nb, b);

    return strcmp(na, nb) == 0;
}

/* -------------------------------------------------- */
/* GESTION AUDIO                                      */
/* -------------------------------------------------- */

/*
Lance la lecture d'un extrait audio avec ffplay.
start = instant de départ
seconds = durée de l'extrait
*/
void play_song_excerpt_at(const char *filename, int start, int seconds)
{
    char command[1024];

    snprintf(command, sizeof(command),
             "ffplay -nodisp -autoexit -loglevel quiet -ss %d -t %d \"%s\"",
             start, seconds, filename);

    system(command);
}
/*
Charge les morceaux depuis songs.txt dans un tableau.
Retourne le nombre de morceaux chargés.
*/
int load_songs(char filename[], Song *firstsong)
{
    FILE *f;
    char line[3 * 256];
    int count = 0;

    f = fopen(filename, "r");
    if (f == NULL)
    {
        perror("Erreur ouverture songs.txt");
        return -1;
    }

    while (fgets(line, sizeof(line), f) != NULL && count < 100)
    {
        char *file;
        char *title;
        char *artist;

        trim_newline(line);

        if (strlen(line) == 0)
        {
            continue;
        }

        file = strtok(line, ";");
        title = strtok(NULL, ";");
        artist = strtok(NULL, ";");

        if (file == NULL || title == NULL || artist == NULL)
        {
            printf("Ligne ignoree dans songs.txt.\n");
            continue;
        }

        strcpy(firstsong->filename, file);
        strcpy(firstsong->title, title);
        strcpy(firstsong->artist, artist);
        firstsong->next = malloc(sizeof(Song));
        firstsong = firstsong->next;

        count++;
    }

    fclose(f);
    return count;
}

void swap_song(int number_song, Song *firstsong, int pos1, int pos2)
{
    if (pos1 == pos2)
    {
        return;
    }
    Song *song1;
    Song *song2;
    Song *current = firstsong;

    for (int i = 0; i < number_song; i++)
    {
        if (i == pos1)
            song1 = current;
        if (i == pos2)
            song2 = current;
        current = current->next;
    }
    char tmp_filename[100];
    char tmp_title[100];
    char tmp_artist[100];

    strcpy(tmp_filename, song1->filename);
    strcpy(tmp_title, song1->title);
    strcpy(tmp_artist, song1->artist);

    strcpy(song1->filename, song2->filename);
    strcpy(song1->title, song2->title);
    strcpy(song1->artist, song2->artist);

    strcpy(song2->filename, tmp_filename);
    strcpy(song2->title, tmp_title);
    strcpy(song2->artist, tmp_artist);
}
void change_song(int number_song, Song *firstsong)
{
    for (int i = 0; i < number_song * 5; i++)
    {
        int pos1 = rand() % (number_song - 1);
        int pos2 = rand() % (number_song - 1);
        if (pos1 == pos2)
        {
            return;
        }
        Song *song1;
        Song *song2;
        Song *current = firstsong;

        for (int i = 0; i < number_song; i++)
        {
            if (i == pos1)
                song1 = current;
            if (i == pos2)
                song2 = current;
            current = current->next;
        }
        char tmp_filename[100];
        char tmp_title[100];
        char tmp_artist[100];

        strcpy(tmp_filename, song1->filename);
        strcpy(tmp_title, song1->title);
        strcpy(tmp_artist, song1->artist);

        strcpy(song1->filename, song2->filename);
        strcpy(song1->title, song2->title);
        strcpy(song1->artist, song2->artist);

        strcpy(song2->filename, tmp_filename);
        strcpy(song2->filename, tmp_title);
        strcpy(song2->artist, tmp_artist);
    }
}
int load_score(char filename[], player *firstplayer)
{
    FILE *f;
    char line[3 * 256];
    int count = 0;

    f = fopen(filename, "r");
    if (f == NULL)
    {
        perror("Erreur ouverture scores.txt");
        return 0;
    }

    while (fgets(line, sizeof(line), f) != NULL && count < 100)
    {
        char *name;
        int score;

        trim_newline(line);

        if (strlen(line) == 0)
        {
            continue;
        }

        name = strtok(line, ";");
        score = atoi(strtok(NULL, ";"));

        if (name == NULL || score == 0)
        {
            printf("Ligne ignoree dans scores.txt.\n");
            continue;
        }

        strcpy(firstplayer->name, name);
        firstplayer->score = score;
        firstplayer->next = malloc(sizeof(player));
        firstplayer = firstplayer->next;

        count++;
    }

    fclose(f);
    return count;
}

void update_score(int number_player, player *firstplayer, char playername[], int newscore)
{
    player *current = firstplayer;
    for (int i = 0; i < number_player; i++)
    {
        if (strcmp(playername, current->name) == 0)
        {
            current->score = newscore;
        }
        current = current->next;
    }
}
void save_scores(char nomfichier[], int number_player, player *firstplayer)
{
    FILE *f;
    f = fopen(nomfichier, "w");
    player *current = firstplayer;
    for (int i = 0; i < number_player; i++)
    {
        fprintf(f, "%s;%d\n", current->name, current->score);
        current = current->next;
    }
}
void afficher_scores(int number_player, player *firstplayer)
{
    char name[100][100];
    int scores[100];
    player *current = firstplayer;
    for (int i = 0; i < number_player; i++)
    {
        strcpy(name[i], current->name);
        scores[i] = current->score;
        current = current->next;
    }
    for (int i = 1; i < number_player; i++)
    {
        int tmp_score = scores[i];
        char tmp_name[100];
        strcpy(tmp_name, name[i]);
        int j = i - 1;
        while (j >= 0 && scores[j] > tmp_score)
        {
            scores[j + 1] = scores[j];
            strcpy(name[j + 1], name[j]);
            j--;
        }
        scores[j + 1] = tmp_score;
        strcpy(name[j + 1], tmp_name);
    }

    printf("Classement des scores (all time):\n");
    for (int i = 0; i < number_player; i++)
    {
        printf("  %d. %s : %d\n", i + 1, name[i], scores[i]);
    }
}

/*fichier main ci dessous present car vu qu'on pas inclure de ficher.c jsp comment faire et j'ai pas la force pour chercher*/

int main()
{
    srand(time(NULL));
    Song *firstsong = malloc(sizeof(Song));
    int number_song = load_score("songs.txt", firstsong);
    Song *current = firstsong;
    for (int i = 0; i < number_song; i++)
    {
        printf("%s %s  \t%s\n", current->filename, current->title, current->artist);
        current = current->next;
    }

    change_song(number_song, firstsong);

    printf("\n");
    current = firstsong;
    for (int i = 0; i < number_song; i++)
    {
        printf("%s %s  \t%s\n", current->filename, current->title, current->artist);
        current = current->next;
    }

    player *firstplayer = malloc(sizeof(player));
    int initial_number_player = load_score("scores.txt", firstplayer);

    printf("\n");
    printf("Joueurs chargés: %d\n", initial_number_player);
    player *current_player = firstplayer;
    for (int i = 0; i < initial_number_player; i++)
    {
        printf("Nom du joueur %d: %s\n", i + 1, current_player->name);
        current_player = current_player->next;
    }

    printf("\n");
    printf("Combien de nouveaux joueurs voulez vous ?\n> ");

    int number_player;
    scanf("%d", &number_player);
    getchar();

    current_player = firstplayer;

    for (int i = 0; i < number_player; i++)
    {
        printf("Nom du joueur %d: > ", i + 1);
        fgets(current_player->name, 100, stdin);
        current_player->name[strcspn(current_player->name, "\n")] = '\0';
        current_player->next = malloc(sizeof(player));
        current_player = current_player->next;
    }
    number_player += initial_number_player;
    current_player = firstplayer;
    printf("\n");
    for (int i = 0; i < number_player; i++)
    {
        printf("Nom du joueur %d: %s\n", i + 1, current_player->name);
        current_player = current_player->next;
    }
    current_player = firstplayer;
    for (int i = 0; i < number_player; i++)
    {
        printf("\n");
        printf("Joueur actuel: %s\n", current_player->name);
        current = firstsong;
        int current_score = 0;
        for (int j = 0; j < number_song; j++)
        {
            int result = 0;
            play_song_excerpt_at(current->title, rand() % 60, 10);
            char current_essai[100];
            printf("Quel est le titre de la chanson ?\n> ");
            fgets(current_essai, 100, stdin);
            if (string_equals_normalized(current_essai, current->title))
            {
                result = 1;
            }
            current_score += result;
            current = current->next;
        }
        if (current_player->score < current_score)
        {
            current_player->score = current_score;
        }
        current_player = current_player->next;
    }
    save_scores("scores.txt", number_player, firstplayer);
    printf("\nOrdre correct:\n");
    current = firstsong;
    for (int i = 0; i < number_song; i++)
    {
        printf("%d. %s - %s\n", i + 1, current->title, current->artist);
        current = current->next;
    }
    printf("\n");
    afficher_scores(number_player, firstplayer);

    return 0;
}