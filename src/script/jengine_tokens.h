#ifndef JENGINE_TOKENS_H
#define JENGINE_TOKENS_H

#include <string>
#include <limits>
#include <cmath>

namespace Jengine {
	namespace Script {

		enum class TOKEN_TYPE {
			Function,
			While,
			If,
			Else,
			Integer,
			Real,
			String,
			IntegerLiteral,
			RealLiteral,
			StringLiteral,
			Plus,
			Minus,
			IntegerDivide,
			Divide,
			Multiply,
			Modulo,
			Assign,
			Equal,
			NotEqual,
			And,
			Or,
			More,
			Less,
			Eof,

			Lparenthesis,
			Rparenthesis,
			LcurlyBrace,
			RcurlyBrace,
			LsquareBrace,
			RsquareBrace,
			Comma,
			SemiColon,
			Invalid
		};

		struct Token {

			bool realEquals(double x, double y) {
				return fabs(x - y) < std::numeric_limits<double>::epsilon();
			}

			// need to remove this
			Token() : type(TOKEN_TYPE::Invalid){}

			Token(TOKEN_TYPE type)
				: type(type) {
			}

			Token(TOKEN_TYPE type, const std::string& value)
				: type(type), value(value) {
			}

			Token(TOKEN_TYPE type, float value)
				: type(type), value(value) {
			}

			Token(TOKEN_TYPE type, int value)
				: type(type), value(value) {
			}

			bool isIdentifier() {
				return type == TOKEN_TYPE::Integer
						|| type == TOKEN_TYPE::Real
						|| type == TOKEN_TYPE::String;
			}

			Token operator+(const Token& token) {
				if (this->type == TOKEN_TYPE::IntegerLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i + token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::RealLiteral, this->value.i + token.value.f);
					}

					if (token.type == TOKEN_TYPE::StringLiteral) {
						return Token(TOKEN_TYPE::StringLiteral, std::to_string(this->value.i) + token.value.s);
					}
				}

				if (this->type == TOKEN_TYPE::RealLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::RealLiteral, this->value.f + token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::RealLiteral, this->value.f + token.value.f);
					}

					if (token.type == TOKEN_TYPE::StringLiteral) {
						return Token(TOKEN_TYPE::StringLiteral, std::to_string(this->value.f) + token.value.s);
					}
				}

				if (this->type == TOKEN_TYPE::StringLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::StringLiteral, this->value.s + std::to_string(token.value.i));
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::StringLiteral, this->value.s + std::to_string(token.value.f));
					}

					if (token.type == TOKEN_TYPE::StringLiteral) {
						return Token(TOKEN_TYPE::StringLiteral, this->value.s + token.value.s);
					}
				}
				return Token(TOKEN_TYPE::Invalid);
			}

			Token operator-(const Token& token) {
				if (this->type == TOKEN_TYPE::IntegerLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i - token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::RealLiteral, this->value.i - token.value.f);
					}
				}

				if (this->type == TOKEN_TYPE::RealLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::RealLiteral, this->value.f - token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::RealLiteral, this->value.f - token.value.f);
					}
				}
				return Token(TOKEN_TYPE::Invalid);
			}

			Token operator*(const Token& token) {
				if (this->type == TOKEN_TYPE::IntegerLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i * token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::RealLiteral, this->value.i * token.value.f);
					}
				}

				if (this->type == TOKEN_TYPE::RealLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::RealLiteral, this->value.f * token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::RealLiteral, this->value.f * token.value.f);
					}
				}
				return Token(TOKEN_TYPE::Invalid);
			}

			Token operator/(const Token& token) {
				if (this->type == TOKEN_TYPE::IntegerLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i / token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::RealLiteral, this->value.i / token.value.f);
					}
				}

				if (this->type == TOKEN_TYPE::RealLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::RealLiteral, this->value.f / (float)token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::RealLiteral, this->value.f / token.value.f);
					}
				}

				return Token(TOKEN_TYPE::Invalid);
			}

			Token operator%(const Token& token) {
				if (this->type == TOKEN_TYPE::IntegerLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i % token.value.i);
					}
				}
				
				return Token(TOKEN_TYPE::Invalid);
			}

			Token operator>(const Token& token) {
				if (this->type == TOKEN_TYPE::IntegerLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i > token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i > token.value.f);
					}
				}

				if (this->type == TOKEN_TYPE::RealLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.f > token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.f > token.value.f);
					}
				}
				return Token(TOKEN_TYPE::Invalid);
			}

			Token operator<(const Token& token) {
				if (this->type == TOKEN_TYPE::IntegerLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i < token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i < token.value.f);
					}
				}

				if (this->type == TOKEN_TYPE::RealLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.f < token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.f < token.value.f);
					}
				}
				return Token(TOKEN_TYPE::Invalid);
			}

			Token operator==(const Token& token) {
				if (this->type == TOKEN_TYPE::IntegerLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i == token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, realEquals(this->value.i, token.value.f));
					}

					if (token.type == TOKEN_TYPE::StringLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}
				}

				if (this->type == TOKEN_TYPE::RealLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, realEquals(this->value.f, token.value.i));
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, realEquals(this->value.f, token.value.f));
					}

					if (token.type == TOKEN_TYPE::StringLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}
				}

				if (this->type == TOKEN_TYPE::StringLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}

					if (token.type == TOKEN_TYPE::StringLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.s == token.value.s);
					}
				}
				return Token(TOKEN_TYPE::Invalid);
			}

			Token operator!=(const Token& token) {
				if (this->type == TOKEN_TYPE::IntegerLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i != token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, !realEquals(this->value.i, token.value.f));
					}

					if (token.type == TOKEN_TYPE::StringLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}
				}

				if (this->type == TOKEN_TYPE::RealLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, !realEquals(this->value.f, token.value.i));
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, !realEquals(this->value.f, token.value.f));
					}

					if (token.type == TOKEN_TYPE::StringLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}
				}

				if (this->type == TOKEN_TYPE::StringLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}

					if (token.type == TOKEN_TYPE::StringLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.s != token.value.s);
					}
				}
				return Token(TOKEN_TYPE::Invalid);
			}

			Token operator&&(const Token& token) {
				if (this->type == TOKEN_TYPE::IntegerLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i && token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i && !realEquals(token.value.f, 0));
					}

					if (token.type == TOKEN_TYPE::StringLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}
				}

				if (this->type == TOKEN_TYPE::RealLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, !realEquals(this->value.f, 0) && token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, !realEquals(this->value.f, 0) && !realEquals(token.value.f, 0));
					}

					if (token.type == TOKEN_TYPE::StringLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}
				}

				if (this->type == TOKEN_TYPE::StringLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}

					if (token.type == TOKEN_TYPE::StringLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}
				}
				return Token(TOKEN_TYPE::Invalid);
			}

			Token operator||(const Token& token) {
				if (this->type == TOKEN_TYPE::IntegerLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i || token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i || !realEquals(token.value.f, 0));
					}

					if (token.type == TOKEN_TYPE::StringLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}
				}

				if (this->type == TOKEN_TYPE::RealLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, !realEquals(this->value.f, 0) || token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, !realEquals(this->value.f, 0) || !realEquals(token.value.f, 0));
					}

					if (token.type == TOKEN_TYPE::StringLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}
				}

				if (this->type == TOKEN_TYPE::StringLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}

					if (token.type == TOKEN_TYPE::StringLiteral) {
						return Token(TOKEN_TYPE::Invalid);
					}
				}
				return Token(TOKEN_TYPE::Invalid);
			}

			Token intDivide(const Token& token) {
				if (this->type == TOKEN_TYPE::IntegerLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i / token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.i / (int)token.value.f);
					}
				}

				if (this->type == TOKEN_TYPE::RealLiteral) {
					if (token.type == TOKEN_TYPE::IntegerLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.f / token.value.i);
					}

					if (token.type == TOKEN_TYPE::RealLiteral) {
						return Token(TOKEN_TYPE::IntegerLiteral, this->value.f / (int)token.value.f);
					}
				}
				return Token(TOKEN_TYPE::Invalid);
			}

			Token operator-() {
				if (this->type == TOKEN_TYPE::IntegerLiteral) {
					return Token(TOKEN_TYPE::IntegerLiteral, -this->value.i);
				}

				if (this->type == TOKEN_TYPE::RealLiteral) {
					return Token(TOKEN_TYPE::RealLiteral, -this->value.f);
				}
				
				return Token(TOKEN_TYPE::Invalid);
			}

			std::string toString() {
				std::string t[] = {
					"Function",
					"While",
					"If",
					"Else",
					"Integer",
					"Real",
					"String",
					"IntegerLiteral",
					"RealLiteral",
					"StringLiteral",
					"Plus",
					"Minus",
					"IntegerDivide",
					"Divide",
					"Multiply",
					"Modulo",
					"Assign",
					"Equal",
					"NotEqual",
					"And",
					"Or",
					"More",
					"Less",
					"Eof",

					"Lparenthesis",
					"Rparenthesis",
					"LcurlyBrace",
					"RcurlyBrace",
					"LsquareBrace",
					"RsquareBrace",
					"Comma",
					"SemiColon",
					"Invalid"
				};

				std::string value = this->type == TOKEN_TYPE::IntegerLiteral ?
										std::to_string(this->value.i) :
									this->type == TOKEN_TYPE::RealLiteral ?
										std::to_string(this->value.f) :
									this->type == TOKEN_TYPE::String
									|| this->type == TOKEN_TYPE::StringLiteral
									|| this->type == TOKEN_TYPE::Integer
									|| this->type == TOKEN_TYPE::Real ?
										('"' + this->value.s + '"') :
										"__NO_VALUE__";

				return '<' + ((int)this->type >= 0 && this->type <= TOKEN_TYPE::Invalid ?
						t[(int)this->type] : "UNKNOWN_TYPE") + ">:{" + value + '}';
			}

			operator bool() {
				if (this->type == TOKEN_TYPE::IntegerLiteral) {
					return this->value.i;
				}

				if (this->type == TOKEN_TYPE::RealLiteral) {
					return !realEquals(this->value.f, 0);
				}

				if (this->type == TOKEN_TYPE::StringLiteral) {
					return this->value.s == "";
				}
			}

			TOKEN_TYPE type;
			struct Value {

				Value() = default;
				Value(const std::string& value)
					: s(value) {
				}

				Value(float value)
					: f(value) {
				}

				Value(int value)
					: i(value) {
				}

				std::string s;
				union {
					int i;
					float f;
				};
			}value;
		};
	}
}

#endif // JENGINE_TOKENS_H
