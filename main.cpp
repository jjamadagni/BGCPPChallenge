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
 
 
 void ValidateSchema(const char* schemaFilePath, const char* xmlFilePath); 
 int xml(string *filename,string *stringMember,string *intmember);
 void json();
 
 
 struct name 
	{
        string filename;
        string stringMember;
        string intmember;
    };
  name a[3];

 
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
	   
	   
	   
	  char function;
	  char i;
	  

	  std::cout << "Please select the process you want the app to perform"  << std::endl;
	  std::cout << "1. For XML Genereation" << std::endl;
	  std::cout << "2. For JASON export" <<std::endl;
	  std::cout << "3. To exit the program" << std::endl;
	  
	bool repeat(true);
	  do{   
	        cin >> function;
			switch (function)
			{
				case '1':
				xml(&a[0].filename, &a[0].stringMember, &a[0].intmember);
				cout << "xml is created" << endl;
                
				//Validator	
				XMLPlatformUtils::Initialize();  
				ValidateSchema(argv[1], "data2.xml");   
				XMLPlatformUtils::Terminate();
				repeat = false;
				break;
	
				case '2':
				json();
				cout << "xml is exported to json" << endl;
				repeat = false;
				break;
		
				case '3':
				exit(0);
				repeat = false;
				break;
		
				default:
				cout << "Please enter a valid option, 1, 2 or 3" << endl;
				repeat = true;
				break;
			}
	    }while(repeat);
	return 0;
	
 
}
       
int xml(string *filename,string *stringMember,string *intmember){
    
	a[0].filename = "data2.xml";
    a[0].stringMember = "str1";
    a[0].intmember = "1";
	
	TiXmlDocument doc  = TiXmlDocument();
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
	cout << "hello" << endl;
    if (domParser.loadGrammar(schemaFilePath, Grammar::SchemaGrammarType) == NULL)
    {
        fprintf(stderr, "couldn't load schema OR XML file doesn't conform to the schema\n");
        return;
    }
   
   cout << "hello1" << endl;
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
void json() 
{ 
    string xml_str, json_str;
    ifstream inf;
    ofstream outf;
    ostringstream oss;
    char BOM[4] = {(char)0xEF, (char)0xBB, (char)0xBF, '\0'}; /*BOM String*/
      

    inf.open("data1.xml");
    outf.open("data2.js.txt");
    oss.str("");
    oss << inf.rdbuf();
    xml_str = oss.str();
    inf.close();
    json_str = xml2json(xml_str.c_str());
    outf << BOM << json_str;
    outf.close();	   
}

       
