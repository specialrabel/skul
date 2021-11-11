#include "stdafx.h"
#include "saveLoadTest.h"


saveLoadTest::saveLoadTest()
{
}


saveLoadTest::~saveLoadTest()
{
}

void saveLoadTest::update()
{
	//if (KEYMANAGER->isOnceKeyDown(VK_F1)) save();
	//if (KEYMANAGER->isOnceKeyDown(VK_F2)) load();
}

void saveLoadTest::save()
{
	//파일 입출력
	//C   - FILE* 기능없고 기능없어서인지 빠름
	//C++ - ifstream, ofstream - 기능 많고 그래서인지 느림
	//WIN32 - CreateFile - 솔직히 보편적이진 않음.
	//유니티 - jSon

	HANDLE file;
	DWORD write;

	char str[128] = "춘춘이는 준포폴도 있지만 팀포폴도 미리생각해라";

	file = CreateFile("반장.txt", GENERIC_WRITE, FALSE,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);
}

void saveLoadTest::load()
{
	HANDLE file;
	DWORD read;

	//문자열 읽어들이는 버퍼수만큼 그때그때 동적할당 하면
	//더 깔끔하고 조옿습니다
	char str[128];

	file = CreateFile("반장.txt", GENERIC_READ, FALSE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);

	//MessageBox(_hWnd, str, "담주 금요일 기획서 알죠?", MB_OK);
}
