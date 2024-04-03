#include <exception>
#include <ostream>

class FileExceptions : std::exception {};

class FileIsWrongFormat : FileExceptions {};

class FileNotOpens : FileExceptions {};

class FileForOutputNotExists : FileExceptions {};

class ParserExceptions : std::exception {};

class ParserGotNotEnoughArgs : ParserExceptions {};

class WrongArguments : std::exception {};

class InvalidMatrix : std::exception {};