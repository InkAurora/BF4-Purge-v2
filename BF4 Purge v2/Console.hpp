#pragma once

#include "Includes.hpp"

class ConsoleFn {
private:
  COORD topLeft;
  HANDLE console;
  CONSOLE_SCREEN_BUFFER_INFO screen;
  DWORD written;

  void clearConsole() {
	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
	  console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
	  console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
	  screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
  }

  void printLogo() {
	cout << ":::::::::  ::::::::::  :::          :::::::::  :::    ::: :::::::::   ::::::::  ::::::::::  " << endl;
	cout << ":+:    :+: :+:        :+:           :+:    :+: :+:    :+: :+:    :+: :+:    :+: :+:         " << endl;
	cout << "+:+    +:+ +:+       +:+ +:+        +:+    +:+ +:+    +:+ +:+    +:+ +:+        +:+         " << endl;
	cout << "+#++:++#+  :#::+::# +#+  +:+        +#++:++#+  +#+    +:+ +#++:++#:  :#:        +#++:++#    " << endl;
	cout << "+#+    +#+ +#+     +#+#+#+#+#+      +#+        +#+    +#+ +#+    +#+ +#+   +#+# +#+         " << endl;
	cout << "#+#    #+# #+#           #+#        #+#        #+#    #+# #+#    #+# #+#    #+# #+#         " << endl;
	cout << "#########  ###           ###        ###         ########  ###    ###  ########  ##########  " << endl;
	cout << "                                                                                      v2    " << endl;
	cout << "by INK" << endl;
	cout << "" << endl;
	cout << "--------------------------------------------------------------------------------------------" << endl;
	cout << "" << endl;
  }

public:
  void updateConsole() {
	clearConsole();
	printLogo();
  }

  ConsoleFn() {
	topLeft = { 0, 0 };
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	updateConsole();
  }
};