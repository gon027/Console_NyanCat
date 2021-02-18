#ifndef CONSOLE_H
#define CONSOLE_H

namespace nyan{

	class Console{
	public:
		static Console* getIns();

	public:
		void createConsoleHandle();
		
		void swapConsoleHandle();
		
		void deleteConsoleHandle();
		
		void print(const char* str);
		
		void draw();
		
		void clearScreen();
		
	private:
		Console() {};
		Console(const Console&);
		Console(Console&&);
	};
	
}

#endif // CONSOLE_H
