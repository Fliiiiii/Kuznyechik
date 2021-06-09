
#ifndef __ARGVPARSER_H
#define __ARGVPARSER_H

#include <string>
#include <vector>
#include <map>
#include <list>

namespace CommandLineProcessing
{


class ArgvParser
{
public:
    typedef int OptionAttributes;
    typedef int ParserResults;
    typedef std::map<std::string, unsigned int> String2KeyMap;
    typedef std::map<unsigned int, OptionAttributes> Key2AttributeMap;
    typedef std::map<unsigned int, std::string> Key2StringMap;
    typedef std::vector<std::string> ArgumentContainer;

    ArgvParser();
    ~ArgvParser();

    /** Attributes for options. */
    enum
    {
        NoOptionAttribute = 0,
        OptionRequiresValue = 1,
        OptionRequired = 2
    };
    /** Return values of the parser. */
    enum
    {
        NoParserError = 0,
        ParserUnknownOption = 1,
        ParserMissingValue = 2,
        ParserOptionAfterArgument = 4,
        ParserMalformedMultipleShortOption = 8,
        ParserRequiredOptionMissing = 16,
        ParserHelpRequested = 32
    };

    
    bool defineOption(const std::string& _name,
                      const std::string& _description = std::string(),
                      OptionAttributes _attributes = NoOptionAttribute);
    
    bool defineOptionAlternative(const std::string& _original,
                                 const std::string& _alternative);
    
    bool isDefinedOption(const std::string& _name) const;
    
    bool foundOption(const std::string& _name) const;
    
    bool setHelpOption(const std::string& _longname = "h",
                       const std::string& _shortname = "help",
                       const std::string& _descr = "");
  
    unsigned int arguments() const;
    
    std::string argument(unsigned int _number) const;
    
    const std::vector<std::string>& allArguments() const;
    
    void addErrorCode(int _code, const std::string& _descr = "");
    
    void setIntroductoryDescription(const std::string& _descr);
    
    ParserResults parse(int _argc, char ** _argv);
    
    std::string optionValue(const std::string& _option) const;
    
    void reset();
   
    const std::string& errorOption() const;
    
    std::string parseErrorDescription(ParserResults _error_code) const;
    
    std::string usageDescription(unsigned int _width = 80) const;

private:
    
    int optionKey( const std::string& _name ) const;
    
    std::list<std::string> getAllOptionAlternatives(unsigned int _key) const;

    
    unsigned int max_key;
    
    String2KeyMap option2key;

    Key2AttributeMap option2attribute;

    Key2StringMap option2descr;

    Key2StringMap option2value;

    /** Map error code to its description. */
    std::map<int, std::string> errorcode2descr;

    /** Vector of command line arguments. */
    ArgumentContainer argument_container;

    /** General description to be returned as first part of the generated help page. */
    std::string intro_description;

    /** Holds the key for the help option. */
    unsigned int help_option;

    /** Holds the name of the option that was responsible for a parser error.
    */
    std::string error_option;
}; // class ArgvParser



bool isValidOptionString(const std::string& _string);


bool isValidLongOptionString(const std::string& _string);


bool splitOptionAndValue(const std::string& _string, std::string& _option,
                         std::string& _value);


template <typename Container>
void splitString(Container& _container, const std::string& _in,
                 const char* const _delimiters = " \t\n")
{
    const std::string::size_type len = _in.length();
    std::string::size_type i = 0;

    while ( i < len )
    {
        // eat leading whitespace
        i = _in.find_first_not_of (_delimiters, i);
        if (i == std::string::npos)
            return;   // nothing left but white space

        // find the end of the token
        std::string::size_type j = _in.find_first_of (_delimiters, i);

        // push token
        if (j == std::string::npos)
        {
            _container.push_back (_in.substr(i));
            return;
        }
        else
            _container.push_back (_in.substr(i, j-i));

        // set up for next loop
        i = j + 1;
    }
}

/** Returns true if the character is a digit (what else?). */
bool isDigit(const char& _char);


bool expandRangeStringToUInt(const std::string& _string,
                             std::vector<unsigned int>& _expanded);
/** Returns a copy of _str with whitespace removed from front and back. */
std::string trimmedString(const std::string& _str);


std::string formatString(const std::string& _string,
                         unsigned int _width,
                         unsigned int _indent = 0);

}
 

#endif // __CMDLINEPARSER_H
