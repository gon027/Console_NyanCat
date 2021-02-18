#include "Console.h"
#include <Windows.h>
#include <string.h>
#include <stdio.h>

namespace nyan{

	namespace {
		constexpr int SCREEN_WIDTH = 100;
		constexpr int SCREEN_HEIGHT = 50;
		
		static int width{ 0 };
		static int height{ 0 };
	
		constexpr SHORT Black = 0;
		constexpr SHORT White = 15;
		constexpr int Colors = 16;
		
		static HANDLE consoleHandle1;
		static HANDLE consoleHandle2;
		static bool isSwap;
		static CONSOLE_CURSOR_INFO cursorInfo;
		static CONSOLE_SCREEN_BUFFER_INFO screenInfo;
		static CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
		
		static HANDLE getHandle(){
			return isSwap ? consoleHandle1 : consoleHandle2;
		}
	}
	
	Console* Console::getIns(){
		static Console Instance;
		return &Instance;
	}
	
	void Console::createConsoleHandle(){
		consoleHandle1 = CreateConsoleScreenBuffer( 
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			CONSOLE_TEXTMODE_BUFFER, 
			NULL
		);
			
		consoleHandle2 = CreateConsoleScreenBuffer( 
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			CONSOLE_TEXTMODE_BUFFER, 
			NULL
		);
			
		cursorInfo.dwSize = 1;
		cursorInfo.bVisible = FALSE;
		::SetConsoleCursorInfo(consoleHandle1, &cursorInfo);
		::SetConsoleCursorInfo(consoleHandle2, &cursorInfo);
		
		::GetConsoleScreenBufferInfo(getHandle(), &screenInfo);
		
		// flase�ŏ�����
		isSwap = false;

		// �o�b�t�@�[��������
		for(int y{0}; y < SCREEN_HEIGHT; ++y){
			for(int x{0}; x < SCREEN_WIDTH; ++x){
				buffer[y][x].Attributes = White + (Black << 4);
				buffer[y][x].Char.UnicodeChar = ' ';
			}
		}
	}
	
	void Console::swapConsoleHandle(){
		::SetConsoleActiveScreenBuffer(getHandle());
		isSwap = !isSwap;
	}
	
	void Console::deleteConsoleHandle(){
		::CloseHandle(consoleHandle2);
		::CloseHandle(consoleHandle1);
	}
	
	void Console::print(const char* _str){
		auto length { strlen( _str ) };

		for(int x { 0 }; x < length; ++x){
			if(_str[x] == '\n'){
				height++;
				width = 0;
				continue;
			}
			
			
			buffer[ height ][ width ].Char.UnicodeChar = _str[x];
			++width;
		}
	}
	
	void Console::draw(){
		static COORD coord { 0, 0 };
		static COORD size { SCREEN_WIDTH, SCREEN_HEIGHT };
		static SMALL_RECT rect { coord.X, coord.Y, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
		
		::WriteConsoleOutputA(getHandle(), *buffer, size, coord, &rect);
	}
	
	void Console::clearScreen(){
		DWORD dwNumberOfCharsWritten{};
		COORD coord { 0, 0 };
		::GetConsoleScreenBufferInfo(getHandle(), &screenInfo);
		
		// �o�b�t�@���̎w�肵�����W����w�肵�����̕����Z���������A�O�i�F�Ɣw�i�F��ݒ�
		::FillConsoleOutputAttribute(
			getHandle(),
			White + (Black << 4),
			screenInfo.dwSize.X * screenInfo.dwSize.Y,
			coord,
			&dwNumberOfCharsWritten
		);
		
		// �o�b�t�@���̎w�肵�����W����A�w�肵���������w�肵����������������
		::FillConsoleOutputCharacter(
			getHandle(),
			' ',
			screenInfo.dwSize.X * screenInfo.dwSize.Y,
			coord,
			&dwNumberOfCharsWritten
		);
		
		width = 0;
		height = 0;
	}
	
}

