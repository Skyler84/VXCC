/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include "ArgParser.hpp"
#include "Common/Assert.hpp"
#include <iostream>

void ArgParser::parse(int argc, const char **argv) {
  VERIFY(argc > 0);
  const char *arg = *argv++;
  const char *called_name = arg, *it = arg;
  while (*it) {
    if (*it == '/')
      called_name = it + 1;
    ++it;
  }
  m_called_name = std::string{called_name};
  m_called_path = std::string{arg, called_name};
  --argc;
  while (argc--) {
    const char *arg = *argv++;
    if (*arg && *arg == '-') {
      arg++;
      if (*arg && *arg == '-') {
        arg++;
        parseLongArg(argc, arg, argv);
      } else {
        parseShortArg(argc, arg, argv);
      }
    } else {
      m_extra.emplace_back(arg);
    }
  }
}

void ArgParser::parseShortArg(int &argc, const char *&arg, const char **&argv) {
  char carg = *arg++;
  if (!carg) {
    return;
  }
  if (carg == 'h') {
    printHelp();
    std::exit(0);
  }
  if (!m_shortargs.contains(carg)) {
    std::cerr << "Unknown option: '-" << carg << "'\n";
    std::exit(-1);
  }
  int argno = m_shortargs.at(carg);
  const Argument &argument = m_args.at(argno);
  if (!argument.allow_multiple && m_parsed_args.contains(argno)) {
    std::cerr << "Argument: '-" << carg << "' may only be used once!\n";
    std::exit(-1);
  }
  switch (argument.opt) {
  case Argument::OptArg::Trailing:
    m_parsed_args[argno].emplace_back(std::string{arg});
    break;
  case Argument::OptArg::Extra:
    if (!argc--) {
      TODO(error);
    }
    m_parsed_args[argno].emplace_back(std::string{*argv});
    argv++;
    break;
  case Argument::OptArg::None:
    m_parsed_args[argno]; // create vector
    break;
  default:
    UNREACHABLE();
  }
  return;
}
void ArgParser::parseLongArg(int &argc, const char *&arg, const char **&argv) {

  if (std::string_view{arg} == "help") {
    printHelp();
    std::exit(0);
  }
  // if(m_shortargs.contains(carg)){
  //   int argno = m_shortargs.at(carg);
  // }else{
  //   std::cerr << "Unknown option: '-"<<carg<<"'\n";
  //   std::exit(-1);
  // }
  UNIMPLEMENTED();
}

int ArgParser::addShortArg(char carg, Argument &&arg) {
  int arg_num = m_args.size();
  arg.shortarg = carg;
  m_args.emplace_back(std::move(arg));
  m_shortargs.insert({carg, arg_num});
  return arg_num;
}

int ArgParser::addLongArg(std::string &&sarg, Argument &&arg) {
  int arg_num = m_args.size();
  arg.longarg = sarg;
  m_args.emplace_back(std::move(arg));
  m_longargs.insert({std::move(sarg), arg_num});
  return arg_num;
}

void ArgParser::printHelp() {
  std::cout << "Usage: " << binaryPath() + binaryName() << '\n';
  for (int i = 0; i < m_args.size(); i++) {
    // indexed for-loop necessary here
    auto &arg = m_args[i];
    if (arg.shortarg) {
      std::cout << "\t-" << arg.shortarg << '\n';
    }
    if (arg.longarg.size()) {
      std::cout << "\t--" << arg.longarg << '\n';
    }
    std::cout << "\t\t" << arg.desc << '\n';
  }
}