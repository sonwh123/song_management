#pragma once
#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void playlistMenu();//�÷��̸���Ʈ ȭ�鿡 ó�� ���� ��

void printPlaylist();//�÷��̸���Ʈ�� ����Ʈ�� ���

void addPlaylist();//�÷��̸���Ʈ �߰�

void deletePlaylist();//�÷��̸���Ʈ ����

void openPlaylist(char* playlistName);//�÷��̸���Ʈ ����

void addSongInPli(char playlistName[]);//�÷��̸���Ʈ�� �뷡 �߰�

void deleteSong(char* playlistName, char* fileName);//�÷��̸���Ʈ�� �뷡 ����

//void delName(char index[], const char* fileName);//�÷��̸���Ʈ ����Ʈ���� �÷��̸���Ʈ �̸��� ����

void fileArrange(FILE* fp, const char* pliName); //�ø� ����� �� �ø� �̸� �տ� ���� index�� ��������

char* removeSpace(char* str);

