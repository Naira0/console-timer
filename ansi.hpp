#pragma once

#include <string>
#include <array>

namespace cli
{
	enum class colors
	{
		black = 30,
		red = 31,
		green = 32,
		yellow = 33,
		blue = 34,
		magenta = 35,
		cyan = 36,
		white = 37,
		bright_black = 90,
		bright_red = 91,
		bright_green = 92,
		bright_yellow = 93,
		bright_blue = 94,
		bright_magenta = 95,
		bright_cyan = 96,
		bright_white = 97
	};

	enum class bg_colors
	{
		black = 40,
		red = 41,
		green = 42,
		yellow = 43,
		blue = 44,
		magenta = 45,
		cyan = 46,
		white = 47,
		bright_black = 100,
		bright_red = 101,
		bright_green = 102,
		bright_yellow = 103,
		bright_blue = 104,
		bright_magenta = 105,
		bright_cyan = 106,
		bright_white = 107
	};

	// sets the text color
	inline std::string color(const std::string& txt, enum class colors c, enum class bg_colors bg = bg_colors::black)
	{
		std::string cStr  = std::to_string((int)c);
		std::string bgStr = std::to_string((int)bg);

		return "\x1B[" + cStr + ";" + bgStr + "m" + txt + "\033[0m";
	}

	// sets the text background color
	inline std::string color(const std::string& txt, enum class bg_colors c)
	{
		std::string cStr = std::to_string((int)c);
		return "\x1B[" + cStr + "m" + txt + "\033[0m";
	}

	// sets the text color within a 255bit color range
	inline std::string color(const std::string& txt, int c, enum class bg_colors bg = bg_colors::black)
	{
		std::string cStr = std::to_string(c);
		std::string bgStr = std::to_string((int)bg);

		return "\x1B[38;5;" + cStr + ";" + bgStr + "m" + txt + "\033[0m";
	}

	// sets the text color using rgb values
	inline std::string color(const std::string& txt, const std::array<std::string, 3>& rgb)
	{
		if (rgb.size() < 3)
			return txt;

		return "\033[38;2;" + rgb[0] + ";" + rgb[1] + ";" + rgb[2] + "m" + txt + "\033[m";
	}

	// underlines the given string
	inline std::string underline(const std::string& txt)
	{
		return "\033[4m" + txt + "\033[m";
	}

	// double underlines given the string
	inline std::string double_underline(const std::string& txt)
	{
		return "\033[21m" + txt + "\033[m";
	}

	// makes the string bold
	inline std::string bold(const std::string& txt)
	{
		return "\033[1m" + txt + "\033[m";
	}

	// makes the string faint
	inline std::string faint(const std::string& txt)
	{
		return "\033[2m" + txt + "\033[m";
	}

	// makes the string italic
	inline std::string italic(const std::string& txt)
	{
		return "\033[3m" + txt + "\033[m";
	}

	// makes the string blink 150+ per minute
	inline std::string fast_blink(const std::string& txt)
	{
		return "\033[6m" + txt + "\033[m";
	}

	// makes the string blink slowly Less than 150 per minute
	inline std::string slow_blink(const std::string& txt)
	{
		return "\033[5m" + txt + "\033[m";
	}

	// strikes out the text
	inline std::string strike(const std::string& txt)
	{
		return "\033[9m" + txt + "\033[m";
	}

	// hides the cursor
	inline std::string hide_cursor()
	{
		return "\033[?25l";
	}

	// makes the cursor visible
	inline std::string show_cursor()
	{
		return "\033[?25h";
	}

	// moves the cursor up by n if n is not given then 1
	inline std::string cursorUp(int n = 1)
	{
		return "\x1B[" + std::to_string(n) + "A\033[m";
	}

	// moves the cursor down by n if n is not given then 1
	inline std::string cursorDown(int n = 1)
	{
		return "\x1B[" + std::to_string(n) + "B\033[m";;
	}

	// moves the cursor down to the next line by n if n is not given then 1. starts at the begining of the line
	inline std::string cursorNextline(int n = 1)
	{
		return "\x1B[" + std::to_string(n) + "E\033[m";
	}

	// moves the cursor up to the previous line by n if n is not given then 1. starts at the begining of the line
	inline std::string cursorPreviousline(int n = 1)
	{
		return "\x1B[" + std::to_string(n) + "F\033[m";
	}

	// moves the cursor back by n if n is not given then it will move it by 1
	inline std::string cursorBack(int n = 1)
	{
		return "\x1B[" + std::to_string(n) + "D\033[m";;
	}

	// moves the cursor horizontally by n if n is not given then it will move it by 1
	inline std::string cursorHorizontal(int n = 1)
	{
		return "\x1B[" + std::to_string(n) + "G\033[m";
	}

	// changes the cursor row and column by the given amount defaults to 1
	inline std::string cursorPosition(int row = 1, int column = 1)
	{
		return "\x1B[" + std::to_string(row) + ";" + std::to_string(column) + "H\033[m";
	}

	// moves the cursor forward by n
	inline std::string cursorForward(int n = 1)
	{
		return "\x1B[" + std::to_string(n) + "C\033[m";;
	}

	// Erases part of the line. If n is 0 (or missing), clear from cursor to the end of the line. If n is 1, clear from cursor to beginning of the line. If n is 2, clear entire line. Cursor position does not change.
	inline std::string eraseLine(int n = 2)
	{
		return "\x1B[" + std::to_string(n) + "K\033[m";;
	}

	//Clears part of the screen. If n is 0 (or missing), clear from cursor to end of screen. If n is 1, clear from cursor to beginning of the screen. If n is 2, clear entire screen (and moves cursor to upper left on DOS ANSI.SYS). If n is 3, clear entire screen and delete all lines saved in the scrollback buffer (this feature was added for xterm and is supported by other terminal applications).
	inline std::string eraseScreen(int n = 1)
	{
		return "\x1B[" + std::to_string(n) + "J\033[m";;
	}

	// scrolles up the terminal
	inline std::string scrollUp(int n = 1)
	{
		return "\x1B[" + std::to_string(n) + "S\033[m";;
	}

	// scrolles down the terminal
	inline std::string scrollDown(int n = 1)
	{
		return "\x1B[" + std::to_string(n) + "T\033[m";;
	}

	// sets the window title by the given argument
	inline std::string setWindowTitle(const std::string& title)
	{
		return "\x1B]0;" + title + "\033";;
	}

	// resets the terminal to its original state
	inline std::string reset()
	{
		return "\033c";
	}

	// Saves the cursor position, encoding shift state and formatting attributes. 
	inline std::string save_cursor()
	{
		return "\0337";
	}

	// Restores the cursor position, encoding shift stateand formatting attributes from the save_cursor() function if it was called, otherwise resets these all to their defaults.
	inline std::string restore_cursor()
	{
		return "\0338";
	}
}