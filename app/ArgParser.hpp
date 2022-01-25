/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#include <cstdlib>
#include <map>
#include <set>
#include <string>
#include <vector>

class ArgParser {
public:
  struct Argument {
    char shortarg{0};
    std::string longarg{};
    std::string desc;
    // bool comma_sep;
    // bool required;
    bool allow_multiple{false};
    enum class OptArg {
      None,
      Assign,
      Trailing,
      Extra,
    } opt{OptArg::None};
    enum class ArgType {
      None,
      File,
      Directory,
      Enum,
      Misc,
    } type{ArgType::None};
    std::set<std::string> m_enum_vals{};

    Argument(std::string &&d) : desc{std::move(d)} {}
    Argument(std::string &&d, OptArg opt) : desc{std::move(d)}, opt{opt} {}
  };
  void parse(int argc, const char **argv);
  int addShortArg(char carg, Argument &&arg);
  int addLongArg(std::string &&sarg, Argument &&arg);
  int addArg(char carg, std::string &&sarg, Argument &&arg);
  const std::string &binaryName() const { return m_called_name; }
  const std::string &binaryPath() const { return m_called_path; }
  const bool hasShortArg(char c) const {
    return m_parsed_args.contains(m_shortargs.at(c));
  }
  const bool hasLongArg(const std::string &s) const {
    return m_parsed_args.contains(m_longargs.at(s));
  }
  const std::vector<std::string> &getShortArg(char c) {
    return m_parsed_args[m_shortargs.at(c)];
  }
  const std::vector<std::string> &getLongArg(const std::string &s) {
    return m_parsed_args[m_longargs.at(s)];
  }
  const std::vector<std::string> &getShortArg(char c) const {
    return m_parsed_args.at(m_shortargs.at(c));
  }
  const std::vector<std::string> &getLongArg(const std::string &s) const {
    return m_parsed_args.at(m_longargs.at(s));
  }
  const std::vector<std::string> &extra() const { return m_extra; }

private:
  std::string m_called_name;
  std::string m_called_path;
  std::map<char, int> m_shortargs;
  std::map<std::string, int> m_longargs;
  /**
   * contains:
   *    help-string
   */
  std::vector<Argument> m_args;
  /**
   *  Parsed arguments:
   */
  std::map<int, std::vector<std::string>> m_parsed_args;
  std::vector<std::string> m_extra;

  void printHelp();
  void parseShortArg(int &argc, const char *&arg, const char **&argv);
  void parseLongArg(int &argc, const char *&arg, const char **&argv);
};