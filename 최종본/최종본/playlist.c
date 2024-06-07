#include "playlist.h"
#include "searchInPli.h"
#define STRING_SIZE 256
#define MAX 10000
#define FILE_NAME 100

void delName(char index[], const char* fileName);

void playlistMenu()
{
	int loop = 1;
	while (loop)
	{
		int getMenu;
		printf("\n���ϴ� �޴��� �ش��ϴ� ���ڸ� �Է����ּ���.\n\n");
		printf("0. �ڷΰ���\n");
		printf("1. �÷��̸���Ʈ ���\n");
		printf("2. �÷��̸���Ʈ �߰�\n");
		printf("3. �÷��̸���Ʈ ����\n\n");
		printf("�޴� ����: ");
		scanf("%d", &getMenu);

		while (getchar() != '\n');//���� ����

		switch (getMenu)
		{
		case 0:
		{
			//�����޴��� ���ư��ϴ�.
			loop = 0;
			break;
		}
		case 1:
		{
			//�ø� ��� ���
			printPlaylist();
			break;
		}
		case 2:
		{
			//�ø� �߰�
			addPlaylist();
			break;
		}
		case 3:
		{
			//�ø� ����
			deletePlaylist();
			break;
		}
		}
	}
	return;
}

//�÷��̸���Ʈ ����� ���
void printPlaylist()
{
	while (1)
	{
		system("cls");
		int getMenu;
		int listCount = 0;
		printf("\n");

		FILE* fp = fopen("Playlist_list.txt", "r");

		char buffer[MAX] = { 0, };

		fread(buffer, 1, MAX, fp);
		printf("%s", buffer);


		buffer[0] = '\n';

		printf("\n���ϴ� �÷��̸���Ʈ�� �ش��ϴ� ��ȣ�� �Է��ϼ���. (���� \"0\"�Է½� ���� �������� �̵�) : ");



		scanf("%d", &getMenu);//���ϴ� �ø��� �ش��ϴ� ��ȣ �Է¹ޱ�
		while (getchar() != '\n');

		int numLength = getMenu / 10 + 1; //���ϴ� �÷��̸���Ʈ�� ��ȣ�� ���� �Է¹���

		if (getMenu == 0)
		{
			fclose(fp);
			break;
		}

		else
		{
			fseek(fp, 0, SEEK_SET);//���� �����͸� �ٽ� ������ ó������ �̵�
			char playlistName[FILE_NAME] = { 0, };
			while (fgets(playlistName, MAX, fp) != NULL || listCount <= getMenu) //���ϴ� �ø��� �ش��ϴ� ��ȣ�� �߰��� ������ ����
			{
				//fgets(playlistName, MAX, fp);

				char index[MAX] = "";

				int j = 0;

				for (int i = 0; i < numLength; i++)
				{
					char numberToAdd[2] = { playlistName[i], '\0' };
					strcat(index, numberToAdd);
					//index += playlistName[i];
					j++;
				}

				//���ϴ� �ø��� ��Ī�� ��ȣ�ΰ� üũ
				if (atoi(index) == getMenu && playlistName[j] == '.') //index�� "12"�϶��� �ø��� ��Ī�� ��ȣ "123. "�� ���Ͻ� �Ǵ� ���� ����
				{
					fclose(fp);
					openPlaylist(playlistName);
					break;
				}
			}

		}
	}

}

void openPlaylist(char playlistName[]) //playlistName�� ���� : 1. ��ٱ� �÷��̸���Ʈ
{
	while (1)
	{
		system("cls");
		//���� �÷��̸���Ʈ �̸����� ����� ���ڸ� ������
		//ex) <1. ��ٱ� �÷��̸���Ʈ -> ��ٱ� �÷��̸���Ʈ>�� �޾� ��������
		char pliName[FILE_NAME] = { 0, };
		strcpy(pliName, playlistName);

		int i = 0;
		char* playlistName = pliName + 3; //���ڸ� ��������
		char copyPliName[FILE_NAME] = { 0, };
		strcpy(copyPliName, pliName);
		int len = 0; // strlen(pliName);
		len = strlen(pliName);

		if (len > 0 && pliName[len - 1] == '\n') {
			pliName[len - 1] = '\0'; // ���� ���ڸ� ����
		}
		printf("\n%s\n", playlistName);

		strcat(playlistName, ".txt");

		FILE* fp = fopen(playlistName, "r");

		char buffer[MAX] = { 0, };

		fread(buffer, 1, MAX, fp);

		printf("\n%s\n", buffer);

		fclose(fp);

		printf("\n�Ʒ��� �޴� �� ���ϴ� ��ȣ�� �������ּ���. \n\n");
		printf("0. �ڷΰ���\n");
		printf("1. ���� �÷��̸���Ʈ�� �뷡 �߰�\n");
		printf("2. ���� �÷��̸���Ʈ�� �뷡 ����\n");
		printf("\n�޴����� : ");

		int getMenu;

		scanf("%d", &getMenu);
		while (getchar() != '\n');

		if (getMenu == 0)
		{
			break;
		}
		else if (getMenu == 1)
		{
			addSongInPli(playlistName);
		}
		else if (getMenu == 2)
		{
			//FILE* fp = fopen(playlistName, "r");
			deleteSong(copyPliName, playlistName);
		}

	}
	return;
}


//�÷��̸���Ʈ �߰�
void addPlaylist()
{
	char pName[STRING_SIZE];
	FILE* fp = fopen("Playlist_list.txt", "r");
	while (1) {
		int duplicated = 0;
		printf("�߰��ϰ� ���� �÷��̸���Ʈ�� �̸��� �Է����ּ���. (���� �Է½� ���� �������� �̵�):");
		gets(pName);

		char temp[STRING_SIZE];
		while (fgets(temp, sizeof(temp), fp) != NULL) {
			char existingName[STRING_SIZE];
			strcpy(existingName, temp + 3);
			existingName[strcspn(existingName, "\n")] = 0; //���� ���� ����
			if (strcmp(existingName, pName) == 0) {
				printf("�̹� �����ϴ� �÷��̸���Ʈ �̸��Դϴ�.�ٸ� �Է��� �Է����ּ���.\n");
				duplicated = 1;
				break;
			}
		}

		if (!duplicated) { //�ߺ��� ������ �ݺ� ����
			break;
		}
	}

	int j = 0;
	int count = 0;
	// �Է¹��� ���ڿ��� ����� �����θ� �̷�������� Ȯ��
	while (pName[j] != '\0') {
		if (pName[j] == ' ' || pName[j] == '\t') {
			count++;
		}
		j++;
	}
	//���� �Է½� ���� �������� �̵�
	if (j == count) {
		if (j == count) {
			fclose(fp);
			playlistMenu();
		}
	}
	//�߰��� ��ȣ ����
	fp = fopen("Playlist_list.txt", "r");
	int num = 0;  // ������ �����ϴ� �÷��̸���Ʈ ����
	char temp[STRING_SIZE];
	while (fgets(temp, sizeof(temp), fp) != NULL) {
		if (temp[0] >= '0' && temp[0] <= '9') {
			num++;
		}
	}


	fp = fopen("Playlist_list.txt", "a");
	fprintf(fp, "\n%d. %s", num + 1, removeSpace(pName)); // ���Ͽ� �÷��̸���Ʈ �߰� 

	// �÷��̸���Ʈ �ؽ�Ʈ ���� ����
	char filename[STRING_SIZE];
	sprintf(filename, "%s.txt", removeSpace(pName));
	fp = fopen(filename, "a");

	fclose(fp);
}

//�÷��̸���Ʈ ����
void deletePlaylist()
{
	while (1)
	{
		system("cls");
		int getMenu;

		printf("\n�÷��̸���Ʈ ���\n\n");

		FILE* fp = fopen("Playlist_list.txt", "r");

		char buffer[MAX] = { 0, };

		fread(buffer, 1, MAX, fp);
		printf("%s", buffer);

		printf("\n������ �÷��̸���Ʈ�� ��ȣ�� �Է����ּ��� (���� \"0\"�Է½� ���� �������� �̵�) : ");


		fseek(fp, 0, SEEK_SET);//���� �����͸� �ٽ� ������ ó������ �̵�

		if (scanf("%d", &getMenu) == 0)
		{
			while (getchar() != '\n');
			continue;
		}//���ۺ���

		int numLength = getMenu / 10 + 1;

		if (getMenu == 0)
		{
			fclose(fp);
			break;
		}
		else
		{
			char playlistName[MAX] = { 0, };


			while (feof(fp) == 0) //���ϴ� �ø��� �ش��ϴ� ��ȣ�� �߰��� ������ ����
			{
				char index[STRING_SIZE] = "";

				fgets(playlistName, MAX, fp);
				//���ϴ� �ø��� ��Ī�� ��ȣ�ΰ� üũ
				int j = 0;

				for (int i = 0; i < numLength; i++)
				{
					char numToAdd[2] = { playlistName[i], '\n' };
					strcat(index, numToAdd);
					//index += playlistName[i];
					j++;
				}
				if (index == "\n")
					break;
				if (atoi(index) == getMenu && playlistName[j] == '.') //index�� "12"�϶��� �ø��� ��Ī�� ��ȣ "123. "�� ���Ͻ� �Ǵ� ���� ����
				{
					char* pliName = playlistName + 3;

					int len = strlen(pliName);

					if (len > 0 && pliName[len - 1] == '\n')
					{
						pliName[len - 1] = '\0'; // ���� ���ڸ� ����
					}

					fclose(fp);

					strcat(pliName, ".txt");
					//�÷��̸���Ʈ ���(Playlist_list.txt)���� ���� �ø� �̸��� �����ֱ�
					delName(index, "Playlist_list.txt"); //�ε��� ��ȣ�� �ľ��ؼ� ������

					FILE* fp = fopen("Playlist_list.txt", "r"); //�ø��� �ε��� ��ȣ�� �����ϱ� ���� �ٽ� ����
					fileArrange(fp, "Playlist_list.txt"); //�����ϰ� ���ϴݱ�

					remove(pliName);
					break;
					//�ø������ ����(�ø� ��ȣ) ���
				}

			}
			fclose(fp);
		}
	}

}

void delName(char index[], const char* fileName)//���Ͽ��� index�� �ش��ϴ� �뷡 �Ǵ� �ø��� ����
{

	char sourcefileName[FILE_NAME] = { 0, };
	strcpy(sourcefileName, fileName);
	FILE* sourceFile = fopen(sourcefileName, "r");//Playlist_list.txt������ ����


	FILE* tempFile; //���� ������ ������ ������
	char tempName[30] = "tempFile.txt";
	char buffer[MAX];

	tempFile = fopen(tempName, "w");
	int currentLine = 1;
	int lineToRemove = atoi(index);

	while (fgets(buffer, MAX, sourceFile) != NULL)
	{
		if (currentLine != lineToRemove) {
			fputs(buffer, tempFile);
		}
		currentLine++;
	}
	fputs("\n", tempFile);

	fclose(sourceFile);
	fclose(tempFile);

	remove(sourcefileName);
	rename("tempFile.txt", sourcefileName);

	return;
}

void fileArrange(FILE* fp, const char* pliName)//�ؽ�Ʈ ���Ͽ� ������ �ε����� ��������
{
	int indexCount = 0;
	int currentLine = 1;
	char buffer[MAX] = { 0, };
	char sourceName[MAX] = { 0, };
	char tempName[MAX] = "temp.txt";

	strcpy(sourceName, pliName);
	//const char* sourceName = strcat(source, ".txt");

	FILE* tempFile = fopen(tempName, "w");

	while (fgets(buffer, sizeof(buffer), fp) != NULL)//���� �ε����� ������� ����
	{
		if (strlen(buffer) <= 2)
			break;
		char index[MAX] = { 0, };//���� ������ ���� index�ޱ��
		sprintf(index, "%d", currentLine);
		int spaceToReplace = 0; //���ο� ���� ������ �ε����� �Է��� ������ ��


		while (buffer[spaceToReplace + 1] == '.')
		{
			spaceToReplace++;
		}

		for (int i = 0; i < spaceToReplace; i++)
		{
			for (int j = 0; j < strlen(buffer); j++)
				buffer[j] = buffer[j + 1];
			buffer[strlen(buffer) - 1] = NULL;
		} //�ε��� �����ֱ� ( ex)"1. ��ٱ� �÷��̸���Ʈ"->". ��ٱ� �÷��̸���Ʈ")

		strcat(index, buffer);
		strcat(index, "\n");
		//���� ���ĵ� �ε����� ������ �÷��̸���Ʈ �̸����� �ε����� ������ �κ��� �����ش�.
		fputs(index, tempFile);

		memset(buffer, 0, sizeof(buffer));//���۸� �����

		currentLine++;
	}

	fclose(fp);
	fclose(tempFile);

	remove(sourceName);
	rename(tempName, sourceName);

	return;
}

void addSongInPli(char pliName[])//�ؽ�Ʈ������ �̸��� ����
{
	while (1)
	{
		system("cls");
		printf("\n");

		int count = 1;
		char getMenu[STRING_SIZE];

		char buffer[MAX] = { 0, };

		FILE* songList = fopen("song_list.txt", "r");//��� �뷡���� ���
		while (fgets(buffer, sizeof(buffer), songList) != NULL) {
			printf("%d. ", count);
			printf("%s", buffer);
			count++;
		}
		fclose(songList);

		memset(buffer, 0, sizeof(buffer));//���� �����

		printf("\n�÷��̸���Ʈ�� �߰��� �뷡 ��ȣ�� �Է��ϰų� \"�˻�\"�� �Է��ϼ���\n");
		printf("���� \"0\"�� �Է½� ���� �������� �̵��մϴ�. \"�˻�\"�� �Է½� �뷡�� �˻��Ͽ� �߰��� �� �ֽ��ϴ�.\n\n");
		printf("�޴� ���� : ");
		scanf("%s", &getMenu);
		while (getchar() != '\n');

		if (!strcmp(getMenu, "�˻�"))
		{
			searchMenuInPli(pliName);
		}
		else if (!strcmp(getMenu,"0"))
			break;
		else
		{
			char* endptr = NULL;
			int songNum = 0;
			songNum = strtol(getMenu, &endptr, 10);

			if (endptr == getMenu) {
				break;
				printf("��ȯ ����: ���ڷ� �����ϴ� ���ڿ��� �ƴմϴ�.\n");
			}
			else if (*endptr != '\0') {
				break;
				printf("��ȯ ����: ���ڷ� ��ȯ�� �Ŀ� �����ִ� ���ڿ�: %s\n", endptr);
			}
			else {
				int lineNumber = 0;
				if (count - 1 < songNum)//���� �뷡 ������ ū ���ڸ� ������ ������ �������ش�.
					continue;
				else
				{
					FILE* songList = fopen("song_list.txt", "r");
					FILE* playlist = fopen(pliName, "a");

					if (playlist == NULL)
						printf("������ �� �� �����ϴ�!\n");
					while (fgets(buffer, sizeof(buffer), songList) != NULL)
					{
						lineNumber++;
						if (lineNumber == songNum) {
							fputs("1. ", playlist);
							fputs(buffer, playlist);
							fputs("\n", playlist);

							fclose(playlist);
							FILE* fp = fopen(pliName, "r"); //���� �� Ŀ���� ��ġ�� �ʱ�ȭ
							fileArrange(playlist, pliName); //��ȣ�� ����

							break; // ã�� �Ŀ��� �� �̻� �ݺ��� �ʿ䰡 �����Ƿ� �ݺ����� ����
						}
					}

				}
			}
		}

	}

	return;
}


//�÷��̸���Ʈ���� �뷡�� ���� ->���� �÷��̸���Ʈ�� file pointer�� ��������
void deleteSong(char* pliName, char* fileName) //���ڷ� ���� pliName�� ".txt"�� �������� ���� �����̴�.
{
	while (1)
	{
		system("cls");
		char playlistName[FILE_NAME] = { 0, };
		strcpy(playlistName, pliName);
		char* noNumName = playlistName + 3;

		FILE* fp = fopen(fileName, "r");

		char getMenu[STRING_SIZE];

		printf("\n\n%s\n\n", noNumName);

		char buffer[MAX] = { 0, };

		fread(buffer, 1, MAX, fp);


		printf("\n%s\n", buffer);

		printf("\n���� \"0\"�� �Է½� ���� �������� �̵��մϴ�.\n");
		printf("�÷��̸���Ʈ���� ������ �뷡�� �ش��ϴ� ��ȣ�� �Է����ּ��� : ");

		scanf("%s", &getMenu);
		while (getchar() != '\n');

		int numLength = strlen(getMenu);

		if (!strcmp(getMenu, "0"))
		{
			fclose(fp);
			break;
		}
		else
		{
			fclose(fp);

			delName(getMenu, fileName);

			FILE* fp = fopen(fileName, "r");
			fileArrange(fp, fileName);

			printf("\n");
		}
	}
}

char* removeSpace(char* str) {
	char* start = str;
	char* finish = str + strlen(str) - 1;
	//���� ����
	while (*start != '\0') {
		if ((*start == ' ') || (*start == '\t'))
			start++;
		else
			break;
	}
	//���� ����
	while (1)
	{
		if ((*finish == ' ') || (*finish == '\t'))
			finish--;
		else {
			*(finish + 1) = '\0';
			break;
		}
	}

	return start;
}
