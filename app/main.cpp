/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "ArgParser.hpp"
#include "Lexer/CLexer.hpp"
#include "Parser/CParser.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>

int main(int argc, const char *argv[]) {
  std::cout << "test\n";
  ArgParser ap;
  ap.addShortArg('O',
                 ArgParser::Argument{"Enable optimizations",
                                     ArgParser::Argument::OptArg::Trailing});
  ap.addShortArg('o', ArgParser::Argument{"Output filename",
                                          ArgParser::Argument::OptArg::Extra});
  ap.addShortArg('D',
                 ArgParser::Argument{"Dump T|A|I - Tokens, AST, IR",
                                     ArgParser::Argument::OptArg::Trailing});
  ap.parse(argc, argv);
  auto &files = ap.extra();
  if (!files.size()) {
    std::cerr << ap.binaryName() << ": Fatal Error: no input files\n";
    std::exit(-1);
  }
  auto outfilenamev = ap.getShortArg('o');
  std::string outfilename;
  if (outfilenamev.size())
    outfilename = outfilenamev[0];
  else
    outfilename = "a.out";

  std::ofstream filestream;
  filestream.open(outfilename);
  auto &outstream = filestream.is_open() && false ? filestream : std::cout;

  for (auto &filename : files) {
    std::ifstream in;
    in.open(filename);
    if (!in.is_open()) {
      std::cerr << "Could not open file: " << filename << "\n";
      std::exit(-2);
    }
    CLexer lexer{in};
    if (!lexer.lex()) {
      std::cerr << "Error lexing file: " << filename << "\n";
      std::exit(-3);
    }
    auto dumpArgs = ap.getShortArg('D');
    if (std::binary_search(dumpArgs.begin(), dumpArgs.end(), "T"))
      for (auto &tok : lexer.ctokens()) {
        auto &_tok = static_cast<const CToken &>(*tok);
        switch (_tok.type()) {
        case CToken::Type::None:
          outstream << "None: ";
          break;
        case CToken::Type::Keyword:
          outstream << "Keyword: ";
          break;
        case CToken::Type::Identifier:
          outstream << "Identifier: ";
          break;
        case CToken::Type::Constant:
          outstream << "Constant: ";
          break;
        case CToken::Type::StringLiteral:
          outstream << "StringLiteral: ";
          break;
        case CToken::Type::Punctuator:
          outstream << "Punctuator: ";
          break;
        }
        outstream << tok->value() << '\n';
      }
    CParser parser{TokenStream{std::move(lexer)}};
    if (!parser.parse()) {
      std::cerr << "Error parsing file: " << filename << "\n";
      std::exit(-4);
    }
    if (std::binary_search(dumpArgs.begin(), dumpArgs.end(), "A"))
      parser.ast().dump(outstream, 0, 3);
  }
  return 0;
}