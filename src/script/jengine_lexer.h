#ifndef LEXER_H
#define LEXER_H

#include "jengine_tokens.h"
#include <unordered_map>

// debug
#include <iostream>

#define isdigit(x) (x) >= '0' && (x) <= '9'
#define isalnum(x) isdigit(x) || (x) >= 'A' && (x) <= 'Z' || (x) >= 'a' && (x) <= 'z'

namespace Jengine {
	namespace Script {

		class Lexer
		{
		public:
			Lexer(std::string text)
				: text(text), position(0), currentCharacter(this->text[this->position]) {
				this->keywords.insert({"function", TOKEN_TYPE::Function});
				this->keywords.insert({"while", TOKEN_TYPE::While});
				this->keywords.insert({"if", TOKEN_TYPE::If});
				this->keywords.insert({"else", TOKEN_TYPE::Else});
			}

			void nextCharacter() {
				this->position++;
				if (this->position < this->text.length())
					this->currentCharacter = this->text[this->position];
				else
					this->currentCharacter = 0;
			}

			char futureCharacter() {
				if (this->position + 1 < this->text.length())
					return this->text[this->position + 1];
				else
					return 0;
			}

			void skipWhitespace() {
				while (this->currentCharacter == ' ' ||
					  this->currentCharacter == '\n' ||
					  this->currentCharacter == '\t' ||
					  this->currentCharacter == '\r')
					nextCharacter();
			}

			void error(const std::string& msg = "") {
				int t1 = this->text.rfind('\n',this->position);
				int t2 = this->text.find('\n',this->position);
				t1<0?t1=0:0;
				t2<0?t2=this->text.length():0;
				std::cout << "Lexer error: character (" << this->currentCharacter << "):"
						  << (int)this->currentCharacter << ':'
						  << msg << '\n'
						  << this->text.substr(t1,t2-t1)
						  << '\n' << [&]{
					std::string result;
					int t = this->text.rfind('\n',this->position);
					for (int i = t < 0 ? 0 : t; i--;) {
						result += ' ';
					}
					return result + '^';}() << '\n'
					;
				exit(-1);
			}

			Token identifier() {
				std::string result;
				while (isalnum(this->currentCharacter)) {
					result += this->currentCharacter;
					nextCharacter();
				}

				if (this->currentCharacter == '$') {
					nextCharacter();
					return {TOKEN_TYPE::String, result};
				}

				if (this->keywords.find(result) != this->keywords.end())
					return {this->keywords[result], result};

				return {TOKEN_TYPE::Integer, result};
			}

			Token number() {
				std::string result;
				while (isdigit(this->currentCharacter)) {
					result += this->currentCharacter;
					nextCharacter();
				}
				if (this->currentCharacter == '.') {
					result += this->currentCharacter;
					nextCharacter();
					while (isdigit(this->currentCharacter)) {
						result += this->currentCharacter;
						nextCharacter();
					}
					return {TOKEN_TYPE::RealLiteral, std::stof(result)};
				}
				return {TOKEN_TYPE::IntegerLiteral, std::stoi(result)};
			}

			Token stringLiteral() {
				std::string result;
				while (this->currentCharacter != '"') {
					result += this->currentCharacter;
					nextCharacter();
				}
				nextCharacter();
				return {TOKEN_TYPE::StringLiteral, result};
			}

			Token nextToken() {

				while (this->currentCharacter != 0) {

					if (this->currentCharacter == ' ' ||
						this->currentCharacter == '\n' ||
						this->currentCharacter == '\t' ||
						this->currentCharacter == '\r') {
						skipWhitespace();
						continue;
					}

					if (isdigit(this->currentCharacter))
						return number();

					if (isalnum(this->currentCharacter))
						return identifier();

					if (this->currentCharacter == '"') {
						nextCharacter();
						return stringLiteral();
					}

					for (int i = 0; i < TWO_TOKEN_SIZE; ++i) {
						if (twoToken[i].tokenChar[0] == this->currentCharacter
							&& twoToken[i].tokenChar[1] == futureCharacter()) {
							nextCharacter();
							nextCharacter();
							return {twoToken[i].type};
						}
					}

					for (int i = ONE_TOKEN_SIZE; i--;) {
						if (oneToken[i].tokenChar == this->currentCharacter) {
							nextCharacter();
							return {oneToken[i].type};
						}

					}

					error("no valid token found");
				}

				return {TOKEN_TYPE::Eof};
			}

		private:

			static constexpr int ONE_TOKEN_SIZE = 16;
			static constexpr int TWO_TOKEN_SIZE = 5;

			struct {
				char tokenChar;
				TOKEN_TYPE type;
			} oneToken[ONE_TOKEN_SIZE] = {
				{'+', TOKEN_TYPE::Plus},
				{'-', TOKEN_TYPE::Minus},
				{'=', TOKEN_TYPE::Assign},
				{'*', TOKEN_TYPE::Multiply},
				{'/', TOKEN_TYPE::Divide},
				{'%', TOKEN_TYPE::Modulo},
				{'>', TOKEN_TYPE::More},
				{'<', TOKEN_TYPE::Less},
				{'(', TOKEN_TYPE::Lparenthesis},
				{')', TOKEN_TYPE::Rparenthesis},
				{'{', TOKEN_TYPE::LcurlyBrace},
				{'}', TOKEN_TYPE::RcurlyBrace},
				{'[', TOKEN_TYPE::LsquareBrace},
				{']', TOKEN_TYPE::RsquareBrace},
				{',', TOKEN_TYPE::Comma},
				{';', TOKEN_TYPE::SemiColon}
			};

			struct {
				char tokenChar[3];
				TOKEN_TYPE type;
			} twoToken[TWO_TOKEN_SIZE] {
				{"==", TOKEN_TYPE::Equal},
				{"!=", TOKEN_TYPE::NotEqual},
				{"//", TOKEN_TYPE::IntegerDivide},
				{"&&", TOKEN_TYPE::And},
				{"||", TOKEN_TYPE::Or}
			};

			std::string text;
			int position;
			char currentCharacter;

			std::unordered_map<std::string, TOKEN_TYPE> keywords;

		};

	} // namespace Script
} // namespace Jengine

#undef isdigit
#undef isalnum

#endif // LEXER_H
