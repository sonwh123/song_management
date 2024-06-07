#include "header.h"

struct Song {
    char title[STRING_SIZE];
    char singer[STRING_SIZE];
    char composer[STRING_SIZE];
    char lyricist[STRING_SIZE];
    char genre[STRING_SIZE];
    char playtime[STRING_SIZE];
    char album[STRING_SIZE];
    char release[STRING_SIZE];
};

//�˻� �Լ� ����
void search();
// �뷡 �˻� �Լ� ����
int searchSong(char* filename, char* searchWord, int found);

void searchMenu();//�뷡 �˻� �޴�
void searchTag(); //�±� �˻�
void searchZero(const char* tag, const char* word);//�±� �˻����� 0 �Է½�
int searchWordExist(const char* tag, const char* word); //�˻��� �������� �Ǵ�
void searchWordOfTag(const char* tag, const char* word); //�˻��� �˻�

void searchMenu() {
    int mode;
    int err = 0;
    while (1)
    {
        if (err == 0) {
            printf("\n�뷡 ���� ���α׷��Դϴ�.\n");
            printf("���ϴ� �޴��� �����ϼ���.\n\n");
        }
        else if (err == 1) {
            printf("\n�ش� �޴��� �������� �ʽ��ϴ�.");
            printf("�ٽ� �����ϼ���.\n\n");
            err = 0;
        }
        printf("1. ���� �˻�\n");
        printf("2. �±� �˻�\n");
        printf("0. �ڷ� ����\n\n");
        printf("�޴� ���� : ");
        scanf(" %d", &mode);
        while (getchar() != '\n');

        switch (mode) {
        case 1: //���� �˻�
            // system("cls");
            search();
            break;

        case 2: //�±� �˻�
            // system("cls");
            searchTag();
            break;

        case 0: //�ڷ� ����
            // system("cls");
            return;
            // main();
            // break;

        default: //error
            //while (getchar() != '\n'); //�Է� ���� ����
            err = 1;
            break;
        }
    }
}
// �˻� �Լ� ����
void search() {
    // �˻��� ���ϸ� ����
    char filename[] = "song_list.txt";
    // �˻��� ���� ���� ����
    char searchWord[STRING_SIZE];
    // �˻� ��� ���θ� ��Ÿ���� ���� �ʱ�ȭ
    int found = 0;
    // ����ڿ��� �˻��� �Է� ��û
    printf("���� �˻��� �����ϼ̽��ϴ�.\n�˻�� �Է��ϼ��� (0 �Է� �� �ڷΰ���): ");
    // ����ڰ� �˻�� �Է��� ������ �ݺ�
    do {
        // ����ڷκ��� �˻��� �Է� ����
        scanf("%s", searchWord);
        printf("\n");
        if (searchWord[0] == '0') {
            searchMenu();
            break;
        }
        else {
            // �˻� ��� ���
            found = searchSong(filename, searchWord, found);
        }
        // ���� �˻� ����� ���ٸ� �ٽ� �˻��� �Է� ��û
        if (found == 0)
            printf("�ش� �˻���� �������� �ʽ��ϴ�.\n�˻�� �ٽ� �Է��ϼ���: ");
    } while (found == 0);
}

// �뷡 �˻� �Լ� ����
int searchSong(char* filename, char* searchWord, int found) {
    FILE* file = fopen(filename, "r");
    found = 0;
    struct Song song;
    char line[STRING_SIZE * 8]; // ���� �� ������ ���̸� �������� ���۸� �Ҵ�
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t\n]", song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
        if (strstr(song.title, searchWord) != NULL || strstr(song.singer, searchWord) != NULL ||
            strstr(song.composer, searchWord) != NULL || strstr(song.lyricist, searchWord) != NULL ||
            strstr(song.genre, searchWord) != NULL || strstr(song.playtime, searchWord) != NULL ||
            strstr(song.album, searchWord) != NULL || strstr(song.release, searchWord) != NULL) {
            printf("���� / ���� / �۰ / �ۻ簡 / �帣 / ����ð� / �ٹ��� / �ٹ���ó�¥\n");
            printf("%s / ", song.title);
            printf("%s / ", song.singer);
            printf("%s / ", song.composer);
            printf("%s / ", song.lyricist);
            int k = strlen(song.title) + strlen(song.singer) + strlen(song.composer) + strlen(song.lyricist) + 4;
            for (k; k < strlen(line); k++) {
                if (line[k] == '\t')
                    printf(" / ");
                else
                    printf("%c", line[k]);
            }
            found = 1;
        }
    }
    fclose(file);
    return found;
}

void searchTag() {
    char tag[STRING_SIZE], word[STRING_SIZE];
    int err = 0;
    int goback;
    while (1) {
        // system("cls");
        if (err == 0) {
            printf("�±� �˻��� �����ϼ̽��ϴ�.\n");
        }
        else {
            printf("\n�ش� �±״� �������� �ʽ��ϴ�.\n");
            err = 0;
        }
        printf("(�±� = ����/����/�۰/�ۻ簡/�帣/����ð�/�ٹ���/�ٹ���ó�¥)\n");
        printf("�˻��� �±׸� �Է��ϼ��� (0 �Է� �� �ڷΰ���) : ");
        scanf("%s", tag);
        while (getchar() != '\n');

        if (strcmp(tag, "����") == 0 || strcmp(tag, "����") == 0 || strcmp(tag, "�۰") == 0 || strcmp(tag, "�ۻ簡") == 0 || strcmp(tag, "�帣") == 0 || strcmp(tag, "����ð�") == 0 || strcmp(tag, "�ٹ���") == 0 || strcmp(tag, "�ٹ���ó�¥") == 0) {
            do {
                printf("�˻�� �Է��ϼ��� (0 �Է� �� �ڷΰ���) : ");
                scanf("%s", word);
                while (getchar() != '\n');
                printf("\n");

                if (word[0] == '0') {
                    searchMenu();
                    break;
                }
                else if (searchWordExist(tag, word) == 0) { // �˻�� �������� ������
                    printf("�ش� �˻���� �������� �ʽ��ϴ�.\n");
                    printf("(�±� = ����/����/�۰/�ۻ簡/�帣/����ð�/�ٹ���/�ٹ���ó�¥)\n");
                    printf("�˻��� �±׸� �Է��ϼ��� (0 �Է� �� �ڷΰ���) : %s\n", tag);
                }
                else {
                    // �˻� ��� ���
                    searchWordOfTag(tag, word);
                    break;
                }
            } while (1);
            break;
        }
        else if (strcmp(tag, "0") == 0) { // �ڷΰ���
            searchMenu();
            break;
        }
        else { // �߸��Է�
            err = 1;
        }
    }
}


void searchZero(const char* tag, const char* word) {
    int err = 0;
    int goback = 0;
    while (1) {
        if (err == 0) {
            printf("'0'�� �Է� �ϼ̽��ϴ�. ���� �ڷ� ���ðڽ��ϱ�?\n\n");
        }
        else {
            printf("�߸� �Է� �ϼ̽��ϴ�. �ٽ� �������ּ���.\n\n");
            err = 0;
        }
        printf("1. �ڷΰ���\n");
        printf("2. '0' �˻��ϱ�\n\n");
        printf("�޴����� : ");
        scanf("%d", &goback);
        while (getchar() != '\n');
        printf("\n");
        if (goback == 1) {
            searchTag();
            break;
        }
        else if (goback == 2) { // '0' �˻�
            searchWordOfTag(tag, word);
            break;
        }
        else {
            err = 1;
            break;
        }
    }
}

int searchWordExist(const char* tag, const char* word) {//�˻�� �����ϴ���
    FILE* file = fopen("song_list.txt", "r");

    struct Song song;
    char line[STRING_SIZE * 8]; // ���� �� ������ ���̸� �������� ���۸� �Ҵ�
    int found = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t\n]", song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);

        if ((strcmp(tag, "����") == 0 && strstr(song.title, word) != NULL) ||
            (strcmp(tag, "����") == 0 && strstr(song.singer, word) != NULL) ||
            (strcmp(tag, "�۰") == 0 && strstr(song.composer, word) != NULL) ||
            (strcmp(tag, "�ۻ簡") == 0 && strstr(song.lyricist, word) != NULL) ||
            (strcmp(tag, "�帣") == 0 && strstr(song.genre, word) != NULL) ||
            (strcmp(tag, "����ð�") == 0 && strstr(song.playtime, word) != NULL) ||
            (strcmp(tag, "�ٹ���") == 0 && strstr(song.album, word) != NULL) ||
            (strcmp(tag, "�ٹ���ó�¥") == 0 && strstr(song.release, word) != NULL)) {
            found = 1;
            break;
        }
    }
    fclose(file);
    return found;
}

void searchWordOfTag(const char* tag, const char* word) {
    FILE* file = fopen("song_list.txt", "r");

    struct Song song;
    char line[STRING_SIZE * 8]; // ���� �� ������ ���̸� �������� ���۸� �Ҵ�
    printf("���� / ���� / �۰ / �ۻ簡 / �帣 / ����ð� / �ٹ��� / �ٹ���ó�¥\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t\n]", song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);

        if ((strcmp(tag, "����") == 0 && strstr(song.title, word) != NULL) ||
            (strcmp(tag, "����") == 0 && strstr(song.singer, word) != NULL) ||
            (strcmp(tag, "�۰") == 0 && strstr(song.composer, word) != NULL) ||
            (strcmp(tag, "�ۻ簡") == 0 && strstr(song.lyricist, word) != NULL) ||
            (strcmp(tag, "�帣") == 0 && strstr(song.genre, word) != NULL) ||
            (strcmp(tag, "����ð�") == 0 && strstr(song.playtime, word) != NULL) ||
            (strcmp(tag, "�ٹ���") == 0 && strstr(song.album, word) != NULL) ||
            (strcmp(tag, "�ٹ���ó�¥") == 0 && strstr(song.release, word) != NULL)) {
            printf("%s / ", song.title);
            printf("%s / ", song.singer);
            printf("%s / ", song.composer);
            printf("%s / ", song.lyricist);
            int k = strlen(song.title) + strlen(song.singer) + strlen(song.composer) + strlen(song.lyricist) + 4; //���� ���� ó��
            for (k; k < strlen(line); k++) {
                if (line[k] == '\t')
                    printf(" / ");
                else
                    printf("%c", line[k]);
            }
            // printf("%s / %s / %s / %s / %s / %s / %s / %s\n", 
            //        song.title, song.singer, song.composer, song.lyricist, song.genre, song.playtime, song.album, song.release);
        }


    }



    fclose(file);

    printf("\n����ȭ������ ���ư����� �ƹ�Ű�� ��������.");
    _getwch(); // �ѱ��� ���͸� �ľ���.
    // system("cls");
    // return;
    main();
}