#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <stdio.h>
#include<set>
#include<list>
#include<math.h>
#include "tinyxml.h"
#include <map>
#include <sys/time.h>
#include <time.h>
#include "xml2json.hpp"
#include <xercesc/util/XMLString.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/validators/common/Grammar.hpp>

XERCES_CPP_NAMESPACE_USE
using namespace std;
 
 int64_t getCurrentTime()
{
    struct timeval tval;
    gettimeofday(&tval, NULL);
    return tval.tv_sec * 1000000LL + tval.tv_usec;
}

 
 struct name {
              string filename;
              string stringMember;
              string intmember;
       };
  name a[3];

 
 class WStr
{
    private:
        XMLCh*  wStr;
 
    public:
        WStr(const char* str)
        {
            wStr = XMLString::transcode(str);
        }
 
        ~WStr()
        {
            XMLString::release(&wStr);
        }
 
        operator const XMLCh*() const
        {
            return wStr;
        }
};
 
 class ParserErrorHandler : public ErrorHandler
{
    private:
        void reportParseException(const SAXParseException& ex)
        {
            char* msg = XMLString::transcode(ex.getMessage());
            fprintf(stderr, "at line %llu column %llu, %s\n", 
                    ex.getColumnNumber(), ex.getLineNumber(), msg);
            XMLString::release(&msg);
        }
 
    public:
        void warning(const SAXParseException& ex)
        {
            reportParseException(ex);
        }
 
        void error(const SAXParseException& ex)
        {
            reportParseException(ex);
        }
 
        void fatalError(const SAXParseException& ex)
        {
            reportParseException(ex);
        }
 
        void resetErrors()
        {
        }
};
 
 
int main(int argc, const char *argv[]) 
{
	
	   void ValidateSchema(const char* schemaFilePath, const char* xmlFilePath);
       int xml(string *filename,string *stringMember,string *intmember);
	   //Reading the xsd file
	   string line;
     ifstream myfile ("XSD.txt");
     if (myfile.is_open())
     {
      while ( getline (myfile,line) )
     {
      cout << line << '\n';
     }
       myfile.close();
     }

     else cout << "Unable to open file"; 
	   
	   //copying the contents of the file in to an array
	   
	   
	    std::vector<std::string> NFAArray;
	    std::string line_2;
	    std::string str2 ("STATES");
	    std::ifstream myFile("XSD.txt");
			if (!myFile)
			{
			std::cout << "Error opening output file" << std::endl;
			system("pause");
			return -1;
			}
			while (std::getline(myFile, line))
		{
			(NFAArray).push_back(line);
		}

		std::vector<std::string> states;
		int num_lines = (NFAArray).size();// sizeof(int);
		//cout << num_lines << endl;
		
	   int function;
	   int i;
	   //std::cout << "Please select the process you want the app to perform"  << std::endl;
	   //std::cout << "A. For XML Genereation" << std::endl;
	   //std::cout << "B. For JASON export" <<std::endl;
	  // std::cout << "C. To exit the program" << std::endl;
	   
	   //cin >> i ;
	   
      
	  
	  
       a[0].filename = "data4.xml";
       a[0].stringMember = "str1";
       a[0].intmember = "1";
       
	   
        
      
       xml(&a[0].filename, &a[0].stringMember, &a[0].intmember);
       
	  
    
       string xml_str, json_str;
       ifstream inf;
       ofstream outf;
       ostringstream oss;
       char BOM[4] = {(char)0xEF, (char)0xBB, (char)0xBF, '\0'}; /*BOM String*/
       int64_t start_time, end_time;

       inf.open("data3.xml");
       outf.open("data1.js.txt");
       oss.str("");
       oss << inf.rdbuf();
       xml_str = oss.str();
       inf.close();
       start_time = getCurrentTime();
       json_str = xml2json(xml_str.c_str());
       end_time = getCurrentTime();
       cout << "time1: " << end_time - start_time << endl;
       outf << BOM << json_str;
       outf.close();

	   
       
	   
	   
	   
	   //Validator
	   
	XMLPlatformUtils::Initialize();
 
    ValidateSchema(argv[1], argv[2]);
 
    XMLPlatformUtils::Terminate();
	
	return 0;
	
 
}
       
int xml(string *filename,string *stringMember,string *intmember){
    
	
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);

	TiXmlElement* element = new TiXmlElement("bit:a");
	element->SetAttribute("xmlns:bit", "http://example.org/types");
	doc.LinkEndChild(element);

    TiXmlElement* element2 = new TiXmlElement("stringMember");
    element->LinkEndChild(element2);
    TiXmlText* text2 = new  TiXmlText(a->stringMember.c_str());
    element2->LinkEndChild(text2); 


	TiXmlElement* element1 = new TiXmlElement("intMember");
	element->LinkEndChild(element1);
	TiXmlText* text1 = new TiXmlText(intmember->c_str());
	element1->LinkEndChild(text1);

	doc.SaveFile(filename->c_str());
    
	return 0;
}


void ValidateSchema(const char* schemaFilePath, const char* xmlFilePath)
{ 
   
    XercesDOMParser domParser;
    if (domParser.loadGrammar(schemaFilePath, Grammar::SchemaGrammarType) == NULL)
    {
        fprintf(stderr, "couldn't load schema\n");
        return;
    }

   ParserErrorHandler parserErrorHandler;
 
    domParser.setErrorHandler(&parserErrorHandler);
    domParser.setValidationScheme(XercesDOMParser::Val_Auto);
    domParser.setDoNamespaces(true);
    domParser.setDoSchema(true);
    domParser.setValidationConstraintFatal(true);
 
    domParser.parse(xmlFilePath);
    if (domParser.getErrorCount() == 0)
        printf("XML file validated against the schema successfully\n");
    else
        printf("XML file doesn't conform to the schema\n");

	  
}


       