#include "pch.h"
#include "api.h"
#include "JsonException.h"
#include <cctype>

bool JSON::validate(const std::string& string)
{
	std::string strPart1(string);
	bool result = false;
	trim(strPart1);

	switch (strPart1[0])
	{
	case '{':
		strPart1[0] = '*';
		result = JSON::matchingChar(strPart1, '}', 0);
		for (int i = 0; i < strPart1.length(); i++)
		{
			if (strPart1[i] == '{' || strPart1[i] == '[' || strPart1[i] == ']' || strPart1[i] == '}')
			{
				return false;
			}
		}
		break;
	case '[':
		strPart1[0] = '*';
		result = JSON::matchingChar(strPart1, ']', 0);
		for (int i = 0; i < strPart1.length(); i++)
		{
			if (strPart1[i] == '{' || strPart1[i] == '[' || strPart1[i] == ']' || strPart1[i] == '}')
			{
				return false;
			}
		}
		break;
	default:
		throw JsonException("JSON string is malformed");
		break;
	}

	return result;
}

bool JSON::matchingChar(std::string& input, char c, int pos)
{
	int counter = 1;

	for (int i = pos; i < input.length(); i++)
	{
		if (input[i] == '{')
		{
			input[i] = '*';
			if (JSON::matchingChar(input, '}', i) == false)
			{
				break;
			}
		}
		else if (input[i] == '[')
		{
			input[i] = '*';
			if (JSON::matchingChar(input, ']', i) == false)
			{
				break;
			}
		}
		else if (input[i] == c)
		{
			counter--;
			input[i] = '*';
			break;
		}
		else if (input[i] == '"')
		{
			input[i] = '.';
			int stringValueCounter = 0;
			for (int j = i + 1; j < input.length(); j++)
			{
				if (input[j] == '"')
				{
					stringValueCounter++;
					input[j] = '.';
					break;
				}
				else if (input[j] == '\\' && input[j + 1] == '"')
				{
					stringValueCounter += 2;
					input[j] = '.';
					input[j + 1] = '.';
					j++;
				}
				stringValueCounter++;
				input[j] = '.';
			}
			i += stringValueCounter;
		}
	}

	return counter == 0 ? true : false;
}

bool JSON::isNumber(char c)
{
	if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
	{
		return true;
	}
	return false;
}

bool JSON::isReplaced(char c)
{
	if (c == '*' || c == '^')
	{
		return true;
	}

	return false;
}

void JSON::trim(std::string& input)
{
	ostringstream oss;
	char processing = '\0';
	int counter = 0;
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == '{')
		{
			oss << '{';
		}
		else if (input[i] == '[')
		{
			oss << '[';
		}
		else if (input[i] == '}')
		{
			oss << '}';
		}
		else if (input[i] == ']')
		{
			oss << ']';
		}
		else if (input[i] == '"')
		{
			oss << '"';
			counter = 0;
			for (int j = i + 1; j < input.length(); j++)
			{
				if (input[j] == '"' && input[j - 1] != '\\')
				{
					counter++;
					oss << input[j];
					break;
				}
				counter++;
				oss << input[j];
			}
			i += counter;
		}
		else if (input[i] == ':')
		{
			oss << ':';
		}
		else if (input[i] == ',')
		{
			oss << ',';
		}
		else if (input[i] == 'n')
		{
			if (input[i] == 'n' && input[i + 1] == 'u' && input[i + 2] == 'l' && input[i + 3] == 'l')
			{
				oss << "null";
				i += 3;
				continue;
			}
			throw JsonException("JSON exception: nullvalue is malformed");
		}
		else if (input[i] == 't')
		{
			if (input[i] == 't' && input[i + 1] == 'r' && input[i + 2] == 'u' && input[i + 3] == 'e')
			{
				oss << "true";
				i += 3;
				continue;
			}
			throw JsonException("JSON exception: boolvalue is malformed");
		}
		else if (input[i] == 'f')
		{
			if (input[i] == 'f' && input[i + 1] == 'a' && input[i + 2] == 'l' && input[i + 3] == 's' && input[i + 4] == 'e')
			{
				oss << "false";
				i += 4;
				continue;
			}
			throw JsonException("JSON exception: boolvalue is malformed");
		}
		else if (isNumber(input[i]))
		{
			oss << input[i];
			counter = 0;
			for (int k = i + 1; k < input.length(); k++)
			{
				if (isNumber(input[k]) || input[k] == '.')
				{
					oss << input[k];
					counter++;
				}
				else if (input[k] == ',')
				{
					oss << input[k];
					counter++;
				}
				else
				{
					break;
				}
			}
			i += counter;
		}
		else if (input[i] == ':' || input[i] == ',' || isspace(input[i]) != 0)
		{
			continue;
		}
		else
		{
			throw JsonException("JSON exception : JSON string validation failed. JSON string is malformed.");
		}
	}

	input = oss.str();
}

int JSON::parseNullOrBool(std::string& input, char valueType, int pos, DynamicArray<string>& keys, DynamicArray<KeyValuePair>& values, DynamicArray<Value*>& arrayValues)
{
	if (input[pos] == 'n')
	{
		if (input[pos] == 'n' && input[pos + 1] == 'u' && input[pos + 2] == 'l' && input[pos + 3] == 'l')
		{
			if (valueType == 'o')
			{
				values.append(KeyValuePair(keys.getElementAt(keys.getSize() - 1), new NullValue()));
			}
			else if (valueType == 'a')
			{
				arrayValues.append(new NullValue());
			}

			return pos += 3;
		}
		throw JsonException("JSON exception: nullvalue is malformed");
	}
	else if (input[pos] == 't')
	{
		if (input[pos] == 't' && input[pos + 1] == 'r' && input[pos + 2] == 'u' && input[pos + 3] == 'e')
		{
			if (valueType == 'o')
			{
				values.append(KeyValuePair(keys.getElementAt(keys.getSize() - 1), new BoolValue(true)));
			}
			else if (valueType == 'a')
			{
				arrayValues.append(new BoolValue(true));
			}

			return pos += 3;
		}
		throw JsonException("JSON exception: boolvalue is malformed");
	}
	else if (input[pos] == 'f')
	{
		if (input[pos] == 'f' && input[pos + 1] == 'a' && input[pos + 2] == 'l' && input[pos + 3] == 's' && input[pos + 4] == 'e')
		{
			if (valueType == 'o')
			{
				values.append(KeyValuePair(keys.getElementAt(keys.getSize() - 1), new BoolValue(false)));
			}
			else if (valueType == 'a')
			{
				arrayValues.append(new BoolValue(false));
			}

			return pos += 4;
		}
		throw JsonException("JSON exception: boolvalue is malformed");
	}

	throw JsonException("JSON exception: NumberOrBool exception");
}

int JSON::parseNumber(std::string& input, char valueType, int pos, DynamicArray<string>& keys, DynamicArray<KeyValuePair>& values, DynamicArray<Value*>& arrayValues)
{
	int counter = 0;
	string subStr;
	for (int k = pos + 1; k < input.length(); k++)
	{
		if (isNumber(input[k]) || input[k] == '.')
		{
			counter++;
		}
		else if (input[k] == ',' || input[k] == '}' || input[k] == ']')
		{
			subStr = input.substr(pos, counter + 1);
			if (valueType == 'o')
			{
				values.append(KeyValuePair(keys.getElementAt(keys.getSize() - 1), new NumberValue(stod(subStr))));
			}
			else if (valueType == 'a')
			{
				arrayValues.append(new NumberValue(stod(subStr)));
			}

			return pos += counter;
		}
		else
		{
			throw JsonException("JSON exception: wrong number format");
		}
	}

	throw JsonException("JSON exception: wrong number format");
}

int JSON::parseValues(std::string& input, int pos, Value* value)
{
	char valueType = '\0';
	ObjectValue* oV = nullptr;
	ArrayValue* aV = nullptr;
	if (oV = dynamic_cast<ObjectValue*>(value))
	{
		valueType = 'o';
	}
	else if (aV = dynamic_cast<ArrayValue*>(value))
	{
		valueType = 'a';
	}
	else
	{
		throw JsonException("JSON exception : invalid value type. Must be of ObjectValue* or ArrayValue* type.");
	}
	int counter = 0;
	char parsing = 'k';
	DynamicArray<string> keys;
	DynamicArray<KeyValuePair> values;
	DynamicArray<Value*> arrayValues;
	string subStr;
	int length = input.length();
	for (int i = pos; i < length; i++)
	{
		if (input[i] == '{')
		{
			ObjectValue* newO = new ObjectValue;
			input[i] = '*';
			i = parseValues(input, i + 1, newO);
			if (valueType == 'o')
			{
				values.append(KeyValuePair(keys.getElementAt(keys.getSize() - 1), newO));
			}
			else if (valueType == 'a')
			{
				arrayValues.append(newO);
			}
			parsing = 'k';
		}
		else if (input[i] == '[')
		{
			ArrayValue* newA = new ArrayValue;
			input[i] = '^';
			i = parseValues(input, i + 1, newA);
			if (valueType == 'o')
			{
				values.append(KeyValuePair(keys.getElementAt(keys.getSize() - 1), newA));
			}
			else if (valueType == 'a')
			{
				arrayValues.append(newA);
			}
			parsing = 'k';
		}
		else if (input[i] == '}')
		{
			for (int j = 0; j < values.getSize(); j++)
			{
				oV->append(values.getElementAt(j));
			}
			input[i] = '*';
			return i;
		}
		else if (input[i] == ']')
		{
			for (int j = 0; j < arrayValues.getSize(); j++)
			{
				aV->append(arrayValues.getElementAt(j));
			}
			input[i] = '^';
			return i;
		}
		else if (input[i] == '"')
		{
			counter = 0;
			for (int j = i + 1; j < length; j++)
			{
				if (input[j] == '"' && input[j - 1] != '\\')
				{
					counter++;
					break;
				}
				counter++;
			}

			subStr = input.substr(i + 1, counter - 1);

			if (valueType == 'o')
			{
				if (parsing == 'k')
				{
					keys.append(subStr);
					parsing = 'v';
				}
				else
				{
					values.append(KeyValuePair(keys.getElementAt(keys.getSize() - 1), new StringValue(subStr)));
					parsing = 'k';
				}
			}
			else
			{
				arrayValues.append(new StringValue(subStr));
			}
			i += counter;
		}
		else if (input[i] == ':')
		{
			continue;
		}
		else if (input[i] == ',')
		{
			continue;
		}
		else if (input[i] == 'n' || input[i] == 'f' || input[i] == 't')
		{
			i = parseNullOrBool(input, valueType, i, keys, values, arrayValues);
			parsing = 'k';
		}
		else if (isNumber(input[i]))
		{
			i = parseNumber(input, valueType, i, keys, values, arrayValues);
			parsing = 'k';
		}
		else if (isReplaced(input[i]))
		{
			continue;
		}
		else
		{
			throw JsonException("JSON exception : JSON string validation failed. JSON string is malformed.");
		}
	}
}

void JSON::escape(const std::string input, std::ostringstream& output)
{
	for (char c : input) {
		switch (c)
		{
		case '\\':
			output << "\\\\";
			break;
		case '"':
			output << "\\\"";
			break;
		default:
			output << c;
			break;
		}
	}
}

Value* JSON::getValueByKey(string key, Value* value)
{
	Value* searching = nullptr;
	if (ObjectValue* oV = dynamic_cast<ObjectValue*>(value))
	{
		DynamicArray<KeyValuePair>* daKVP = oV->getValues();
		for (int i = 0; i < daKVP->getSize(); i++)
		{
			if (daKVP->getElementAt(i).getKey() == key)
			{
				searching = daKVP->getElementAt(i).getValue();
				break;
			}
			else if (ObjectValue* oV2 = dynamic_cast<ObjectValue*>(daKVP->getElementAt(i).getValue())) {
				searching = getValueByKey(key, oV2);
				if (searching != nullptr)
				{
					break;
				}
			}
			else if (ArrayValue* aV2 = dynamic_cast<ArrayValue*>(daKVP->getElementAt(i).getValue()))
			{
				searching = getValueByKey(key, aV2);
				if (searching != nullptr)
				{
					break;
				}
			}
		}
	}
	else if (ArrayValue* aV = dynamic_cast<ArrayValue*>(value))
	{
		DynamicArray<Value*>* daAV = aV->getValues();
		for (int i = 0; i < daAV->getSize(); i++)
		{
			if (ObjectValue* oV3 = dynamic_cast<ObjectValue*>(daAV->getElementAt(i))) {
				searching = getValueByKey(key, oV3);
				if (searching != nullptr)
				{
					break;
				}
			}
		}
	}

	return searching;
}

Value* JSON::deserialize(const std::string& string)
{
	std::string jsonStringTmp(string);
	trim(jsonStringTmp);
	int strLength = jsonStringTmp.length();

	if (!validate(jsonStringTmp))
	{
		throw JsonException("JSON exception : JSON string validation failed. JSON string is malformed.");
	}

	if (jsonStringTmp[0] == '{')
	{
		ObjectValue* objectV = new ObjectValue;
		std::string subStrO = jsonStringTmp.substr(1, strLength);
		parseValues(subStrO, 0, objectV);
		return objectV;
	}
	else if (jsonStringTmp[0] == '[')
	{
		ArrayValue* arrayV = new ArrayValue;
		std::string subStrA = jsonStringTmp.substr(1, strLength);
		parseValues(subStrA, 0, arrayV);
		return arrayV;
	}
	else
	{
		throw JsonException("JSON exception : JSON string validation failed. JSON string is malformed.");
	}

	throw JsonException("JSON exception : JSON string validation failed. JSON string is malformed.");
}

std::string JSON::serialize(const Value* value)
{
	ostringstream oss;
	oss << value->serialize();	
	return oss.str();
}