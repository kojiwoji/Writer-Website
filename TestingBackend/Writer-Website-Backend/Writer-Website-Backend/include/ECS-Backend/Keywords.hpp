#ifndef BACKEND_KEY_HPP
#define BACKEND_KEY_HPP

//~ Unsigned base types

// 8-bit unsigned integer
typedef unsigned char 		UInt8;

// 16-bit unsigned integer
typedef unsigned short int	UInt16;

// 32-bit unsigned integer
typedef unsigned int		UInt32;

// 64-bit unsigned integer
typedef unsigned long long	UInt64;

//~ Signed base types.

// 8-bit signed integer
typedef	signed char			Int8;

// 16-bit signed integer
typedef signed short int	Int16;

// 32-bit signed integer
typedef signed int	 		Int32;

// 64-bit signed integer
typedef signed long long	Int64;

//~ Float Types

// 4-bit float
typedef float				Float32;

// 8-bit float
typedef double				Float64;

// 16-bit float
typedef long double			Float128;


//~ Character types
// An ANSI character. 8-bit fixed-width representation of 7-bit characters.
typedef char				ANSICHAR;
typedef const char* DarkCharConst;
typedef char* DarkChar;

// A wide character. In-memory only. ?-bit fixed-width representation of the platform's natural wide character set. Could be different sizes on different platforms.
typedef wchar_t				WIDECHAR;

// An 8-bit character type. In-memory only. 8-bit representation. Should really be char8_t but making this the generic option is easier for compilers which don't fully support C++20 yet.
enum UTF8CHAR : unsigned char {};

// A 16-bit character type. In-memory only.  16-bit representation. Should really be char16_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).
typedef UInt16				CHAR16;

// A 32-bit character type. In-memory only. 32-bit representation. Should really be char32_t but making this the generic option is easier for compilers which don't fully support C++11 yet (i.e. MSVC).
typedef UInt32				CHAR32;

// C
#include <cstring>
#include <stdio.h> 
#include <fcntl.h>

// C++
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

// Other Libraries
#include <flecs.h>

//#include <DarkEnTT/tags/Tags.hpp>

typedef struct DTuple
{
	int firstValue;
	int secondValue;
};

enum RaceFamily
{
	Accipitridae,
	Arachnida,
	Bovidae,
	Canidae,
	Celestial,
	Cervidae,
	Chiroptera,
	Corvidae,
	Crocodilia,
	Decapoda,
	Delphinidae,
	Dracanthropus,
	Dwarf,
	Elf,
	Equidae,
	Fae,
	Felidae,
	Fiend,
	Flora,
	Galeomorphii,
	Goblin,
	Human,
	Hyaenidae,
	Hymenoptera,
	Insectia,
	Lepidoptera,
	Leporidae,
	Limus,
	Mortis,
	Octopoda,
	Primate,
	Reptilia,
	Rhinocerotidae,
	Rodentia,
	Scorpiones,
	Scylla,
	Selachisiren,
	Serpentes,
	Sirena,
	Strigiformes,
	Succubae,
	Suidae,
	Ursidae
};

enum Rarity
{
	Normal
};

enum DAMAGETYPES
{
	IMPACT,
	RENDING,
	ENERGY,
	EXPLOSIVE,
	NONE_DT
};

enum OBJECTSIZE
{
	ONEHANDED,
	TWOHANDED,
	NONE_OS
};

enum ARMAMENTTYPE
{
	RANGED,
	MELEE,
	THROWABLE,
	NONE_AT
};

enum Archetype
{
	AREA,
	AREATYPE,
	DURABILITY,
	LOCATION,
	REGION
};


// Remake this to Small, Medium and Big Container if needed later on.
struct IdentityContainer
{
	char* container_name = nullptr;
	Int32 alive_size;
	Int32 dead_size;
	std::array<Int32, 1000> id;
	std::array<Int32, 1000> alive_id;
	std::array<Int32, 1000> dead_id;
};

struct Dark_Bool
{
	bool hit;
	bool value;
};

struct entity_null
{
	Int16 id;
	char* description;
};

bool entityCreated(flecs::world& _World, flecs::entity e) // Remake or delete
{
	bool bCreated = false;
	if (e.has<entity_null>()) { ecs_delete(_World, e); }
	else
	{
		bCreated = true;
	}

	return bCreated;
}

void DarkSetCharValue(char*& target, std::string target_data, bool init = false)
{
	size_t target_data_size = target_data.size() + 1;
	auto target_data_ptr = target_data.c_str();
	char* target_data_data = new char[target_data_size];
	strncpy_s(target_data_data, target_data_size, target_data_ptr, target_data_size);

	if (init)
	{
		target = target_data_data;
	}
	else
	{
		delete target;
		target = target_data_data;
	}
}

bool DarkFindKeyword(std::string str, std::string target)
{

	if (str.size() == target.size())
	{
		bool bTarget = false;
		for (Int16 i = 0; i < target.size(); i++)
		{
			if (str[i] == target[i])
			{
				bTarget = true;
			}
			else
			{
				bTarget = false;
				break;
			}
		}

		return bTarget;
	}
	else
	{
		return false;
	}
}

bool DarkFindKeyword(std::string str, char target)
{
	bool bTarget = false;
	if (str[0] == target)
	{
		bTarget = true;
	}
	else
	{
		bTarget = false;
	}

	return bTarget;
}

std::string DarkGetWord(std::string str, Int16 pos01, Int16 pos02)
{
	std::string result;
	for (Int16 i = pos01; i < pos02; i++)
	{
		result += str[i];
	}

	return result;
}

std::string DarkGetVariableName(std::string str)
{
	std::string result;

	Int32 startIndex = 0, endIndex = 0;
	std::vector<std::string> DarkVector;
	for (Int32 i = 0; i <= str.size(); i++)
	{
		if (str[i] == ' ' || i == str.size())
		{
			endIndex = i;
			std::string word;
			word.append(str, startIndex, endIndex - startIndex);
			DarkVector.push_back(word);
			startIndex = endIndex + 1;
		}
	}

	return DarkVector[1];
}

std::string DarkGetVariableValue(std::string str)
{
	std::string result;

	Int32 startIndex = 0, endIndex = 0;
	std::vector<std::string> DarkVector;
	for (Int32 i = 0; i <= str.size(); i++)
	{
		if (str[i] == ' ' || i == str.size())
		{
			endIndex = i;
			std::string word;
			word.append(str, startIndex, endIndex - startIndex);
			DarkVector.push_back(word);
			startIndex = endIndex + 1;
		}
	}

	return DarkVector[3];
}

std::vector<std::string> DarkGetStringVector(std::string str, char ch = ' ')
{
	Int32 startIndex = 0, endIndex = 0;
	std::vector<std::string> DarkVector;
	for (Int32 i = 0; i <= str.size(); i++)
	{
		if (str[i] == ch || i == str.size())
		{
			endIndex = i;
			std::string word;
			word.append(str, startIndex, endIndex - startIndex);
			DarkVector.push_back(word);
			startIndex = endIndex + 1;
		}
	}

	return DarkVector;
}

std::string DarkGetListName(std::string str)
{
	std::string Result;
	auto DarkVector01 = DarkGetStringVector(str, '=');

	Result = DarkVector01[1];

	return Result;
}

std::vector<std::string> DarkGetListValue(std::string str)
{
	std::vector<std::string> Result;
	auto DarkVector01 = DarkGetStringVector(str, '=');

	for (int i = 3; i < DarkVector01.size(); i++)
	{
		std::string DarkVector01Value;
		if (i != DarkVector01.size() - 1)
		{
			DarkVector01Value = DarkGetWord(DarkVector01[i], 0, DarkVector01[i].size() - 1);
		}
		else
		{
			DarkVector01Value = DarkVector01[i];
		}
		Result.push_back(DarkVector01Value);
	}

	return Result;
}

std::string DarkGetConstName(std::string str)
{
	std::string Result;
	auto DarkVector01 = DarkGetStringVector(str, '=');

	Result = DarkVector01[1];

	return Result;
}

std::string DarkGetConstValue(std::string str)
{
	std::string Result;
	auto DarkVector01 = DarkGetStringVector(str, '=');

	Result = DarkVector01[3];

	return Result;
}

Dark_Bool DarkGetBool(std::string str)
{
	Dark_Bool Result;
	if (str == "true")
	{
		Result.hit = true;
		Result.value = true;
	}
	else if (str == "false")
	{
		Result.hit = true;
		Result.value = false;
	}
	else
	{
		Result.hit = false;
	}
	return Result;
}

Dark_Bool DarkCharIsUppercase(char ch)
{
	Dark_Bool Result;
	if (std::toupper(ch) == ch)
	{
		Result.hit = true;
		Result.value = true;
	}
	else
	{
		Result.hit = true;
		Result.value = false;
	}

	return Result;
}

Dark_Bool DarkCharIsNumber(char ch)
{
	Dark_Bool Result;

	if (isalpha(ch) == 0)
	{
		Result.hit = true;
		Result.value = true;
	}
	else
	{
		Result.hit = true;
		Result.value = false;
	}

	return Result;
}

Dark_Bool DarkStringIsNumber(std::string str)
{
	Dark_Bool Result;
	Result.hit = true;
	Result.value = true;

	for (Int16 i = 0; i < str.size(); i++)
	{
		if (isalpha(str[i]) != 0
			&& Result.value == true
			)
		{
			Result.value = false;
		}
	}

	return Result;
}

Dark_Bool DarkStringIsFloat(std::string str)
{
	Dark_Bool Result;
	Result.hit = true;
	Result.value = false;

	for (Int16 i = 0; i < str.size(); i++)
	{
		if (str[i] == '.')
		{
			Result.value = true;
		}
	}

	return Result;
}

Int32 DarkStringToInt32(std::string str)
{
	Int32 Result;
	Result = std::stoi(str);
	return Result;
}

std::string DarkInt32ToString(Int32 i)
{
	std::string Result;
	Result = std::to_string(i);
	return Result;
}

Int16 DarkStringToInt16(std::string str)
{
	Int16 Result;
	Result = std::stoi(str);
	return Result;
}

Float32 DarkStringToFloat32(std::string str)
{
	Float32 Result;
	Result = std::stof(str);
	return Result;
}

namespace Dark
{
	// @return String as uppercase
	std::string StringUpperRT(std::string str)
	{
		std::string rt = str;
		for (Int32 i = 0; i < rt.size(); i++)
		{
			rt[i] = std::toupper(rt[i]);
		}

		return rt;
	}

	// @brief Changes the input string to uppercase.
	void StringUpper(std::string& str)
	{
		for (Int32 i = 0; i < str.size(); i++)
		{
			str[i] = std::toupper(str[i]);
		}
	}

	// @brief Changes the input string to uppercase at the desired location.
	void StringUpper(std::string& str, Int32 Loc)
	{
		for (Int32 i = 0; i < str.size(); i++)
		{
			if (i == Loc)
			{
				str[i] = std::toupper(str[i]);
			}
		}
	}

	// @return String as lowercase
	std::string StringLowerRT(std::string str)
	{
		std::string rt = str;
		for (Int32 i = 0; i < rt.size(); i++)
		{
			rt[i] = std::tolower(rt[i]);
		}

		return rt;
	}

	// @brief Changes the input string to lowercase.
	void StringLower(std::string& str)
	{
		for (Int32 i = 0; i < str.size(); i++)
		{
			str[i] = std::tolower(str[i]);
		}
	}

	// @brief converts string to Int16
	Int16 StringToInt16(const std::string& _Str, bool& ValidReturnVal, size_t* _Idx = nullptr, int _Base = 10)
	{

		std::vector<bool> bValidParams;
		std::vector<bool>::iterator CATPTR;

		Int16 ReturnVal = 1;

		for (Int32 i = 0; i < _Str.size(); i++)
		{
			if (isalpha((char)_Str[i]) == 0)
			{
				bValidParams.push_back(true);
			}
			else
			{
				bValidParams.push_back(false);
			}
		}

		for (CATPTR = bValidParams.begin(); CATPTR < bValidParams.end(); CATPTR++)
		{
			if (*CATPTR != 1)
			{

				ValidReturnVal = false;
				ReturnVal = 0;
				break;
			}
			else
			{
				ValidReturnVal = true;
			}
		}

		if (ReturnVal == 1)
		{
			ReturnVal = std::stoi(_Str);
		}

		return ReturnVal;
	}

	// @brief converts string to Int32
	Int32 StringToInt32(const std::string& _Str, bool& ValidReturnVal, size_t* _Idx = nullptr, int _Base = 10)
	{

		std::vector<bool> bValidParams;
		std::vector<bool>::iterator CATPTR;

		Int32 ReturnVal = 1;

		for (Int32 i = 0; i < _Str.size(); i++)
		{
			if (isalpha((char)_Str[i]) == 0)
			{
				bValidParams.push_back(true);
			}
			else
			{
				bValidParams.push_back(false);
			}
		}

		for (CATPTR = bValidParams.begin(); CATPTR < bValidParams.end(); CATPTR++)
		{
			if (*CATPTR != 1)
			{

				ValidReturnVal = false;
				ReturnVal = 0;
				break;
			}
			else
			{
				ValidReturnVal = true;
			}
		}

		if (ReturnVal == 1)
		{
			ReturnVal = std::stoi(_Str);
		}

		return ReturnVal;
	}

	// @brief converts string to Int64
	Int64 StringToInt64(const std::string& _Str, bool& ValidReturnVal, size_t* _Idx = nullptr, int _Base = 10)
	{

		std::vector<bool> bValidParams;
		std::vector<bool>::iterator CATPTR;

		Int64 ReturnVal = 1;

		for (Int32 i = 0; i < _Str.size(); i++)
		{
			if (isalpha((char)_Str[i]) == 0)
			{
				bValidParams.push_back(true);
			}
			else
			{
				bValidParams.push_back(false);
			}
		}

		for (CATPTR = bValidParams.begin(); CATPTR < bValidParams.end(); CATPTR++)
		{
			if (*CATPTR != 1)
			{

				ValidReturnVal = false;
				ReturnVal = 0;
				break;
			}
			else
			{
				ValidReturnVal = true;
			}
		}

		if (ReturnVal == 1)
		{
			ReturnVal = std::stoll(_Str);
		}

		return ReturnVal;
	}

	// @brief converts string to Float32
	Float32 StringToFloat32(const std::string& _Str, bool& ValidReturnVal, size_t* _Idx = nullptr)
	{
		std::vector<bool> bValidParams;
		std::vector<bool>::iterator CATPTR;

		Float32 ReturnVal = 1;

		for (Int32 i = 0; i < _Str.size(); i++)
		{
			if (isalpha((char)_Str[i]) == 0)
			{
				bValidParams.push_back(true);
			}
			else
			{
				bValidParams.push_back(false);
			}
		}

		for (CATPTR = bValidParams.begin(); CATPTR < bValidParams.end(); CATPTR++)
		{
			if (*CATPTR != 1)
			{

				ValidReturnVal = false;
				ReturnVal = 0;
				break;
			}
			else
			{
				ValidReturnVal = true;
			}
		}

		if (ReturnVal == 1)
		{
			ReturnVal = std::stof(_Str);
		}

		return ReturnVal;
	}

	// @brief converts string to Int64
	Float64 StringToFloat64(const std::string& _Str, bool& ValidReturnVal, size_t* _Idx = nullptr)
	{
		std::vector<bool> bValidParams;
		std::vector<bool>::iterator CATPTR;

		Float64 ReturnVal = 1;

		for (Int32 i = 0; i < _Str.size(); i++)
		{
			if (isalpha((char)_Str[i]) == 0)
			{
				bValidParams.push_back(true);
			}
			else
			{
				bValidParams.push_back(false);
			}
		}

		for (CATPTR = bValidParams.begin(); CATPTR < bValidParams.end(); CATPTR++)
		{
			if (*CATPTR != 1)
			{

				ValidReturnVal = false;
				ReturnVal = 0;
				break;
			}
			else
			{
				ValidReturnVal = true;
			}
		}

		if (ReturnVal == 1)
		{
			ReturnVal = std::stod(_Str);
		}

		return ReturnVal;
	}

	// @brief converts string to Float128
	Float128 StringToFloat128(const std::string& _Str, bool& ValidReturnVal, size_t* _Idx = nullptr)
	{

		std::vector<bool> bValidParams;
		std::vector<bool>::iterator CATPTR;

		Float128 ReturnVal = 1;

		for (Int32 i = 0; i < _Str.size(); i++)
		{
			if (isalpha((char)_Str[i]) == 0)
			{
				bValidParams.push_back(true);
			}
			else
			{
				bValidParams.push_back(false);
			}
		}

		for (CATPTR = bValidParams.begin(); CATPTR < bValidParams.end(); CATPTR++)
		{
			if (*CATPTR != 1)
			{

				ValidReturnVal = false;
				ReturnVal = 0;
				break;
			}
			else
			{
				ValidReturnVal = true;
			}
		}

		if (ReturnVal == 1)
		{
			ReturnVal = std::stold(_Str);
		}

		return ReturnVal;
	}

	// @brief A simple function to handle string seperation. Standard seperation is blankspace
	// @returns std::vector filled with each seperated string
	std::vector<std::string> SplitString(std::string str, ANSICHAR separator = ' ')
	{
		Int32 startIndex = 0, endIndex = 0;
		std::vector<std::string> tempVector;
		for (Int32 i = 0; i <= str.size(); i++)
		{
			if (str[i] == separator || i == str.size())
			{
				endIndex = i;
				std::string temp;
				temp.append(str, startIndex, endIndex - startIndex);
				tempVector.push_back(temp);
				startIndex = endIndex + 1;
			}
		}

		return tempVector;
	}

	std::vector<Int16> SplitStringToInt(std::string str, ANSICHAR separator = ' ')
	{
		Int32 startIndex = 0, endIndex = 0;
		std::vector<Int16> tempVector;
		for (Int32 i = 0; i <= str.size(); i++)
		{
			if (str[i] == separator || i == str.size())
			{
				bool ConvertToNumber = false;
				endIndex = i;
				std::string temp;
				temp.append(str, startIndex, endIndex - startIndex);

				tempVector.push_back(StringToInt16(temp, ConvertToNumber));
				startIndex = endIndex + 1;
			}
		}

		return tempVector;
	}
}

#endif // !DUNGEON_KEY_HPP