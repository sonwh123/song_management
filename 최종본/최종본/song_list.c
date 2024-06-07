#include "header.h"

int IsSpace(char ch); //���� Ȯ��
char* strrtrim(char* s); //�� ���� ����
char* strltrim(char* s); //�� ���� ����
char* trim(char* s); //�յ� ���� ����
void duplicate_people(const char* filename, const char* people); //�������� Ȯ��
int check_date(int y, int m, int d); //��¥ ���� ���� Ȯ��

int IsSpace(char ch)
{
    if (ch < 0)  // �����ΰ�� �ѱ۷� ����
        return 0;
    else
        return isspace(ch);
}

char* strrtrim(char* s)   //�� ���� ����
{
    char* t;

    t = strchr(s, '\0');
    while (t > s && IsSpace(t[-1]))
        --t;
    *t = '\0';
    return s;
}

char* strltrim(char* s)   //�� ���� ����
{
    char* t;
    char* e;

    t = s;
    e = strchr(s, '\0');
    while (IsSpace(*t))
        ++t;

    memmove(s, t, e - t + 1);

    return s;
}

char* trim(char* s)   //�յ� ���� ����
{
    strltrim(s);
    strrtrim(s);

    return s;
}

void duplicate_people(const char* filename, const char* people) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "������ �� �� �����ϴ�: %s\n", filename);
        return;
    }

    char d_line[256]; // txt���� �� ���� �б� ���� ����
    char dupli_peoples[256][256]; // index�� �Բ� �ߺ��� ��� ���� �迭
    int people_count = 0; // �ߺ��� ��� ��
    int is_duplicate; // �ߺ� ���� Ȯ��

    while (fgets(d_line, sizeof(d_line), file)) { // txt������ �� �� d_line�� ����
        char* tab_pos_q = strchr(d_line, '\t');   //�� ��Ű
        char* tab_pos_p = strchr(tab_pos_q + 1, '\t');   //�� ��Ű
        char dupli_words[STRING_SIZE] = "";
        strncpy(dupli_words, tab_pos_q + 1, tab_pos_p - tab_pos_q - 1);   //���� ����� ����
        //      printf("%s\n", dupli_words);   //(�˻�)

        for (int i = 0; i < 3; i++) {   //����, �۰, �ۻ簡 ���ʷ� Ȯ��
            char* dupli_word = strtok(dupli_words, ",");   // ,�� �����ڷ� ���� dupli_word�� ����
            while (dupli_word != NULL) {
                dupli_word = trim(dupli_word);   //�յ� ���� ����
                char* pipe_pos = strchr(dupli_word, '|'); // '|' ��ġ ã��

                if (pipe_pos != NULL) {
                    *pipe_pos = '\0'; // '|' ������ ���ڿ� ����
                    char extra[256] = ""; // '|' ������ ���ڿ� ����

                    char* after_pipe = pipe_pos + 1; // '|' ������ ���� ��ġ
                    char* next_comma_pos = strchr(after_pipe, ',');   //���� ',' ��ġ ã��
                    if (next_comma_pos != NULL) {
                        *next_comma_pos = '\0'; // ',' ���� ����      
                    }
                    after_pipe = trim(after_pipe);   //�յ� ���� ����
                    strcpy(extra, after_pipe); // '|' ������ ���ڿ� ����

                    if (strcmp(dupli_word, people) == 0) { // '|'������ ���ڿ��� �Է��� ������ ��ġ�ϸ�
                        strcat(dupli_word, "|");
                        strcat(dupli_word, extra);  //dupli_word�� '|' ���� ���ڿ� �߰�

                        // �ߺ� ���� Ȯ��
                        is_duplicate = 0;
                        for (int i = 0; i < people_count; i++) {
                            if (strcmp(dupli_peoples[i], dupli_word) == 0) { // �ߺ� Ȯ��
                                is_duplicate = 1;   //�ߺ��̶��
                                break;
                            }
                        }

                        if (is_duplicate == 0) { // �ߺ��� �ƴϸ� ����
                            strcpy(dupli_peoples[people_count], dupli_word);
                            people_count++;
                        }
                    }
                }
                dupli_word = strtok(NULL, ",");
            }

            tab_pos_q = tab_pos_p;   //�� ��Ű
            tab_pos_p = strchr(tab_pos_q + 1, '\t');   //�� ��Ű
            strcpy(dupli_words, tab_pos_q + 1, tab_pos_p - tab_pos_q - 1);   //�۰ ����� ���� > �ۻ簡 ����� ����
            dupli_words[tab_pos_p - tab_pos_q - 1] = '\0';   //��ȿ�� ���ڿ������� �ڸ���
        }
    }

    int dupli_index;
    char dupli_add[100];
    if (people_count >= 1) {   // �ߺ��� ��� ���� 1�� �̻��̸� �ε����� �Բ� ���
        while (1) {
            printf("�������� ��Ƽ��Ʈ�� �����մϴ�. ������ ��Ƽ��Ʈ�� ����ּ���.\n");
            for (int i = 0; i < people_count; i++) {    // �ߺ��� ��� ���
                printf("%d. %s\n", i + 1, dupli_peoples[i]);
            }
            printf("0. ����\n");
            printf("�Է�: ");
            scanf("%d", &dupli_index);  // ��ȣ �Է�
            while (getchar() != '\n'); //�Է� ���� ����
            if (dupli_index == 0) { // 0. ���� ���ý�, ���� ��ȣ ���� �� ����
                sprintf(dupli_add, "|%d", people_count);
                break;
            }
            else if (dupli_index > 0 && dupli_index < people_count + 1) {   // ������ ������� index ����
                sprintf(dupli_add, "|%d", dupli_index - 1);
                break;
            }
        }
    }
    else {
        sprintf(dupli_add, "|%d", 0);   // �ߺ��� ����� ���ٸ� |0 �� ����
    }
    strcat(people, dupli_add);  // �ϼ��� ���ڿ��� people�� ����
    fclose(file); // ���� �ݱ�
}

int check_date(int y, int m, int d) {
    if (y > 1907 && y <= 2024 && m >= 1 && m <= 12) {   //��,�� ����
        if ((y % 4) == 0 && (y % 100) != 0 || (y % 400) == 0) {   //����
            int months[] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
            if (d >= 1 && d <= months[m - 1]) { return 1; }   //�� �������� ������ TRUE
            else { return 0; }   //Ʋ���� FALSE
        }
        else {   //���
            int months[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
            if (d >= 1 && d <= months[m - 1]) { return 1; }   //�� �������� ������ TRUE
            else { return 0; }   //Ʋ���� FALSE
        }
    }
    else { return 0; }
}

void song_list_menu() //�뷡 ����Ʈ �� �޴�
{
    char input_text[STRING_SIZE];   //������ ���ڿ�(�뷡)�� �� �迭
    int mode, err = 0;
    while (1)
    {
        if (err == 0) //�Է� ���ǿ� �¾��� ��
        {
            printf("\n���ϴ� �޴��� �����ϼ���.\n\n");
        }
        else //�Է� ���ǿ� ���� �ʾ��� ��
        {
            printf("\n�ش� �޴��� �������� �ʽ��ϴ�.\n");
            printf("���� �޴� �� �����ϼ���(����:1)\n\n");
            err = 0;
        }
        printf("1. �뷡 ����Ʈ ���\n");
        printf("2. �뷡 �߰�\n");
        printf("3. �뷡 ����\n");
        printf("0. �ڷ� ����\n");
        printf("\n�޴� ���� : ");
        scanf(" %d", &mode);
        while (getchar() != '\n'); //�Է� ���� ����

        switch (mode) {
        case 1: //�뷡 ����Ʈ ���
            song_list_print();
            break;
        case 2: //�뷡 �߰�
            add_song();
            break;
        case 3: //�뷡 ����
            get_dlt_song(input_text); //���� ���ڿ� �Է� �� ���� �� ����
            break;
        case 0: //�ڷ� ����
            return 0;
            break;
        default: //error
            err = 1;
            break;
        }
    }
}


void song_list_print()//�뷡 ����Ʈ ���
{
    printf("\n�뷡 ����Ʈ�� ����մϴ�.");
    printf("\n\n���� / ���� / �۰ / �ۻ簡 / �帣 / ����ð� / �ٹ��� / �ٹ� ��� ��¥\n\n");
    FILE* fp;
    fp = fopen("song_list.txt", "r"); //�ؽ�Ʈ ���� �ҷ�����
    //if (fp == NULL) //���� ���� üũ
    //{
    //    printf("����");
    //}
    char name[STRING_SIZE]; //����
    char singer[STRING_SIZE]; //����
    char song_writer[STRING_SIZE]; //�۰
    char lylic_writer[STRING_SIZE]; //�ۻ簡
    char genre[STRING_SIZE]; //�帣
    char playtime[STRING_SIZE]; //����ð�
    char album_name[STRING_SIZE]; //�ٹ���
    char album_time[STRING_SIZE]; //�ٹ� ��� ��¥

    char song[STRING_SIZE * 8]; //�ҷ��� �� ��
    while (fgets(song, sizeof(song), fp) != NULL) //�� �� �� �ҷ�����
    {
        sscanf(song, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t\n]", name, singer, song_writer, lylic_writer, genre, playtime, album_name, album_time); //��Ű�� �����ڷ� �ϳ��� �ҷ�����
        printf("%s / ", name); //���� ���
        int size = 0;

        //���� ���
        while (1)
        {
            if (singer[size] == '|') //�ι� �����ڸ� ������ ��
            {
                while (1) //���⸦ ���� �� �Ǵ� ���� �� ���� �ǳʶٱ�
                {
                    size++;
                    if (singer[size] == NULL) //���ڿ��� ������ ��
                    {
                        break;
                    }
                    else if (singer[size] == ' ') //���⸦ ������ ��
                    {
                        size = size + 1; //���� �ι��� �̸����� �̵�
                        break;
                    }
                }
            }
            if (singer[size] == NULL) //���ڿ��� ������ ��
            {
                printf(" / ");
                break;
            }
            printf("%c", singer[size]);
            size++;
        }
        size = 0;

        //�۰ ���
        while (1)
        {
            if (song_writer[size] == '|') //�ι� �����ڸ� ������ ��
            {
                while (1) //���⸦ ���� �� �Ǵ� ���� �� ���� �ǳʶٱ�
                {
                    size++;
                    if (song_writer[size] == NULL) //���ڿ��� ������ ��
                    {
                        break;
                    }
                    else if (song_writer[size] == ' ') //���⸦ ������ ��
                    {
                        size = size + 1;
                        break;
                    }
                }
            }
            if (song_writer[size] == NULL) //���ڿ��� ������ ��
            {
                printf(" / ");
                break;
            }
            printf("%c", song_writer[size]);
            size++;
        }
        size = 0;

        //�ۻ簡 ���
        while (1)
        {
            if (lylic_writer[size] == '|') //�ι� �����ڸ� ������ ��
            {
                while (1) //���⸦ ���� �� �Ǵ� ���� �� ���� �ǳʶٱ�
                {
                    size++;
                    if (lylic_writer[size] == NULL) //���ڿ��� ������ ��
                    {
                        break;
                    }
                    else if (lylic_writer[size] == ' ') //���⸦ ������ ��
                    {
                        size = size + 1;
                        break;
                    }
                }
            }
            if (lylic_writer[size] == NULL) //���ڿ��� ������ ��
            {
                printf(" / ");
                break;
            }
            printf("%c", lylic_writer[size]);
            size++;
        }

        int k = strlen(name) + strlen(singer) + strlen(song_writer) + strlen(lylic_writer) + 4; //���� ���� ó��
        for (k; k < strlen(song); k++) {
            if (song[k] == '\t')
                printf(" / ");
            else
                printf("%c", song[k]);
        }
    }
    fclose(fp);
    printf("\n\n�뷡����Ʈ ���� �޴��� ���ư����� �ƹ�Ű�� ��������.");
    _getwch();
}


void add_song() {
    //�Է��� ���� ����
    char title_buffer[STRING_SIZE] = "";   //����
    char singers_buffer[STRING_SIZE] = "";   //����
    char composers_buffer[STRING_SIZE] = "";   //�۰
    char lyricists_buffer[STRING_SIZE] = "";   //�ۻ簡
    char genre_buffer[STRING_SIZE] = "";    //�帣
    char playtime_buffer[STRING_SIZE] = ""; //����ð�
    char album_buffer[STRING_SIZE] = "";    //�ٹ���
    char release_buffer[STRING_SIZE] = "";  //�ٹ���ó�¥

    //�Է��� ������ ����
    char title_result[STRING_SIZE] = "";   //����
    char singers_result[STRING_SIZE] = "";   //����
    char composers_result[STRING_SIZE] = "";   //�۰
    char lyricists_result[STRING_SIZE] = "";   //�ۻ簡
    char genre_result[STRING_SIZE] = "";    //�帣
    char playtime_result[STRING_SIZE] = ""; //����ð�
    char album_result[STRING_SIZE] = "";    //�ٹ���
    char release_result[STRING_SIZE] = "";  //�ٹ���ó�¥

    FILE* fp = fopen("song_list.txt", "a");   //�߰����� ���� ����


    printf("\n������ �Է��ϼ���.\n");   //����
    while (1) {
        printf("\n");
        printf("���� :");
        gets(title_buffer, STRING_SIZE);   //���� �Է¹ޱ�

        char* title = trim(title_buffer);   //�յ� ���� ����

        //printf("%s\n", title);         //����� �ԷµǾ����� Ȯ��(�˻�)
        if (strlen(title) == 0) {   //Ʋ�� �Է��� ���
            printf("\n���� �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:����)\n");
            continue;
        }
        else {      //�´� �Է��� ���
            strcat(title_result, title);   //���� ����
        }
        break;
    }   //���� ��

    printf("\n������ �Է��ϼ���.\n");   //����
    while (1) {
        int error = 0;   //���� Ȯ��
        printf("\n");
        printf("���� :");
        gets(singers_buffer);   //���� �Է¹ޱ�

        char* singers = trim(singers_buffer);   //�յ� ���� ����

        if (strlen(singers) == 0) {   //Ʋ�� �Է��� ���
            printf("\n���� �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:������)\n");
            continue;
        }
        else {      //�´� �Է��� ���
            char* ptr_comma_q = singers;   //�� �޸�
            char* ptr_comma_p = strchr(singers, ',');   //�� �޸�
            if (ptr_comma_p == NULL) {   //������ �Ѹ��� ��
                duplicate_people("song_list.txt", singers);
                strcat(singers_result, singers);
            }
            else {
                //���� �Ѹ��Ѹ��� �������� üũ
                char check_first_singer_buffer[STRING_SIZE] = "";
                strncpy(check_first_singer_buffer, ptr_comma_q, ptr_comma_p - ptr_comma_q);   //ù ���� ����
                char* check_first_singer = trim(check_first_singer_buffer);   //�յ� ���� ����
                if (strcmp(check_first_singer, "") == 0) {   //�����ϰ��
                    printf("\n���� �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:������)\n");
                    continue;
                }
                ptr_comma_q = ptr_comma_p;
                ptr_comma_p = strchr(ptr_comma_p + 1, ',');
                while (ptr_comma_p != NULL) {
                    char check_singer_buffer[STRING_SIZE] = "";
                    strncpy(check_singer_buffer, ptr_comma_q + 1, ptr_comma_p - ptr_comma_q - 1);   //���� ����
                    char* check_singer = trim(check_singer_buffer);   //�յ� ���� ����
                    if (strcmp(check_singer, "") == 0) { error = 1; break; }   //������ ���
                    ptr_comma_q = ptr_comma_p;
                    ptr_comma_p = strchr(ptr_comma_p + 1, ',');
                }
                if (error == 1) {   //Ʋ�� �Է��� ���
                    printf("\n���� �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:������)\n");
                    continue;
                }
                char check_last_singer_buffer[STRING_SIZE] = "";
                ptr_comma_p = strrchr(singers, ',');
                strncpy(check_last_singer_buffer, ptr_comma_p + 1, (singers + strlen(singers) - 1) - ptr_comma_p);   //������ ���� ����
                char* check_last_singer = trim(check_last_singer_buffer);   //�յ� ���� ����
                if (strcmp(check_last_singer, "") == 0) {   //�����ϰ��
                    printf("\n���� �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:������)\n");
                    continue;
                }

                //���� ������ ���� �������� �� �� ����
                ptr_comma_q = singers;
                ptr_comma_p = strchr(singers, ',');
                char first_singer_buffer[STRING_SIZE] = "";
                strncpy(first_singer_buffer, ptr_comma_q, ptr_comma_p - ptr_comma_q);   //ù ���� ����
                char* first_singer = trim(first_singer_buffer);   //�յ� ���� ����
                duplicate_people("song_list.txt", first_singer);   //�ߺ�Ȯ��
                strcat(singers_result, first_singer);   //ù ���� ����
                ptr_comma_q = ptr_comma_p;
                ptr_comma_p = strchr(ptr_comma_p + 1, ',');
                while (ptr_comma_p != NULL) {   //������ �� �ִ��� Ȯ��
                    char singer_buffer[STRING_SIZE] = "";
                    strncpy(singer_buffer, ptr_comma_q + 1, ptr_comma_p - ptr_comma_q - 1);   //���� ����
                    char* singer = trim(singer_buffer);   //�յ� ���� ����
                    duplicate_people("song_list.txt", singer);   //�ߺ�Ȯ��
                    strcat(singers_result, " , ");
                    strcat(singers_result, singer);   //���� ����
                    ptr_comma_q = ptr_comma_p;
                    ptr_comma_p = strchr(ptr_comma_p + 1, ',');
                }
                char last_singer_buffer[STRING_SIZE] = "";
                ptr_comma_p = strrchr(singers, ',');
                strncpy(last_singer_buffer, ptr_comma_p + 1, (singers + strlen(singers) - 1) - ptr_comma_p);   //������ ���� ����
                char* last_singer = trim(last_singer_buffer);   //�յ� ���� ����
                duplicate_people("song_list.txt", last_singer);   //�ߺ�Ȯ��
                strcat(singers_result, " , ");
                strcat(singers_result, last_singer);   //������ ���� ����
            }
        }

        break;
    }      //���� ��


    printf("\n�۰�� �Է��ϼ���.\n");   //�۰
    while (1) {
        int error = 0;   //���� Ȯ��
        printf("\n");
        printf("�۰ :");
        gets(composers_buffer);   //�۰ �Է¹ޱ�

        char* composers = trim(composers_buffer);   //�յ� ���� ����

        if (strlen(composers) == 0) {   //Ʋ�� �Է��� ���
            printf("\n�۰ �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:������)\n");
            continue;
        }
        else {      //�´� �Է��� ���
            char* ptr_comma_q = composers;   //�� �޸�
            char* ptr_comma_p = strchr(composers, ',');   //�� �޸�
            if (ptr_comma_p == NULL) {   //�۰ �Ѹ��� ��
                duplicate_people("song_list.txt", composers);
                strcat(composers_result, composers);
            }
            else {
                //�۰ �Ѹ��Ѹ��� �������� üũ
                char check_first_composer_buffer[STRING_SIZE] = "";
                strncpy(check_first_composer_buffer, ptr_comma_q, ptr_comma_p - ptr_comma_q);   //ù �۰ ����
                char* check_first_composer = trim(check_first_composer_buffer);   //�յ� ���� ����
                if (strcmp(check_first_composer, "") == 0) {   //�����ϰ��
                    printf("\n�۰ �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:������)\n");
                    continue;
                }
                ptr_comma_q = ptr_comma_p;
                ptr_comma_p = strchr(ptr_comma_p + 1, ',');
                while (ptr_comma_p != NULL) {
                    char check_composer_buffer[STRING_SIZE] = "";
                    strncpy(check_composer_buffer, ptr_comma_q + 1, ptr_comma_p - ptr_comma_q - 1);   //�۰ ����
                    char* check_composer = trim(check_composer_buffer);   //�յ� ���� ����
                    if (strcmp(check_composer, "") == 0) { error = 1; break; }   //������ ���
                    ptr_comma_q = ptr_comma_p;
                    ptr_comma_p = strchr(ptr_comma_p + 1, ',');
                }
                if (error == 1) {   //Ʋ�� �Է��� ���
                    printf("\n�۰ �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:������)\n");
                    continue;
                }
                char check_last_composer_buffer[STRING_SIZE] = "";
                ptr_comma_p = strrchr(composers, ',');
                strncpy(check_last_composer_buffer, ptr_comma_p + 1, (composers + strlen(composers) - 1) - ptr_comma_p);   //������ �۰ ����
                char* check_last_composer = trim(check_last_composer_buffer);   //�յ� ���� ����
                if (strcmp(check_last_composer, "") == 0) {   //�����ϰ��
                    printf("\n�۰ �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:������)\n");
                    continue;
                }

                //���� ������ �۰ �������� �� �� ����
                ptr_comma_q = composers;
                ptr_comma_p = strchr(composers, ',');
                char first_composer_buffer[STRING_SIZE] = "";
                strncpy(first_composer_buffer, ptr_comma_q, ptr_comma_p - ptr_comma_q);   //ù �۰ ����
                char* first_composer = trim(first_composer_buffer);   //�յ� ���� ����
                duplicate_people("song_list.txt", first_composer);   //�ߺ�Ȯ��
                strcat(composers_result, first_composer);   //ù �۰ ����
                ptr_comma_q = ptr_comma_p;
                ptr_comma_p = strchr(ptr_comma_p + 1, ',');
                while (ptr_comma_p != NULL) {   //�۰�� �� �ִ��� Ȯ��
                    char composer_buffer[STRING_SIZE] = "";
                    strncpy(composer_buffer, ptr_comma_q + 1, ptr_comma_p - ptr_comma_q - 1);   //�۰ ����
                    char* composer = trim(composer_buffer);   //�յ� ���� ����
                    duplicate_people("song_list.txt", composer);   //�ߺ�Ȯ��
                    strcat(composers_result, " , ");
                    strcat(composers_result, composer);   //�۰ ����
                    ptr_comma_q = ptr_comma_p;
                    ptr_comma_p = strchr(ptr_comma_p + 1, ',');
                }
                char last_composer_buffer[STRING_SIZE] = "";
                ptr_comma_p = strrchr(composers, ',');
                strncpy(last_composer_buffer, ptr_comma_p + 1, (composers + strlen(composers) - 1) - ptr_comma_p);   //������ ���� ����
                char* last_composer = trim(last_composer_buffer);   //�յ� ���� ����
                duplicate_people("song_list.txt", last_composer);   //�ߺ�Ȯ��
                strcat(composers_result, " , ");
                strcat(composers_result, last_composer);   //������ �۰ ����
            }
        }
        break;   //�۰ ��
    }

    printf("\n�ۻ簡�� �Է��ϼ���.\n");   //�ۻ簡
    while (1) {
        int error = 0;   //���� Ȯ��
        printf("\n");
        printf("�ۻ簡 :");
        gets(lyricists_buffer);   //�ۻ簡 �Է¹ޱ�

        char* lyricists = trim(lyricists_buffer);   //�յ� ���� ����

        if (strlen(lyricists) == 0) {   //Ʋ�� �Է��� ���
            printf("\n�ۻ簡 �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:������)\n");
            continue;
        }
        else {      //�´� �Է��� ���
            char* ptr_comma_q = lyricists;   //�� �޸�
            char* ptr_comma_p = strchr(lyricists, ',');   //�� �޸�
            if (ptr_comma_p == NULL) {   //�ۻ簡�� �Ѹ��� ��
                duplicate_people("song_list.txt", lyricists);
                strcat(lyricists_result, lyricists);
            }
            else {
                //�ۻ簡 �Ѹ��Ѹ��� �������� üũ
                char check_first_lyricist_buffer[STRING_SIZE] = "";
                strncpy(check_first_lyricist_buffer, ptr_comma_q, ptr_comma_p - ptr_comma_q);   //ù �ۻ簡 ����
                char* check_first_lyricist = trim(check_first_lyricist_buffer);   //�յ� ���� ����
                if (strcmp(check_first_lyricist, "") == 0) {   //�����ϰ��
                    printf("\n�ۻ簡 �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:������)\n");
                    continue;
                }
                ptr_comma_q = ptr_comma_p;
                ptr_comma_p = strchr(ptr_comma_p + 1, ',');
                while (ptr_comma_p != NULL) {
                    char check_lyricist_buffer[STRING_SIZE] = "";
                    strncpy(check_lyricist_buffer, ptr_comma_q + 1, ptr_comma_p - ptr_comma_q - 1);   //�ۻ簡 ����
                    char* check_lyricist = trim(check_lyricist_buffer);   //�յ� ���� ����
                    if (strcmp(check_lyricist, "") == 0) { error = 1; break; }   //������ ���
                    ptr_comma_q = ptr_comma_p;
                    ptr_comma_p = strchr(ptr_comma_p + 1, ',');
                }
                if (error == 1) {   //Ʋ�� �Է��� ���
                    printf("\n�ۻ簡 �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:������)\n");
                    continue;
                }
                char check_last_lyricist_buffer[STRING_SIZE] = "";
                ptr_comma_p = strrchr(lyricists, ',');
                strncpy(check_last_lyricist_buffer, ptr_comma_p + 1, (lyricists + strlen(lyricists) - 1) - ptr_comma_p);   //������ �ۻ簡 ����
                char* check_last_lyricist = trim(check_last_lyricist_buffer);   //�յ� ���� ����
                if (strcmp(check_last_lyricist, "") == 0) {   //�����ϰ��
                    printf("\n�ۻ簡 �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:������)\n");
                    continue;
                }

                //���� ������ �ۻ簡 �������� �� �� ����
                ptr_comma_q = lyricists;
                ptr_comma_p = strchr(lyricists, ',');
                char first_lyricist_buffer[STRING_SIZE] = "";
                strncpy(first_lyricist_buffer, ptr_comma_q, ptr_comma_p - ptr_comma_q);   //ù �ۻ簡 ����
                char* first_lyricist = trim(first_lyricist_buffer);   //�յ� ���� ����
                duplicate_people("song_list.txt", first_lyricist);   //�ߺ�Ȯ��
                strcat(lyricists_result, first_lyricist);   //ù �ۻ簡 ����
                ptr_comma_q = ptr_comma_p;
                ptr_comma_p = strchr(ptr_comma_p + 1, ',');
                while (ptr_comma_p != NULL) {   //�ۻ簡�� �� �ִ��� Ȯ��
                    char lyricist_buffer[STRING_SIZE] = "";
                    strncpy(lyricist_buffer, ptr_comma_q + 1, ptr_comma_p - ptr_comma_q - 1);   //�ۻ簡 ����
                    char* lyricist = trim(lyricist_buffer);   //�յ� ���� ����
                    duplicate_people("song_list.txt", lyricist);   //�ߺ�Ȯ��
                    strcat(lyricists_result, " , ");
                    strcat(lyricists_result, lyricist);   //�ۻ簡 ����
                    ptr_comma_q = ptr_comma_p;
                    ptr_comma_p = strchr(ptr_comma_p + 1, ',');
                }
                char last_lyricist_buffer[STRING_SIZE] = "";
                ptr_comma_p = strrchr(lyricists, ',');
                strncpy(last_lyricist_buffer, ptr_comma_p + 1, (lyricists + strlen(lyricists) - 1) - ptr_comma_p);   //������ ���� ����
                char* last_singer = trim(last_lyricist_buffer);   //�յ� ���� ����
                duplicate_people("song_list.txt", last_singer);   //�ߺ�Ȯ��
                strcat(lyricists_result, " , ");
                strcat(lyricists_result, last_singer);   //������ �ۻ簡 ����
            }
        }
        break;   //�ۻ簡 ��
    }

    printf("\n�帣�� �Է��ϼ���.\n");   //�帣
    while (1) {
        printf("\n");
        printf("�帣 :");
        gets(genre_buffer);

        char* genre = trim(genre_buffer);   //�յ� ���� ����

        if (strcmp(genre, "Ŭ����") * strcmp(genre, "����") * strcmp(genre, "��") * strcmp(genre, "�߶��") * strcmp(genre, "����") * strcmp(genre, "Ʈ��Ʈ") * strcmp(genre, "����") * strcmp(genre, "��") == 0 || strlen(genre) == 0) {   //�´� �Է��� ���
            strcat(genre_result, genre);   //�帣 ����
        }
        else {      //Ʋ�� �Է��� ���
            printf("\n�帣 �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:����)\n");
            continue;
        }
        break;
    }      //�帣 ��

    printf("\n�ð��� �Է��ϼ���.\n");   //����ð�
    while (1) {
        char minute_str[STRING_SIZE] = "";
        char second_str[STRING_SIZE] = "";
        int count_m = 0;
        int count_s = 0;
        int error = 0;
        printf("\n");
        printf("�ð� :");
        gets(playtime_buffer);

        char* playtime = trim(playtime_buffer);   //�յ� ���� ����

        //"��","��" ���� ���� ����
        char* ptr_m_temp = strstr(playtime, "��");
        while (ptr_m_temp != NULL) // ���̻� "��"�� �������� ���� ������ �ݺ�
        {
            ptr_m_temp = strstr(ptr_m_temp + 1, "��"); // ���� ���� ��ġ Ž��
            count_m++;
        }
        char* ptr_s_temp = strstr(playtime, "��");
        while (ptr_s_temp != NULL) // ���̻� "��"�� �������� ���� ������ �ݺ�
        {
            ptr_s_temp = strstr(ptr_s_temp + 1, "��"); // ���� ���� ��ġ Ž��
            count_s++;
        }

        //����ð� ���� ���� Ȯ��
        if (strlen(playtime) == 0) { error = 1; }   //Ʋ�� �Է��� ���   
        else if (count_m == 1 && count_s == 1) {   //��� 1���� �ִ� ���
            char* ptr_m = strstr(playtime, "��");
            char* ptr_s = strstr(playtime, "��");
            if ((ptr_s - playtime) == strlen(playtime) - 2 && ptr_m < ptr_s) {   //"��"�� �������̰� "��"�� "��"���� �տ� �־�� ��
                strncpy(minute_str, playtime, ptr_m - playtime);
                strncpy(second_str, ptr_m + 2, ptr_s - ptr_m - 2);
                if (strchr(minute_str, ' ') || strchr(minute_str, '\t') || strcmp(minute_str, "") == 0 || strchr(second_str, ' ') || strchr(second_str, '\t') || strcmp(second_str, "") == 0) { error = 1; }   //������ ����� ��
                else {
                    for (int i = 0; i < strlen(minute_str); i++)   //���ڿ��� �������� Ȯ��
                    {
                        if ((int)minute_str[i] < 48 || (int)minute_str[i] > 57) { error = 1; }
                    }
                    for (int i = 0; i < strlen(second_str); i++)   //���ڿ��� �������� Ȯ��
                    {
                        if ((int)second_str[i] < 48 || (int)second_str[i] > 57) { error = 1; }
                    }
                }
            }
            else { error = 1; }
        }
        else if (count_m == 1 && count_s == 0) {   //�Է¿� "��"�� 1�� �ִ� ���
            char* ptr_m = strstr(playtime, "��");
            if ((ptr_m - playtime) == strlen(playtime) - 2) {   //"��"�� �������̾�� ��
                strncpy(minute_str, playtime, ptr_m - playtime);
                if (strchr(minute_str, ' ') || strchr(minute_str, '\t') || strcmp(minute_str, "") == 0) { error = 1; }   //������ ����� ��
                else {
                    for (int i = 0; i < strlen(minute_str); i++)   //���ڿ��� �������� Ȯ��
                    {
                        if ((int)minute_str[i] < 48 || (int)minute_str[i] > 57) { error = 1; }
                    }
                }
            }
            else { error = 1; }
        }
        else if (count_m == 0 && count_s == 1) {   //�Է¿� "��"�� 1�� �ִ� ���
            char* ptr_s = strstr(playtime, "��");
            if ((ptr_s - playtime) == strlen(playtime) - 2) {   //"��"�� �������̾�� ��
                strncpy(second_str, playtime, ptr_s - playtime);
                if (strchr(second_str, ' ') || strchr(second_str, '\t') || strcmp(second_str, "") == 0) { error = 1; }   //������ ����� ��
                else {
                    for (int i = 0; i < strlen(second_str); i++)   //���ڿ��� �������� Ȯ��
                    {
                        if ((int)second_str[i] < 48 || (int)second_str[i] > 57) { error = 1; }
                    }
                }
            }
            else { error = 1; }
        }
        else { error = 1; }      //�������� ��� Ʋ�� ���

        if (error == 1) {      //���� ó��
            printf("\n�ð� �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:02��44��)\n");
            continue;
        }

        //����ð� �ǹ� ��Ģ Ȯ��
        int minute = 0;
        int second = 0;
        if (strcmp(minute_str, "")) {   //"��"�� ������ �ƴϸ�
            minute = atoi(minute_str);
            if (minute <= 0) { error = 1; }   //"��"�� 0���� ũ��
        }
        if (strcmp(second_str, "")) {   //"��"�� ������ �ƴϸ�
            second = atoi(second_str);
            if (second <= 0 || second >= 60) { error = 1; }   //"��"�� 1~59����
        }
        if (error == 1) {      //���� ó��
            printf("\n�ð� �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:02��44��)\n");
            continue;
        }

        if (strcmp(minute_str, "")) {   //"��"�� ������ �ƴϸ� "��" ����
            sprintf(minute_str, "%02d", minute);
            strcat(playtime_result, minute_str);
            strcat(playtime_result, "��");
        }
        if (strcmp(second_str, "")) {   //"��"�� ������ �ƴϸ� "��" ����
            sprintf(second_str, "%02d", second);
            strcat(playtime_result, second_str);
            strcat(playtime_result, "��");
        }
        break;
    }      //����ð� ��

    printf("\n�ٹ����� �Է��ϼ���.\n");   //�ٹ���
    while (1) {
        printf("\n");
        printf("�ٹ��� :");
        gets(album_buffer);   //�ٹ��� �Է¹ޱ�

        char* album = trim(album_buffer);   //�յ� ���� ����

        if (0) {   //Ʋ�� �Է��� ���(����)
            printf("\n�ٹ��� �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.(����:��簻)\n");
            continue;
        }
        else {      //�´� �Է��� ���
            strcat(album_result, album);   //�ٹ��� ����
        }
        break;
    }   //�ٹ��� ��

    printf("\n�ٹ� ��� ��¥�� �Է��ϼ���.\n");   //�ٹ� ��� ��¥
    while (1) {
        char year_str[5] = "";
        char month_str[3] = "";
        char day_str[3] = "";
        int count_hyphen = 0;
        int count_slash = 0;
        int count_dot = 0;
        int error = 0;
        printf("\n");
        printf("�ٹ� ��� ��¥ :");
        gets(release_buffer);

        char* release = trim(release_buffer);   //�յ� ���� ����

        if (strlen(release) == 0) {      //������ ���
            strcat(release_result, release);
            break;
        }

        //'-','/','.' ���� ���� ����
        char* ptr_hyphen_temp = strchr(release, '-');
        while (ptr_hyphen_temp != NULL) // ���̻� '-'�� �������� ���� ������ �ݺ�
        {
            ptr_hyphen_temp = strchr(ptr_hyphen_temp + 1, '-'); // ���� ���� ��ġ Ž��
            count_hyphen++;
        }
        char* ptr_slash_temp = strchr(release, '/');
        while (ptr_slash_temp != NULL) // ���̻� '/'�� �������� ���� ������ �ݺ�
        {
            ptr_slash_temp = strchr(ptr_slash_temp + 1, '/'); // ���� ���� ��ġ Ž��
            count_slash++;
        }
        char* ptr_dot_temp = strchr(release, '.');
        while (ptr_dot_temp != NULL) // ���̻� '.'�� �������� ���� ������ �ݺ�
        {
            ptr_dot_temp = strchr(ptr_dot_temp + 1, '.'); // ���� ���� ��ġ Ž��
            count_dot++;
        }

        //�ٹ� ��� ��¥ ���� ���� Ȯ��
        if (strlen(release) == 10) {
            if (count_hyphen == 2 && count_slash == 0 && count_dot == 0) {   //'-'�� 2���� ���
                char* ptr_hyphen_1 = strchr(release, '-');
                char* ptr_hyphen_2 = strchr(ptr_hyphen_1 + 1, '-');
                if ((ptr_hyphen_1 - release) == 4 && (ptr_hyphen_2 - ptr_hyphen_1) == 3) {   //��,��,���� ���� 4,2,2�ڸ����� Ȯ��
                    strncpy(year_str, release, 4);
                    strncpy(month_str, ptr_hyphen_1 + 1, 2);
                    strncpy(day_str, ptr_hyphen_2 + 1, 2);
                }
                else { error = 1; }
            }
            else if (count_hyphen == 0 && count_slash == 2 && count_dot == 0) {   //'/'�� 2���� ���
                char* ptr_slash_1 = strchr(release, '/');
                char* ptr_slash_2 = strchr(ptr_slash_1 + 1, '/');
                if ((ptr_slash_1 - release) == 4 && (ptr_slash_2 - ptr_slash_1) == 3) {   //��,��,���� ���� 4,2,2�ڸ����� Ȯ��
                    strncpy(year_str, release, 4);
                    strncpy(month_str, ptr_slash_1 + 1, 2);
                    strncpy(day_str, ptr_slash_2 + 1, 2);
                }
                else { error = 1; }
            }
            else if (count_hyphen == 0 && count_slash == 0 && count_dot == 2) {   //'.'�� 2���� ���
                char* ptr_dot_1 = strchr(release, '.');
                char* ptr_dot_2 = strchr(ptr_dot_1 + 1, '.');
                if ((ptr_dot_1 - release) == 4 && (ptr_dot_2 - ptr_dot_1) == 3) {   //��,��,���� ���� 4,2,2�ڸ����� Ȯ��
                    strncpy(year_str, release, 4);
                    strncpy(month_str, ptr_dot_1 + 1, 2);
                    strncpy(day_str, ptr_dot_2 + 1, 2);
                }
                else { error = 1; }
            }
            else { error = 1; }
        }
        else if (strlen(release) == 8) {
            strncpy(year_str, release, 4);
            strncpy(month_str, release + 4, 2);
            strncpy(day_str, release + 6, 2);
        }
        else { error = 1; }   //�������� ��� Ʋ�� ���

        if (error == 1) {
            printf("\n�ٹ� ��� ��¥ �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.\n(����:2024-04-01 �Ǵ� 2024/04/01 �Ǵ� 2024.04.01 �Ǵ� 20240401)\n");
            continue;
        }

        for (int i = 0; i < strlen(year_str); i++)   //���ڿ��� �������� Ȯ��
        {
            if ((int)year_str[i] < 48 || (int)year_str[i] > 57) { error = 1; }
        }
        for (int i = 0; i < strlen(month_str); i++)   //���ڿ��� �������� Ȯ��
        {
            if ((int)month_str[i] < 48 || (int)month_str[i] > 57) { error = 1; }
        }
        for (int i = 0; i < strlen(day_str); i++)   //���ڿ��� �������� Ȯ��
        {
            if ((int)day_str[i] < 48 || (int)day_str[i] > 57) { error = 1; }
        }

        if (error == 1) {
            printf("\n�ٹ� ��� ��¥ �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.\n(����:2024-04-01 �Ǵ� 2024/04/01 �Ǵ� 2024.04.01 �Ǵ� 20240401)\n");
            continue;
        }

        //�ٹ� ��� ��¥ �ǹ� ��Ģ Ȯ��
        int year = atoi(year_str);
        int month = atoi(month_str);
        int day = atoi(day_str);
        if (check_date(year, month, day)) {   //��¥ ���� ���� Ȯ��
            sprintf(release_result, "%04d-%02d-%02d", year, month, day);
        }
        else {
            printf("\n�ٹ� ��� ��¥ �Է��� �߸��Ǿ����ϴ�.��Ȯ�� �Է����ּ���.\n(����:2024-04-01 �Ǵ� 2024/04/01 �Ǵ� 2024.04.01 �Ǵ� 20240401)\n");
            continue;
        }
        break;
    }      //�ٹ� ��� ��¥ ��

    fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", title_result, singers_result, composers_result, lyricists_result, genre_result, playtime_result, album_result, release_result);
    fclose(fp);
}

void get_dlt_song(char* dlt_song) { // ���� ���ڿ� �Է� �� ���� �Լ� -> �ش� ���ڿ� ���� �Լ��� �Ѿ
    char dlt_songname[STRING_SIZE];   // ������ �뷡 ����
    char dlt_singer[STRING_SIZE];   // ������ �뷡 ����
    int line_number_check[MAX_SIZE] = { 0 };   // �뷡 �ߺ��� ������ �뷡 ���� �� ����� �迭
    int line_num = 0;   // �ߺ� �뷡 ���� ���� ����

    printf("�뷡�� �����մϴ�.\n");
    printf("������ �뷡�� ������ �Է��ϼ���: ");
    fgets(dlt_songname, STRING_SIZE, stdin);
    dlt_songname[strcspn(dlt_songname, "\n")] = '\0'; // ���� ���� ����

    printf("������ �뷡�� ������ �Է��ϼ���: ");
    fgets(dlt_singer, STRING_SIZE, stdin);
    dlt_singer[strcspn(dlt_singer, "\n")] = '\0'; // ���� ���� ����

    FILE* file = fopen("song_list.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    char buffer[STRING_SIZE];   // txt���Ͽ��� �о�� ���ڿ� ����
    char dlt_print[STRING_SIZE];   // �뷡 ������ �����ڸ� '\t' ���� ' / ' �� �ٲ� ����� �迭
    int line_number = 1; // �ߺ� �뷡 �� �� ��ȣ�� ������ ����
    int selected_line = 0; // �뷡�� �ߺ����� ������ ������ Ư�� �뷡�� ���� ���, �ߺ��Ǹ� ����ڰ� ������ ��ȣ ������ ����
    while (fgets(buffer, STRING_SIZE, file) != NULL) {
        char* token = strtok(buffer, "\t"); // ���� �����ڷ� ����Ͽ� ���ڿ��� ����
        char* song = strtok(NULL, "\t");

        // �Է��� ����� ������ txt���Ͽ��� ���ϸ�, �ߺ� �뷡 ���� ī��Ʈ
        if (strcmp(dlt_songname, token) == 0 && strcmp(dlt_singer, song) == 0) {
            line_number_check[line_num] = line_number;
            line_num++;
        }
        line_number++;
    }

    fclose(file);

    if (line_num > 1) { // ���� �뷡 ����� ������ �ߺ��� ���
        line_number = 1; // �� ��ȣ �ʱ�ȭ
        file = fopen("song_list.txt", "r"); // ������ �ٽ� ��� ���
        while (fgets(buffer, STRING_SIZE, file) != NULL) {
            strcpy(dlt_print, buffer);
            char* token = strtok(buffer, "\t"); // ���� �����ڷ� ����Ͽ� ���ڿ��� ����
            char* song = strtok(NULL, "\t");

            // ����� ���� ��ġ�� �ش� �뷡 ���� ���
            if (strcmp(dlt_songname, token) == 0 && strcmp(dlt_singer, song) == 0) {
                printf("%d.  ", line_number);
                for (int k = 0; k < strlen(dlt_print); k++) {
                    if (dlt_print[k] == '\t')
                        printf(" / ");
                    else
                        printf("%c", dlt_print[k]);
                }
            }
            line_number++;
        }
        fclose(file);

        printf("������ �뷡�� ��ȣ�� �����ϼ���: ");
        scanf("%d", &selected_line);
        getchar();

        // ������ ��ȣ�� �߸��� ��� ���� �޽��� ��� �� ����
        int valid_selection = 0;
        for (int i = 0; i < line_num; i++) {
            if (selected_line == line_number_check[i]) {
                valid_selection = 1;
                break;
            }
        }
        if (!valid_selection) {
            printf("�߸��� �뷡�� ��ȣ�Դϴ�.\n");
            return;
        }
    }
    else if (line_num == 1) { // ���� �뷡�� �ߺ����� ���� ���
        line_number = 1; // �� ��ȣ �ʱ�ȭ
        file = fopen("song_list.txt", "r"); // ������ �ٽ� ��� ���
        while (fgets(buffer, STRING_SIZE, file) != NULL) {
            strcpy(dlt_print, buffer);
            char* token = strtok(buffer, "\t"); // ���� �����ڷ� ����Ͽ� ���ڿ��� ����
            char* song = strtok(NULL, "\t");

            // ����� ���� ��ġ�� �ش� �뷡 ���� ���
            if (strcmp(dlt_songname, token) == 0 && strcmp(dlt_singer, song) == 0) {
                for (int k = 0; k < strlen(dlt_print); k++) {
                    if (dlt_print[k] == '\t')
                        printf(" / ");
                    else
                        printf("%c", dlt_print[k]);
                }
                selected_line = line_number;
            }
            line_number++;
        }
        fclose(file);
    }
    else {
        printf(".!! ���� ����� �������� �ʽ��ϴ�\n");
        return;
    }

    // ������ ��ȣ�� �ش��ϴ� ���� �ٽ� �б� ���� fopen
    file = fopen("song_list.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    // ������ ��ȣ�� �ش��ϴ� ���� �ٽ� �о dlt_song�� ����
    line_number = 1;
    while (fgets(buffer, STRING_SIZE, file) != NULL) {
        if (line_number == selected_line) {
            strcpy(dlt_song, buffer);
            break;
        }
        line_number++;
    }

    fclose(file);

    // dlt_song ���ڿ��� song_list���� �����ϴ� �Լ�
    song_dlt("song_list.txt", dlt_song);
}

void song_dlt(const char* filename, const char* dlt_song) {   // dlt_song ���ڿ��� song_list���� �����ϴ� �Լ�
    FILE* input_file = fopen(filename, "r");    // ���� txt ����
    if (input_file == NULL) {
        printf("%s������ ã�� ���߽��ϴ�.\n", filename);
        return;
    }

    FILE* output_file = fopen("temp.txt", "w"); // ���� ����� txt ����
    if (output_file == NULL) {
        printf("���� ���� ����\n");
        fclose(input_file);
        return;
    }

    char line[STRING_SIZE];   // ���� ���ڿ��� ��Ƶ� �迭
    int found = 0;  // ���ڿ� �߰� ���� Ȯ�� ����

    while (fgets(line, sizeof(line), input_file)) {
        // ã������ ���ڿ��� ���Ե� ���� �ƴ� ��� �� ���Ͽ� ����
        if (strstr(line, dlt_song) == NULL) {
            fputs(line, output_file);
        }
        else {
            found = 1; // ���ڿ� �߰�
        }
    }

    char dlt_ans[STRING_SIZE];   // ���� ���� �亯 �Է� �迭
    if (found) {
        printf("���� �����Ͻðڽ��ϱ�? (Delete/...)\n");
        fgets(dlt_ans, STRING_SIZE, stdin);
        if (dlt_ans[0] == 'D' && dlt_ans[1] == 'e' && dlt_ans[2] == 'l' && dlt_ans[3] == 'e' && dlt_ans[4] == 't' && dlt_ans[5] == 'e' && dlt_ans[6] == '\n')   // "Delete"�� ��ġ�� ���� ����
            printf("���������� �뷡�� �����߽��ϴ�.\n");
        else
            return;   // ��ġ���� ������ ����
    }
    else {
        printf("..! ���� ����� �������� �ʽ��ϴ�\n");
    }

    fclose(input_file);
    fclose(output_file);

    remove(filename);   // ���� ���� ����
    rename("temp.txt", filename);   // ���� �� ������ �̸� ����
}