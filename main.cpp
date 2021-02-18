#include <Windows.h>
#include <vector>
#include <string>
#include "Console.h"
using namespace std;
using VString = std::vector<string>;
using VVString = std::vector<VString>;

VString nyan1{
	#include "Cats/nyan1.txt"
};

VString nyan2{
	#include "Cats/nyan2.txt"
};

VString nyan3{
	#include "Cats/nyan3.txt"
};

VString nyan4{
	#include "Cats/nyan4.txt"
};

VString nyan5{
	#include "Cats/nyan5.txt"
};

VString nyan6{
	#include "Cats/nyan6.txt"
};

VVString cat{
	nyan1, nyan2, nyan3, nyan4, nyan5, nyan6
};

int main(){

	int frameCount{ 0 };
	using nyan::Console;
	Console::getIns()->createConsoleHandle();
	while(1){
		Console::getIns()->clearScreen();
		
		for(auto& s : cat[ frameCount ]){
			Console::getIns()->print(s.data());
		}
		
		Console::getIns()->draw();
		Console::getIns()->swapConsoleHandle();
		frameCount = (++frameCount) % 6;
		Sleep(100);
	}
	Console::getIns()->deleteConsoleHandle();
}
