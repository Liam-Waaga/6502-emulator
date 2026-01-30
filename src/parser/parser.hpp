#pragma once


#include <cstddef>
#include <vector>
#include <string>
#include <filesystem>

namespace INI_Parser {

    class INI_Field {
        
        public:
        INI_Field(std::string line);

        std::string get_field();
        std::string get_value();
        
        
        private:
        std::string _field;
        std::string _value; 
    };
    
    
    class INI_Section {
        
        public:
        /* Don't include newline */
        /* expects lines to be the entire ini document */
        /* nothing bad happens if it isn't except logs give the wrong line numbers */
        /* auto increments current_line to be the first line of the next section */
        /* if there is no other section, current_line will equal lines.size() */
        INI_Section(std::vector<std::string> &lines, std::size_t &current_line, bool section_global = false);

        /* returns the value of the field contained inside the field with the name `field` */
        /* returns an empty string if the field is not found (or field's value is an empty string) */
        /* returns the *first* found result */
        std::string operator[](std::string field);

        std::string get_section_name();
        
        private:
        std::vector<INI_Field> _fields;
        std::string _section_name;
    };

    /* the following parse functions return the first INI_Field to be the global options */
    /* ie options declared without section header */
    /* and the section name is "" */
    
    /* accepts the *contents* of the ini as a single string, not a path */
    std::vector<INI_Section> ini_parse(std::string ini_source);

    /* accepts the *contents* of the ini as a vector of strings, each value is a line, without newlines */
    std::vector<INI_Section> ini_parse(std::vector<std::string> ini_source);
    
    /* accepts the path to the ini */
    std::vector<INI_Section> ini_parse(std::filesystem::path ini_path);
}